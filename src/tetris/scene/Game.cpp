#include "Game.hpp"
#include "opengl/PerspectiveCamera.hpp"
#include "game/cameraView/Rotate.hpp"
#include "game/cameraView/Fixed.hpp"
#include "GameOver.hpp"
#include <iostream>

std::string GameScene::getStateID() const {
	return "GameScene";
}

GameScene::GameScene(UserActions &userActions) :
	SceneState(userActions),
	m_rules(Rules()),
	m_board(Board())
{
}

bool GameScene::onEnter() {
	m_board.init();
	glm::vec3 boardPosition = m_board.getPosition();
	boardPosition.x += BOARD_WIDTH / 2;
	boardPosition.y += BOARD_HEIGHT / 2;
	boardPosition.z -= BOARD_WIDTH / 2;
	setCameraView(std::shared_ptr<CameraView>(new RotateView(boardPosition, 30.0f)));
	std::static_pointer_cast<RotateView>(m_cameraView)->rotateVertical(25.0f);
	std::static_pointer_cast<RotateView>(m_cameraView)->rotateHorizontal(90.0f);

	setCamera(std::shared_ptr<Camera>(new PerspectiveCamera(m_cameraView, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f)));

	std::shared_ptr<CameraView> uiView = std::shared_ptr<CameraView>(new FixedView(glm::vec3(0.0f, 0.0f, -1.0f)));
	uiView->setPosition(glm::vec3(4.5f, 6.5f, 22.4f));
	m_cameraUI = std::shared_ptr<Camera>(new PerspectiveCamera(uiView, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
	uiView->update();
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	_update();
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
	m_rules.handleUserEvents(m_userActions, m_board);
	if (m_userActions.getActionState("CAMERA_LEFT")) {
		std::static_pointer_cast<RotateView>(m_cameraView)->rotateHorizontal(1.1f);
	}
	else if (m_userActions.getActionState("CAMERA_RIGHT")) {
		std::static_pointer_cast<RotateView>(m_cameraView)->rotateHorizontal(-1.1f);
	}
	m_cameraView->update();
	m_rules.update(m_board);
	if (m_rules.hasLost()) {
		stateMachine.changeState(new GameOverScene(m_userActions));
	}
}

void GameScene::render() {
	m_board.render(m_camera, m_cameraUI);
}
