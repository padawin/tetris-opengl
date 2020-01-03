#include <iostream>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "Rules.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "PieceFactory.hpp"

const float TIME_BETWEEN_PIECE_SIDE_MOVE = 0.1f; // seconds
const float TIME_BETWEEN_ACTIONS = 0.75f; // seconds
const float TURBO_TIME_BETWEEN_ACTIONS = 0.05f; // seconds

void Rules::handleUserEvents(UserActions &userActions, Board &board) {
	_setTurbo(m_state == PIECE_FALLS && userActions.getActionState("TURBO"));
	_rotatePiece(userActions.getActionState("ROTATE"), board);

	if (glfwGetTime() - m_fLastPieceSideMove < TIME_BETWEEN_PIECE_SIDE_MOVE) {
		return;
	}

	if (userActions.getActionState("LEFT")) {
		board.movePieceSide(DIRECTION_LEFT);
		m_fLastPieceSideMove = glfwGetTime();
	}
	else if (userActions.getActionState("RIGHT")) {
		board.movePieceSide(DIRECTION_RIGHT);
		m_fLastPieceSideMove = glfwGetTime();
	}
}

void Rules::_setTurbo(bool turbo) {
	m_bTurbo = turbo;
}

void Rules::_rotatePiece(bool rotatePressed, Board &board) {
	if (!rotatePressed) {
		m_bRotatedPressed = false;
		return;
	}

	if (!m_bRotatedPressed) {
		board.rotatePiece();
		m_bRotatedPressed = true;
	}
}

void Rules::update(Board &board) {
	double timeBetweenActions = m_bTurbo ? TURBO_TIME_BETWEEN_ACTIONS : TIME_BETWEEN_ACTIONS;
	if (glfwGetTime() - m_fLastActionTime >= timeBetweenActions) {
		if (m_state == GENERATE_PIECE) {
			board.setCurrentPiece();
			board.generateNextPiece();
			if (board.collides(board.getCurrentPieceCellIndex(), OVERLAPS, DIRECTION_DOWN)) {
				m_state = LOST;
			}
			else {
				m_state = PIECE_FALLS;
			}
		}
		else if (m_state == PIECE_FALLS) {
			if (board.collides(board.getCurrentPieceCellIndex(), TOUCHES, DIRECTION_DOWN)) {
				board.createPlacedPieces();
				int fullLinesCount = board.countFullLines();
				if (fullLinesCount > 0) {
					m_state = REMOVE_FULL_LINES;
				}
				else {
					m_state = GENERATE_PIECE;
				}
			}
			else {
				board.movePieceDown();
			}
		}
		else if (m_state == REMOVE_FULL_LINES) {
			int fullLinesCount = board.countFullLines();
			if (fullLinesCount > 0) {
				board.removeFullLines();
				_addPoints(fullLinesCount);
				_levelUp(fullLinesCount);
				m_state = MOVE_PIECES_DOWN;
			}
			else {
				m_state = GENERATE_PIECE;
			}
		}
		else if (m_state == MOVE_PIECES_DOWN) {
			board.groupBlocks();
			m_state = GENERATE_PIECE;
		}
		m_fLastActionTime = glfwGetTime();
	}
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
