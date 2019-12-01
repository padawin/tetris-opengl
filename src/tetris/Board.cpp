#include <iostream>
#include "Board.hpp"
#include "opengl/ObjectRenderer.hpp"

void Board::init() {
	int boardTop = BOARD_HEIGHT * CELL_HEIGHT;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		m_cells[i].init();
		int cellX = (i % BOARD_WIDTH) * CELL_WIDTH;
		int cellY = boardTop - (i / BOARD_WIDTH) * CELL_HEIGHT;
		m_cells[i].setPosition(m_position.x + (float) cellX, m_position.y + (float) cellY, 0.0f);
	}
}

void Board::update() {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		m_cells[i].update();
	}
}

void Board::render(std::shared_ptr<Camera> camera) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		m_cells[i].render(camera);
	}
}
