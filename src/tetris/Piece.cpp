#include "Piece.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

std::vector<glm::ivec2> Piece::getBlocks() const {
	std::vector<glm::ivec2> coords = {};
	for (auto blockCoords : m_vBlockCoordinates) {
		glm::vec2 c = glm::rotate(blockCoords, glm::radians(m_angle.z));
		// https://stackoverflow.com/a/9695341/3866623
		int x = (int) (c.x + 0.5 - (c.x<0));
		int y = (int) (c.y + 0.5 - (c.y<0));
		coords.push_back({x, y});
	}
	return coords;
}

void Piece::rotate(int quarter) {
	m_angle.z = (float) quarter * 90.0f;
}
