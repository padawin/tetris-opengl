#include "PieceFactory.hpp"
#include "pieces/L.hpp"
#include "pieces/Bolt.hpp"
#include "pieces/Bar.hpp"
#include "pieces/Square.hpp"
#include "pieces/Placed.hpp"
#include <stdlib.h> // rand

std::shared_ptr<Piece> PieceFactory::create() {
	int p = rand() % 4;
	std::shared_ptr<Piece> piece;
	if (p == 0) {
		piece = std::shared_ptr<Piece>(new LPiece());
	}
	else if (p == 1) {
		piece = std::shared_ptr<Piece>(new BoltPiece());
	}
	else if (p == 2) {
		piece = std::shared_ptr<Piece>(new BarPiece());
	}
	else if (p == 3) {
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
