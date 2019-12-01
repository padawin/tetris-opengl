#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include <vector>
#include <memory>
#include "game/SceneState.hpp"
#include "game/GameObject.hpp"
#include "game/UserActions.hpp"

class GameScene : public SceneState {
	private:
	std::shared_ptr<GameObject> m_player = 0;
	std::vector<std::shared_ptr<GameObject>> m_vObjects = {};

	public:
	GameScene(UserActions &userActions);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
