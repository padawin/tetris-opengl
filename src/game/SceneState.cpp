#include "SceneState.hpp"

SceneState::SceneState(UserActions &userActions) :
	m_userActions(userActions)
{
}

void SceneState::setCamera(std::shared_ptr<Camera> camera) {
	m_camera = camera;
}
