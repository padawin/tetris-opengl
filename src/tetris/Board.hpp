#ifndef __BOARD__
#define __BOARD__

#include <memory>
#include "game/Camera.hpp"
#include "game/GameObject.hpp"
#include "opengl/ObjectRenderer.hpp"
#include "Piece.hpp"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 18
#ifndef MODE_3D
#define BOARD_DEPTH 1
#define BOARD_SIZE 180
#else
#define BOARD_DEPTH 10
#define BOARD_SIZE 1800
#endif

#define NEXT_PIECE_X BOARD_WIDTH+4
#define NEXT_PIECE_Y 1
#define NEXT_PIECE_Z BOARD_DEPTH+4

#define CELL_WIDTH 1
#define CELL_HEIGHT 1
#define CELL_DEPTH 1

enum CollisionType {TOUCHES, OVERLAPS};

const unsigned int DIRECTION_DOWN = 0x01;
const unsigned int DIRECTION_UP = 0x02;
const unsigned int DIRECTION_LEFT = 0x04;
const unsigned int DIRECTION_RIGHT = 0x08;
const unsigned int DIRECTION_FRONT = 0x10;
const unsigned int DIRECTION_BACK = 0x20;

const glm::vec4 COLOR_SIDE = glm::vec4(0.64f, 0.64f, 0.64f, 1.0f);

class Board : public GameObject {
	private:
	std::shared_ptr<Piece> m_pieces[BOARD_SIZE];
	std::shared_ptr<Piece> m_currentPiece = nullptr;
	std::shared_ptr<Piece> m_nextPiece = nullptr;
	// Coordinates as board cells of the point 0 of the current piece
	int m_currentPieceCell = 0;

	int _getCurrentPieceTopOverlap() const;
	int _getCellIndex(int x, int y, int z) const;
	void _moveCurrentPiece(int cellDelta);
	bool _isValid(int x, int y, int z) const;
	int _getGridX(int cellIndex) const;
	int _getGridY(int cellIndex) const;
	int _getGridZ(int cellIndex) const;
	float _getWorldX(int cellIndex) const;
	float _getWorldY(int cellIndex) const;
	float _getWorldZ(int cellIndex) const;
	void _updateGhost();

	void _renderPiece(std::shared_ptr<Camera> camera, std::shared_ptr<Piece> piece);

	protected:
	ObjectRenderer m_sideRenderer = ObjectRenderer();
	ObjectRenderer m_pieceRenderer = ObjectRenderer();
	virtual void _init();
	virtual void _render(std::shared_ptr<Camera> camera, std::shared_ptr<Camera> cameraUI);

	public:
	virtual ~Board() {}
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

	virtual void init() = 0;
	virtual void render(std::shared_ptr<Camera> camera, std::shared_ptr<Camera> cameraUI) = 0;
};

#endif
