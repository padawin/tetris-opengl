#include "Board.hpp"
#include "PieceFactory.hpp"

void Board::_init() {
	generateNextPiece();
}

void Board::generateNextPiece() {
	m_nextPiece = std::shared_ptr<Piece>(PieceFactory::create());
	m_nextPiece->setPosition(NEXT_PIECE_X, NEXT_PIECE_Y, NEXT_PIECE_Z);
}

void Board::movePieceSide(unsigned int direction) {
	if (m_currentPiece == nullptr) {
		return;
	}

	if (collides(m_currentPieceCell, TOUCHES, direction)) {
		return;
	}

	int distance = 0;
	if (direction == DIRECTION_LEFT) {
		distance = -1;
	}
	else if (direction == DIRECTION_RIGHT) {
		distance = 1;
	}
	else if (direction == DIRECTION_BACK) {
		distance = -BOARD_DEPTH;
	}
	else if (direction == DIRECTION_FRONT) {
		distance = BOARD_DEPTH;
	}
	_moveCurrentPiece(distance);
	_updateGhost();
}

void Board::movePieceDown() {
	_moveCurrentPiece(-BOARD_WIDTH * BOARD_DEPTH);
}

void Board::setCurrentPiece() {
	m_currentPiece = m_nextPiece;
	m_currentPiece->initGhost();
	m_currentPieceCell = BOARD_SIZE - BOARD_WIDTH / 2;
	int maxDistanceFromTop = _getCurrentPieceTopOverlap();

	// Move the piece down so that it in not out of the board
	_moveCurrentPiece(-maxDistanceFromTop * BOARD_WIDTH * BOARD_DEPTH);
	_updateGhost();
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

void Board::_moveCurrentPiece(int cellDelta) {
	m_currentPieceCell += cellDelta;
	m_currentPiece->setPosition(
		_getWorldX(m_currentPieceCell),
		_getWorldY(m_currentPieceCell),
		_getWorldZ(m_currentPieceCell)
	);
}

void Board::_updateGhost() {
	int ghostIndex = m_currentPieceCell;
	while (!collides(ghostIndex, TOUCHES, DIRECTION_DOWN)) {
		ghostIndex -= BOARD_WIDTH*BOARD_DEPTH;
	}
	m_currentPiece->getGhost()->setPosition(
		_getWorldX(ghostIndex),
		_getWorldY(ghostIndex),
		_getWorldZ(ghostIndex)
	);
}

int Board::_getGridX(int cellIndex) const {
	return cellIndex % BOARD_WIDTH;
}

int Board::_getGridY(int cellIndex) const {
	return cellIndex / (BOARD_WIDTH * BOARD_DEPTH);
}

int Board::_getGridZ(int cellIndex) const {
	return (cellIndex / BOARD_WIDTH) % BOARD_DEPTH;
}

float Board::_getWorldX(int cellIndex) const {
	return m_position.x + (float) _getGridX(cellIndex) * CELL_WIDTH;
}

float Board::_getWorldY(int cellIndex) const {
	return m_position.y + (float) _getGridY(cellIndex) * CELL_HEIGHT;
}

float Board::_getWorldZ(int cellIndex) const {
	return m_position.z + (float) _getGridZ(cellIndex) * CELL_DEPTH;
}

bool Board::collides(int cellIndex, CollisionType type, unsigned int directions) const {
	int currentPieceX = _getGridX(cellIndex);
	int currentPieceY = _getGridY(cellIndex);
	int currentPieceZ = _getGridZ(cellIndex);
	int isDown = directions & DIRECTION_DOWN;
	int isUp = directions & DIRECTION_UP;
	int isLeft = directions & DIRECTION_LEFT;
	int isRight = directions & DIRECTION_RIGHT;
	int isBack = directions & DIRECTION_BACK;
	int isFront = directions & DIRECTION_FRONT;
	int distance = type == TOUCHES ? 1 : 0;
	for (auto block : m_currentPiece->getBlocks()) {
		if ((isLeft && !_isValid(currentPieceX + block.x - distance, currentPieceY + block.y, currentPieceZ + block.z))
			|| (isRight && !_isValid(currentPieceX + block.x + distance, currentPieceY + block.y, currentPieceZ + block.z))
			|| (isDown && !_isValid(currentPieceX + block.x, currentPieceY + block.y - distance, currentPieceZ + block.z))
			|| (isUp && !_isValid(currentPieceX + block.x, currentPieceY + block.y + distance, currentPieceZ + block.z))
			|| (isBack && !_isValid(currentPieceX + block.x, currentPieceY + block.y, currentPieceZ + block.z - distance))
			|| (isFront && !_isValid(currentPieceX + block.x, currentPieceY + block.y, currentPieceZ + block.z + distance))
		) {
			return true;
		}
	}
	return false;
}

bool Board::_isValid(int x, int y, int z) const {
	if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT || z < 0 || z >= BOARD_DEPTH) {
	   return false;
	}
	int cellIndex = _getCellIndex(x, y, z);
	return m_pieces[cellIndex] == nullptr;
}

void Board::createPlacedPieces() {
	for (auto block : m_currentPiece->getBlocks()) {
		int pieceCell = m_currentPieceCell + _getCellIndex(block.x, block.y, block.z);
		m_pieces[pieceCell] = std::shared_ptr<Piece>(PieceFactory::createPlaced());
		m_pieces[pieceCell]->setPosition(
			_getWorldX(pieceCell),
			_getWorldY(pieceCell),
			_getWorldZ(pieceCell)
		);
	}
	m_currentPiece = nullptr;
}

int Board::_getCellIndex(int x, int y, int z) const {
	return z * BOARD_WIDTH + y * BOARD_WIDTH * BOARD_DEPTH + x;
}

void Board::_render(std::shared_ptr<Camera> camera, std::shared_ptr<Camera> cameraUI) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		_renderPiece(camera, m_pieces[i]);
	}
	_renderPiece(camera, m_currentPiece);
	_renderPiece(cameraUI, m_nextPiece);
}

void Board::_renderPiece(std::shared_ptr<Camera> camera, std::shared_ptr<Piece> piece) {
	if (piece != nullptr) {
		piece->render(camera, &m_pieceRenderer);
	}
}

int Board::getCurrentPieceCellIndex() const {
	return m_currentPieceCell;
}

void Board::rotatePiece() {
	if (m_currentPiece == nullptr) {
		return;
	}

	m_currentPiece->rotate(1);
	if (collides(m_currentPieceCell, OVERLAPS, DIRECTION_DOWN | DIRECTION_UP | DIRECTION_LEFT | DIRECTION_RIGHT)) {
		m_currentPiece->rotate(-1);
	}
	_updateGhost();
}

int Board::countFullLines() const {
	int fullLinesCount = 0;
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
			fullLinesCount++;
		}
	}
	return fullLinesCount;
}

void Board::removeFullLines() {
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

void Board::groupBlocks() {
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
						_getWorldZ(newCellIndex)
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
