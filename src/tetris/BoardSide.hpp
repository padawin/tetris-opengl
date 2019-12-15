#ifndef __BOARD_SIDE__
#define __BOARD_SIDE__

#include "game/GameObject.hpp"

class BoardSide : public GameObject {
	private:
	int m_iHeight;

	public:
	BoardSide(int height);
	void init();
};

#endif
