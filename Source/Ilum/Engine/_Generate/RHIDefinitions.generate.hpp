#include "E:/Workspace/Ilum/Source/Ilum/RHI/RHIDefinitions.hpp"
#include <rttr/registration.h>

namespace Ilum_1973678632099992664
{
RTTR_REGISTRATION
{
    rttr::registration::enumeration<Ilum::RHIBackend>("RHIBackend")
    (
        rttr::value("Unknown", Ilum::RHIBackend::Unknown),
        rttr::value("Vulkan", Ilum::RHIBackend::Vulkan),
        rttr::value("DX12", Ilum::RHIBackend::DX12),
        rttr::value("OpenGL", Ilum::RHIBackend::OpenGL),
        rttr::value("CUDA", Ilum::RHIBackend::CUDA)
    );
    rttr::registration::enumeration<Ilum::RHIShaderStage>("RHIShaderStage")
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
    rttr::registration::enumeration<Ilum::RHIFeature>("RHIFeature")
    (
        rttr::value("RayTracing", Ilum::RHIFeature::RayTracing),
        rttr::value("MeshShading", Ilum::RHIFeature::MeshShading),
        rttr::value("BufferDeviceAddress", Ilum::RHIFeature::BufferDeviceAddress),
        rttr::value("Bindless", Ilum::RHIFeature::Bindless)
    );
    
}


}                                