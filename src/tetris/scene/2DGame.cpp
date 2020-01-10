#include "2DGame.hpp"
#include "tetris/2DBoard.hpp"
#include "opengl/PerspectiveCamera.hpp"
#include "game/cameraView/Rotate.hpp"
#include "game/cameraView/Fixed.hpp"
#include "GameOver.hpp"
#include <iostream>

std::string Game2DScene::getStateID() const {
	return "Game2DScene";
}

Game2DScene::Game2DScene(UserActions &userActions) :
	GameScene(userActions, std::shared_ptr<Board>(new Board2D()))
{
}

void Game2DScene::_initCamera() {
	setCameraView(std::shared_ptr<CameraView>(new FixedView(glm::vec3(0.0f, 0.0f, -1.0f))));
	m_cameraView->setPosition(glm::vec3(4.5f, 8.5f, 22.4f));
	m_cameraView->update();
}

unsigned int Game2DScene::_getLeft() {
	return DIRECTION_LEFT;
}

unsigned int Game2DScene::_getRight() {
	return DIRECTION_RIGHT;
}

void Game2DScene::render() {
	m_board->render(m_camera, m_camera);
}
