#ifndef __BOARD__
#define __BOARD__

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 18
#define BOARD_SIZE 180

#define CELL_WIDTH 1
#define CELL_HEIGHT 1

#include "game/GameObject.hpp"
#include "BoardCell.hpp"

//class Piece;
class Board : public GameObject {
	private:
	BoardCell m_cells[BOARD_SIZE];
	//Piece** m_pieces[BOARD_SIZE];

	public:
	void init();
	void update();
	void render(std::shared_ptr<Camera> camera);
};

#endif
