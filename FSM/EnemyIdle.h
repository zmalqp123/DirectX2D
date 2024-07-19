#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class GameObject;
class EnemyIdle : public FSMState
{
public:
	EnemyIdle(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {

	}
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

	GameObject* target = nullptr;
	float distance = 500.f;
};

