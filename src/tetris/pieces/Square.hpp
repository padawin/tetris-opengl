#ifndef __SQUARE_PIECE__
#define __SQUARE_PIECE__

#include "../Piece.hpp"

class SquarePiece : public Piece {
	protected:
	void _create();

	public:
	void init();
};

#endif
