#include "Piece.hpp"

std::vector<std::pair<int, int>> Piece::getBlocks() const {
	return m_vBlockCoordinates;
}
