#include "Triangle.hpp"

void Triangle::init() {
	float vertices[] = {
		// vertices       // texture
		0.5f, 1.0f, 0.0f, 0.5f, 1.0f, // top
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f  // bottom left
	};
	unsigned int indices[] = {
		0, 1, 2,
	};
	m_objectRenderer.init();
	m_objectRenderer.setShaderProgram("default");
	m_objectRenderer.setTexture("wall.jpg");
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
