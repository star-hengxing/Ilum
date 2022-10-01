#include "CopyPass.hpp"

namespace Ilum
{
RenderPassDesc CopyPass::CreateDesc()
{
	RenderPassDesc desc = {};

	desc.name = "CopyPass";
	desc
	    .SetName("CopyPass")
	    .SetBindPoint(BindPoint::None)
	    .Read("Source", RenderResourceDesc::Type::Texture, RHIResourceState::ShaderResource)
	    .Write("Target", RenderResourceDesc::Type::Texture, RHIResourceState::RenderTarget);

	return desc;
}

RenderGraph::RenderTask CopyPass::Create(const RenderPassDesc &desc, RenderGraphBuilder &builder, Renderer *renderer)
{
	return [=](RenderGraph &render_graph, RHICommand *cmd_buffer, rttr::variant &config) {};
}
}        // namespace Ilum