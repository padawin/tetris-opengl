#include "GameObject.hpp"
#include <iostream>

void GameObject::update() {
	if (m_renderer != 0) {
		m_renderer->setPosition(m_position.x, m_position.y, m_position.z);
		m_renderer->setRotation(m_angle.x, m_angle.y, m_angle.z);
		m_renderer->setScale(m_scale.x, m_scale.y, m_scale.z);
	}
}

void GameObject::render(std::shared_ptr<Camera> camera) {
	if (m_renderer != 0) {
		m_renderer->render(camera);
	}
}

void GameObject::setPosition(float x, float y, float z) {
	m_position = glm::vec3(x, y, z);
}

glm::vec3 GameObject::getPosition() const {
	return m_position;
}
