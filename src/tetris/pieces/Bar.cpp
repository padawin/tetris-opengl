#include "Bar.hpp"

void BarPiece::init() {
	// Looks like:
	// #0##
	m_vBlockCoordinates[0] = {{-1, 0}, {0, 0}, {1, 0}, {2, 0}};
	// #
	// #
	// 0
	// #
	m_vBlockCoordinates[1] = {{0, -1}, {0, 0}, {0, 1}, {0, 2}};
	// #0##
	m_vBlockCoordinates[2] = {{-1, 0}, {0, 0}, {1, 0}, {2, 0}};
	// #
	// #
	// 0
	// #
	m_vBlockCoordinates[3] = {{0, -1}, {0, 0}, {0, 1}, {0, 2}};
	m_color.r = 0.176f,
	m_color.g = 0.477f,
	m_color.b = 0.875f;
	Piece::init();
}
