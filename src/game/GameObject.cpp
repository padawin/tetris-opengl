#include "GameObject.hpp"

void GameObject::render() {
	if (m_renderer != 0) {
		m_renderer->render();
	}
}

void GameObject::setPos(float x, float y) {
	m_iX = x;
	m_iY = y;
}

float GameObject::getX() const {
	return m_iX;
}

float GameObject::getY() const {
	return m_iY;
}
