#ifndef __BOARD__
#define __BOARD__

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 18
#define BOARD_SIZE 180

#define CELL_WIDTH 1
#define CELL_HEIGHT 1

#include "game/GameObject.hpp"
#include "BoardCell.hpp"
#include "Piece.hpp"

enum BoardState {
	GENERATE_PIECE,
	PIECE_FALLS
};

//class Piece;
class Board : public GameObject {
	private:
	BoardCell m_cells[BOARD_SIZE];
	//Piece** m_pieces[BOARD_SIZE];
	std::shared_ptr<Piece> m_currentPiece = nullptr;
	// Coordinates as board cells of the point 0 of the current piece
	int m_currentPieceCell = 0;
	BoardState m_state = GENERATE_PIECE;

	void _generatePiece();
	int _cellToX(int cellIndex) const;
	int _cellToY(int cellIndex) const;
	float _getXPosInBoard(int cellIndex) const;
	float _getYPosInBoard(int cellIndex) const;

	public:
	void init();
	void update();
	void render(std::shared_ptr<Camera> camera);
};

#endif
