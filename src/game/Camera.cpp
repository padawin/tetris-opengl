#include "Camera.hpp"
#include "GameObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
	m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_positionFromTarget(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_view(glm::mat4())
{
}

void Camera::setTarget(std::shared_ptr<GameObject> target) {
	m_target = target;
}

void Camera::update() {
	if (m_target == nullptr) {
		m_view = glm::translate(glm::mat4(1.0f), -m_position);
		return;
	}
	_updatePosition();
	_updateView();
}

void Camera::setPosition(glm::vec3 position) {
	m_position = position;
}

void Camera::setPositionFromTarget(glm::vec3 position) {
	m_positionFromTarget = position;
}

glm::vec3 Camera::getPosition() const {
	return m_position;
}

glm::mat4 Camera::getView() const {
	return m_view;
}

/**
 * If the camera is not fixed (@TOIMPLEMENT), it needs to move according to its
 * target (to be always placed in the same place relative to it).
 */
void Camera::_updatePosition() {
	m_position = m_positionFromTarget + m_target->getPosition();
}

void Camera::_updateView() {
	glm::vec3 targetPosition = m_target->getPosition();
	glm::vec3 cameraDirection = glm::normalize(m_position - targetPosition);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, right);
	m_view = glm::lookAt(m_position, targetPosition, cameraUp);
}
