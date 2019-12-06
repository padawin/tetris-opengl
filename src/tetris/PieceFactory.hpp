#ifndef __PIECE_FACTORY__
#define __PIECE_FACTORY__

#include <memory>
#include "Piece.hpp"

class PieceFactory {
	public:
	static std::shared_ptr<Piece> create();
};

#endif
