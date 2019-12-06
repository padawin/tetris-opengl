#ifndef __PIECE__
#define __PIECE__

#include <vector>
#include "game/GameObject.hpp"

class Piece : public GameObject {
	protected:
	std::vector<std::pair<int, int>> m_vBlockCoordinates = {};

	virtual void _create() = 0;

	public:
	virtual ~Piece() {}
	virtual std::vector<std::pair<int, int>> getBlocks() const;
};

#endif
