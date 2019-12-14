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
	m_color.r = 0.843f,
	m_color.g = 0.373f,
	m_color.b = 0.843f;
	Piece::init();
}
