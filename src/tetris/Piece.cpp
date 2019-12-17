#include "Piece.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "opengl/ObjectRenderer.hpp"

const glm::vec3 COLOR_GHOST = glm::vec3(0.15f, 0.15f, 0.15f);

std::vector<glm::ivec2> Piece::getBlocks() const {
	return m_vBlockCoordinates[m_iOrientation];
}

void Piece::rotate(int quarter) {
	m_iOrientation = (4 + m_iOrientation + quarter) % 4;
}

void Piece::init() {
	float vertices[] = {
		// vertices        // texture  // color
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
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
}

void Piece::initGhost() {
	m_ghost = std::shared_ptr<GameObject>(new GameObject());
}

std::shared_ptr<GameObject> Piece::getGhost() {
	return m_ghost;
}

void Piece::render(std::shared_ptr<Camera> camera) {
	ObjectRenderer *renderer = (ObjectRenderer *) m_renderer.get();
	renderer->setUniform("color", m_color);
	_render(camera, getPosition());
	if (m_ghost != nullptr) {
		renderer->setUniform("color", COLOR_GHOST);
		_render(camera, m_ghost->getPosition());
	}
}

void Piece::_render(std::shared_ptr<Camera> camera, glm::vec3 position) {
	for (auto block : m_vBlockCoordinates[m_iOrientation]) {
		glm::vec3 positionBlock = glm::vec3(
			position.x + (float) block.x,
			position.y + (float) block.y,
			position.z
		);
		GameObject::render(camera, positionBlock, m_angle, m_scale);
	}
}
