#include "Game.hpp"
#include "example/Triangle.hpp"
#include "example/Rectangle.hpp"

bool Game::init() {
	auto rectangle = std::shared_ptr<GameObject>(new Rectangle());
	auto triangle = std::shared_ptr<GameObject>(new Triangle());
	rectangle->init();
	triangle->init();
	m_vObjects.push_back(rectangle);
	m_vObjects.push_back(triangle);
	return true;
}

void Game::update() {

}

void Game::render() {
	for (auto object : m_vObjects) {
		object->render();
	}
}
