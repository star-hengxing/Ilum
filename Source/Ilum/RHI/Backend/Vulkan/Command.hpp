#pragma once

#include "RHI/RHICommand.hpp"

#include <volk.h>

namespace Ilum::Vulkan
{
class Descriptor;
class RenderTarget;

class Command : public RHICommand
{
  public:
	Command(RHIDevice *device, RHIQueueFamily family);

	Command(RHIDevice *device, VkCommandPool pool, RHIQueueFamily family);

	virtual ~Command() override;

	void SetState(CommandState state);

	VkCommandBuffer GetHandle() const;

	virtual void Begin() override;
	virtual void End() override;

	virtual void BeginRenderPass(RHIRenderTarget *render_target) override;
	virtual void EndRenderPass() override;

	virtual void BindVertexBuffer(RHIBuffer *vertex_buffer) override;
	virtual void BindIndexBuffer(RHIBuffer *index_buffer, bool is_short = false) override;

	virtual void BindDescriptor(RHIDescriptor *descriptor) override;
	virtual void BindPipelineState(RHIPipelineState *pipeline_state) override;

	virtual void SetViewport(float width, float height, float x = 0.f, float y = 0.f) override;
	virtual void SetScissor(uint32_t width, uint32_t height, int32_t offset_x = 0, int32_t offset_y = 0) override;

	virtual void Dispatch(uint32_t group_x, uint32_t group_y, uint32_t group_z) override;
	virtual void Draw(uint32_t vertex_count, uint32_t instance_count, uint32_t first_vertex, uint32_t first_instance) override;
	virtual void DrawIndexed(uint32_t index_count, uint32_t instance_count, uint32_t first_index, uint32_t vertex_offset, uint32_t first_instance) override;

	virtual void CopyBufferToTexture(RHIBuffer *src_buffer, RHITexture *dst_texture, uint32_t mip_level, uint32_t base_layer, uint32_t layer_count) override;

	virtual void ResourceStateTransition(const std::vector<TextureStateTransition> &texture_transitions, const std::vector<BufferStateTransition> &buffer_transitions) override;

  private:
	VkCommandBuffer m_handle = VK_NULL_HANDLE;
	VkCommandPool   m_pool   = VK_NULL_HANDLE;

	Descriptor *p_descriptor = nullptr;
	RenderTarget *p_render_target = nullptr;
};
}        // namespace Ilum::Vulkan