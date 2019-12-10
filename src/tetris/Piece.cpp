#include "Piece.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "opengl/ObjectRenderer.hpp"

std::vector<glm::ivec2> Piece::getBlocks() const {
	return m_vBlockCoordinates[m_iOrientation];
}

void Piece::rotate(int quarter) {
	m_iOrientation = (4 + m_iOrientation + quarter) % 4;
}

void Piece::init() {
	float r = m_color.r,
		  g = m_color.g,
		  b = m_color.b;
	float vertices[] = {
		// vertices        // texture  // color
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, r, g, b, // top right
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, r, g, b, // top left
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, r, g, b, // bottom left
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
}

void Piece::render(std::shared_ptr<Camera> camera) {
	glm::vec3 position = getPosition();
	for (auto block : m_vBlockCoordinates[m_iOrientation]) {
		setPosition(position.x + (float) block.x, position.y + (float) block.y, position.z);
		update();
		GameObject::render(camera);
	}
	setPosition(position.x, position.y, position.z);
}
