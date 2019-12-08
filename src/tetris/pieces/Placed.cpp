#include <iostream>
#include "Placed.hpp"
#include "opengl/ObjectRenderer.hpp"

void PlacedPiece::_create() {
	// Square of 1 by 1
	m_vBlockCoordinates.push_back({0, 0});
}

void PlacedPiece::init() {
	float vertices[] = {
		// vertices        // texture
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top left
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2, // first triangle
		1, 2, 3  // second triangle
	};
	m_renderer = std::shared_ptr<GameObjectRenderer>(new ObjectRenderer());
	ObjectRenderer *renderer = (ObjectRenderer *) m_renderer.get();

	renderer->init();
	renderer->setShaderProgram("default");
	renderer->setTexture("piece.png");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
	_create();
}
