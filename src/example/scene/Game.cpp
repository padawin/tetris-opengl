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
	m_vObjects.push_back(rectangle);
	m_vObjects.push_back(triangle);
	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
	}
}

void GameScene::render() {
	for (auto object : m_vObjects) {
		object->render();
	}
}
