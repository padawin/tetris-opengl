#ifndef __2DBOARD__
#define __2DBOARD__

#include "Board.hpp"

class Board2D : public Board {
	private:
	GameObject m_left = GameObject();
	GameObject m_right = GameObject();

	public:
	void init();
	void render(std::shared_ptr<Camera> camera, std::shared_ptr<Camera> cameraUI);
};

#endif
