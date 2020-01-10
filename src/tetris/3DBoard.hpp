#ifndef __3DBOARD__
#define __3DBOARD__

#include "Board.hpp"

class Board3D : public Board {
	private:
	GameObject m_frontLeft = GameObject();
	GameObject m_frontRight = GameObject();
	GameObject m_backLeft = GameObject();
	GameObject m_backRight = GameObject();

	public:
	void init();
	void render(std::shared_ptr<Camera> camera, std::shared_ptr<Camera> cameraUI);
};

#endif
