#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class Camera;
class PlayerIdle : public FSMState
{
public:
	PlayerIdle(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {

	}

	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

	Camera* cam = nullptr;
};

