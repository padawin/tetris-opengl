#ifndef __PLACED_PIECE__
#define __PLACED_PIECE__

#include "../Piece.hpp"

class PlacedPiece : public Piece {
	protected:
	void _create();

	public:
	void init();
};

#endif
