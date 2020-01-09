#ifndef __BOARD__
#define __BOARD__

#include <memory>
#include "game/Camera.hpp"
#include "game/GameObject.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "Piece.hpp"

#define BOARD_WIDTH 10
#define BOARD_DEPTH 10
#define BOARD_HEIGHT 18
#define BOARD_SIZE 1800

#define NEXT_PIECE_X BOARD_WIDTH+4
#define NEXT_PIECE_Y 1

#define CELL_WIDTH 1
#define CELL_HEIGHT 1

enum CollisionType {TOUCHES, OVERLAPS};

const unsigned int DIRECTION_DOWN = 0x01;
const unsigned int DIRECTION_UP = 0x02;
const unsigned int DIRECTION_LEFT = 0x04;
const unsigned int DIRECTION_RIGHT = 0x08;

class Board : public GameObject {
	private:
	GameObject m_frontLeft = GameObject();
	GameObject m_frontRight = GameObject();
	GameObject m_backLeft = GameObject();
	GameObject m_backRight = GameObject();
	ObjectRenderer m_sideRenderer = ObjectRenderer();
	ObjectRenderer m_pieceRenderer = ObjectRenderer();
	std::shared_ptr<Piece> m_pieces[BOARD_SIZE];
	std::shared_ptr<Piece> m_currentPiece = nullptr;
	std::shared_ptr<Piece> m_nextPiece = nullptr;
	// Coordinates as board cells of the point 0 of the current piece
	int m_currentPieceCell = 0;

	int _getCurrentPieceTopOverlap() const;
	void _moveCurrentPiece(int cellDelta);
	bool _isValid(int x, int y) const;
	int _getGridX(int cellIndex) const;
	int _getGridY(int cellIndex) const;
	float _getWorldX(int cellIndex) const;
	float _getWorldY(int cellIndex) const;
	void _updateGhost();

	void _renderPiece(std::shared_ptr<Camera> camera, std::shared_ptr<Piece> piece);

	public:
	void init();
	int getCurrentPieceCellIndex() const;
	bool collides(int cellIndex, CollisionType type, unsigned int directions) const;
	void movePieceSide(unsigned int direction);
	void movePieceDown();

	void setCurrentPiece();
	void generateNextPiece();
	void createPlacedPieces();
	void rotatePiece();
	int countFullLines() const;
	void removeFullLines();
	void groupBlocks();

	void render(std::shared_ptr<Camera> camera, std::shared_ptr<Camera> cameraUI);
};

#endif
