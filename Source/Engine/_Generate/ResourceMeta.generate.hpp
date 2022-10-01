#include "E:/Workspace/Ilum/Source/Runtime/Resource/Public/Resource/ResourceMeta.hpp"
#include <rttr/registration.h>

namespace Ilum_5988281310158489175
{
RTTR_REGISTRATION
{
    rttr::registration::enumeration<Ilum::ResourceType>("ResourceType")
    (
        rttr::value("Unknown", Ilum::ResourceType::Unknown),
        rttr::value("Texture", Ilum::ResourceType::Texture),
        rttr::value("Model", Ilum::ResourceType::Model),
        rttr::value("Scene", Ilum::ResourceType::Scene),
        rttr::value("RenderGraph", Ilum::ResourceType::RenderGraph)
    );
    
}
}                                 