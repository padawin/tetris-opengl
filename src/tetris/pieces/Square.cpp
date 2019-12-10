#include "Square.hpp"

void SquarePiece::init() {
	// Looks like:
	// ##
	// #0
	m_vBlockCoordinates[0] = {{-1, 1}, {0, 1}, {0, 0}, {-1, 0}};
	// #0
	// ##
	m_vBlockCoordinates[1] = {{-1, 1}, {0, 1}, {0, 0}, {-1, 0}};
	// 0#
	// ##
	m_vBlockCoordinates[2] = {{-1, 1}, {0, 1}, {0, 0}, {-1, 0}};
	// ##
	// 0#
	m_vBlockCoordinates[3] = {{-1, 1}, {0, 1}, {0, 0}, {-1, 0}};
	m_color.r = 0.312f,
	m_color.g = 0.071f,
	m_color.b = 0.66f;
	Piece::init();
}
