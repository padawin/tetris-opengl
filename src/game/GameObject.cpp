#include "GameObject.hpp"
#include <iostream>

void GameObject::update() {
	if (m_renderer != 0) {
		m_renderer->setPosition(m_iX, m_iY, m_iZ);
		m_renderer->setRotation(m_iAngleX, m_iAngleY, m_iAngleZ);
		m_renderer->setScale(m_iScaleX, m_iScaleY, m_iScaleZ);
	}
}

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
