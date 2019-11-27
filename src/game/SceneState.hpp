#ifndef __SCENE_STATE__
#define __SCENE_STATE__

#include "State.hpp"
#include "StateMachine.hpp"
#include "Camera.hpp"

class SceneState : public State {
	protected:
	UserActions &m_userActions;
	std::shared_ptr<Camera> m_camera = nullptr;

	public:
	SceneState(UserActions &userActions);
	virtual void update(StateMachine<SceneState> &stateMachine) = 0;
	void setCamera(std::shared_ptr<Camera> camera);
};

#endif
