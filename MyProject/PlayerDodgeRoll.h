#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class Camera;
class PlayerWalk;
class Movement;
class PlayerDodgeRoll : public FSMState
{
public:
	PlayerDodgeRoll(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {

	}

	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

	Camera* cam = nullptr;
	PlayerWalk* pWalk = nullptr;
	Movement* movement = nullptr;
private:
	float timer = 0.f;
	float maxTimer = 1.1f;
};

