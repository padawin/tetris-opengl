#include "Piece.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

std::vector<glm::vec2> Piece::getBlocks() const {
	std::vector<glm::vec2> coords = {};
	for (auto blockCoords : m_vBlockCoordinates) {
		glm::vec2 c = glm::rotate(blockCoords, glm::radians(m_angle.z));
		coords.push_back(c);
	}
	return coords;
}

void Piece::rotate(int quarter) {
	m_angle.z = (float) quarter * 90.0f;
}
