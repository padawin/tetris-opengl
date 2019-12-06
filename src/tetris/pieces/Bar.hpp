#ifndef __BAR_PIECE__
#define __BAR_PIECE__

#include "../Piece.hpp"

class BarPiece : public Piece {
	protected:
	void _create();

	public:
	void init();
};

#endif
