#ifndef __RULES__
#define __RULES__

#include "Board.hpp"
#include <memory>

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

	void _addPoints(int linesRemovedCount);
	void _levelUp(int linesRemovedCount);

	double _getTimeBetweenActions() const;

	void _generatePiece(std::shared_ptr<Board> board);
	void _pieceFall(std::shared_ptr<Board> board);
	void _removeFullLines(std::shared_ptr<Board> board);
	void _movePieceDown(std::shared_ptr<Board> board);

	public:
	void update(std::shared_ptr<Board> board);
	void rotatePiece(bool rotatePressed, std::shared_ptr<Board> board);

	bool playerCanMovePiece() const;
	void setPlayerMovedPiece();
	void setTurbo(bool turbo);

	bool hasLost() const;
};

#endif
