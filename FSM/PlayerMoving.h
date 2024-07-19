#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class Movement;
class PlayerMoving : public FSMState
{
public:
	PlayerMoving(FiniteStateMachine* _fsm, std::string _name);
	// FSMState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

	Movement* movement = nullptr;
};

