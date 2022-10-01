#include "E:/Workspace/Ilum/Source/Runtime/Renderer/Private/BasePass/PresentPass.hpp"
#include <rttr/registration.h>

namespace Ilum_9435026849588976845
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::PresentPass>("PresentPass")(rttr::metadata("RenderPass", "Present Pass"), rttr::metadata("Category", "Basic Pass"))
    
    
        .constructor<>()(rttr::policy::ctor::as_object)
        .method("CreateDesc", &Ilum::PresentPass::CreateDesc)
        .method("Create", &Ilum::PresentPass::Create)
    ;
}
}                                 