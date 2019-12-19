#include "Game.hpp"
#include "opengl/PerspectiveCamera.hpp"
#include "game/cameraView/Fixed.hpp"
#include "GameOver.hpp"
#include <iostream>

std::string GameScene::getStateID() const {
	return "GameScene";
}

GameScene::GameScene(UserActions &userActions) :
	SceneState(userActions),
	m_board(Board())
{
}

bool GameScene::onEnter() {
	m_board.init();
	setCameraView(std::shared_ptr<CameraView>(new FixedView(glm::vec3(0.0f, 0.0f, -1.0f))));
	m_cameraView->setPosition(glm::vec3(4.5f, 8.5f, 22.4f));

	setCamera(std::shared_ptr<Camera>(new PerspectiveCamera(m_cameraView, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f)));
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	_update();
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
	m_board.handleUserEvents(m_userActions);
	m_cameraView->update();
	m_board.update();
	if (m_board.hasLost()) {
		stateMachine.changeState(new GameOverScene(m_userActions));
	}
}

void GameScene::render() {
	m_board.render(m_camera);
}
