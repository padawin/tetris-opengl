#include "BoardCell.hpp"
#include "opengl/ObjectRenderer.hpp"

void BoardCell::init() {
	float r = 0.502f,
		  g = 0.742f,
		  b = 0.86f;
	float vertices[] = {
		// vertices        // texture    // color
		 0.45f, 0.45f, 0.0f, 1.0f, 1.0f, r, g, b, // top right
		-0.45f, 0.45f, 0.0f, 0.0f, 1.0f, r, g, b, // top left
		 0.45f, -0.45f, 0.0f, 1.0f, 0.0f, r, g, b, // bottom right
		-0.45f, -0.45f, 0.0f, 0.0f, 0.0f, r, g, b  // bottom left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		1, 2, 3    // second triangle
	};
	m_renderer = std::shared_ptr<GameObjectRenderer>(new ObjectRenderer());
	ObjectRenderer *renderer = (ObjectRenderer *) m_renderer.get();

	renderer->init();
	renderer->setShaderProgram("boardcell");
	renderer->setTexture("piece.png");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}
