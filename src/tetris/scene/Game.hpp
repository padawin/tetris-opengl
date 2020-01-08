#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "game/SceneState.hpp"
#include "game/UserActions.hpp"
#include "tetris/Rules.hpp"
#include "tetris/Board.hpp"

class GameScene : public SceneState {
	private:
	Rules m_rules;
	Board m_board;
	std::shared_ptr<Camera> m_cameraUI = nullptr;

	public:
	GameScene(UserActions &userActions);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	void render();
	std::string getStateID() const;
};

#endif
