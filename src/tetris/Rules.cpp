#include <iostream>
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
				m_state = REMOVE_FULL_LINES;
			}
			else {
				board.movePieceDown();
			}
		}
		else if (m_state == REMOVE_FULL_LINES) {
			if (board.hasFullLines()) {
				board.removeFullLines();
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

bool Rules::hasLost() const {
	return m_state == LOST;
}
