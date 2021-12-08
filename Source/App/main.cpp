#include <Ilum/Device/PhysicalDevice.hpp>
#include <Ilum/Device/Window.hpp>
#include <Ilum/Editor/Editor.hpp>
#include <Ilum/Engine/Context.hpp>
#include <Ilum/Engine/Engine.hpp>
#include <Ilum/Graphics/GraphicsContext.hpp>
#include <Ilum/Renderer/RenderPass/PostProcess/BlendPass.hpp>
#include <Ilum/Renderer/RenderPass/PostProcess/BloomPass.hpp>
#include <Ilum/Renderer/RenderPass/PostProcess/BlurPass.hpp>
#include <Ilum/Renderer/RenderPass/PostProcess/BrightPass.hpp>
#include <Ilum/Renderer/RenderPass/Compute/MeshletCullingPass.hpp>
#include <Ilum/Renderer/RenderPass/Compute/InstanceCullingPass.hpp>
#include <Ilum/Renderer/RenderPass/Deferred/GeometryPass.hpp>
#include <Ilum/Renderer/RenderPass/Deferred/LightPass.hpp>
#include <Ilum/Renderer/RenderPass/Compute/HizPass.hpp>
#include <Ilum/Renderer/RenderPass/CopyPass.hpp>
#include <Ilum/Renderer/RenderPass/PostProcess/TonemappingPass.hpp>
#include <Ilum/Renderer/Renderer.hpp>
#include <Ilum/Scene/Component/Hierarchy.hpp>
#include <Ilum/Scene/Component/MeshRenderer.hpp>
#include <Ilum/Scene/Component/Tag.hpp>
#include <Ilum/Scene/Component/Transform.hpp>
#include <Ilum/Scene/Scene.hpp>
#include <Ilum/Scene/System.hpp>
#include <Ilum/Threading/ThreadPool.hpp>
#include <Ilum/Timing/Timer.hpp>

int main()
{
	Ilum::Engine engine;

	Ilum::Renderer::instance()->buildRenderGraph = [](Ilum::RenderGraphBuilder &builder) {
		builder
		    .addRenderPass("HizPass", std::make_unique<Ilum::pass::HizPass>())
		    .addRenderPass("InstanceCulling", std::make_unique<Ilum::pass::InstanceCullingPass>())
		    .addRenderPass("MeshletCulling", std::make_unique<Ilum::pass::MeshletCullingPass>())
		    .addRenderPass("GeometryPass", std::make_unique<Ilum::pass::GeometryPass>())
		    .addRenderPass("LightPass", std::make_unique<Ilum::pass::LightPass>())
		    .addRenderPass("BrightPass", std::make_unique<Ilum::pass::BrightPass>("lighting"))
		    .addRenderPass("Blur1", std::make_unique<Ilum::pass::BlurPass>("bright", "blur1"))
		    .addRenderPass("Blur2", std::make_unique<Ilum::pass::BlurPass>("blur1", "blur2", true))
		    .addRenderPass("Blend", std::make_unique<Ilum::pass::BlendPass>("blur2", "lighting", "blooming"))
		    .addRenderPass("Tonemapping", std::make_unique<Ilum::pass::TonemappingPass>("blooming"))
		    .addRenderPass("CopyBuffer", std::make_unique<Ilum::pass::CopyPass>())

		    .setView("gbuffer - normal")
		    .setOutput("gbuffer - normal");
	};

	Ilum::Renderer::instance()->rebuild();

	Ilum::Window::instance()->setIcon(std::string(PROJECT_SOURCE_DIR) + "Asset/Texture/Icon/logo.bmp");

	while (!Ilum::Window::instance()->shouldClose())
	{
		engine.onTick();

		Ilum::Window::instance()->setTitle((Ilum::Scene::instance()->name.empty() ? "IlumEngine" : Ilum::Scene::instance()->name) + " FPS: " + std::to_string(Ilum::Timer::instance()->getFPS()));
	}

	return 0;
}