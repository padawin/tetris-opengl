#ifndef __PIECE__
#define __PIECE__

#include <vector>
#include "game/GameObject.hpp"

class Piece : public GameObject {
	protected:
	std::vector<glm::vec2> m_vBlockCoordinates = {};
	// From 0 to 3, represents the quarter of a circle
	int m_iOrientation = 0;

	virtual void _create() = 0;

	public:
	virtual ~Piece() {}
	virtual std::vector<glm::ivec2> getBlocks() const;
	virtual void rotate(int quarter);
};

#endif
