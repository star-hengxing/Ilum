#pragma once

#include "Precompile.hpp"

#include <RHI/RHIBuffer.hpp>
#include <RHI/RHIContext.hpp>
#include <RHI/RHITexture.hpp>

namespace Ilum
{
STRUCT(RGHandle, Enable)
{
	size_t handle;

	RGHandle();

	RGHandle(size_t handle);

	~RGHandle() = default;

	bool IsValid();

	bool operator<(const RGHandle &rhs) const;

	bool operator==(const RGHandle &rhs) const;

	size_t GetHandle() const;
};

STRUCT(RenderResourceDesc, Enable)
{
	ENUM(Type, Enable){
	    Buffer,
	    Texture};

	ENUM(Attribute, Enable){
	    Read,
	    Write};

	Type type;

	Attribute attribute;

	RHIResourceState state;

	RGHandle handle;
};

ENUM(BindPoint, Enable){
    None,
    Rasterization,
    Compute,
    RayTracing,
    CUDA};

struct PassConfig
{
	template <typename Archive>
	void serialize(Archive &archive)
	{
	}

	template <>
	void serialize(InputArchive &archive)
	{
		_serialize(archive);
	}

	template <>
	void serialize(OutputArchive &archive)
	{
		_serialize(archive);
	}

  private:
	virtual void _serialize(InputArchive &archive)  = 0;
	virtual void _serialize(OutputArchive &archive) = 0;
};

STRUCT(RenderPassDesc, Enable)
{
	std::string name;

	std::any config;

	std::map<std::string, RenderResourceDesc> resources;

	RGHandle prev_pass;

	BindPoint bind_point;

	RenderPassDesc &Write(const std::string &name, RenderResourceDesc::Type type, RHIResourceState state)
	{
		resources.emplace(name, RenderResourceDesc{type, RenderResourceDesc::Attribute::Write, state});
		return *this;
	}

	RenderPassDesc &Read(const std::string &name, RenderResourceDesc::Type type, RHIResourceState state)
	{
		resources.emplace(name, RenderResourceDesc{type, RenderResourceDesc::Attribute::Read, state});
		return *this;
	}

	RenderPassDesc &SetName(const std::string &name)
	{
		this->name = name;
		return *this;
	}

	template <typename T>
	RenderPassDesc &SetConfig(T var)
	{
		config = var;
		return *this;
	}

	RenderPassDesc &SetBindPoint(BindPoint bind_point)
	{
		this->bind_point = bind_point;
		return *this;
	}
};

STRUCT(RenderGraphDesc, Enable)
{
	std::map<RGHandle, RenderPassDesc> passes;

	std::map<RGHandle, TextureDesc> textures;

	std::map<RGHandle, BufferDesc> buffers;
};

class EXPORT_API RenderGraph
{
	friend class RenderGraphBuilder;

  public:
	using RenderTask  = std::function<void(RenderGraph &, RHICommand *, std::any &)>;
	using BarrierTask = std::function<void(RenderGraph &, RHICommand *)>;

	struct RenderPassInfo
	{
		std::string name;

		BindPoint bind_point;

		std::any config;

		RenderTask  execute;
		BarrierTask barrier;

		std::unique_ptr<RHIProfiler> profiler = nullptr;
	};

  public:
	RenderGraph(RHIContext *rhi_context);

	~RenderGraph();

	RHITexture *GetTexture(RGHandle handle);

	RHIBuffer *GetBuffer(RGHandle handle);

	RHITexture *GetCUDATexture(RGHandle handle);

	void Execute();

	const std::vector<RenderPassInfo> &GetRenderPasses() const;

  private:
	struct TextureCreateInfo
	{
		TextureDesc desc;
		RGHandle    handle;
	};

	struct BufferCreateInfo
	{
		BufferDesc desc;
		RGHandle   handle;
	};

	RenderGraph &AddPass(
	    const std::string   &name,
	    BindPoint            bind_point,
	    const std::any &config,
	    RenderTask         &&execute,
	    BarrierTask        &&barrier);

	RenderGraph &AddInitializeBarrier(BarrierTask &&barrier);

	// Without memory alias
	RenderGraph &RegisterTexture(const TextureCreateInfo &create_infos);

	// With memory alias
	RenderGraph &RegisterTexture(const std::vector<TextureCreateInfo> &create_info);

	RenderGraph &RegisterBuffer(const BufferCreateInfo &create_info);

	RHISemaphore *MapToCUDASemaphore(RHISemaphore *semaphore);

  private:
	struct Impl;
	Impl *m_impl = nullptr;
};
}        // namespace Ilum