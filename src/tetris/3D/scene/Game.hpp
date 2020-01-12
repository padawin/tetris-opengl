#ifndef __3D_GAME_SCENE__
#define __3D_GAME_SCENE__

#include "tetris/scene/Game.hpp"

class Game3DScene : public GameScene {
	protected:
	std::shared_ptr<Camera> m_cameraUI = nullptr;
	void _initCamera();
	void _handleEvents();
	unsigned int _getLeft();
	unsigned int _getRight();

	public:
	Game3DScene(UserActions &userActions);
	std::string getStateID() const;
	void render();
};

#endif
