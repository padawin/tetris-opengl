#include <iostream>
#include <GLFW/glfw3.h>
#include "Board.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "PieceFactory.hpp"

const float TIME_BETWEEN_ACTIONS = 0.75f; // seconds
const float TURBO_TIME_BETWEEN_ACTIONS = 0.05f; // seconds

const unsigned int DIRECTION_DOWN = 0x01;
const unsigned int DIRECTION_LEFT = 0x02;
const unsigned int DIRECTION_RIGHT = 0x04;

void Board::init() {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		m_cells[i].init();
		m_cells[i].setPosition(_getWorldX(i), _getWorldY(i), 0.0f);
		m_cells[i].update();
	}
}

int Board::_getGridX(int cellIndex) const {
	return cellIndex % BOARD_WIDTH;
}

int Board::_getGridY(int cellIndex) const {
	return cellIndex / BOARD_WIDTH;
}

float Board::_getWorldX(int cellIndex) const {
	return m_position.x + (float) _getGridX(cellIndex) * CELL_WIDTH;
}

float Board::_getWorldY(int cellIndex) const {
	return m_position.y + (float) _getGridY(cellIndex) * CELL_HEIGHT;
}

void Board::handleUserEvents(UserActions &userActions) {
	setTurbo(userActions.getActionState("TURBO"));
}

void Board::update() {
	double timeBetweenActions = m_bTurbo ? TURBO_TIME_BETWEEN_ACTIONS : TIME_BETWEEN_ACTIONS;
	if (glfwGetTime() - m_fLastActionTime >= timeBetweenActions) {
		if (m_state == GENERATE_PIECE) {
			_generatePiece();
			m_state = PIECE_FALLS;
		}
		else if (m_state == PIECE_FALLS) {
			if (_collides(DIRECTION_DOWN)) {
				_createPlacedPieces();
				m_state = REMOVE_FULL_LINES;
			}
			else {
				_movePieceDown();
			}
		}
		m_fLastActionTime = glfwGetTime();
	}

	if (m_currentPiece != nullptr) {
		m_currentPiece->update();
	}
}

void Board::_generatePiece() {
	m_currentPiece = std::shared_ptr<Piece>(PieceFactory::create());
	m_currentPieceCell = BOARD_SIZE - BOARD_WIDTH / 2;
	int currentPieceCellY = _getGridY(m_currentPieceCell);
	int maxDistanceFromTop = 0;
	int topRow = BOARD_HEIGHT - 1;
	for (auto block : m_currentPiece->getBlocks()) {
		int cellY = currentPieceCellY + block.y;
		int distanceFromTop = cellY - topRow;
		if (distanceFromTop > maxDistanceFromTop) {
			maxDistanceFromTop = distanceFromTop;
		}
	}
	// Move the piece down so that it in not out of the board
	m_currentPieceCell -= maxDistanceFromTop * BOARD_WIDTH;
	m_currentPiece->setPosition(
		_getWorldX(m_currentPieceCell),
		_getWorldY(m_currentPieceCell),
		0.1f
	);
}

bool Board::_collides(unsigned int directions) const {
	int currentPieceX = _getGridX(m_currentPieceCell);
	int currentPieceY = _getGridY(m_currentPieceCell);
	int isDown = directions & DIRECTION_DOWN;
	int isLeft = directions & DIRECTION_LEFT;
	int isRight = directions & DIRECTION_RIGHT;
	for (auto block : m_currentPiece->getBlocks()) {
		if ((isDown && !_isValid(currentPieceX + block.x, currentPieceY + block.y - 1))
			|| (isLeft && !_isValid(currentPieceX + block.x - 1, currentPieceY + block.y))
			|| (isRight && !_isValid(currentPieceX + block.x + 1, currentPieceY + block.y))
		) {
			return true;
		}
	}
	return false;
}

bool Board::_isValid(int x, int y) const {
	if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
	   return false;
	}
	int cellIndex = y * BOARD_WIDTH + x;
	return m_pieces[cellIndex] == nullptr;
}

void Board::_createPlacedPieces() {
	for (auto block : m_currentPiece->getBlocks()) {
		int pieceCell = m_currentPieceCell + block.x + block.y * BOARD_WIDTH;
		m_pieces[pieceCell] = std::shared_ptr<Piece>(PieceFactory::createPlaced());
		m_pieces[pieceCell]->setPosition(
			_getWorldX(pieceCell),
			_getWorldY(pieceCell),
			0.1f
		);
		m_pieces[pieceCell]->update();
	}
	m_currentPiece = nullptr;
}

void Board::_movePieceDown() {
	m_currentPieceCell -= BOARD_WIDTH;
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
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (m_pieces[i] != nullptr) {
			m_pieces[i]->render(camera);
		}
	}
	if (m_currentPiece != nullptr) {
		m_currentPiece->render(camera);
	}
}

void Board::setTurbo(bool turbo) {
	m_bTurbo = turbo;
}
