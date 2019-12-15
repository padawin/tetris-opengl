#ifndef __BOARD__
#define __BOARD__

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 18
#define BOARD_SIZE 180

#define NEXT_PIECE_X BOARD_WIDTH+4
#define NEXT_PIECE_Y 1

#define CELL_WIDTH 1
#define CELL_HEIGHT 1

#include "game/UserActions.hpp"
#include "game/GameObject.hpp"
#include "BoardSide.hpp"
#include "Piece.hpp"

enum BoardState {
	GENERATE_PIECE,
	PIECE_FALLS,
	REMOVE_FULL_LINES,
	MOVE_PIECES_DOWN
};

enum CollisionType {TOUCHES, OVERLAPS};

//class Piece;
class Board : public GameObject {
	private:
	BoardSide m_left = BoardSide(BOARD_HEIGHT);
	BoardSide m_right = BoardSide(BOARD_HEIGHT);
	std::shared_ptr<Piece> m_pieces[BOARD_SIZE];
	std::shared_ptr<Piece> m_currentPiece = nullptr;
	std::shared_ptr<Piece> m_nextPiece = nullptr;
	// Coordinates as board cells of the point 0 of the current piece
	int m_currentPieceCell = 0;
	BoardState m_state = GENERATE_PIECE;
	double m_fLastPieceSideMove = 0.0f;
	double m_fLastActionTime = 0.0f;
	bool m_bTurbo = false;
	bool m_bRotatedPressed = false;

	void _generateNextPiece();
	void _setCurrentPiece();
	bool _collides(CollisionType type, unsigned int directions) const;
	bool _isValid(int x, int y) const;
	void _createPlacedPieces();
	void _movePieceDown();
	int _getGridX(int cellIndex) const;
	int _getGridY(int cellIndex) const;
	float _getWorldX(int cellIndex) const;
	float _getWorldY(int cellIndex) const;
	void _movePiece(int direction);
	void _rotatePiece(bool rotatePressed);
	bool _hasFullLines() const;
	void _removeFullLines();
	void _groupBlocks();

	public:
	void init();
	void handleUserEvents(UserActions &userActions);
	void update();
	void render(std::shared_ptr<Camera> camera);

	void setTurbo(bool turbo);
};

#endif
