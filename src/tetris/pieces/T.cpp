#include "T.hpp"

void TPiece::init() {
	// Looks like:
	//  #
	// #0#
	m_vBlockCoordinates[0] = {{-1, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
	//  #
	// #0
	//  #
	m_vBlockCoordinates[1] = {{0, -1, 0}, {0, 0, 0}, {0, 1, 0}, {-1, 0, 0}};
	// #0#
	//  #
	m_vBlockCoordinates[2] = {{1, 0, 0}, {0, 0, 0}, {-1, 0, 0}, {0, -1, 0}};
	// #
	// 0#
	// #
	m_vBlockCoordinates[3] = {{0, 1, 0}, {0, 0, 0}, {0, -1, 0}, {1, 0, 0}};

	m_color.r = 0.961f,
	m_color.g = 0.475f,
	m_color.b = 0.0f;
}
