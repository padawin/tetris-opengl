#include "Triangle.hpp"

void Triangle::init() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		 0.5f, -0.5f, 0.0f, // right
		 0.0f,  0.5f, 0.0f  // top
	};
	m_objectRenderer.init();
	m_objectRenderer.setVertices(
		vertices,
		(int) sizeof(vertices)
	);
}

void Triangle::setPos(int x, int y) {
	m_iX = x;
	m_iY = y;
}

int Triangle::getX() const {
	return m_iX;
}

int Triangle::getY() const {
	return m_iY;
}

void Triangle::render() const {
	m_objectRenderer.render();
}
