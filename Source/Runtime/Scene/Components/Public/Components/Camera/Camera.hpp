#pragma once

#include <SceneGraph/Component.hpp>

#include <glm/glm.hpp>

namespace Ilum
{
namespace Cmpt
{
class EXPORT_API Camera : public Component
{
  public:
	Camera(const char *name, Node *node);

	virtual ~Camera() = default;

	virtual void OnImGui() override = 0;

	virtual std::type_index GetType() const = 0;

	void SetAspect(float aspect);

	float GetAspect();

	void SetNearPlane(float near_plane);

	void SetFarPlane(float far_plane);

	float GetNearPlane() const;

	float GetFarPlane() const;

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix();

	glm::mat4 GetViewProjectionMatrix();

	glm::mat4 GetInvViewMatrix();

	glm::mat4 GetInvProjectionMatrix();

	glm::mat4 GetInvViewProjectionMatrix();

  protected:
	virtual void UpdateProjection() = 0;

	void UpdateView();

  protected:
	bool m_dirty = false;

	float m_aspect = 1.f;
	float m_near   = 0.01f;
	float m_far    = 1000.f;

	glm::mat4 m_view                = glm::mat4(1.f);
	glm::mat4 m_inv_view            = glm::mat4(1.f);
	glm::mat4 m_projection          = glm::mat4(1.f);
	glm::mat4 m_inv_projection      = glm::mat4(1.f);
	glm::mat4 m_view_projection     = glm::mat4(1.f);
	glm::mat4 m_inv_view_projection = glm::mat4(1.f);
};
}        // namespace Cmpt
}        // namespace Ilum