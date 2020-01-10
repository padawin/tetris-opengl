#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "game/SceneState.hpp"
#include "game/UserActions.hpp"
#include "tetris/Rules.hpp"
#include "tetris/Board.hpp"

class GameScene : public SceneState {
	private:
	Rules m_rules;

	protected:
	std::shared_ptr<Board> m_board;
	virtual void _initCamera() = 0;
	virtual void _handleEvents();
	virtual unsigned int _getLeft() = 0;
	virtual unsigned int _getRight() = 0;

	public:
	GameScene(UserActions &userActions, std::shared_ptr<Board> board);
	bool onEnter();
	void update(StateMachine<SceneState> &stateMachine);
	virtual void render() = 0;
};

#endif
