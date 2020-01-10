#ifndef __2D_GAME_SCENE__
#define __2D_GAME_SCENE__

#include "Game.hpp"

class Game2DScene : public GameScene {
	protected:
	void _initCamera();
	unsigned int _getLeft();
	unsigned int _getRight();

	public:
	Game2DScene(UserActions &userActions);
	std::string getStateID() const;
	void render();
};

#endif
