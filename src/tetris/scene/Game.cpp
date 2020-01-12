#include "Game.hpp"
#include "opengl/PerspectiveCamera.hpp"
#include "game/cameraView/Rotate.hpp"
#include "game/cameraView/Fixed.hpp"
#include "GameOver.hpp"
#include <iostream>

GameScene::GameScene(UserActions &userActions, std::shared_ptr<Board> board) :
	SceneState(userActions),
	m_rules(Rules()),
	m_board(board)
{
}

bool GameScene::onEnter() {
	m_board->init();
	_initCamera();
	m_cameraView->update();
	setCamera(std::shared_ptr<Camera>(new PerspectiveCamera(m_cameraView, 45.0f, 800.0f / 600.0f, 0.1f, 100.0f)));

	return true;
}

void GameScene::update(StateMachine<SceneState> &stateMachine) {
	_update();
	if (m_userActions.getActionState("QUIT")) {
		stateMachine.clean();
		return;
	}

	_handleEvents();
	m_rules.update(m_board);
	if (m_rules.hasLost()) {
		stateMachine.changeState(new GameOverScene(m_userActions));
	}
}

void GameScene::_handleEvents() {
	m_rules.setTurbo(m_userActions.getActionState("TURBO"));
	m_rules.rotatePiece(m_userActions.getActionState("ROTATE"), m_board);

	if (m_rules.playerCanMovePiece()) {
		if (m_userActions.getActionState("LEFT")) {
			m_board->movePieceSide(_getLeft());
			m_rules.setPlayerMovedPiece();
		}
		else if (m_userActions.getActionState("RIGHT")) {
			m_board->movePieceSide(_getRight());
			m_rules.setPlayerMovedPiece();
		}
	}
}
