#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class GameObject;
class Movement;
class EnemyTracking : public FSMState
{
public:
	EnemyTracking(FiniteStateMachine* _fsm, std::string _name);
	// FSMState을(를) 통해 상속됨
	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

	GameObject* target = nullptr;
	float trackDistance = 500.f;
	float attackDistance = 100.f;
	Movement* movement = nullptr;
};

