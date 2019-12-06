#include <iostream>
#include "Board.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "PieceFactory.hpp"

void Board::init() {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		m_cells[i].init();
		m_cells[i].setPosition(_getXPosInBoard(i), _getYPosInBoard(i), 0.0f);
		m_cells[i].update();
	}
}

float Board::_getXPosInBoard(int cellIndex) const {
	int cellX = (cellIndex % BOARD_WIDTH) * CELL_WIDTH;
	return m_position.x + (float) cellX;
}

float Board::_getYPosInBoard(int cellIndex) const {
	int boardTop = BOARD_HEIGHT * CELL_HEIGHT;
	int cellY = boardTop - (cellIndex / BOARD_WIDTH) * CELL_HEIGHT;
	return m_position.y + (float) cellY;
}

void Board::update() {
	if (m_state == GENERATE_PIECE) {
		_generatePiece();
		m_state = PIECE_FALLS;
	}

	if (m_currentPiece != nullptr) {
		m_currentPiece->update();
	}
}

void Board::_generatePiece() {
	m_currentPiece = std::shared_ptr<Piece>(PieceFactory::create());
	m_currentPiece->setPosition(
		_getXPosInBoard(BOARD_WIDTH / 2),
		_getYPosInBoard(0),
		0.1f
	);
}

void Board::render(std::shared_ptr<Camera> camera) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		m_cells[i].render(camera);
	}
	if (m_currentPiece != nullptr) {
		m_currentPiece->render(camera);
	}
}
