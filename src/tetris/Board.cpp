#include <iostream>
#include <GLFW/glfw3.h>
#include "Board.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "PieceFactory.hpp"

void Board::init() {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		m_cells[i].init();
		m_cells[i].setPosition(_getWorldX(i), _getWorldY(i), 0.0f);
		m_cells[i].update();
	}
}

int Board::_getGridX(int cellIndex) const {
	return (cellIndex % BOARD_WIDTH) * CELL_WIDTH;
}

int Board::_getGridY(int cellIndex) const {
	int boardTop = BOARD_HEIGHT * CELL_HEIGHT;
	return boardTop - (cellIndex / BOARD_WIDTH) * CELL_HEIGHT;
}

float Board::_getWorldX(int cellIndex) const {
	return m_position.x + (float) _getGridX(cellIndex);
}

float Board::_getWorldY(int cellIndex) const {
	return m_position.y + (float) _getGridY(cellIndex);
}

void Board::update() {
	if (glfwGetTime() - m_fLastActionTime < TIME_BETWEEN_ACTIONS) {
		return;
	}
	if (m_state == GENERATE_PIECE) {
		_generatePiece();
		m_state = PIECE_FALLS;
	}
	else if (m_state == PIECE_FALLS) {
		if (_hasCollisions()) {
			m_state = REMOVE_FULL_LINES;
		}
		else {
			_movePieceDown();
		}
	}

	if (m_currentPiece != nullptr) {
		m_currentPiece->update();
	}
	m_fLastActionTime = glfwGetTime();
}

void Board::_generatePiece() {
	m_currentPiece = std::shared_ptr<Piece>(PieceFactory::create());
	m_currentPieceCell = BOARD_WIDTH / 2;
	int currentPieceCellY = _getGridY(m_currentPieceCell);
	int delta = 0;
	for (auto block : m_currentPiece->getBlocks()) {
		int cellY = currentPieceCellY + block.y;
		if (delta < cellY - BOARD_HEIGHT) {
			delta = cellY - BOARD_HEIGHT;
		}
	}
	m_currentPieceCell += delta * BOARD_WIDTH;
	m_currentPiece->setPosition(
		_getWorldX(m_currentPieceCell),
		_getWorldY(m_currentPieceCell),
		0.1f
	);
}

bool Board::_hasCollisions() const {
	bool collides = false;
	int currentPieceCellY = _getGridY(m_currentPieceCell);
	for (auto block : m_currentPiece->getBlocks()) {
		int cellY = currentPieceCellY + block.y - 1;
		if (cellY < 0) {
			collides = true;
		}
	}
	return collides;
}

void Board::_movePieceDown() {
	m_currentPieceCell += BOARD_WIDTH;
	m_currentPiece->setPosition(
		_getWorldX(m_currentPieceCell),
		_getWorldY(m_currentPieceCell),
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
