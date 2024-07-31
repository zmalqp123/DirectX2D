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
#include "../D2DEngine/PublicData.h"

#include "../D2DEngine/InputManager.h"
#include "PlayerController.h"
#include "PlayerIdle.h"
#include "PlayerWalk.h"
#include "PlayerDodgeRoll.h"
#include "Generator.h"
#include "Bullet.h"
#include "../D2DEngine/TextRenderer.h"
//SpriteAnimation* sprite[3];

void MyGame::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);

	scene = new Scene();
	auto camera = scene->CreateGameObject<GameObject>();
	camera->transform->m_RelativeScale = { 0.7f, 0.7f };
	auto pCam = camera->CreateComponent<Camera>();
	scene->SetMainCamera(pCam);

	auto background = scene->CreateGameObject<GameObject>();
	auto spr = background->CreateComponent<SpriteRenderer>();
	spr->SetSortingLayer(-10);
	spr->LoadTexture(L"../Resource/BG/TopDownMap.png");
	{
		auto backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 0.f, 315.f });
		backColl->SetOffset({ -600.f, 0.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 0.f, 315.f });
		backColl->SetOffset({ 600.f, 0.f });
		
		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 600.f, 0.f });
		backColl->SetOffset({ 0.f, 315.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 600.f, 0.f });
		backColl->SetOffset({ 0.f, -315.f });
		
		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 0.f, 90.f });
		backColl->SetOffset({ -35.f, 24.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 0.f, 90.f });
		backColl->SetOffset({ 70.f, 24.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 0.f, 60.f });
		backColl->SetOffset({ -160.f, 180.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 0.f, 60.f });
		backColl->SetOffset({ 195.f, 180.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 0.f, 40.f });
		backColl->SetOffset({ -100.f, 280.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 0.f, 40.f });
		backColl->SetOffset({ 135.f, 280.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 40.f, 0.f });
		backColl->SetOffset({ 175.f, 240.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 40.f, 0.f });
		backColl->SetOffset({ -140.f, 240.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 62.f, 0.f });
		backColl->SetOffset({ -97.f, 120.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 62.f, 0.f });
		backColl->SetOffset({ 132.f, 120.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 30.f, 30.f });
		backColl->SetOffset({ -165.f, -20.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 70.f, 60.f });
		backColl->SetOffset({ -105.f, 60.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 70.f, 60.f });
		backColl->SetOffset({ 140.f, 60.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 130.f, 80.f });
		backColl->SetOffset({ -435.f, -215.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 40.f, 160.f });
		backColl->SetOffset({ -520.f, -5.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 160.f, 20.f });
		backColl->SetOffset({ -330.f, 130.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 120.f, 20.f });
		backColl->SetOffset({ 330.f, 130.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 70.f, 100.f });
		backColl->SetOffset({ 395.f, 25.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 70.f, 100.f });
		backColl->SetOffset({ 525.f, -175.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 230.f, 40.f });
		backColl->SetOffset({ -85.f, -300.f });

		backColl = background->CreateComponent<BoxCollider>();
		backColl->SetCollisionType(CollisionType::Block);
		backColl->SetExtent({ 130.f, 40.f });
		backColl->SetOffset({ 405.f, -300.f });
	}

	Texture* t = nullptr;
	ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/Animations/TheBullet.png", &t);

	auto txtObj = scene->CreateGameObject<GameObject>();
	txtObj->CreateComponent<TextRenderer>()->SetSortingLayer(2);

	auto animObj = scene->CreateGameObject<GameObject>();
	animObj->transform->m_RelativeLocation = { 17.f, 210.f };
	auto sprite = animObj->CreateComponent<SpriteAnimation>();
	//sprite->SetSortingLayer(-1);
	sprite->m_pTexture = t;
	sprite->LoadAnimationAsset(L"TheBullet");
	sprite->SetAnimation(0, false);
	auto pCon = animObj->CreateComponent<PlayerController>();
	pCon->timerObj = txtObj;
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
	coll->SetCenter({ 0.f, 50.f });
	coll->SetExtent({ 15.f, 5.f });
	coll->SetOffset({ 0.f, -45.f });

	auto txtRender = camera->CreateComponent<TextRenderer>();
	txtRender->SetSortingLayer(1);
	txtRender->text = L"Count : 0";

	auto shadowObj = scene->CreateGameObject<GameObject>();
	auto shadowSpr = shadowObj->CreateComponent<SpriteRenderer>();
	shadowSpr->LoadTexture(L"../Resource/Animations/TheBulletShadow.png");
	shadowSpr->SetSortingLayer(-1);
	shadowObj->transform->SetParent(animObj->transform);

	{
		GameObject* gen = scene->CreateGameObject<GameObject>();
		auto cGen = gen->CreateComponent<Generator>();
		cGen->target = animObj->transform;
		for (int i = 0; i < 40; i++) {
			GameObject* it = scene->CreateGameObject<GameObject>();
			it->transform->m_RelativeLocation = { 0.f, 0.f };

			BoxCollider* c = it->CreateComponent<BoxCollider>();
			c->SetCollisionType(CollisionType::Overlap);
			c->isKinemetic = true;
			c->SetCenter({ 0.f, 0.f });
			c->SetExtent({ 16.f, 16.f });

			auto drop = it->CreateComponent<Bullet>();
			drop->SetTarget(animObj->transform);
			drop->gn = cGen;

			it->isActive = false;
			cGen->pools.push(drop);

			auto spr = it->CreateComponent<SpriteRenderer>();
			spr->LoadTexture(L"../Resource/Animations/Bullet.png");

			shadowObj = scene->CreateGameObject<GameObject>();
			shadowObj->transform->m_RelativeLocation = { 0.f, -20.f };
			auto shadowSpr = shadowObj->CreateComponent<SpriteRenderer>();
			shadowSpr->LoadTexture(L"../Resource/Animations/TheBulletShadow.png");
			shadowSpr->SetSortingLayer(-1);
			shadowObj->transform->SetParent(it->transform);
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
