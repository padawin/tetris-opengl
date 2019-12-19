#include "GameOver.hpp"

std::string GameOverScene::getStateID() const {
	return "GameOverScene";
}

GameOverScene::GameOverScene(UserActions &userActions) :
	SceneState(userActions)
{
}

bool GameOverScene::onEnter() {
	return true;
}

void GameOverScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
}

void GameOverScene::render() {
}
