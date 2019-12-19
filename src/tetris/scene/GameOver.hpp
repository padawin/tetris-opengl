#ifndef __GAME_OVER_SCENE__
#define __GAME_OVER_SCENE__

#include "game/SceneState.hpp"
#include "game/UserActions.hpp"

class GameOverScene : public SceneState {
	public:
	GameOverScene(UserActions &userActions);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
