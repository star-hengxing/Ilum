#include "VisibilityPass.hpp"

#include <RHI/FrameBuffer.hpp>

#include <Render/RGBuilder.hpp>
#include <Render/Renderer.hpp>

#include <Scene/Component/MeshRenderer.hpp>
#include <Scene/Scene.hpp>

namespace Ilum
{
VisibilityPass::VisibilityPass() :
    RenderPass("VisibilityPass")
{
}

void VisibilityPass::Create(RGBuilder &builder)
{
	std::unique_ptr<RenderPass> pass = std::make_unique<VisibilityPass>();

	TextureDesc rt_desc = {};
	rt_desc.width       = builder.GetRenderer().GetExtent().width;
	rt_desc.height      = builder.GetRenderer().GetExtent().height;
	rt_desc.depth       = 1;
	rt_desc.mips        = 1;
	rt_desc.layers      = 1;
	rt_desc.format      = VK_FORMAT_R8G8B8A8_UNORM;
	rt_desc.usage       = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	auto texture = builder.CreateTexture(
	    "Result",
	    rt_desc,
	    TextureState{VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT});

	pass->AddResource(texture);

	TextureViewDesc view_desc  = {};
	view_desc.aspect           = VK_IMAGE_ASPECT_COLOR_BIT;
	view_desc.view_type        = VK_IMAGE_VIEW_TYPE_2D;
	view_desc.base_array_layer = 0;
	view_desc.base_mip_level   = 0;
	view_desc.layer_count      = 1;
	view_desc.level_count      = 1;

	ShaderDesc vertex_shader  = {};
	vertex_shader.filename    = "./Source/Shaders/visibility.vert";
	vertex_shader.entry_point = "main";
	vertex_shader.stage       = VK_SHADER_STAGE_VERTEX_BIT;
	vertex_shader.type        = ShaderType::GLSL;

	ShaderDesc frag_shader  = {};
	frag_shader.filename    = "./Source/Shaders/visibility.frag";
	frag_shader.entry_point = "main";
	frag_shader.stage       = VK_SHADER_STAGE_FRAGMENT_BIT;
	frag_shader.type        = ShaderType::GLSL;

	DynamicState dynamic_state = {};
	dynamic_state.dynamic_states.push_back(VK_DYNAMIC_STATE_SCISSOR);
	dynamic_state.dynamic_states.push_back(VK_DYNAMIC_STATE_VIEWPORT);

	ColorBlendState color_blend_state = {};
	color_blend_state.attachment_states.push_back(ColorBlendAttachmentState{});

	VertexInputState vertex_input_state = {};
	vertex_input_state.attribute_descriptions = {
	    VkVertexInputAttributeDescription{0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(ShaderInterop::Vertex, position)},
	    VkVertexInputAttributeDescription{1, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(ShaderInterop::Vertex, texcoord)},
	    VkVertexInputAttributeDescription{2, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(ShaderInterop::Vertex, normal)},
	    VkVertexInputAttributeDescription{3, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(ShaderInterop::Vertex, tangent)}};
	vertex_input_state.binding_descriptions = {
	    VkVertexInputBindingDescription{0, sizeof(ShaderInterop::Vertex), VK_VERTEX_INPUT_RATE_VERTEX}};

	PipelineState pso;
	pso.SetDynamicState(dynamic_state);
	pso.SetColorBlendState(color_blend_state);
	pso.SetVertexInputState(vertex_input_state);

	pso.LoadShader(vertex_shader);
	pso.LoadShader(frag_shader);

	pass->BindCallback([=](CommandBuffer &cmd_buffer, const RGResources &resource, Renderer &renderer) {
		FrameBuffer framebuffer;
		framebuffer.Bind(resource.GetTexture(texture), view_desc, ColorAttachmentInfo{});
		cmd_buffer.BeginRenderPass(framebuffer);
		cmd_buffer.Bind(pso);
		cmd_buffer.SetViewport(static_cast<float>(renderer.GetViewport().width), static_cast<float>(renderer.GetViewport().height));
		cmd_buffer.SetScissor(renderer.GetViewport().width, renderer.GetViewport().height);

		auto *scene     = renderer.GetScene();
		auto  mesh_view = scene->GetRegistry().view<cmpt::MeshRenderer>();
		if (scene)
		{
			mesh_view.each([&](cmpt::MeshRenderer &mesh_renderer) {
				if (mesh_renderer.mesh)
				{
					for (auto &submesh : mesh_renderer.mesh->GetSubmeshes())
					{
						cmd_buffer.BindVertexBuffer(&submesh->GetVertexBuffer());
						cmd_buffer.BindIndexBuffer(&submesh->GetIndexBuffer());
						cmd_buffer.DrawIndexed(submesh->GetIndexBuffer().GetSize() / sizeof(uint32_t));
					}
				}
			});
		}
		cmd_buffer.EndRenderPass();
	});

	pass->BindImGui([=](ImGuiContext &, const RGResources &) {

	});

	builder.AddPass(std::move(pass));
}

}        // namespace Ilum