#include "E:/Workspace/Ilum/Source/Runtime/RenderCore/Public/RenderCore/RenderGraph/RenderGraph.hpp"
#include <rttr/registration.h>

namespace Ilum_7964622506339216333
{
RTTR_REGISTRATION
{
    rttr::registration::enumeration<Ilum::RenderResourceDesc::Type>("Type")
    (
        rttr::value("Buffer", Ilum::RenderResourceDesc::Type::Buffer),
        rttr::value("Texture", Ilum::RenderResourceDesc::Type::Texture)
    );
    rttr::registration::enumeration<Ilum::RenderResourceDesc::Attribute>("Attribute")
    (
        rttr::value("Read", Ilum::RenderResourceDesc::Attribute::Read),
        rttr::value("Write", Ilum::RenderResourceDesc::Attribute::Write)
    );
    rttr::registration::enumeration<Ilum::BindPoint>("BindPoint")
    (
        rttr::value("None", Ilum::BindPoint::None),
        rttr::value("Rasterization", Ilum::BindPoint::Rasterization),
        rttr::value("Compute", Ilum::BindPoint::Compute),
        rttr::value("RayTracing", Ilum::BindPoint::RayTracing),
        rttr::value("CUDA", Ilum::BindPoint::CUDA)
    );
    rttr::registration::class_<Ilum::RGHandle>("RGHandle")
        .property("handle", &Ilum::RGHandle::handle)
        .constructor<>()
        .constructor<size_t>()
    
        .method("IsValid", &Ilum::RGHandle::IsValid)
        .method("operator<", &Ilum::RGHandle::operator<)
        .method("operator==", &Ilum::RGHandle::operator==)
        .method("GetHandle", &Ilum::RGHandle::GetHandle)
    ;
    rttr::registration::class_<Ilum::RenderResourceDesc>("RenderResourceDesc")
        .property("type", &Ilum::RenderResourceDesc::type)
        .property("attribute", &Ilum::RenderResourceDesc::attribute)
        .property("state", &Ilum::RenderResourceDesc::state)
        .property("handle", &Ilum::RenderResourceDesc::handle)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
    rttr::registration::class_<Ilum::RenderPassDesc>("RenderPassDesc")
        .property("name", &Ilum::RenderPassDesc::name)
        .property("config", &Ilum::RenderPassDesc::config)
        .property("resources", &Ilum::RenderPassDesc::resources)
        .property("prev_pass", &Ilum::RenderPassDesc::prev_pass)
        .property("bind_point", &Ilum::RenderPassDesc::bind_point)
    
        .constructor<>()(rttr::policy::ctor::as_object)
        .method("Write", &Ilum::RenderPassDesc::Write)
        .method("Read", &Ilum::RenderPassDesc::Read)
        .method("SetName", &Ilum::RenderPassDesc::SetName)
        .method("SetBindPoint", &Ilum::RenderPassDesc::SetBindPoint)
    ;
    rttr::registration::class_<Ilum::RenderGraphDesc>("RenderGraphDesc")
        .property("passes", &Ilum::RenderGraphDesc::passes)
        .property("textures", &Ilum::RenderGraphDesc::textures)
        .property("buffers", &Ilum::RenderGraphDesc::buffers)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 