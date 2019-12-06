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

int Board::_cellToX(int cellIndex) const {
	return (cellIndex % BOARD_WIDTH) * CELL_WIDTH;
}

int Board::_cellToY(int cellIndex) const {
	int boardTop = BOARD_HEIGHT * CELL_HEIGHT;
	return boardTop - (cellIndex / BOARD_WIDTH) * CELL_HEIGHT;
}

float Board::_getXPosInBoard(int cellIndex) const {
	return m_position.x + (float) _cellToX(cellIndex);
}

float Board::_getYPosInBoard(int cellIndex) const {
	return m_position.y + (float) _cellToY(cellIndex);
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
	m_currentPieceCell = BOARD_WIDTH / 2;
	int currentPieceCellY = _cellToY(m_currentPieceCell);
	int delta = 0;
	for (auto block : m_currentPiece->getBlocks()) {
		int cellY = currentPieceCellY + block.second;
		if (delta < cellY - BOARD_HEIGHT) {
			delta = cellY - BOARD_HEIGHT;
		}
	}
	m_currentPieceCell += delta * BOARD_WIDTH;
	m_currentPiece->setPosition(
		_getXPosInBoard(m_currentPieceCell),
		_getYPosInBoard(m_currentPieceCell),
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
