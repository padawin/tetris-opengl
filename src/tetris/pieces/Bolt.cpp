#include "Bolt.hpp"
#include "opengl/ObjectRenderer.hpp"

void BoltPiece::_create() {
	// Looks like:
	//  0#
	// ##
	m_vBlockCoordinates.push_back(std::make_pair(-1, -1));
	m_vBlockCoordinates.push_back(std::make_pair(0, -1));
	m_vBlockCoordinates.push_back(std::make_pair(0, 0));
	m_vBlockCoordinates.push_back(std::make_pair(1, 0));
}

void BoltPiece::init() {
	float vertices[] = {
		// vertices        // texture
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left

		 1.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
		 1.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left

		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // top right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // top left
		 0.5f, -1.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -1.5f, 0.0f, 0.0f, 0.0f, // bottom left

		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // top right
		-1.5f, -0.5f, 0.0f, 0.0f, 1.0f, // top left
		-0.5f, -1.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-1.5f, -1.5f, 0.0f, 0.0f, 0.0f, // bottom left

	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		1, 2, 3,   // second triangle

		4, 5, 6,   // first triangle
		5, 6, 7,   // second triangle

		8, 9, 10,   // first triangle
		9, 10, 11,   // second triangle

		12, 13, 14,   // first triangle
		13, 14, 15,   // second triangle
	};
	m_renderer = std::shared_ptr<GameObjectRenderer>(new ObjectRenderer());
	ObjectRenderer *renderer = (ObjectRenderer *) m_renderer.get();

	renderer->init();
	renderer->setShaderProgram("default");
	renderer->setTexture("lblock.png");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
	_create();
}
