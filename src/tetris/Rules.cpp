#include <iostream>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "Rules.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "PieceFactory.hpp"

const float TIME_BETWEEN_PIECE_SIDE_MOVE = 0.07f; // seconds
const float BASE_TIME_BETWEEN_ACTIONS = 0.75f; // seconds
const float TIME_REDUCTION_PER_LEVEL = 0.1f; // percent
const float TURBO_TIME_COEF = 9.0f; // coef

bool Rules::playerCanMovePiece() const {
	return glfwGetTime() - m_fLastPieceSideMove > TIME_BETWEEN_PIECE_SIDE_MOVE;
}

void Rules::setPlayerMovedPiece() {
	m_fLastPieceSideMove = glfwGetTime();
}

void Rules::setTurbo(bool turbo) {
	m_bTurbo = m_state == PIECE_FALLS && turbo;
}

void Rules::rotatePiece(bool rotatePressed, std::shared_ptr<Board> board) {
	if (!rotatePressed) {
		m_bRotatedPressed = false;
		return;
	}

	if (!m_bRotatedPressed) {
		board->rotatePiece();
		m_bRotatedPressed = true;
	}
}

void Rules::update(std::shared_ptr<Board> board) {
	if (glfwGetTime() - m_fLastActionTime >= _getTimeBetweenActions()) {
		if (m_state == GENERATE_PIECE) {
			_generatePiece(board);
		}
		else if (m_state == PIECE_FALLS) {
			_pieceFall(board);
		}
		else if (m_state == REMOVE_FULL_LINES) {
			_removeFullLines(board);
		}
		else if (m_state == MOVE_PIECES_DOWN) {
			_movePieceDown(board);
		}
		m_fLastActionTime = glfwGetTime();
	}
}

double Rules::_getTimeBetweenActions() const {
	if (m_state != PIECE_FALLS) {
		return BASE_TIME_BETWEEN_ACTIONS;
	}

	// cap level to 10, after 10 the speed does not increase further
	// this allows each level to increase of a 10th the speed of the pieces
	float level = m_iLevel <= 10 ? (float) m_iLevel : 10.0f;
	// calculate the time based on the level
	double t = BASE_TIME_BETWEEN_ACTIONS * (1.0f - level * TIME_REDUCTION_PER_LEVEL);
	// reduce the time if the turbo mode is on
	t = t / (m_bTurbo ? TURBO_TIME_COEF : 1);
	return t;
}

void Rules::_generatePiece(std::shared_ptr<Board> board) {
	board->setCurrentPiece();
	board->generateNextPiece();
	if (board->collides(board->getCurrentPieceCellIndex(), OVERLAPS, DIRECTION_DOWN)) {
		m_state = LOST;
	}
	else {
		m_state = PIECE_FALLS;
	}
}

void Rules::_pieceFall(std::shared_ptr<Board> board) {
	if (board->collides(board->getCurrentPieceCellIndex(), TOUCHES, DIRECTION_DOWN)) {
		board->createPlacedPieces();
		int fullLinesCount = board->countFullLines();
		if (fullLinesCount > 0) {
			m_state = REMOVE_FULL_LINES;
		}
		else {
			m_state = GENERATE_PIECE;
		}
	}
	else {
		board->movePieceDown();
	}
}

void Rules::_removeFullLines(std::shared_ptr<Board> board) {
	int fullLinesCount = board->countFullLines();
	if (fullLinesCount > 0) {
		board->removeFullLines();
		_addPoints(fullLinesCount);
		_levelUp(fullLinesCount);
		m_state = MOVE_PIECES_DOWN;
	}
	else {
		m_state = GENERATE_PIECE;
	}
}

void Rules::_movePieceDown(std::shared_ptr<Board> board) {
	board->groupBlocks();
	m_state = GENERATE_PIECE;
}

void Rules::_addPoints(int linesRemovedCount) {
	int basePoints = 0;
	switch (linesRemovedCount) {
		case 1:
			basePoints = 40;
			break;
		case 2:
			basePoints = 100;
			break;
		case 3:
			basePoints = 300;
			break;
		case 4:
			basePoints = 1200;
			break;
		default:
			std::cerr << "Unhandled number of lines removed: " << linesRemovedCount << std::endl;
			break;
	}
	int points = basePoints * (m_iLevel + 1);
	m_iPoints += points;
	if (points > 0) {
		printf(
			"%d lines removed, +%d points, total: %d lines, %d points\n",
			linesRemovedCount, points, m_iTotalLinesRemoved, m_iPoints
		);
	}
}

void Rules::_levelUp(int linesRemovedCount) {
	int currentTens = (m_iTotalLinesRemoved / 10) % 10;
	m_iTotalLinesRemoved += linesRemovedCount;
	int newTens = (m_iTotalLinesRemoved / 10) % 10;
	int delta = newTens - currentTens;
	m_iLevel += delta;
	if (delta > 0) {
		std::cout << "Level up to: " << m_iLevel << std::endl;
	}
}

bool Rules::hasLost() const {
	return m_state == LOST;
}
