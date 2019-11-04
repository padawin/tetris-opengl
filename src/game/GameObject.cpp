#include "GameObject.hpp"

void GameObject::render() {
	if (m_renderer != 0) {
		m_renderer->render();
	}
}

void GameObject::setPos(float x, float y, float z) {
	m_iX = x;
	m_iY = y;
	m_iZ = z;
}

float GameObject::getX() const {
	return m_iX;
}

float GameObject::getY() const {
	return m_iY;
}

float GameObject::getZ() const {
	return m_iZ;
}
