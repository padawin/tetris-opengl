#include "PieceFactory.hpp"
#include "pieces/T.hpp"
#include "pieces/L.hpp"
#include "pieces/InvertedL.hpp"
#include "pieces/S.hpp"
#include "pieces/Z.hpp"
#include "pieces/Bar.hpp"
#include "pieces/Square.hpp"
#include "pieces/Placed.hpp"
#include <stdlib.h> // rand

std::shared_ptr<Piece> PieceFactory::create() {
	int p = rand() % 7;
	std::shared_ptr<Piece> piece;
	if (p == 0) {
		piece = std::shared_ptr<Piece>(new LPiece());
	}
	else if (p == 1) {
		piece = std::shared_ptr<Piece>(new InvertedLPiece());
	}
	else if (p == 2) {
		piece = std::shared_ptr<Piece>(new SPiece());
	}
	else if (p == 3) {
		piece = std::shared_ptr<Piece>(new ZPiece());
	}
	else if (p == 4) {
		piece = std::shared_ptr<Piece>(new TPiece());
	}
	else if (p == 5) {
		piece = std::shared_ptr<Piece>(new BarPiece());
	}
	else if (p == 6) {
		piece = std::shared_ptr<Piece>(new SquarePiece());
	}
	piece->init();
	piece->rotate(rand() % 4);
	return piece;
}

std::shared_ptr<Piece> PieceFactory::createPlaced() {
	std::shared_ptr<Piece> piece = std::shared_ptr<Piece>(new PlacedPiece());
	piece->init();
	return piece;
}
