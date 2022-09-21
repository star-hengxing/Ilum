#pragma once
#include <rttr/registration.h>
#include "E:/Workspace/Ilum/Source/Ilum/Geometry/Bound/AABB.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/Geometry/Mesh/TriangleMesh.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/Geometry/Precompile.hpp"
#include "E:/Workspace/Ilum/Source/Ilum/Geometry/Vertex.hpp"
// This code is generated by meta generator
namespace NAMESPACE_14836227744367893400
{
RTTR_REGISTRATION
{
using namespace Ilum;

rttr::registration::class_<Ilum::AABB>("Ilum::AABB")
	.property("min", &Ilum::AABB::min)
	.property("max", &Ilum::AABB::max)
	.constructor<>()
	.constructor<const glm::vec3&, const glm::vec3&>()
	.method("Merge",  static_cast<void (Ilum::AABB::*)(const glm::vec3&)>(&Ilum::AABB::Merge))
	.method("Merge",  static_cast<void (Ilum::AABB::*)(const std::vector<glm::vec3>&)>(&Ilum::AABB::Merge))
	.method("Merge",  static_cast<void (Ilum::AABB::*)(const AABB&)>(&Ilum::AABB::Merge))
	.method("Transform", &Ilum::AABB::Transform)
	.method("Center", &Ilum::AABB::Center)
	.method("Scale", &Ilum::AABB::Scale);

rttr::registration::class_<Ilum::Vertex>("Ilum::Vertex")
	.property("position", &Ilum::Vertex::position)
	.property("normal", &Ilum::Vertex::normal)
	.property("tangent", &Ilum::Vertex::tangent)
	.property("texcoord", &Ilum::Vertex::texcoord)
	.constructor<>()(rttr::policy::ctor::as_object);

SERIALIZER_REGISTER_TYPE(decltype(Ilum::AABB::min))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::AABB::max))
SERIALIZER_REGISTER_TYPE(Ilum::AABB)
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Vertex::position))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Vertex::normal))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Vertex::tangent))
SERIALIZER_REGISTER_TYPE(decltype(Ilum::Vertex::texcoord))
SERIALIZER_REGISTER_TYPE(Ilum::Vertex)
}
}

//Generate for Serialization

namespace cereal
{
template <class Archive>
void serialize(Archive& archive, Ilum::AABB& v)
{
	archive(v.min, v.max);
}

template <class Archive>
void serialize(Archive& archive, Ilum::Vertex& v)
{
	archive(v.position, v.normal, v.tangent, v.texcoord);
}


}
