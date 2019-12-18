#include "Piece.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

const glm::vec3 COLOR_GHOST = glm::vec3(0.15f, 0.15f, 0.15f);

std::vector<glm::ivec2> Piece::getBlocks() const {
	return m_vBlockCoordinates[m_iOrientation];
}

void Piece::rotate(int quarter) {
	m_iOrientation = (4 + m_iOrientation + quarter) % 4;
}

void Piece::initGhost() {
	m_ghost = std::shared_ptr<GameObject>(new GameObject());
}

std::shared_ptr<GameObject> Piece::getGhost() {
	return m_ghost;
}

void Piece::render(std::shared_ptr<Camera> camera, ObjectRenderer *renderer) {
	renderer->setUniform("color", m_color);
	_render(camera, renderer, getPosition());
	if (m_ghost != nullptr) {
		renderer->setUniform("color", COLOR_GHOST);
		_render(camera, renderer, m_ghost->getPosition());
	}
}

void Piece::_render(std::shared_ptr<Camera> camera, ObjectRenderer *renderer, glm::vec3 position) {
	for (auto block : m_vBlockCoordinates[m_iOrientation]) {
		glm::vec3 positionBlock = glm::vec3(
			position.x + (float) block.x,
			position.y + (float) block.y,
			position.z
		);
		GameObject::render(camera, renderer, positionBlock, m_angle, m_scale);
	}
}
