#ifndef __CAMERA__
#define __CAMERA__

#include <glm/glm.hpp>
#include <memory>

class GameObject;

class Camera {
	private:
	std::shared_ptr<GameObject> m_target = nullptr;
	glm::vec3 m_position;
	glm::vec3 m_positionFromTarget;
	glm::mat4 m_view;

	void _updatePosition();
	void _updateView();

	public:
	Camera();
	virtual ~Camera() {}
	void setTarget(std::shared_ptr<GameObject> target);

	virtual void update();

	virtual void setPosition(glm::vec3 position);
	virtual void setPositionFromTarget(glm::vec3 position);
	glm::vec3 getPosition() const;
	glm::mat4 getView() const;

	virtual glm::mat4 getProjection() const = 0;
};

#endif
