#include "./Game.hpp"
#include "tetris/3D/Board.hpp"
#include "tetris/scene/GameOver.hpp"
#include "opengl/PerspectiveCamera.hpp"
#include "game/cameraView/Rotate.hpp"
#include "game/cameraView/Fixed.hpp"
#include <iostream>

std::string Game3DScene::getStateID() const {
	return "Game3DScene";
}

Game3DScene::Game3DScene(UserActions &userActions) :
	GameScene(userActions, std::shared_ptr<Board>(new Board3D()))
{
}

void Game3DScene::_initCamera() {
	glm::vec3 boardPosition = m_board->getPosition();
	boardPosition.x += BOARD_WIDTH / 2;
	boardPosition.y += BOARD_HEIGHT / 2;
	boardPosition.z = BOARD_DEPTH / 2;
	setCameraView(std::shared_ptr<CameraView>(new RotateView(boardPosition, 30.0f)));
	std::static_pointer_cast<RotateView>(m_cameraView)->rotateVertical(25.0f);
	std::static_pointer_cast<RotateView>(m_cameraView)->rotateHorizontal(90.0f);

	std::shared_ptr<CameraView> uiView = std::shared_ptr<CameraView>(new FixedView(glm::vec3(0.0f, 0.0f, -1.0f)));
	uiView->setPosition(glm::vec3(4.5f, 6.5f, 22.4f));
	m_cameraUI = std::shared_ptr<Camera>(new PerspectiveCamera(uiView, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
	uiView->update();
}

void Game3DScene::_handleEvents() {
	GameScene::_handleEvents();

	auto view = std::static_pointer_cast<RotateView>(m_cameraView);
	if (m_userActions.getActionState("CAMERA_LEFT")) {
		view->rotateHorizontal(1.1f);
	}
	else if (m_userActions.getActionState("CAMERA_RIGHT")) {
		view->rotateHorizontal(-1.1f);
	}
	m_cameraView->update();
}

unsigned int Game3DScene::_getLeft() {
	auto view = std::static_pointer_cast<RotateView>(m_cameraView);
	float cameraAngle = view->getHorizontalAngle();
	if (cameraAngle >= 45.0f && cameraAngle < 135.0f) {
		return DIRECTION_LEFT;
	}
	else if (cameraAngle >= 135.0f && cameraAngle < 225.0f) {
		return DIRECTION_BACK;
	}
	else if (cameraAngle >= 225.0f && cameraAngle < 315.0f) {
		return DIRECTION_RIGHT;
	}
	else { // cameraAngle >= 225.0f || cameraAngle < 45.0f
		return DIRECTION_FRONT;
	}
}

unsigned int Game3DScene::_getRight() {
	auto view = std::static_pointer_cast<RotateView>(m_cameraView);
	float cameraAngle = view->getHorizontalAngle();
	if (cameraAngle >= 45.0f && cameraAngle < 135.0f) {
		return DIRECTION_RIGHT;
	}
	else if (cameraAngle >= 135.0f && cameraAngle < 225.0f) {
		return DIRECTION_FRONT;
	}
	else if (cameraAngle >= 225.0f && cameraAngle < 315.0f) {
		return DIRECTION_LEFT;
	}
	else { // cameraAngle >= 225.0f || cameraAngle < 45.0f
		return DIRECTION_BACK;
	}
}

void Game3DScene::render() {
	m_board->render(m_camera, m_cameraUI);
}
