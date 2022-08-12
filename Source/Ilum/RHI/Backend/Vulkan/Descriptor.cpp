#include "Descriptor.hpp"
#include "Buffer.hpp"
#include "Definitions.hpp"
#include "Device.hpp"
#include "Sampler.hpp"
#include "Texture.hpp"

namespace Ilum::Vulkan
{
inline static VkDescriptorPool DescriptorPool = VK_NULL_HANDLE;

inline static size_t DescriptorCount = 0;

inline static std::unordered_map<ShaderMeta::Descriptor::Type, VkDescriptorType> DescriptorTypeMap = {
    {ShaderMeta::Descriptor::Type::Sampler, VK_DESCRIPTOR_TYPE_SAMPLER},
    {ShaderMeta::Descriptor::Type::TextureSRV, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE},
    {ShaderMeta::Descriptor::Type::TextureUAV, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE},
    {ShaderMeta::Descriptor::Type::ConstantBuffer, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER},
    {ShaderMeta::Descriptor::Type::StructuredBuffer, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER},
    {ShaderMeta::Descriptor::Type::AccelerationStructure, VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR},
};

Descriptor::Descriptor(RHIDevice *device, const ShaderMeta &meta) :
    RHIDescriptor(device, meta)
{
	if (DescriptorCount++ == 0)
	{
		VkPhysicalDeviceProperties properties = {};
		vkGetPhysicalDeviceProperties(static_cast<Device *>(p_device)->GetPhysicalDevice(), &properties);

		VkDescriptorPoolSize pool_sizes[] =
		    {
		        {VK_DESCRIPTOR_TYPE_SAMPLER, properties.limits.maxDescriptorSetSamplers},
		        {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, properties.limits.maxDescriptorSetSampledImages},
		        {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, properties.limits.maxDescriptorSetStorageImages},
		        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, properties.limits.maxDescriptorSetUniformBuffers},
		        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, properties.limits.maxDescriptorSetStorageBuffers},
		        {VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR, 1024},
		    };

		VkDescriptorPoolCreateInfo descriptor_pool_create_info = {};
		descriptor_pool_create_info.sType                      = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptor_pool_create_info.pPoolSizes                 = pool_sizes;
		descriptor_pool_create_info.poolSizeCount              = 6;
		descriptor_pool_create_info.maxSets                    = 4096;
		descriptor_pool_create_info.flags                      = 0;
	}

	std::unordered_map<uint32_t, ShaderMeta> set_meta;
	for (auto &descriptor : m_meta.descriptors)
	{
		set_meta[descriptor.set].descriptors.emplace_back(descriptor);
		HashCombine(
		    set_meta[descriptor.set].hash,
		    descriptor.array_size,
		    descriptor.binding,
		    descriptor.name,
		    descriptor.set,
		    descriptor.stage,
		    descriptor.type);

		m_binding_hash[descriptor.name]      = 0;
		m_descriptor_lookup[descriptor.name] = std::make_pair(descriptor.set, descriptor.binding);

		switch (descriptor.type)
		{
			case ShaderMeta::Descriptor::Type::TextureSRV:
				m_texture_resolves.emplace(descriptor.name, TextureResolve{descriptor.set, descriptor.binding, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL});
				break;
			case ShaderMeta::Descriptor::Type::TextureUAV:
				m_texture_resolves.emplace(descriptor.name, TextureResolve{descriptor.set, descriptor.binding, VK_IMAGE_LAYOUT_GENERAL});
				break;
			case ShaderMeta::Descriptor::Type::Sampler:
				m_texture_resolves.emplace(descriptor.name, TextureResolve{descriptor.set, descriptor.binding});
				break;
			case ShaderMeta::Descriptor::Type::ConstantBuffer:
			case ShaderMeta::Descriptor::Type::StructuredBuffer:
				m_buffer_resolve.emplace(descriptor.name, BufferResolve{descriptor.set, descriptor.binding});
				break;
			case ShaderMeta::Descriptor::Type::AccelerationStructure:
				m_acceleration_structures.emplace(descriptor.name, AccelerationStructureResolve{descriptor.set, descriptor.binding});
				break;
			default:
				break;
		}
	}

	for (auto &[set, meta] : set_meta)
	{
		m_descriptor_set_layouts.emplace(set, CreateDescriptorSetLayout(meta));

		VkDescriptorSetAllocateInfo allocate_info = {};
		allocate_info.sType                       = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocate_info.descriptorPool              = DescriptorPool;
		allocate_info.descriptorSetCount          = 1;
		allocate_info.pSetLayouts                 = &m_descriptor_set_layouts.at(set);

		VkDescriptorSet descriptor_set = VK_NULL_HANDLE;
		vkAllocateDescriptorSets(static_cast<Device *>(p_device)->GetDevice(), &allocate_info, &descriptor_set);

		m_descriptor_sets.emplace(set, descriptor_set);

		m_binding_dirty.emplace(set, false);
	}
}

Descriptor ::~Descriptor()
{
	for (auto &[set, descriptor_set] : m_descriptor_sets)
	{
		vkFreeDescriptorSets(static_cast<Device *>(p_device)->GetDevice(), DescriptorPool, 1, &descriptor_set);
	}

	for (auto &[set, layout] : m_descriptor_set_layouts)
	{
		vkDestroyDescriptorSetLayout(static_cast<Device *>(p_device)->GetDevice(), layout, nullptr);
	}

	m_descriptor_set_layouts.clear();
	m_descriptor_sets.clear();

	if (--DescriptorCount == 0)
	{
		if (DescriptorPool)
		{
			vkDestroyDescriptorPool(static_cast<Device *>(p_device)->GetDevice(), DescriptorPool, nullptr);
			DescriptorPool = VK_NULL_HANDLE;
		}
	}
}
RHIDescriptor &Descriptor::BindTexture(const std::string &name, RHITexture *texture, RHITextureDimension dimension)
{
	return BindTexture(name, texture, dimension, 0, 0, texture->GetDesc().layers, texture->GetDesc().mips);
}

RHIDescriptor &Descriptor::BindTexture(const std::string &name, RHITexture *texture, RHITextureDimension dimension, uint32_t base_mip, uint32_t mip_count, uint32_t base_layer, uint32_t layer_count)
{
	size_t hash = 0;
	HashCombine(hash, texture, dimension, base_mip, mip_count, base_layer, layer_count);

	if (m_binding_hash[name] != hash)
	{
		TextureRange range = {};
		range.dimension    = dimension;
		range.base_layer   = base_layer;
		range.base_mip     = base_mip;
		range.layer_count  = layer_count;
		range.mip_count    = mip_count;

		VkImageView view = static_cast<Texture *>(texture)->GetView(range);

		m_texture_resolves[name].views = {view};
		m_binding_hash[name]           = hash;

		m_binding_dirty[m_descriptor_lookup[name].first] = true;
	}

	return *this;
}

RHIDescriptor &Descriptor::BindTexture(const std::string &name, const std::vector<RHITexture *> &textures, RHITextureDimension dimension)
{
	size_t hash = 0;
	HashCombine(hash, textures, dimension);

	if (m_binding_hash[name] != hash)
	{
		m_texture_resolves[name].views.clear();
		m_texture_resolves[name].views.reserve(textures.size());

		for (auto *texture : textures)
		{
			TextureRange range = {};
			range.dimension    = dimension;
			range.base_layer   = 0;
			range.base_mip     = 0;
			range.layer_count  = texture->GetDesc().layers;
			range.mip_count    = texture->GetDesc().mips;
			VkImageView view   = static_cast<Texture *>(texture)->GetView(range);

			m_texture_resolves[name].views.push_back(view);
		}

		m_binding_hash[name] = hash;

		m_binding_dirty[m_descriptor_lookup[name].first] = true;
	}

	return *this;
}

RHIDescriptor &Descriptor::BindSampler(const std::string &name, RHISampler *sampler)
{
	size_t hash = 0;
	HashCombine(hash, sampler);

	if (m_binding_hash[name] != hash)
	{
		m_texture_resolves[name].samplers = {static_cast<Sampler *>(sampler)->GetHandle()};

		m_binding_hash[name] = hash;

		m_binding_dirty[m_descriptor_lookup[name].first] = true;
	}

	return *this;
}

RHIDescriptor &Descriptor::BindSampler(const std::string &name, const std::vector<RHISampler *> &samplers)
{
	size_t hash = 0;
	HashCombine(hash, samplers);

	if (m_binding_hash[name] != hash)
	{
		m_texture_resolves[name].samplers.clear();
		m_texture_resolves[name].samplers.reserve(samplers.size());

		for (auto *sampler : samplers)
		{
			m_texture_resolves[name].samplers.push_back(static_cast<Sampler *>(sampler)->GetHandle());
		}

		m_binding_hash[name] = hash;

		m_binding_dirty[m_descriptor_lookup[name].first] = true;
	}

	return *this;
}

RHIDescriptor &Descriptor::BindBuffer(const std::string &name, RHIBuffer *buffer)
{
	return BindBuffer(name, buffer, 0, buffer->GetDesc().size);
}

RHIDescriptor &Descriptor::BindBuffer(const std::string &name, RHIBuffer *buffer, size_t offset, size_t range)
{
	size_t hash = 0;
	HashCombine(hash, buffer, offset, range);

	if (m_binding_hash[name] != hash)
	{
		m_buffer_resolve[name].buffers = {static_cast<Buffer *>(buffer)->GetHandle()};
		m_buffer_resolve[name].ranges  = {range};
		m_buffer_resolve[name].offsets = {offset};

		m_binding_hash[name] = hash;

		m_binding_dirty[m_descriptor_lookup[name].first] = true;
	}

	return *this;
}

RHIDescriptor &Descriptor::BindBuffer(const std::string &name, const std::vector<RHIBuffer *> &buffers)
{
	size_t hash = 0;
	HashCombine(hash, buffers);

	if (m_binding_hash[name] != hash)
	{
		m_buffer_resolve[name].buffers.clear();
		m_buffer_resolve[name].buffers.reserve(buffers.size());
		m_buffer_resolve[name].ranges.clear();
		m_buffer_resolve[name].ranges.reserve(buffers.size());
		m_buffer_resolve[name].offsets.clear();
		m_buffer_resolve[name].offsets.reserve(buffers.size());

		for (auto *buffer : buffers)
		{
			m_buffer_resolve[name].buffers.push_back(static_cast<Buffer *>(buffer)->GetHandle());
			m_buffer_resolve[name].ranges.push_back(buffer->GetDesc().size);
			m_buffer_resolve[name].offsets.push_back(0);
		}

		m_binding_hash[name] = hash;

		m_binding_dirty[m_descriptor_lookup[name].first] = true;
	}

	return *this;
}

RHIDescriptor &Descriptor::BindConstant(const std::string &name, const void *constant, size_t size)
{
	return *this;
}

const std::unordered_map<uint32_t, VkDescriptorSet> &Descriptor::GetDescriptorSet()
{
	// Check update
	for (auto &[set, dirty] : m_binding_dirty)
	{
		if (dirty)
		{
			std::vector<VkWriteDescriptorSet> write_sets;
			for (auto &descriptor : m_meta.descriptors)
			{
				if (descriptor.set == set)
				{
					bool     is_texture       = false;
					bool     is_buffer        = false;
					uint32_t descriptor_count = 0;

					std::vector<VkDescriptorImageInfo>  image_infos = {};
					std::vector<VkDescriptorBufferInfo> buffer_infos = {};

					if (descriptor.type == ShaderMeta::Descriptor::Type::TextureSRV ||
					    descriptor.type == ShaderMeta::Descriptor::Type::TextureUAV)
					{
						is_texture = true;
					}

					VkWriteDescriptorSet write_set = {};
					write_set.sType                = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					write_set.dstSet               = m_descriptor_sets[set];
					write_set.dstBinding           = descriptor.binding;
					write_set.dstArrayElement      = 0;
					write_set.descriptorCount      = descriptor_count;
					write_set.descriptorType       = DescriptorTypeMap[descriptor.type];
					write_set.pImageInfo           = image_infos.data();
					write_set.pBufferInfo          = buffer_infos.data();
					write_set.pTexelBufferView     = nullptr;
				}
			}

			dirty = false;
		}
	}

	return m_descriptor_sets;
}

const std::unordered_map<uint32_t, VkDescriptorSetLayout> &Descriptor::GetDescriptorSetLayout()
{
	return m_descriptor_set_layouts;
}

VkDescriptorSetLayout Descriptor::CreateDescriptorSetLayout(const ShaderMeta &meta)
{
	std::vector<VkDescriptorBindingFlags>     descriptor_binding_flags       = {};
	std::vector<VkDescriptorSetLayoutBinding> descriptor_set_layout_bindings = {};

	for (const auto &descriptor : meta.descriptors)
	{
		VkDescriptorSetLayoutBinding layout_binding = {};
		layout_binding.binding                      = descriptor.binding;
		layout_binding.descriptorType               = DescriptorTypeMap[descriptor.type];
		layout_binding.stageFlags                   = ToVulkanShaderStage(descriptor.stage);
		layout_binding.descriptorCount              = descriptor.array_size == 0 ? 1024 : descriptor.array_size;
		descriptor_set_layout_bindings.push_back(layout_binding);
		descriptor_binding_flags.push_back(descriptor.array_size == 0 ? VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT : 0);
	}

	VkDescriptorSetLayoutCreateInfo descriptor_set_layout_create_info = {};
	descriptor_set_layout_create_info.sType                           = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptor_set_layout_create_info.bindingCount                    = static_cast<uint32_t>(descriptor_set_layout_bindings.size());
	descriptor_set_layout_create_info.pBindings                       = descriptor_set_layout_bindings.data();
	descriptor_set_layout_create_info.flags                           = VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT;

	VkDescriptorSetLayoutBindingFlagsCreateInfo descriptor_set_layout_binding_flag_create_info = {};
	descriptor_set_layout_binding_flag_create_info.sType                                       = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
	descriptor_set_layout_binding_flag_create_info.bindingCount                                = static_cast<uint32_t>(descriptor_binding_flags.size());
	descriptor_set_layout_binding_flag_create_info.pBindingFlags                               = descriptor_binding_flags.data();

	descriptor_set_layout_create_info.pNext = &descriptor_set_layout_binding_flag_create_info;

	VkDescriptorSetLayout layout = VK_NULL_HANDLE;
	vkCreateDescriptorSetLayout(static_cast<Device *>(p_device)->GetDevice(), &descriptor_set_layout_create_info, nullptr, &layout);

	return layout;
}

}        // namespace Ilum::Vulkan