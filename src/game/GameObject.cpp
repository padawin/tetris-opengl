#include "GameObject.hpp"
#include <iostream>

void GameObject::update() {
}

void GameObject::render(std::shared_ptr<Camera> camera) {
	render(camera, m_position, m_angle, m_scale);
}

void GameObject::render(std::shared_ptr<Camera> camera, glm::vec3 position, glm::vec3 angle, glm::vec3 scale) {
	if (m_renderer == nullptr) {
		return;
	}

	m_renderer->setPosition(position.x, position.y, position.z);
	m_renderer->setRotation(angle.x, angle.y, angle.z);
	m_renderer->setScale(scale.x, scale.y, scale.z);
	m_renderer->render(camera);
}

void GameObject::setPosition(float x, float y, float z) {
	m_position = glm::vec3(x, y, z);
}

glm::vec3 GameObject::getPosition() const {
	return m_position;
}
