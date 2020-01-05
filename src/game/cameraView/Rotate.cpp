#include "Rotate.hpp"
#include <glm/gtc/matrix_transform.hpp>

#define PI 3.14159265

RotateView::RotateView(glm::vec3 center, float distanceFromCenter) :
	m_center(center),
	m_fDistanceFromCenter(distanceFromCenter)
{
}

void RotateView::setCenter(glm::vec3 center) {
	m_center = center;
}

void RotateView::rotateVertical(float angle) {
	m_fVerticalAngle = (float) fmod(360.0f + m_fVerticalAngle + angle, 360.0f);
}

void RotateView::rotateHorizontal(float angle) {
	m_fHorizontalAngle = (float) fmod(360.0f + m_fHorizontalAngle + angle, 360.0f);
}

float RotateView::getVerticalAngle() const {
	return m_fVerticalAngle;
}

float RotateView::getHorizontalAngle() const {
	return m_fHorizontalAngle;
}

void RotateView::update() {
	// XXX Update this method
	glm::vec3 relativePosition;
	float horizontalAngleRad = m_fHorizontalAngle * (float) PI / 180.0f;
	float verticalAngleRad = m_fVerticalAngle * (float) PI / 180.0f;
	relativePosition.x = (float) cos(horizontalAngleRad) * m_fDistanceFromCenter;
	relativePosition.y = (float) sin(verticalAngleRad) * m_fDistanceFromCenter;
	relativePosition.z = (float) sin(horizontalAngleRad) * m_fDistanceFromCenter;

	m_position = m_center + relativePosition;

	glm::vec3 cameraDirection = glm::normalize(m_position - m_center);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, right);
	m_view = glm::lookAt(m_position, m_center, cameraUp);
}
