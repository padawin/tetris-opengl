#include "Piece.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

const glm::vec4 COLOR_GHOST = glm::vec4(0.35f, 0.35f, 0.35f, 0.6f);

std::vector<glm::ivec3> Piece::getBlocks() const {
	std::vector<glm::ivec3> blocks = {};
	for (auto block : m_vBlockCoordinates[m_iOrientation]) {
		blocks.push_back(glm::ivec3(
			block.x,
#ifdef MODE_3D
			block.z,
			block.y
#else
			block.y,
			block.z
#endif
		));
	}
	return blocks;
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
#ifdef MODE_3D
			position.y + (float) block.z,
			position.z + (float) block.y
#else
			position.y + (float) block.y,
			position.z + (float) block.z
#endif
		);
		GameObject::render(camera, renderer, positionBlock, m_angle, m_scale);
	}
}
