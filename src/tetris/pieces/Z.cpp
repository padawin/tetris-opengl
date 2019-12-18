#include "Z.hpp"

void ZPiece::init() {
	// Looks like:
	// #0
	//  ##
	m_vBlockCoordinates[0] = {{-1, 0}, {0, 0}, {0, -1}, {1, -1}};
	//  #
	// 0#
	// #
	m_vBlockCoordinates[1] = {{0, -1}, {0, 0}, {1, 0}, {1, 1}};
	// #0
	//  ##
	m_vBlockCoordinates[2] = {{-1, 0}, {0, 0}, {0, -1}, {1, -1}};
	//  #
	// 0#
	// #
	m_vBlockCoordinates[3] = {{0, -1}, {0, 0}, {1, 0}, {1, 1}};
	m_color.r = 0.915f,
	m_color.g = 0.866f,
	m_color.b = 0.209f;
}
