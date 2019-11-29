#include "Game.hpp"
#include "example/Triangle.hpp"
#include "example/Rectangle.hpp"
#include "opengl/PerspectiveCamera.hpp"
#include <iostream>

std::string GameScene::getStateID() const {
	return "GameScene";
}

GameScene::GameScene(UserActions &userActions) :
	SceneState(userActions)
{
}

bool GameScene::onEnter() {
	auto rectangle = std::shared_ptr<GameObject>(new Rectangle());
	auto triangle = std::shared_ptr<GameObject>(new Triangle());
	rectangle->init();
	triangle->init();
	m_player = rectangle;
	m_vObjects.push_back(rectangle);
	m_vObjects.push_back(triangle);
	setCamera(std::shared_ptr<Camera>(new PerspectiveCamera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)));
	// Example for Orthogonal camera:
	//setCamera(std::shared_ptr<Camera>(new OrthoCamera(0.0f, 2.0f, 0.0f, 2.0f, 0.1f, 100.0f)));
	m_camera->setPositionFromTarget(glm::vec3(0.0f, 0.0f, 2.0f));

	m_camera->setTarget(rectangle);
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}

	const float playerSpeedX = 0.01f;
	const float playerSpeedY = 0.01f;
	glm::vec3 playerPosition = m_player->getPosition();
	float playerX = playerPosition.x;
	float playerY = playerPosition.y;
	float playerZ = playerPosition.z;
	if (m_userActions.getActionState("RIGHT")) {
		playerX += playerSpeedX;
	} else if (m_userActions.getActionState("LEFT")) {
		playerX -= playerSpeedX;
	}
	if (m_userActions.getActionState("UP")) {
		playerY += playerSpeedY;
	} else if (m_userActions.getActionState("DOWN")) {
		playerY -= playerSpeedY;
	}
	m_player->setPosition(playerX, playerY, playerZ);
	m_camera->update();
	for (auto object : m_vObjects) {
		object->update();
	}
}

void GameScene::render() {
	for (auto object : m_vObjects) {
		object->render(m_camera);
	}
}
