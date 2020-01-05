#ifndef __CAMERA_VIEW_ROTATE__
#define __CAMERA_VIEW_ROTATE__

#include "game/CameraView.hpp"
#include "game/GameObject.hpp"
#include <glm/glm.hpp>
#include <memory>

class RotateView : public CameraView {
	private:
	glm::vec3 m_center;
	float m_fDistanceFromCenter = 1.0f;
	float m_fHorizontalAngle = 0.0f;
	float m_fVerticalAngle = 0.0f;

	public:
	RotateView(glm::vec3 center, float distanceFromCenter);
	void setCenter(glm::vec3 center);
	void rotateVertical(float angle);
	void rotateHorizontal(float angle);
	float getVerticalAngle() const;
	float getHorizontalAngle() const;
	void update();
};

#endif
