#pragma once
#include <rttr/registration.h>
#include "E:/Workspace/Ilum/Source/Ilum/RHI/Precompile.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIAccelerationStructure.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIBuffer.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHICommand.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIContext.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIDefinitions.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIDescriptor.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIDevice.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIFrame.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIPipelineState.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIProfiler.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIQueue.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIRenderTarget.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHISampler.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIShader.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHISwapchain.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHISynchronization.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHITexture.hpp"
// This code is generated by meta generator
namespace NAMESPACE_45427588121943506
{
RTTR_REGISTRATION
{
using namespace Ilum;

rttr::registration::class_<Ilum::BufferDesc>("Ilum::BufferDesc")
	.property("name", &Ilum::BufferDesc::name)
	.property("usage", &Ilum::BufferDesc::usage)
	.property("memory", &Ilum::BufferDesc::memory)
	.property("size", &Ilum::BufferDesc::size)(rttr::metadata("min", 1))
	.property("stride", &Ilum::BufferDesc::stride)(rttr::metadata("min", 0))
	.property("count", &Ilum::BufferDesc::count)(rttr::metadata("min", 0))
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::enumeration<Ilum::CommandState>("Ilum::CommandState")
(
	rttr::value("Available", Ilum::CommandState::Available),
	rttr::value("Initial", Ilum::CommandState::Initial),
	rttr::value("Recording", Ilum::CommandState::Recording),
	rttr::value("Executable", Ilum::CommandState::Executable),
	rttr::value("Pending", Ilum::CommandState::Pending)
);

rttr::registration::enumeration<Ilum::RHIBackend>("Ilum::RHIBackend")
(
	rttr::value("Unknown", Ilum::RHIBackend::Unknown),
	rttr::value("Vulkan", Ilum::RHIBackend::Vulkan),
	rttr::value("DX12", Ilum::RHIBackend::DX12),
	rttr::value("CUDA", Ilum::RHIBackend::CUDA)
);

rttr::registration::enumeration<Ilum::RHIShaderStage>("Ilum::RHIShaderStage")
(
	rttr::value("Vertex", Ilum::RHIShaderStage::Vertex),
	rttr::value("TessellationControl", Ilum::RHIShaderStage::TessellationControl),
	rttr::value("TessellationEvaluation", Ilum::RHIShaderStage::TessellationEvaluation),
	rttr::value("Geometry", Ilum::RHIShaderStage::Geometry),
	rttr::value("Fragment", Ilum::RHIShaderStage::Fragment),
	rttr::value("Compute", Ilum::RHIShaderStage::Compute),
	rttr::value("RayGen", Ilum::RHIShaderStage::RayGen),
	rttr::value("AnyHit", Ilum::RHIShaderStage::AnyHit),
	rttr::value("ClosestHit", Ilum::RHIShaderStage::ClosestHit),
	rttr::value("Miss", Ilum::RHIShaderStage::Miss),
	rttr::value("Intersection", Ilum::RHIShaderStage::Intersection),
	rttr::value("Callable", Ilum::RHIShaderStage::Callable),
	rttr::value("Mesh", Ilum::RHIShaderStage::Mesh),
	rttr::value("Task", Ilum::RHIShaderStage::Task)
);

rttr::registration::enumeration<Ilum::RHIFeature>("Ilum::RHIFeature")
(
	rttr::value("RayTracing", Ilum::RHIFeature::RayTracing),
	rttr::value("MeshShading", Ilum::RHIFeature::MeshShading),
	rttr::value("BufferDeviceAddress", Ilum::RHIFeature::BufferDeviceAddress),
	rttr::value("Bindless", Ilum::RHIFeature::Bindless)
);

rttr::registration::enumeration<Ilum::RHIQueueFamily>("Ilum::RHIQueueFamily")
(
	rttr::value("Graphics", Ilum::RHIQueueFamily::Graphics),
	rttr::value("Compute", Ilum::RHIQueueFamily::Compute),
	rttr::value("Transfer", Ilum::RHIQueueFamily::Transfer)
);

rttr::registration::enumeration<Ilum::RHIFormat>("Ilum::RHIFormat")
(
	rttr::value("Undefined", Ilum::RHIFormat::Undefined),
	rttr::value("R16_UINT", Ilum::RHIFormat::R16_UINT),
	rttr::value("R16_SINT", Ilum::RHIFormat::R16_SINT),
	rttr::value("R16_FLOAT", Ilum::RHIFormat::R16_FLOAT),
	rttr::value("R8G8B8A8_UNORM", Ilum::RHIFormat::R8G8B8A8_UNORM),
	rttr::value("B8G8R8A8_UNORM", Ilum::RHIFormat::B8G8R8A8_UNORM),
	rttr::value("R32_UINT", Ilum::RHIFormat::R32_UINT),
	rttr::value("R32_SINT", Ilum::RHIFormat::R32_SINT),
	rttr::value("R32_FLOAT", Ilum::RHIFormat::R32_FLOAT),
	rttr::value("D32_FLOAT", Ilum::RHIFormat::D32_FLOAT),
	rttr::value("D24_UNORM_S8_UINT", Ilum::RHIFormat::D24_UNORM_S8_UINT),
	rttr::value("R16G16_UINT", Ilum::RHIFormat::R16G16_UINT),
	rttr::value("R16G16_SINT", Ilum::RHIFormat::R16G16_SINT),
	rttr::value("R16G16_FLOAT", Ilum::RHIFormat::R16G16_FLOAT),
	rttr::value("R16G16B16A16_UINT", Ilum::RHIFormat::R16G16B16A16_UINT),
	rttr::value("R16G16B16A16_SINT", Ilum::RHIFormat::R16G16B16A16_SINT),
	rttr::value("R16G16B16A16_FLOAT", Ilum::RHIFormat::R16G16B16A16_FLOAT),
	rttr::value("R32G32_UINT", Ilum::RHIFormat::R32G32_UINT),
	rttr::value("R32G32_SINT", Ilum::RHIFormat::R32G32_SINT),
	rttr::value("R32G32_FLOAT", Ilum::RHIFormat::R32G32_FLOAT),
	rttr::value("R32G32B32_UINT", Ilum::RHIFormat::R32G32B32_UINT),
	rttr::value("R32G32B32_SINT", Ilum::RHIFormat::R32G32B32_SINT),
	rttr::value("R32G32B32_FLOAT", Ilum::RHIFormat::R32G32B32_FLOAT),
	rttr::value("R32G32B32A32_UINT", Ilum::RHIFormat::R32G32B32A32_UINT),
	rttr::value("R32G32B32A32_SINT", Ilum::RHIFormat::R32G32B32A32_SINT),
	rttr::value("R32G32B32A32_FLOAT", Ilum::RHIFormat::R32G32B32A32_FLOAT)
);

rttr::registration::enumeration<Ilum::RHIVertexSemantics>("Ilum::RHIVertexSemantics")
(
	rttr::value("Binormal", Ilum::RHIVertexSemantics::Binormal),
	rttr::value("Blend_Indices", Ilum::RHIVertexSemantics::Blend_Indices),
	rttr::value("Blend_Weights", Ilum::RHIVertexSemantics::Blend_Weights),
	rttr::value("Color", Ilum::RHIVertexSemantics::Color),
	rttr::value("Normal", Ilum::RHIVertexSemantics::Normal),
	rttr::value("Position", Ilum::RHIVertexSemantics::Position),
	rttr::value("Tangent", Ilum::RHIVertexSemantics::Tangent),
	rttr::value("Texcoord", Ilum::RHIVertexSemantics::Texcoord)
);

rttr::registration::enumeration<Ilum::RHIMemoryUsage>("Ilum::RHIMemoryUsage")
(
	rttr::value("GPU_Only", Ilum::RHIMemoryUsage::GPU_Only),
	rttr::value("CPU_TO_GPU", Ilum::RHIMemoryUsage::CPU_TO_GPU),
	rttr::value("GPU_TO_CPU", Ilum::RHIMemoryUsage::GPU_TO_CPU)
);

rttr::registration::enumeration<Ilum::RHITextureDimension>("Ilum::RHITextureDimension")
(
	rttr::value("Texture1D", Ilum::RHITextureDimension::Texture1D),
	rttr::value("Texture2D", Ilum::RHITextureDimension::Texture2D),
	rttr::value("Texture3D", Ilum::RHITextureDimension::Texture3D),
	rttr::value("TextureCube", Ilum::RHITextureDimension::TextureCube),
	rttr::value("Texture1DArray", Ilum::RHITextureDimension::Texture1DArray),
	rttr::value("Texture2DArray", Ilum::RHITextureDimension::Texture2DArray),
	rttr::value("TextureCubeArray", Ilum::RHITextureDimension::TextureCubeArray)
);

rttr::registration::enumeration<Ilum::RHIBufferUsage>("Ilum::RHIBufferUsage")
(
	rttr::value("Undefined", Ilum::RHIBufferUsage::Undefined),
	rttr::value("Vertex", Ilum::RHIBufferUsage::Vertex),
	rttr::value("Index", Ilum::RHIBufferUsage::Index),
	rttr::value("Indirect", Ilum::RHIBufferUsage::Indirect),
	rttr::value("Transfer", Ilum::RHIBufferUsage::Transfer),
	rttr::value("AccelerationStructure", Ilum::RHIBufferUsage::AccelerationStructure),
	rttr::value("ShaderResource", Ilum::RHIBufferUsage::ShaderResource),
	rttr::value("UnorderedAccess", Ilum::RHIBufferUsage::UnorderedAccess),
	rttr::value("ConstantBuffer", Ilum::RHIBufferUsage::ConstantBuffer)
);

rttr::registration::enumeration<Ilum::RHITextureUsage>("Ilum::RHITextureUsage")
(
	rttr::value("Undefined", Ilum::RHITextureUsage::Undefined),
	rttr::value("Transfer", Ilum::RHITextureUsage::Transfer),
	rttr::value("ShaderResource", Ilum::RHITextureUsage::ShaderResource),
	rttr::value("UnorderedAccess", Ilum::RHITextureUsage::UnorderedAccess),
	rttr::value("RenderTarget", Ilum::RHITextureUsage::RenderTarget)
);

rttr::registration::enumeration<Ilum::RHIResourceState>("Ilum::RHIResourceState")
(
	rttr::value("Undefined", Ilum::RHIResourceState::Undefined),
	rttr::value("VertexBuffer", Ilum::RHIResourceState::VertexBuffer),
	rttr::value("ConstantBuffer", Ilum::RHIResourceState::ConstantBuffer),
	rttr::value("IndexBuffer", Ilum::RHIResourceState::IndexBuffer),
	rttr::value("IndirectBuffer", Ilum::RHIResourceState::IndirectBuffer),
	rttr::value("TransferSource", Ilum::RHIResourceState::TransferSource),
	rttr::value("TransferDest", Ilum::RHIResourceState::TransferDest),
	rttr::value("ShaderResource", Ilum::RHIResourceState::ShaderResource),
	rttr::value("UnorderedAccess", Ilum::RHIResourceState::UnorderedAccess),
	rttr::value("RenderTarget", Ilum::RHIResourceState::RenderTarget),
	rttr::value("DepthWrite", Ilum::RHIResourceState::DepthWrite),
	rttr::value("DepthRead", Ilum::RHIResourceState::DepthRead),
	rttr::value("AccelerationStructure", Ilum::RHIResourceState::AccelerationStructure),
	rttr::value("Present", Ilum::RHIResourceState::Present)
);

rttr::registration::enumeration<Ilum::RHIFilter>("Ilum::RHIFilter")
(
	rttr::value("Nearest", Ilum::RHIFilter::Nearest),
	rttr::value("Linear", Ilum::RHIFilter::Linear)
);

rttr::registration::enumeration<Ilum::RHIAddressMode>("Ilum::RHIAddressMode")
(
	rttr::value("Repeat", Ilum::RHIAddressMode::Repeat),
	rttr::value("Mirrored_Repeat", Ilum::RHIAddressMode::Mirrored_Repeat),
	rttr::value("Clamp_To_Edge", Ilum::RHIAddressMode::Clamp_To_Edge),
	rttr::value("Clamp_To_Border", Ilum::RHIAddressMode::Clamp_To_Border),
	rttr::value("Mirror_Clamp_To_Edge", Ilum::RHIAddressMode::Mirror_Clamp_To_Edge)
);

rttr::registration::enumeration<Ilum::RHIMipmapMode>("Ilum::RHIMipmapMode")
(
	rttr::value("Nearest", Ilum::RHIMipmapMode::Nearest),
	rttr::value("Linear", Ilum::RHIMipmapMode::Linear)
);

rttr::registration::enumeration<Ilum::RHISamplerBorderColor>("Ilum::RHISamplerBorderColor")
(
	rttr::value("Float_Transparent_Black", Ilum::RHISamplerBorderColor::Float_Transparent_Black),
	rttr::value("Int_Transparent_Black", Ilum::RHISamplerBorderColor::Int_Transparent_Black),
	rttr::value("Float_Opaque_Black", Ilum::RHISamplerBorderColor::Float_Opaque_Black),
	rttr::value("Int_Opaque_Black", Ilum::RHISamplerBorderColor::Int_Opaque_Black),
	rttr::value("Float_Opaque_White", Ilum::RHISamplerBorderColor::Float_Opaque_White),
	rttr::value("Int_Opaque_White", Ilum::RHISamplerBorderColor::Int_Opaque_White)
);

rttr::registration::enumeration<Ilum::RHICompareOp>("Ilum::RHICompareOp")
(
	rttr::value("Never", Ilum::RHICompareOp::Never),
	rttr::value("Less", Ilum::RHICompareOp::Less),
	rttr::value("Equal", Ilum::RHICompareOp::Equal),
	rttr::value("Less_Or_Equal", Ilum::RHICompareOp::Less_Or_Equal),
	rttr::value("Greater", Ilum::RHICompareOp::Greater),
	rttr::value("Not_Equal", Ilum::RHICompareOp::Not_Equal),
	rttr::value("Greater_Or_Equal", Ilum::RHICompareOp::Greater_Or_Equal),
	rttr::value("Always", Ilum::RHICompareOp::Always)
);

rttr::registration::enumeration<Ilum::RHILogicOp>("Ilum::RHILogicOp")
(
	rttr::value("Clear", Ilum::RHILogicOp::Clear),
	rttr::value("And", Ilum::RHILogicOp::And),
	rttr::value("And_Reverse", Ilum::RHILogicOp::And_Reverse),
	rttr::value("Copy", Ilum::RHILogicOp::Copy),
	rttr::value("And_Inverted", Ilum::RHILogicOp::And_Inverted),
	rttr::value("No_Op", Ilum::RHILogicOp::No_Op),
	rttr::value("XOR", Ilum::RHILogicOp::XOR),
	rttr::value("Or", Ilum::RHILogicOp::Or),
	rttr::value("Nor", Ilum::RHILogicOp::Nor),
	rttr::value("Equivalent", Ilum::RHILogicOp::Equivalent),
	rttr::value("Invert", Ilum::RHILogicOp::Invert),
	rttr::value("Or_Reverse", Ilum::RHILogicOp::Or_Reverse),
	rttr::value("Copy_Inverted", Ilum::RHILogicOp::Copy_Inverted),
	rttr::value("Or_Inverted", Ilum::RHILogicOp::Or_Inverted),
	rttr::value("Nand", Ilum::RHILogicOp::Nand),
	rttr::value("Set", Ilum::RHILogicOp::Set)
);

rttr::registration::enumeration<Ilum::RHIBlendFactor>("Ilum::RHIBlendFactor")
(
	rttr::value("Zero", Ilum::RHIBlendFactor::Zero),
	rttr::value("One", Ilum::RHIBlendFactor::One),
	rttr::value("Src_Color", Ilum::RHIBlendFactor::Src_Color),
	rttr::value("One_Minus_Src_Color", Ilum::RHIBlendFactor::One_Minus_Src_Color),
	rttr::value("Dst_Color", Ilum::RHIBlendFactor::Dst_Color),
	rttr::value("One_Minus_Dst_Color", Ilum::RHIBlendFactor::One_Minus_Dst_Color),
	rttr::value("Src_Alpha", Ilum::RHIBlendFactor::Src_Alpha),
	rttr::value("One_Minus_Src_Alpha", Ilum::RHIBlendFactor::One_Minus_Src_Alpha),
	rttr::value("Dst_Alpha", Ilum::RHIBlendFactor::Dst_Alpha),
	rttr::value("One_Minus_Dst_Alpha", Ilum::RHIBlendFactor::One_Minus_Dst_Alpha),
	rttr::value("Constant_Color", Ilum::RHIBlendFactor::Constant_Color),
	rttr::value("One_Minus_Constant_Color", Ilum::RHIBlendFactor::One_Minus_Constant_Color),
	rttr::value("Constant_Alpha", Ilum::RHIBlendFactor::Constant_Alpha),
	rttr::value("One_Minus_Constant_Alpha", Ilum::RHIBlendFactor::One_Minus_Constant_Alpha),
	rttr::value("Src_Alpha_Saturate", Ilum::RHIBlendFactor::Src_Alpha_Saturate),
	rttr::value("Src1_Color", Ilum::RHIBlendFactor::Src1_Color),
	rttr::value("One_Minus_Src1_Color", Ilum::RHIBlendFactor::One_Minus_Src1_Color),
	rttr::value("Src1_Alpha", Ilum::RHIBlendFactor::Src1_Alpha),
	rttr::value("One_Minus_Src1_Alpha", Ilum::RHIBlendFactor::One_Minus_Src1_Alpha)
);

rttr::registration::enumeration<Ilum::RHIBlendOp>("Ilum::RHIBlendOp")
(
	rttr::value("Add", Ilum::RHIBlendOp::Add),
	rttr::value("Subtract", Ilum::RHIBlendOp::Subtract),
	rttr::value("Reverse_Subtract", Ilum::RHIBlendOp::Reverse_Subtract),
	rttr::value("Min", Ilum::RHIBlendOp::Min),
	rttr::value("Max", Ilum::RHIBlendOp::Max)
);

rttr::registration::enumeration<Ilum::RHICullMode>("Ilum::RHICullMode")
(
	rttr::value("None", Ilum::RHICullMode::None),
	rttr::value("Front", Ilum::RHICullMode::Front),
	rttr::value("Back", Ilum::RHICullMode::Back)
);

rttr::registration::enumeration<Ilum::RHIFrontFace>("Ilum::RHIFrontFace")
(
	rttr::value("Counter_Clockwise", Ilum::RHIFrontFace::Counter_Clockwise),
	rttr::value("Clockwise", Ilum::RHIFrontFace::Clockwise)
);

rttr::registration::enumeration<Ilum::RHIPolygonMode>("Ilum::RHIPolygonMode")
(
	rttr::value("Wireframe", Ilum::RHIPolygonMode::Wireframe),
	rttr::value("Solid", Ilum::RHIPolygonMode::Solid)
);

rttr::registration::enumeration<Ilum::RHIPrimitiveTopology>("Ilum::RHIPrimitiveTopology")
(
	rttr::value("Point", Ilum::RHIPrimitiveTopology::Point),
	rttr::value("Line", Ilum::RHIPrimitiveTopology::Line),
	rttr::value("Triangle", Ilum::RHIPrimitiveTopology::Triangle),
	rttr::value("Patch", Ilum::RHIPrimitiveTopology::Patch)
);

rttr::registration::enumeration<Ilum::RHIVertexInputRate>("Ilum::RHIVertexInputRate")
(
	rttr::value("Vertex", Ilum::RHIVertexInputRate::Vertex),
	rttr::value("Instance", Ilum::RHIVertexInputRate::Instance)
);

rttr::registration::enumeration<Ilum::RHILoadAction>("Ilum::RHILoadAction")
(
	rttr::value("DontCare", Ilum::RHILoadAction::DontCare),
	rttr::value("Load", Ilum::RHILoadAction::Load),
	rttr::value("Clear", Ilum::RHILoadAction::Clear)
);

rttr::registration::enumeration<Ilum::RHIStoreAction>("Ilum::RHIStoreAction")
(
	rttr::value("DontCare", Ilum::RHIStoreAction::DontCare),
	rttr::value("Store", Ilum::RHIStoreAction::Store)
);

rttr::registration::class_<Ilum::DepthStencilState>("Ilum::DepthStencilState")
	.property("depth_test_enable", &Ilum::DepthStencilState::depth_test_enable)
	.property("depth_write_enable", &Ilum::DepthStencilState::depth_write_enable)
	.property("compare", &Ilum::DepthStencilState::compare)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::BlendState::AttachmentState>("Ilum::BlendState::AttachmentState")
	.property("blend_enable", &Ilum::BlendState::AttachmentState::blend_enable)
	.property("src_color_blend", &Ilum::BlendState::AttachmentState::src_color_blend)
	.property("dst_color_blend", &Ilum::BlendState::AttachmentState::dst_color_blend)
	.property("color_blend_op", &Ilum::BlendState::AttachmentState::color_blend_op)
	.property("src_alpha_blend", &Ilum::BlendState::AttachmentState::src_alpha_blend)
	.property("dst_alpha_blend", &Ilum::BlendState::AttachmentState::dst_alpha_blend)
	.property("alpha_blend_op", &Ilum::BlendState::AttachmentState::alpha_blend_op)
	.property("color_write_mask", &Ilum::BlendState::AttachmentState::color_write_mask)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::BlendState>("Ilum::BlendState")
	.property("enable", &Ilum::BlendState::enable)
	.property("logic_op", &Ilum::BlendState::logic_op)
	.property("blend_constants", &Ilum::BlendState::blend_constants)
	.property("attachment_states", &Ilum::BlendState::attachment_states)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::RasterizationState>("Ilum::RasterizationState")
	.property("cull_mode", &Ilum::RasterizationState::cull_mode)
	.property("front_face", &Ilum::RasterizationState::front_face)
	.property("polygon_mode", &Ilum::RasterizationState::polygon_mode)
	.property("depth_bias", &Ilum::RasterizationState::depth_bias)
	.property("depth_bias_clamp", &Ilum::RasterizationState::depth_bias_clamp)
	.property("depth_bias_slope", &Ilum::RasterizationState::depth_bias_slope)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::VertexInputState::InputBinding>("Ilum::VertexInputState::InputBinding")
	.property("binding", &Ilum::VertexInputState::InputBinding::binding)
	.property("stride", &Ilum::VertexInputState::InputBinding::stride)
	.property("rate", &Ilum::VertexInputState::InputBinding::rate)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::VertexInputState::InputAttribute>("Ilum::VertexInputState::InputAttribute")
	.property("semantics", &Ilum::VertexInputState::InputAttribute::semantics)
	.property("location", &Ilum::VertexInputState::InputAttribute::location)
	.property("binding", &Ilum::VertexInputState::InputAttribute::binding)
	.property("format", &Ilum::VertexInputState::InputAttribute::format)
	.property("offset", &Ilum::VertexInputState::InputAttribute::offset)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::VertexInputState>("Ilum::VertexInputState")
	.property("input_attributes", &Ilum::VertexInputState::input_attributes)
	.property("input_bindings", &Ilum::VertexInputState::input_bindings)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::InputAssemblyState>("Ilum::InputAssemblyState")
	.property("topology", &Ilum::InputAssemblyState::topology)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::ColorAttachment>("Ilum::ColorAttachment")
	.property("load", &Ilum::ColorAttachment::load)
	.property("store", &Ilum::ColorAttachment::store)
	.property("clear_value", &Ilum::ColorAttachment::clear_value)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::SamplerDesc>("Ilum::SamplerDesc")
	.property("min_filter", &Ilum::SamplerDesc::min_filter)
	.property("mag_filter", &Ilum::SamplerDesc::mag_filter)
	.property("address_mode_u", &Ilum::SamplerDesc::address_mode_u)
	.property("address_mode_v", &Ilum::SamplerDesc::address_mode_v)
	.property("address_mode_w", &Ilum::SamplerDesc::address_mode_w)
	.property("mipmap_mode", &Ilum::SamplerDesc::mipmap_mode)
	.property("border_color", &Ilum::SamplerDesc::border_color)
	.property("anisotropic", &Ilum::SamplerDesc::anisotropic)
	.property("mip_lod_bias", &Ilum::SamplerDesc::mip_lod_bias)
	.property("min_lod", &Ilum::SamplerDesc::min_lod)
	.property("max_lod", &Ilum::SamplerDesc::max_lod)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::enumeration<Ilum::DescriptorType>("Ilum::DescriptorType")
(
	rttr::value("Sampler", Ilum::DescriptorType::Sampler),
	rttr::value("TextureSRV", Ilum::DescriptorType::TextureSRV),
	rttr::value("TextureUAV", Ilum::DescriptorType::TextureUAV),
	rttr::value("ConstantBuffer", Ilum::DescriptorType::ConstantBuffer),
	rttr::value("StructuredBuffer", Ilum::DescriptorType::StructuredBuffer),
	rttr::value("AccelerationStructure", Ilum::DescriptorType::AccelerationStructure)
);

rttr::registration::class_<Ilum::ShaderMeta::Variable>("Ilum::ShaderMeta::Variable")
	.property("spirv_id", &Ilum::ShaderMeta::Variable::spirv_id)
	.property("location", &Ilum::ShaderMeta::Variable::location)
	.property("format", &Ilum::ShaderMeta::Variable::format)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::ShaderMeta::Descriptor>("Ilum::ShaderMeta::Descriptor")
	.property("spirv_id", &Ilum::ShaderMeta::Descriptor::spirv_id)
	.property("name", &Ilum::ShaderMeta::Descriptor::name)
	.property("array_size", &Ilum::ShaderMeta::Descriptor::array_size)
	.property("set", &Ilum::ShaderMeta::Descriptor::set)
	.property("binding", &Ilum::ShaderMeta::Descriptor::binding)
	.property("type", &Ilum::ShaderMeta::Descriptor::type)
	.property("stage", &Ilum::ShaderMeta::Descriptor::stage)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::TextureDesc>("Ilum::TextureDesc")
	.property("name", &Ilum::TextureDesc::name)
	.property("width", &Ilum::TextureDesc::width)(rttr::metadata("min", 1))
	.property("height", &Ilum::TextureDesc::height)(rttr::metadata("min", 1))
	.property("depth", &Ilum::TextureDesc::depth)(rttr::metadata("min", 1))
	.property("mips", &Ilum::TextureDesc::mips)(rttr::metadata("min", 1))
	.property("layers", &Ilum::TextureDesc::layers)(rttr::metadata("min", 1))
	.property("samples", &Ilum::TextureDesc::samples)(rttr::metadata("min", 1))
	.property("format", &Ilum::TextureDesc::format)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::TextureRange>("Ilum::TextureRange")
	.property("dimension", &Ilum::TextureRange::dimension)
	.property("base_mip", &Ilum::TextureRange::base_mip)(rttr::metadata("min", 0))
	.property("mip_count", &Ilum::TextureRange::mip_count)(rttr::metadata("min", 1))
	.property("base_layer", &Ilum::TextureRange::base_layer)(rttr::metadata("min", 0))
	.property("layer_count", &Ilum::TextureRange::layer_count)(rttr::metadata("min", 1))
	.method("Hash", &Ilum::TextureRange::Hash)
	.constructor<>()(rttr::policy::ctor::as_object);

SERIALIZER_REGISTER_TYPE(decltype(Ilum::BufferDesc::name))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BufferDesc::usage))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BufferDesc::memory))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BufferDesc::size))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BufferDesc::stride))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BufferDesc::count))
SERIALIZER_REGISTER_TYPE(Ilum::BufferDesc)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilState::depth_test_enable))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilState::depth_write_enable))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilState::compare))
SERIALIZER_REGISTER_TYPE(Ilum::DepthStencilState)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::AttachmentState::blend_enable))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::AttachmentState::src_color_blend))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::AttachmentState::dst_color_blend))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::AttachmentState::color_blend_op))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::AttachmentState::src_alpha_blend))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::AttachmentState::dst_alpha_blend))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::AttachmentState::alpha_blend_op))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::AttachmentState::color_write_mask))
SERIALIZER_REGISTER_TYPE(Ilum::BlendState::AttachmentState)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::enable))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::logic_op))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::blend_constants))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::BlendState::attachment_states))
SERIALIZER_REGISTER_TYPE(Ilum::BlendState)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RasterizationState::cull_mode))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RasterizationState::front_face))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RasterizationState::polygon_mode))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RasterizationState::depth_bias))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RasterizationState::depth_bias_clamp))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RasterizationState::depth_bias_slope))
SERIALIZER_REGISTER_TYPE(Ilum::RasterizationState)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::MultisampleState::enable))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::MultisampleState::samples))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::MultisampleState::sample_mask))
SERIALIZER_REGISTER_TYPE(Ilum::MultisampleState)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::InputBinding::binding))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::InputBinding::stride))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::InputBinding::rate))
SERIALIZER_REGISTER_TYPE(Ilum::VertexInputState::InputBinding)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::InputAttribute::semantics))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::InputAttribute::location))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::InputAttribute::binding))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::InputAttribute::format))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::InputAttribute::offset))
SERIALIZER_REGISTER_TYPE(Ilum::VertexInputState::InputAttribute)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::input_attributes))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::VertexInputState::input_bindings))
SERIALIZER_REGISTER_TYPE(Ilum::VertexInputState)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::InputAssemblyState::topology))
SERIALIZER_REGISTER_TYPE(Ilum::InputAssemblyState)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ColorAttachment::load))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ColorAttachment::store))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ColorAttachment::clear_value))
SERIALIZER_REGISTER_TYPE(Ilum::ColorAttachment)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilAttachment::depth_load))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilAttachment::depth_store))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilAttachment::stencil_load))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilAttachment::stencil_store))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilAttachment::clear_depth))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::DepthStencilAttachment::clear_stencil))
SERIALIZER_REGISTER_TYPE(Ilum::DepthStencilAttachment)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::min_filter))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::mag_filter))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::address_mode_u))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::address_mode_v))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::address_mode_w))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::mipmap_mode))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::border_color))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::anisotropic))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::mip_lod_bias))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::min_lod))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::SamplerDesc::max_lod))
SERIALIZER_REGISTER_TYPE(Ilum::SamplerDesc)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Variable::spirv_id))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Variable::location))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Variable::format))
SERIALIZER_REGISTER_TYPE(Ilum::ShaderMeta::Variable)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Constant::spirv_id))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Constant::name))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Constant::size))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Constant::offset))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Constant::stage))
SERIALIZER_REGISTER_TYPE(Ilum::ShaderMeta::Constant)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Descriptor::spirv_id))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Descriptor::name))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Descriptor::array_size))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Descriptor::set))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Descriptor::binding))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Descriptor::type))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::Descriptor::stage))
SERIALIZER_REGISTER_TYPE(Ilum::ShaderMeta::Descriptor)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::descriptors))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::constants))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::inputs))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::outputs))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderMeta::hash))
SERIALIZER_REGISTER_TYPE(Ilum::ShaderMeta)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::name))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::width))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::height))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::depth))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::mips))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::layers))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::samples))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::format))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::usage))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureDesc::external))
SERIALIZER_REGISTER_TYPE(Ilum::TextureDesc)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureRange::dimension))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureRange::base_mip))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureRange::mip_count))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureRange::base_layer))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::TextureRange::layer_count))
SERIALIZER_REGISTER_TYPE(Ilum::TextureRange)
}
}

//Generate for Serialization

namespace cereal
{
template <class Archive>
void serialize(Archive& archive, Ilum::BufferDesc& v)
{
	archive(v.name, v.usage, v.memory, v.size, v.stride, v.count);
}

template <class Archive>
void serialize(Archive& archive, Ilum::DepthStencilState& v)
{
	archive(v.depth_test_enable, v.depth_write_enable, v.compare);
}

template <class Archive>
void serialize(Archive& archive, Ilum::BlendState::AttachmentState& v)
{
	archive(v.blend_enable, v.src_color_blend, v.dst_color_blend, v.color_blend_op, v.src_alpha_blend, v.dst_alpha_blend, v.alpha_blend_op, v.color_write_mask);
}

template <class Archive>
void serialize(Archive& archive, Ilum::BlendState& v)
{
	archive(v.enable, v.logic_op, v.blend_constants, v.attachment_states);
}

template <class Archive>
void serialize(Archive& archive, Ilum::RasterizationState& v)
{
	archive(v.cull_mode, v.front_face, v.polygon_mode, v.depth_bias, v.depth_bias_clamp, v.depth_bias_slope);
}

template <class Archive>
void serialize(Archive& archive, Ilum::MultisampleState& v)
{
	archive(v.enable, v.samples, v.sample_mask);
}

template <class Archive>
void serialize(Archive& archive, Ilum::VertexInputState::InputBinding& v)
{
	archive(v.binding, v.stride, v.rate);
}

template <class Archive>
void serialize(Archive& archive, Ilum::VertexInputState::InputAttribute& v)
{
	archive(v.semantics, v.location, v.binding, v.format, v.offset);
}

template <class Archive>
void serialize(Archive& archive, Ilum::VertexInputState& v)
{
	archive(v.input_attributes, v.input_bindings);
}

template <class Archive>
void serialize(Archive& archive, Ilum::InputAssemblyState& v)
{
	archive(v.topology);
}

template <class Archive>
void serialize(Archive& archive, Ilum::ColorAttachment& v)
{
	archive(v.load, v.store, v.clear_value);
}

template <class Archive>
void serialize(Archive& archive, Ilum::DepthStencilAttachment& v)
{
	archive(v.depth_load, v.depth_store, v.stencil_load, v.stencil_store, v.clear_depth, v.clear_stencil);
}

template <class Archive>
void serialize(Archive& archive, Ilum::SamplerDesc& v)
{
	archive(v.min_filter, v.mag_filter, v.address_mode_u, v.address_mode_v, v.address_mode_w, v.mipmap_mode, v.border_color, v.anisotropic, v.mip_lod_bias, v.min_lod, v.max_lod);
}

template <class Archive>
void serialize(Archive& archive, Ilum::ShaderMeta::Variable& v)
{
	archive(v.spirv_id, v.location, v.format);
}

template <class Archive>
void serialize(Archive& archive, Ilum::ShaderMeta::Constant& v)
{
	archive(v.spirv_id, v.name, v.size, v.offset, v.stage);
}

template <class Archive>
void serialize(Archive& archive, Ilum::ShaderMeta::Descriptor& v)
{
	archive(v.spirv_id, v.name, v.array_size, v.set, v.binding, v.type, v.stage);
}

template <class Archive>
void serialize(Archive& archive, Ilum::ShaderMeta& v)
{
	archive(v.descriptors, v.constants, v.inputs, v.outputs, v.hash);
}

template <class Archive>
void serialize(Archive& archive, Ilum::TextureDesc& v)
{
	archive(v.name, v.width, v.height, v.depth, v.mips, v.layers, v.samples, v.format, v.usage, v.external);
}

template <class Archive>
void serialize(Archive& archive, Ilum::TextureRange& v)
{
	archive(v.dimension, v.base_mip, v.mip_count, v.base_layer, v.layer_count);
}


}
