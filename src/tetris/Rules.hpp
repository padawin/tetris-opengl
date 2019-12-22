#ifndef __RULES__
#define __RULES__

#include "game/UserActions.hpp"
#include "Board.hpp"

enum BoardState {
	GENERATE_PIECE,
	PIECE_FALLS,
	REMOVE_FULL_LINES,
	MOVE_PIECES_DOWN,
	LOST
};

class Rules {
	private:
	BoardState m_state = GENERATE_PIECE;
	double m_fLastPieceSideMove = 0.0f;
	double m_fLastActionTime = 0.0f;
	bool m_bTurbo = false;
	bool m_bRotatedPressed = false;

	void _setTurbo(bool turbo);
	void _rotatePiece(bool rotatePressed, Board &board);

	public:
	void handleUserEvents(UserActions &userActions, Board &board);
	void update(Board &board);

	bool hasLost() const;
};

#endif
