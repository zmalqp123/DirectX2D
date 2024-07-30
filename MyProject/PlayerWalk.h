#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class Camera;
class Movement;
class PlayerWalk : public FSMState
{
public:
	PlayerWalk(FiniteStateMachine* _fsm, std::string _name);
	// FSMState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

	Camera* cam = nullptr;
	Movement* movement = nullptr;
};

