#pragma once

#include <Core/Core.hpp>

namespace Ilum
{
enum class ResourceType
{
	Prefab,
	Mesh,
	SkinnedMesh,
	Texture,
	Animation,
	Material,
};

class EXPORT_API IResource
{
  public:
	IResource() = default;

	virtual ~IResource() = default;
};

template <ResourceType Type>
class EXPORT_API Resource : public IResource
{
  public:
	Resource() = default;

	virtual ~Resource() override = default;
};
}        // namespace Ilum