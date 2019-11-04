#include "Game.hpp"
#include "example/Triangle.hpp"
#include "example/Rectangle.hpp"
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
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}

	const float playerSpeedX = 0.01f;
	const float playerSpeedY = 0.01f;
	float playerX = m_player->getX();
	float playerY = m_player->getY();
	float playerZ = m_player->getZ();
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
	m_player->setPos(playerX, playerY, playerZ);
	for (auto object : m_vObjects) {
		object->update();
	}
}

void GameScene::render() {
	for (auto object : m_vObjects) {
		object->render();
	}
}
