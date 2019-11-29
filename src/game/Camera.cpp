#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
	m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_view(glm::mat4())
{
}
//
//void Camera::setTarget(GameObject* target) {
//	m_target = target;
//}

void Camera::update() {
	m_view = glm::translate(glm::mat4(1.0f), -m_position);
}

void Camera::setPosition(glm::vec3 position) {
	m_position = position;
}

glm::vec3 Camera::getPosition() const {
	return m_position;
}

glm::mat4 Camera::getView() const {
	return m_view;
}
