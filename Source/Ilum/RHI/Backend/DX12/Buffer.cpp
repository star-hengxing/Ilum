#include "Buffer.hpp"
#include "Definitions.hpp"
#include "Device.hpp"

namespace Ilum::DX12
{
BufferState BufferState::Create(RHIResourceState state)
{
	BufferState dx_state = {};
	switch (state)
	{
		case RHIResourceState::Undefined:
			dx_state.state = D3D12_RESOURCE_STATE_COMMON;
			break;
		case RHIResourceState::VertexBuffer:
			dx_state.state = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
			break;
		case RHIResourceState::IndexBuffer:
			dx_state.state = D3D12_RESOURCE_STATE_INDEX_BUFFER;
			break;
		case RHIResourceState::IndirectBuffer:
			dx_state.state = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
			break;
		case RHIResourceState::TransferSource:
			dx_state.state = D3D12_RESOURCE_STATE_COPY_SOURCE;
			break;
		case RHIResourceState::TransferDest:
			dx_state.state = D3D12_RESOURCE_STATE_COPY_DEST;
			break;
		case RHIResourceState::AccelerationStructure:
			dx_state.state = D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE;
			break;
		case RHIResourceState::ShaderResource:
			dx_state.state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
			break;
		case RHIResourceState::UnorderedAccess:
			dx_state.state = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
			break;
		case RHIResourceState::ConstantBuffer:
			dx_state.state = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
			break;
		default:
			dx_state.state = D3D12_RESOURCE_STATE_COMMON;
			break;
	}
	return dx_state;
}

Buffer::Buffer(RHIDevice *device, const BufferDesc &desc) :
    RHIBuffer(device, desc)
{
	D3D12_RESOURCE_DESC d3d12_desc = {};
	d3d12_desc.Dimension           = D3D12_RESOURCE_DIMENSION_UNKNOWN;
	d3d12_desc.Alignment           = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
	d3d12_desc.Width               = desc.size;
	d3d12_desc.Height              = 1;
	d3d12_desc.DepthOrArraySize    = 1;
	d3d12_desc.MipLevels           = 1;
	d3d12_desc.Format              = DXGI_FORMAT_UNKNOWN;
	d3d12_desc.SampleDesc.Count    = 1;
	d3d12_desc.SampleDesc.Quality  = 0;
	d3d12_desc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	d3d12_desc.Flags               = ToDX12ResourceFlags(desc.usage);

	D3D12MA::ALLOCATION_DESC alloc_desc = {};
	alloc_desc.HeapType                 = ToDX12HeapType(desc.memory);

	static_cast<Device *>(p_device)->GetAllocator()->CreateResource(
	    &alloc_desc, &d3d12_desc,
	    D3D12_RESOURCE_STATE_COMMON, NULL,
	    &m_allocation, IID_PPV_ARGS(&m_handle));
}

Buffer ::~Buffer()
{
	if (m_allocation)
	{
		m_allocation->Release();
		m_allocation = nullptr;
	}
}

void *Buffer::Map()
{
	if (!m_mapped)
	{
		m_handle->Map(0, nullptr, &m_mapped);
	}
	return m_mapped;
}

void Buffer::Unmap()
{
	if (m_mapped)
	{
		m_handle->Unmap(0, nullptr);
		m_mapped = nullptr;
	}
}

void Buffer::Flush(size_t offset, size_t size)
{
}

ID3D12Resource *Buffer::GetHandle()
{
	return m_handle.Get();
}
}        // namespace Ilum::DX12