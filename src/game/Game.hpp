#ifndef __GAME__
#define __GAME__

#include <vector>
#include <memory>
#include "game/GameObject.hpp"

class Game {
	private:
	std::vector<std::shared_ptr<GameObject>> m_vObjects = {};

	public:
	bool init();
	void update();
	void render();
};

#endif
