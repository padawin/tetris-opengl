#include "Camera.hpp"

Camera::Camera() :
	m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_up(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_right(glm::vec3(0.0f, 0.0f, 0.0f))
{
}
//
//void Camera::setTarget(GameObject* target) {
//	m_target = target;
//}
//
//void Camera::update() {
//	if (m_target == nullptr) {
//		return;
//	}
//}

void Camera::setPosition(glm::vec3 position) {
	m_position = position;
}

glm::vec3 Camera::getPosition() const {
	return m_position;
}
