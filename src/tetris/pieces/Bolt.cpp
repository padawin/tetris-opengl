#include "Bolt.hpp"
#include "opengl/ObjectRenderer.hpp"

void BoltPiece::_create() {
	// Looks like:
	//  0#
	// ##
	m_vBlockCoordinates.push_back({-1, -1});
	m_vBlockCoordinates.push_back({0, -1});
	m_vBlockCoordinates.push_back({0, 0});
	m_vBlockCoordinates.push_back({1, 0});
}

void BoltPiece::init() {
	float r = 0.915f,
		  g = 0.866f,
		  b = 0.209f;
	float vertices[] = {
		// vertices        // texture  // color
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, r, g, b, // top right
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, r, g, b, // top left
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, r, g, b, // bottom left

		 1.5f, 0.5f, 0.0f, 1.0f, 1.0f, r, g, b, // top right
		 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, r, g, b, // top left
		 1.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b, // bottom right
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, r, g, b, // bottom left

		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, r, g, b, // top right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, r, g, b, // top left
		 0.5f, -1.5f, 0.0f, 1.0f, 0.0f, r, g, b, // bottom right
		-0.5f, -1.5f, 0.0f, 0.0f, 0.0f, r, g, b, // bottom left

		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, r, g, b, // top right
		-1.5f, -0.5f, 0.0f, 0.0f, 1.0f, r, g, b, // top left
		-0.5f, -1.5f, 0.0f, 1.0f, 0.0f, r, g, b, // bottom right
		-1.5f, -1.5f, 0.0f, 0.0f, 0.0f, r, g, b, // bottom left

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
	renderer->setTexture("piece.png");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
	_create();
}
