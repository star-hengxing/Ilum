#include "E:/Workspace/Ilum/Source/Runtime/Renderer/Private/BasePass/TrianglePass.hpp"
#include <rttr/registration.h>

namespace Ilum_8826872755708282140
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::TrianglePass::Config>("Config")
        .property("a", &Ilum::TrianglePass::Config::a)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
    rttr::registration::class_<Ilum::TrianglePass>("TrianglePass")(rttr::metadata("RenderPass", "Triangle Pass"), rttr::metadata("Category", "Basic Pass"))
    
    
        .constructor<>()(rttr::policy::ctor::as_object)
        .method("CreateDesc", &Ilum::TrianglePass::CreateDesc)
        .method("Create", &Ilum::TrianglePass::Create)
    ;
}
}                                 