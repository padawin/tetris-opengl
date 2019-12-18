#include <iostream>
#include <GLFW/glfw3.h>
#include "Board.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "PieceFactory.hpp"

const float TIME_BETWEEN_PIECE_SIDE_MOVE = 0.1f; // seconds
const float TIME_BETWEEN_ACTIONS = 0.75f; // seconds
const float TURBO_TIME_BETWEEN_ACTIONS = 0.05f; // seconds

const unsigned int DIRECTION_DOWN = 0x01;
const unsigned int DIRECTION_UP = 0x02;
const unsigned int DIRECTION_LEFT = 0x04;
const unsigned int DIRECTION_RIGHT = 0x08;

void Board::init() {
	m_left.setPosition(-1.0f, BOARD_HEIGHT / 2 - 0.5f, 0.0f);
	m_right.setPosition(BOARD_WIDTH, BOARD_HEIGHT / 2 - 0.5f, 0.0f);
	m_left.init();
	m_right.init();
	_generateNextPiece();
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
	setTurbo(m_state == PIECE_FALLS && userActions.getActionState("TURBO"));
	_rotatePiece(userActions.getActionState("ROTATE"));

	if (glfwGetTime() - m_fLastPieceSideMove < TIME_BETWEEN_PIECE_SIDE_MOVE) {
		return;
	}

	if (userActions.getActionState("LEFT")) {
		_movePiece(-1);
		m_fLastPieceSideMove = glfwGetTime();

	}
	else if (userActions.getActionState("RIGHT")) {
		_movePiece(1);
		m_fLastPieceSideMove = glfwGetTime();
	}
}

void Board::update() {
	double timeBetweenActions = m_bTurbo ? TURBO_TIME_BETWEEN_ACTIONS : TIME_BETWEEN_ACTIONS;
	if (glfwGetTime() - m_fLastActionTime >= timeBetweenActions) {
		if (m_state == GENERATE_PIECE) {
			_setCurrentPiece();
			_generateNextPiece();
			m_state = PIECE_FALLS;
		}
		else if (m_state == PIECE_FALLS) {
			if (_collides(m_currentPieceCell, TOUCHES, DIRECTION_DOWN)) {
				_createPlacedPieces();
				m_state = REMOVE_FULL_LINES;
			}
			else {
				_moveCurrentPiece(-BOARD_WIDTH);
			}
		}
		else if (m_state == REMOVE_FULL_LINES) {
			if (_hasFullLines()) {
				_removeFullLines();
				m_state = MOVE_PIECES_DOWN;
			}
			else {
				m_state = GENERATE_PIECE;
			}
		}
		else if (m_state == MOVE_PIECES_DOWN) {
			_groupBlocks();
			m_state = GENERATE_PIECE;
		}
		m_fLastActionTime = glfwGetTime();
	}
}

void Board::_generateNextPiece() {
	m_nextPiece = std::shared_ptr<Piece>(PieceFactory::create());
	m_nextPiece->setPosition(NEXT_PIECE_X, NEXT_PIECE_Y, 0.1f);
}

void Board::_setCurrentPiece() {
	m_currentPiece = m_nextPiece;
	m_currentPiece->initGhost();
	m_currentPieceCell = BOARD_SIZE - BOARD_WIDTH / 2;
	int maxDistanceFromTop = _getCurrentPieceTopOverlap();

	// Move the piece down so that it in not out of the board
	_moveCurrentPiece(-maxDistanceFromTop * BOARD_WIDTH);
	_updateGhost();
}

void Board::_moveCurrentPiece(int cellDelta) {
	m_currentPieceCell += cellDelta;
	m_currentPiece->setPosition(
		_getWorldX(m_currentPieceCell),
		_getWorldY(m_currentPieceCell),
		0.1f
	);
}

int Board::_getCurrentPieceTopOverlap() const {
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
	return maxDistanceFromTop;
}

bool Board::_collides(int cellIndex, CollisionType type, unsigned int directions) const {
	int currentPieceX = _getGridX(cellIndex);
	int currentPieceY = _getGridY(cellIndex);
	int isDown = directions & DIRECTION_DOWN;
	int isUp = directions & DIRECTION_UP;
	int isLeft = directions & DIRECTION_LEFT;
	int isRight = directions & DIRECTION_RIGHT;
	int distance = type == TOUCHES ? 1 : 0;
	for (auto block : m_currentPiece->getBlocks()) {
		if ((isDown && !_isValid(currentPieceX + block.x, currentPieceY + block.y - distance))
			|| (isUp && !_isValid(currentPieceX + block.x, currentPieceY + block.y + distance))
			|| (isLeft && !_isValid(currentPieceX + block.x - distance, currentPieceY + block.y))
			|| (isRight && !_isValid(currentPieceX + block.x + distance, currentPieceY + block.y))
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
	}
	m_currentPiece = nullptr;
}

void Board::render(std::shared_ptr<Camera> camera) {
	m_left.render(camera);
	m_right.render(camera);
	for (int i = 0; i < BOARD_SIZE; ++i) {
		_renderPiece(camera, m_pieces[i]);
	}
	_renderPiece(camera, m_currentPiece);
	_renderPiece(camera, m_nextPiece);
}

void Board::_renderPiece(std::shared_ptr<Camera> camera, std::shared_ptr<Piece> piece) {
	if (piece != nullptr) {
		piece->render(camera, &m_pieceRenderer);
	}
}

void Board::setTurbo(bool turbo) {
	m_bTurbo = turbo;
}

void Board::_movePiece(int direction) {
	if (m_currentPiece == nullptr) {
		return;
	}

	if (_collides(m_currentPieceCell, TOUCHES, direction == -1 ? DIRECTION_LEFT : DIRECTION_RIGHT)) {
		return;
	}

	_moveCurrentPiece(direction);
	_updateGhost();
}

void Board::_rotatePiece(bool rotatePressed) {
	if (m_currentPiece == nullptr) {
		return;
	}

	if (!rotatePressed) {
		m_bRotatedPressed = false;
		return;
	}

	if (!m_bRotatedPressed) {
		m_currentPiece->rotate(1);
		if (_collides(m_currentPieceCell, OVERLAPS, DIRECTION_DOWN | DIRECTION_UP | DIRECTION_LEFT | DIRECTION_RIGHT)) {
			m_currentPiece->rotate(-1);
		}
		m_bRotatedPressed = true;
		_updateGhost();
	}
}

bool Board::_hasFullLines() const {
	for (int line = 0; line < BOARD_HEIGHT; line++) {
		bool lineIsFull = true;
		for (int column = 0; column < BOARD_WIDTH; column++) {
			int cellIndex = line * BOARD_WIDTH + column;
			if (m_pieces[cellIndex] == nullptr) {
				lineIsFull = false;
				break;
			}
		}
		if (lineIsFull) {
			return true;
		}
	}
	return false;
}

void Board::_removeFullLines() {
	for (int line = 0; line < BOARD_HEIGHT; line++) {
		bool lineIsFull = true;
		for (int column = 0; column < BOARD_WIDTH; column++) {
			int cellIndex = line * BOARD_WIDTH + column;
			if (m_pieces[cellIndex] == nullptr) {
				lineIsFull = false;
				break;
			}
		}
		if (lineIsFull) {
			for (int column = 0; column < BOARD_WIDTH; column++) {
				int cellIndex = line * BOARD_WIDTH + column;
				m_pieces[cellIndex] = nullptr;
			}
		}
	}
}

void Board::_groupBlocks() {
	int currY = 0;
	for (int line = 0; line < BOARD_HEIGHT; line++) {
		bool lineIsEmpty = true;
		for (int column = 0; column < BOARD_WIDTH; column++) {
			int cellIndex = line * BOARD_WIDTH + column;
			if (m_pieces[cellIndex] != nullptr) {
				lineIsEmpty = false;
				break;
			}
		}
		if (!lineIsEmpty) {
			for (int column = 0; column < BOARD_WIDTH; column++) {
				int oldCellIndex = line * BOARD_WIDTH + column;
				int newCellIndex = currY * BOARD_WIDTH + column;
				m_pieces[newCellIndex] = m_pieces[oldCellIndex];
				if (m_pieces[newCellIndex] != nullptr) {
					m_pieces[newCellIndex]->setPosition(
						_getWorldX(newCellIndex),
						_getWorldY(newCellIndex),
						0.1f
					);
					m_pieces[newCellIndex]->update();
				}
			}
			currY++;
		}
	}
	for (; currY < BOARD_HEIGHT; currY++) {
		for (int column = 0; column < BOARD_WIDTH; column++) {
				int newCellIndex = currY * BOARD_WIDTH + column;
				m_pieces[newCellIndex] = nullptr;
		}
	}
}

void Board::_updateGhost() {
	int ghostIndex = m_currentPieceCell;
	while (!_collides(ghostIndex, TOUCHES, DIRECTION_DOWN)) {
		ghostIndex -= BOARD_WIDTH;
	}
	m_currentPiece->getGhost()->setPosition(
		_getWorldX(ghostIndex),
		_getWorldY(ghostIndex),
		-0.1f
	);
}
