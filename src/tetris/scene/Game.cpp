#include "Game.hpp"
#include "tetris/Board.hpp"
#include "opengl/PerspectiveCamera.hpp"
#include "game/cameraView/Fixed.hpp"
#include <iostream>

std::string GameScene::getStateID() const {
	return "GameScene";
}

GameScene::GameScene(UserActions &userActions) :
	SceneState(userActions)
{
}

bool GameScene::onEnter() {
	auto board = std::shared_ptr<GameObject>(new Board());
	board->init();
	m_vObjects.push_back(board);
	setCameraView(std::shared_ptr<CameraView>(new FixedView(glm::vec3(0.0f, 0.3f, -1.0f))));
	m_cameraView->setPosition(glm::vec3(3.5f, 2.4f, 20.0f));

	setCamera(std::shared_ptr<Camera>(new PerspectiveCamera(m_cameraView, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f)));
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	_update();
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}
	m_cameraView->update();
	for (auto object : m_vObjects) {
		object->update();
	}
}

void GameScene::render() {
	for (auto object : m_vObjects) {
		object->render(m_camera);
	}
}
