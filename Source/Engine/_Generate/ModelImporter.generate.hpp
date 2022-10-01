#include "E:/Workspace/Ilum/Source/Runtime/Resource/Private/Importer/Model/ModelImporter.hpp"
#include <rttr/registration.h>

namespace Ilum_14103667558776811945
{
RTTR_REGISTRATION
{
    
    rttr::registration::class_<Ilum::ModelImportInfo>("ModelImportInfo")
        .property("name", &Ilum::ModelImportInfo::name)
        .property("submeshes", &Ilum::ModelImportInfo::submeshes)
        .property("vertices", &Ilum::ModelImportInfo::vertices)
        .property("indices", &Ilum::ModelImportInfo::indices)
        .property("meshlets", &Ilum::ModelImportInfo::meshlets)
        .property("meshlet_vertices", &Ilum::ModelImportInfo::meshlet_vertices)
        .property("meshlet_primitives", &Ilum::ModelImportInfo::meshlet_primitives)
        .property("aabb", &Ilum::ModelImportInfo::aabb)
    
        .constructor<>()(rttr::policy::ctor::as_object)
    
    ;
}
}                                 