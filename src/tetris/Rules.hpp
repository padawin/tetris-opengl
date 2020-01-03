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

	int m_iPoints = 0;
	int m_iLevel = 0;
	int m_iTotalLinesRemoved = 0;

	void _setTurbo(bool turbo);
	void _rotatePiece(bool rotatePressed, Board &board);
	void _addPoints(int linesRemovedCount);
	void _levelUp(int linesRemovedCount);

	double _getTimeBetweenActions() const;

	void _generatePiece(Board &board);
	void _pieceFall(Board &board);
	void _removeFullLines(Board &board);
	void _movePieceDown(Board &board);

	public:
	void handleUserEvents(UserActions &userActions, Board &board);
	void update(Board &board);

	bool hasLost() const;
};

#endif
