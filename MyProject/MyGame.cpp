#include "MyGame.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Camera.h"

#include "../D2DEngine/InputManager.h"
#include "PlayerController.h"
#include "PlayerIdle.h"
#include "PlayerWalk.h"
#include "PlayerDodgeRoll.h"
#include "Generator.h"
#include "Bullet.h"
//SpriteAnimation* sprite[3];

void MyGame::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);

	scene = new Scene();
	scene->cam = scene->CreateGameObject<GameObject>();
	auto pCam = scene->cam->CreateComponent<Camera>();
	//scene->cam->transform->m_RelativeScale = { 0.5f,0.5f };

	auto background = scene->CreateGameObject<GameObject>();
	auto spr = background->CreateComponent<SpriteRenderer>();
	spr->LoadTexture(L"../Resource/BG/BG.png");

	Texture* t = nullptr;
	ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/Animations/TheBullet.png", &t);


	auto animObj = scene->CreateGameObject<GameObject>();
	animObj->transform->m_RelativeLocation = { 0.f, 0.f };
	auto sprite = animObj->CreateComponent<SpriteAnimation>();
	//sprite->SetSortingLayer(-1);
	sprite->m_pTexture = t;
	sprite->LoadAnimationAsset(L"TheBullet");
	sprite->SetAnimation(0, false);
	auto pCon = animObj->CreateComponent<PlayerController>();
	pCon->cam = pCam;
	auto fsm = animObj->CreateComponent<FiniteStateMachine>();
	auto idle = fsm->CreateState<PlayerIdle>("Idle");
	idle->cam = pCam;
	auto walk = fsm->CreateState<PlayerWalk>("Walk");
	walk->cam = pCam;
	auto dodgeRoll = fsm->CreateState<PlayerDodgeRoll>("DodgeRoll");
	dodgeRoll->cam = pCam;
	dodgeRoll->pWalk = walk;
	dodgeRoll->movement = walk->movement;
	fsm->SetState("Idle");
	auto coll = animObj->CreateComponent<BoxCollider>();
	coll->SetCollisionType(CollisionType::Block);
	coll->SetExtent({ 15.f, 5.f });
	coll->SetOffset({ 0.f, -45.f });


	{
		GameObject* gen = scene->CreateGameObject<GameObject>();
		auto cGen = gen->CreateComponent<Generator>();
		cGen->target = animObj->transform;
		for (int i = 0; i < 20; i++) {
			GameObject* it = scene->CreateGameObject<GameObject>();
			it->transform->m_RelativeLocation = { 0.f, 0.f };

			BoxCollider* c = it->CreateComponent<BoxCollider>();
			c->SetCollisionType(CollisionType::Block);
			c->isKinemetic = true;
			c->SetCenter({ 0.f, 0.f });
			//c->SetExtent({ 35.f, 35.f });

			auto drop = it->CreateComponent<Bullet>();
			drop->SetTarget(animObj->transform);
			drop->gn = cGen;

			it->isActive = false;
			cGen->pools.push(drop);

			auto spr = it->CreateComponent<SpriteRenderer>();
			spr->LoadTexture(L"../Resource/Tiles/boxItemAlt.png");
		}
	}
}

//void MyGame::Run()
//{
//	__super::Run();
//}

void MyGame::Update(float deltaTime)
{
	__super::Update(deltaTime);
	scene->Update(deltaTime);

	/*if (GetKeyState(0x44) < 0) {
		sprite[0]->SetAnimation(1, false, true);
		sprite[1]->SetAnimation(5, false, true);
		sprite[2]->SetAnimation(9, false, true);
	}
	else if (GetKeyState(0x41) < 0) {
		sprite[0]->SetAnimation(2, false, true);
		sprite[1]->SetAnimation(6, false, true);
		sprite[2]->SetAnimation(10, false, true);
	}
	if (GetKeyState(0x57) < 0) {
		sprite[0]->SetAnimation(3, false, true);
		sprite[1]->SetAnimation(7, false, true);
		sprite[2]->SetAnimation(11, false, true);
	}
	else if (GetKeyState(0x53) < 0) {
		sprite[0]->SetAnimation(0, false, true);
		sprite[1]->SetAnimation(4, false, true);
		sprite[2]->SetAnimation(8, false, true);
	}*/

	if (GetKeyState(VK_RIGHT) < 0) {
		///scene->cam->transform->m_RelativeLocation.y += 100.f * deltaTime;
	}
	else if (GetKeyState(VK_LEFT) < 0) {
		//scene->cam->transform->m_RelativeLocation.y -= 100.f * deltaTime;
	}

	/*if (InputManager::GetInstance().IsKeyDown(1)) {
		scene->cam->transform->m_RelativeLocation.x += 100.f;
		auto cam = scene->cam->GetComponent<Camera>();
		Vector2 mPos = cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition());

		std::cout << "X : " << mPos.x << ", Y : " << mPos.y << std::endl;
	}
	else if (InputManager::GetInstance().IsKeyDown(2)) {
		scene->cam->transform->m_RelativeLocation.x -= 100.f;
		auto cam = scene->cam->GetComponent<Camera>();
		Vector2 mPos = cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition());

		std::cout << "X : " << mPos.x << ", Y : " << mPos.y << std::endl;
	}*/

	if (InputManager::GetInstance().GetMouseState().wheel > 0) {
		scene->cam->transform->m_RelativeScale -= {deltaTime * 10.f, deltaTime * 10.f};
		std::cout << InputManager::GetInstance().GetMouseState().wheel << std::endl;
	}
	else if (InputManager::GetInstance().GetMouseState().wheel < 0) {
		scene->cam->transform->m_RelativeScale += {deltaTime * 10.f, deltaTime * 10.f};
	}
}

void MyGame::Render(D2DRenderer* _render)
{
	__super::Render(_render);
	scene->Render(_render);
}

void MyGame::Uninitialize()
{
	__super::Uninitialize();
}
