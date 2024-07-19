#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class Movement;
class PlayerMoving : public FSMState
{
public:
	PlayerMoving(FiniteStateMachine* _fsm, std::string _name);
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

	Movement* movement = nullptr;
};

