#include "Board.hpp"
#include "tetris/renderers.hpp"

void Board3D::init() {
	m_frontLeft.setPosition(-1.0f, BOARD_HEIGHT / 2 - 0.5f, 0.0f);
	m_frontRight.setPosition(BOARD_WIDTH, BOARD_HEIGHT / 2 - 0.5f, 0.0f);
	m_backLeft.setPosition(-1.0f, BOARD_HEIGHT / 2 - 0.5f, -BOARD_DEPTH);
	m_backRight.setPosition(BOARD_WIDTH, BOARD_HEIGHT / 2 - 0.5f, -BOARD_DEPTH);
	renderer_init3DSideRenderer(&m_sideRenderer, BOARD_HEIGHT);
	renderer_init3DPieceRenderer(&m_pieceRenderer);
	_init();
}

void Board3D::render(std::shared_ptr<Camera> camera, std::shared_ptr<Camera> cameraUI) {
	m_sideRenderer.setUniform("color", COLOR_SIDE);
	m_frontLeft.render(camera, &m_sideRenderer);
	m_frontRight.render(camera, &m_sideRenderer);
	m_backLeft.render(camera, &m_sideRenderer);
	m_backRight.render(camera, &m_sideRenderer);
	_render(camera, cameraUI);
}
