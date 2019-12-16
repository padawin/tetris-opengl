#include "BoardSide.hpp"
#include "opengl/ObjectRenderer.hpp"

BoardSide::BoardSide(int height) : m_iHeight(height) {
}

void BoardSide::init() {
	glm::vec3 color = glm::vec3(0.64f, 0.64f, 0.64f);
	float top = (float) m_iHeight / 2;
	float bottom = (float) m_iHeight / -2;
	float vertices[] = {
		// vertices        // texture
		 0.5f, top, 0.0f, 1.0f, (float) m_iHeight, // top right
		-0.5f, top, 0.0f, 0.0f, (float) m_iHeight, // top left
		 0.5f, bottom, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, bottom, 0.0f, 0.0f, 0.0f, // bottom left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		1, 2, 3    // second triangle
	};
	m_renderer = std::shared_ptr<GameObjectRenderer>(new ObjectRenderer());
	ObjectRenderer *renderer = (ObjectRenderer *) m_renderer.get();

	renderer->init();
	renderer->setShaderProgram("boardcell");
	renderer->setUniform("color", color);
	renderer->setTexture("piece.png");
	renderer->setVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}
