#ifndef __BOLT_PIECE__
#define __BOLT_PIECE__

#include "../Piece.hpp"

class BoltPiece : public Piece {
	protected:
	void _create();

	public:
	void init();
};

#endif
