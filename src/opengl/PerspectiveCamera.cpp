#include "PerspectiveCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(float angleDegrees, float screenRatio, float near, float far) :
	m_projectionMatrix(glm::perspective(glm::radians(angleDegrees), screenRatio, near, far)),
	m_position(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

glm::mat4 PerspectiveCamera::getProjection() const {
	return m_projectionMatrix;
}
