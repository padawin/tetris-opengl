#include "Rectangle.hpp"

void Rectangle::init() {
	float vertices[] = {
		// vertices        // texture
		 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
		 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-1.0f, 0.0f, 0.0f, 0.0f, 0.0f  // bottom left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		1, 2, 3    // second triangle
	};
	m_objectRenderer.init();
	m_objectRenderer.setShaderProgram("default");
	m_objectRenderer.setTexture("container.jpg");
	m_objectRenderer.setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}

void Rectangle::setPos(int x, int y) {
	m_iX = x;
	m_iY = y;
}

int Rectangle::getX() const {
	return m_iX;
}

int Rectangle::getY() const {
	return m_iY;
}

void Rectangle::render() const {
	m_objectRenderer.render();
}
