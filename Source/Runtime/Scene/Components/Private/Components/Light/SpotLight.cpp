#include "Light/SpotLight.hpp"

#include <imgui.h>

namespace Ilum
{
namespace Cmpt
{
SpotLight::SpotLight(Node *node) :
    Light("Spot Light", node)
{
}

void SpotLight::OnImGui()
{
	ImGui::DragFloat("Intensity", &m_data.intensity, 0.1f, 0.f, std::numeric_limits<float>::max(), "%.1f");
}

std::type_index SpotLight::GetType() const
{
	return typeid(SpotLight);
}

size_t SpotLight::GetDataSize() const
{
	return sizeof(m_data);
}

void *SpotLight::GetData() const
{
	return (void *) (&m_data);
}
}        // namespace Cmpt
}        // namespace Ilum