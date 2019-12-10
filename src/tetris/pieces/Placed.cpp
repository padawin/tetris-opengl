#include "Placed.hpp"

void PlacedPiece::init() {
	// Square of 1 by 1
	m_vBlockCoordinates[0] = {{0, 0}};
	m_vBlockCoordinates[1] = {{0, 0}};
	m_vBlockCoordinates[2] = {{0, 0}};
	m_vBlockCoordinates[3] = {{0, 0}};

	m_color.r = 0.502f,
	m_color.g = 0.742f,
	m_color.b = 0.86f;
	Piece::init();
}
