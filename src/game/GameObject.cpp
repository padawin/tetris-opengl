#include "GameObject.hpp"

void GameObject::render() {
	if (m_renderer != 0) {
		m_renderer->render();
	}
}

void GameObject::setPos(int x, int y) {
	m_iX = x;
	m_iY = y;
}

int GameObject::getX() const {
	return m_iX;
}

int GameObject::getY() const {
	return m_iY;
}
