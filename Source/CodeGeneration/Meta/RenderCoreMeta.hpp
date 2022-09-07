#pragma once
#include <rttr/registration.h>
#include "D:/Workspace/IlumEngine/Source/Ilum/RenderCore/Precompile.hpp"
#include "D:/Workspace/IlumEngine/Source/Ilum/RenderCore/RenderGraph/RenderGraph.hpp"
#include "D:/Workspace/IlumEngine/Source/Ilum/RenderCore/RenderGraph/RenderGraphBuilder.hpp"
#include "D:/Workspace/IlumEngine/Source/Ilum/RenderCore/ShaderCompiler/ShaderCompiler.hpp"
#include "D:/Workspace/IlumEngine/Source/Ilum/RenderCore/ShaderCompiler/SpirvReflection.hpp"
// This code is generated by meta generator
namespace NAMESPACE_7042130567007298195
{
RTTR_REGISTRATION
{
using namespace Ilum;

rttr::registration::class_<Ilum::RGHandle>("Ilum::RGHandle")
	.property("handle", &Ilum::RGHandle::handle)
	.constructor<>()
	.constructor<size_t>()
	.method("IsValid", &Ilum::RGHandle::IsValid)
	.method("GetHandle", &Ilum::RGHandle::GetHandle);

rttr::registration::enumeration<Ilum::RenderResourceDesc::Type>("Ilum::RenderResourceDesc::Type")
(
	rttr::value("Buffer", Ilum::RenderResourceDesc::Type::Buffer),
	rttr::value("Texture", Ilum::RenderResourceDesc::Type::Texture)
);

rttr::registration::enumeration<Ilum::RenderResourceDesc::Attribute>("Ilum::RenderResourceDesc::Attribute")
(
	rttr::value("Read", Ilum::RenderResourceDesc::Attribute::Read),
	rttr::value("Write", Ilum::RenderResourceDesc::Attribute::Write)
);

rttr::registration::class_<Ilum::RenderResourceDesc>("Ilum::RenderResourceDesc")
	.property("type", &Ilum::RenderResourceDesc::type)
	.property("attribute", &Ilum::RenderResourceDesc::attribute)
	.property("state", &Ilum::RenderResourceDesc::state)
	.property("handle", &Ilum::RenderResourceDesc::handle)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::RenderPassDesc>("Ilum::RenderPassDesc")
	.property("name", &Ilum::RenderPassDesc::name)
	.property("config", &Ilum::RenderPassDesc::config)
	.property("resources", &Ilum::RenderPassDesc::resources)
	.property("prev_pass", &Ilum::RenderPassDesc::prev_pass)
	.method("Write", &Ilum::RenderPassDesc::Write)
	.method("Read", &Ilum::RenderPassDesc::Read)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::class_<Ilum::RenderGraphDesc>("Ilum::RenderGraphDesc")
	.property("passes", &Ilum::RenderGraphDesc::passes)
	.property("textures", &Ilum::RenderGraphDesc::textures)
	.property("buffers", &Ilum::RenderGraphDesc::buffers)
	.constructor<>()(rttr::policy::ctor::as_object);

rttr::registration::enumeration<Ilum::ShaderSource>("Ilum::ShaderSource")
(
	rttr::value("HLSL", Ilum::ShaderSource::HLSL),
	rttr::value("GLSL", Ilum::ShaderSource::GLSL)
);

rttr::registration::enumeration<Ilum::ShaderTarget>("Ilum::ShaderTarget")
(
	rttr::value("SPIRV", Ilum::ShaderTarget::SPIRV),
	rttr::value("DXIL", Ilum::ShaderTarget::DXIL),
	rttr::value("PTX", Ilum::ShaderTarget::PTX)
);

rttr::registration::class_<Ilum::ShaderDesc>("Ilum::ShaderDesc")
	.property("code", &Ilum::ShaderDesc::code)
	.property("source", &Ilum::ShaderDesc::source)
	.property("target", &Ilum::ShaderDesc::target)
	.property("stage", &Ilum::ShaderDesc::stage)
	.property("entry_point", &Ilum::ShaderDesc::entry_point)
	.property("macros", &Ilum::ShaderDesc::macros)
	.constructor<>()(rttr::policy::ctor::as_object);

SERIALIZER_REGISTER_TYPE(decltype(Ilum::RGHandle::handle))
SERIALIZER_REGISTER_TYPE(Ilum::RGHandle)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderResourceDesc::type))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderResourceDesc::attribute))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderResourceDesc::state))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderResourceDesc::handle))
SERIALIZER_REGISTER_TYPE(Ilum::RenderResourceDesc)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderPassDesc::name))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderPassDesc::config))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderPassDesc::resources))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderPassDesc::prev_pass))
SERIALIZER_REGISTER_TYPE(Ilum::RenderPassDesc)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderGraphDesc::passes))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderGraphDesc::textures))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::RenderGraphDesc::buffers))
SERIALIZER_REGISTER_TYPE(Ilum::RenderGraphDesc)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderDesc::code))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderDesc::source))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderDesc::target))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderDesc::stage))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderDesc::entry_point))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::ShaderDesc::macros))
SERIALIZER_REGISTER_TYPE(Ilum::ShaderDesc)
}
}

//Generate for Serialization

namespace cereal
{
template <class Archive>
void serialize(Archive& archive, Ilum::RGHandle& v)
{
	archive(v.handle);
}

template <class Archive>
void serialize(Archive& archive, Ilum::RenderResourceDesc& v)
{
	archive(v.type, v.attribute, v.state, v.handle);
}

template <class Archive>
void serialize(Archive& archive, Ilum::RenderPassDesc& v)
{
	archive(v.name, v.config, v.resources, v.prev_pass);
}

template <class Archive>
void serialize(Archive& archive, Ilum::RenderGraphDesc& v)
{
	archive(v.passes, v.textures, v.buffers);
}

template <class Archive>
void serialize(Archive& archive, Ilum::ShaderDesc& v)
{
	archive(v.code, v.source, v.target, v.stage, v.entry_point, v.macros);
}


}
