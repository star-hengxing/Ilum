#include "SceneView.hpp"

#include "Device/Input.hpp"
#include "Device/Window.hpp"

#include "Renderer/RenderGraph/RenderGraph.hpp"
#include "Renderer/Renderer.hpp"

#include "Scene/Component/MeshRenderer.hpp"
#include "Scene/Component/Transform.hpp"
#include "Scene/Entity.hpp"
#include "Scene/Scene.hpp"

#include "Editor/Editor.hpp"

#include "ImGui/ImGuiContext.hpp"
#include "ImGui/ImGuiTool.hpp"

#include <SDL.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <ImGuizmo/ImGuizmo.h>
#include <imgui.h>

namespace Ilum::panel
{
SceneView::SceneView()
{
	m_name = "SceneView";

	auto &main_camera                  = Renderer::instance()->Main_Camera;
	main_camera.view                   = glm::lookAt(main_camera.position, main_camera.front + main_camera.position, main_camera.up);
	main_camera.camera.view_projection = main_camera.projection * main_camera.view;
	main_camera.camera.aspect          = static_cast<float>(Window::instance()->getWidth()) / static_cast<float>(Window::instance()->getHeight());
	main_camera.projection             = glm::perspective(glm::radians(main_camera.camera.fov),
                                              main_camera.camera.aspect,
                                              main_camera.camera.near,
                                              main_camera.camera.far);
}

void SceneView::draw(float delta_time)
{
	auto render_graph = Renderer::instance()->getRenderGraph();
	ImGui::Begin("SceneView");
	updateMainCamera(delta_time);

	auto region = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();

	// Setup guizmo
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, (float) ImGui::GetWindowWidth(), (float) ImGui::GetWindowHeight());
	ImGuizmo::DrawGrid(glm::value_ptr(Renderer::instance()->Main_Camera.view), glm::value_ptr(Renderer::instance()->Main_Camera.projection), glm::value_ptr(glm::mat4(1.0)), 100.f);

	onResize(VkExtent2D{static_cast<uint32_t>(region.x), static_cast<uint32_t>(region.y)});

	if (render_graph->hasAttachment(render_graph->view()))
	{
		ImGui::Image(ImGuiContext::textureID(render_graph->getAttachment(render_graph->view()), Renderer::instance()->getSampler(Renderer::SamplerType::Trilinear_Clamp)), region);
	}

	// Drag new model
	if (ImGui::BeginDragDropTarget())
	{
		if (const auto *pay_load = ImGui::AcceptDragDropPayload("Model"))
		{
			ASSERT(pay_load->DataSize == sizeof(std::string));
			auto  entity        = Scene::instance()->createEntity("New Model");
			auto &mesh_renderer = entity.addComponent<cmpt::MeshRenderer>();
			mesh_renderer.model = *static_cast<std::string *>(pay_load->Data);
			mesh_renderer.materials.resize(Renderer::instance()->getResourceCache().loadModel(*static_cast<std::string *>(pay_load->Data)).get().getSubMeshes().size());
		}
		ImGui::EndDragDropTarget();
	}

	// Guizmo operation
	if (Editor::instance()->getSelect())
	{
		auto &transform = Editor::instance()->getSelect().getComponent<cmpt::Transform>();
		if (ImGuizmo::Manipulate(
		        glm::value_ptr(Renderer::instance()->Main_Camera.view),
		        glm::value_ptr(Renderer::instance()->Main_Camera.projection),
		        ImGuizmo::TRANSLATE,
		        ImGuizmo::LOCAL, glm::value_ptr(transform.local_transform), NULL, NULL, NULL, NULL))
		{
			ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform.local_transform),
			                                      glm::value_ptr(transform.translation),
			                                      glm::value_ptr(transform.rotation),
			                                      glm::value_ptr(transform.scale));
			transform.update = true;
		}
	}

	auto view = Renderer::instance()->Main_Camera.view;
	ImGuizmo::ViewManipulate(
	    glm::value_ptr(Renderer::instance()->Main_Camera.view),
	    8.f,
	    ImVec2(ImGui::GetWindowPos().x + region.x - 128, ImGui::GetWindowPos().y),
	    ImVec2(128, 128),
	    0x10101010);
	if (view != Renderer::instance()->Main_Camera.view)
	{
		auto &main_camera = Renderer::instance()->Main_Camera;

		// Decompose view matrix
		main_camera.right    = glm::vec3(main_camera.view[0][0], main_camera.view[1][0], main_camera.view[2][0]);
		main_camera.up       = glm::vec3(main_camera.view[0][1], main_camera.view[1][1], main_camera.view[2][1]);
		main_camera.front    = glm::vec3(main_camera.view[0][2], main_camera.view[1][2], main_camera.view[2][2]);
		main_camera.position = -glm::transpose(glm::mat3(main_camera.view)) * main_camera.view[3];
		main_camera.yaw      = std::atan2f(main_camera.view[0][2], main_camera.view[2][2]);
		main_camera.pitch    = std::asinf(-main_camera.view[1][2]);

		main_camera.camera.view_projection = main_camera.projection * main_camera.view;
	}

	ImGui::End();
}

void SceneView::updateMainCamera(float delta_time)
{
	if (!ImGui::IsWindowFocused())
	{
		return;
	}

	if (Input::instance()->getKey(KeyCode::Click_Right))
	{
		if (!m_cursor_hidden)
		{
			m_cursor_hidden = true;
			m_last_position = Input::instance()->getMousePosition();
		}

		ImGui::SetMouseCursor(ImGuiMouseCursor_None);

		auto [delta_x, delta_y] = Input::instance()->getMouseDelta();

		Input::instance()->setMousePosition(m_last_position.first, m_last_position.second);

		auto &main_camera = Renderer::instance()->Main_Camera;

		bool update = false;

		if (delta_x != 0)
		{
			main_camera.yaw += main_camera.sensitivity * delta_time * static_cast<float>(delta_x);
			main_camera.yaw = glm::clamp(main_camera.yaw, -glm::radians(360.f), glm::radians(360.f));
			update = true;
		}

		if (delta_y != 0)
		{
			main_camera.pitch -= main_camera.sensitivity * delta_time * static_cast<float>(delta_y);
			main_camera.pitch = glm::clamp(main_camera.pitch, -glm::radians(90.f), glm::radians(90.f));
			update = true;
		}

		if (update)
		{
			main_camera.front.x = std::cosf(main_camera.pitch) * std::cosf(main_camera.yaw);
			main_camera.front.y = std::sinf(main_camera.pitch);
			main_camera.front.z = std::cosf(main_camera.pitch) * std::sinf(main_camera.yaw);
			main_camera.front   = glm::normalize(main_camera.front);

			main_camera.right = glm::normalize(glm::cross(main_camera.front, glm::vec3{0.f, 1.f, 0.f}));
			main_camera.up    = glm::normalize(glm::cross(main_camera.right, main_camera.front));
		}

		if (Input::instance()->getKey(KeyCode::W))
		{
			main_camera.position += main_camera.front * main_camera.speed * delta_time;
			update = true;
		}
		if (Input::instance()->getKey(KeyCode::S))
		{
			main_camera.position -= main_camera.front * main_camera.speed * delta_time;
			update = true;
		}

		if (Input::instance()->getKey(KeyCode::D))
		{
			main_camera.position += main_camera.right * main_camera.speed * delta_time;
			update = true;
		}
		if (Input::instance()->getKey(KeyCode::A))
		{
			main_camera.position -= main_camera.right * main_camera.speed * delta_time;
			update = true;
		}
		if (Input::instance()->getKey(KeyCode::Q))
		{
			main_camera.position = main_camera.position + main_camera.up * main_camera.speed * delta_time;
			update               = true;
		}
		if (Input::instance()->getKey(KeyCode::E))
		{
			main_camera.position -= main_camera.up * main_camera.speed * delta_time;
			update = true;
		}

		if (update)
		{
			main_camera.view                   = glm::lookAt(main_camera.position, main_camera.front + main_camera.position, main_camera.up);
			main_camera.camera.view_projection = main_camera.projection * main_camera.view;
		}
	}
	else if (m_cursor_hidden)
	{
		m_cursor_hidden = false;
	}
}

void SceneView::onResize(VkExtent2D extent)
{
	if (extent.width != Renderer::instance()->getRenderTargetExtent().width ||
	    extent.height != Renderer::instance()->getRenderTargetExtent().height)
	{
		Renderer::instance()->resizeRenderTarget(extent);

		// Reset camera aspect
		auto &main_camera = Renderer::instance()->Main_Camera;
		if (main_camera.camera.aspect != static_cast<float>(extent.width) / static_cast<float>(extent.height))
		{
			main_camera.camera.aspect = static_cast<float>(extent.width) / static_cast<float>(extent.height);

			switch (main_camera.camera.type)
			{
				case cmpt::CameraType::Orthographic:
					main_camera.projection = glm::ortho(-glm::radians(main_camera.camera.fov),
					                                    glm::radians(main_camera.camera.fov),
					                                    -glm::radians(main_camera.camera.fov) / main_camera.camera.aspect,
					                                    glm::radians(main_camera.camera.fov) / main_camera.camera.aspect,
					                                    main_camera.camera.near,
					                                    main_camera.camera.far);
					break;
				case cmpt::CameraType::Perspective:
					main_camera.projection = glm::perspective(glm::radians(main_camera.camera.fov),
					                                          main_camera.camera.aspect,
					                                          main_camera.camera.near,
					                                          main_camera.camera.far);
					break;
				default:
					break;
			}

			main_camera.camera.view_projection = main_camera.projection * main_camera.view;
		}
	}
}
}        // namespace Ilum::panel