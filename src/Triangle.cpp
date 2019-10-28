#include "Triangle.hpp"

void Triangle::init() {
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	m_objectRenderer.init();
	m_objectRenderer.setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
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
