#include "S.hpp"

void SPiece::init() {
	// Looks like:
	//  0#
	// ##
	m_vBlockCoordinates[0] = {{-1, -1}, {0, -1}, {0, 0}, {1, 0}};
	// #
	// #0
	//  #
	m_vBlockCoordinates[1] = {{0, -1}, {0, 0}, {-1, 0}, {-1, 1}};
	//  0#
	// ##
	m_vBlockCoordinates[2] = {{-1, -1}, {0, -1}, {0, 0}, {1, 0}};
	// #
	// #0
	//  #
	m_vBlockCoordinates[3] = {{0, -1}, {0, 0}, {-1, 0}, {-1, 1}};
	m_color.r = 0.447f,
	m_color.g = 0.624f,
	m_color.b = 0.812f;
	Piece::init();
}
