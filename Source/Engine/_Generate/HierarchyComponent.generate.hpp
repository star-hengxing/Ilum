#include "E:/Workspace/Ilum/Source/Runtime/Scene/Public/Scene/Component/HierarchyComponent.hpp"
#include <rttr/registration.h>

namespace Ilum_15790444028245869086
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::HierarchyComponent>("HierarchyComponent")
        .property("parent", &Ilum::HierarchyComponent::parent)
        .property("first", &Ilum::HierarchyComponent::first)
        .property("next", &Ilum::HierarchyComponent::next)
        .property("prev", &Ilum::HierarchyComponent::prev)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 