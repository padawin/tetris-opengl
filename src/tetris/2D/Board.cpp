#include "./Board.hpp"
#include "tetris/renderers.hpp"

void Board2D::init() {
	m_left.setPosition(-1.0f, BOARD_HEIGHT / 2 - 0.5f, 0.0f);
	m_right.setPosition(BOARD_WIDTH, BOARD_HEIGHT / 2 - 0.5f, 0.0f);
	renderer_init2DSideRenderer(&m_sideRenderer, BOARD_HEIGHT);
	renderer_init2DPieceRenderer(&m_pieceRenderer);
	_init();
}

void Board2D::render(std::shared_ptr<Camera> camera, std::shared_ptr<Camera> cameraUI) {
	m_sideRenderer.setUniform("color", COLOR_SIDE);
	m_left.render(camera, &m_sideRenderer);
	m_right.render(camera, &m_sideRenderer);
	_render(camera, cameraUI);
}
