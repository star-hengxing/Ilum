#pragma once

#include <Core/Core.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Ilum
{
class EXPORT_API Bone
{
  public:
	struct KeyPosition
	{
		glm::vec3 position;
		float     time_stamp;
	};

	struct KeyRotation
	{
		glm::quat orientation;
		float     time_stamp;
	};

	struct KeyScale
	{
		glm::vec3 scale;
		float     time_stamp;
	};

  public:
	Bone(
	    const std::string         &name,
	    uint32_t                   id,
	    std::vector<KeyPosition> &&positions,
	    std::vector<KeyRotation> &&rotations,
	    std::vector<KeyScale>    &&scales);

	~Bone();

	Bone(Bone &&bone);

	void Update(float time);

	glm::mat4 GetLocalTransform() const;

	std::string GetBoneName() const;

	uint32_t GetBoneID() const;

	size_t GetPositionIndex(float time) const;

	size_t GetRotationIndex(float time) const;

	size_t GetScaleIndex(float time) const;

  private:
	float GetScaleFactor(float last, float next, float time);

	glm::mat4 InterpolatePosition(float time);

	glm::mat4 InterpolateRotation(float time);

	glm::mat4 InterpolateScaling(float time);

  private:
	struct Impl;
	Impl *m_impl = nullptr;
};
}        // namespace Ilum