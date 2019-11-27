#ifndef __CAMERA__
#define __CAMERA__

#include <glm/glm.hpp>
//#include "GameObject.hpp"

class Camera {
	private:
	//GameObject *m_target = 0;
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_right;


	public:
	Camera();
	virtual ~Camera() {}
	//void setTarget(GameObject *target);

	//virtual void update();

	virtual void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;

	virtual glm::mat4 getProjection() const = 0;
};

#endif
