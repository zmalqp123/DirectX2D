// ColliderDemo.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "ColliderDemo.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Scene.h"
#include "Player.h"
#include "DropIt.h"
#include "Generator.h"

void ColliderDemo::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);
	std::srand(std::time(0));
	scene = new Scene();

	scene->cam = scene->CreateGameObject<GameObject>();

	GameObject* gameObject = scene->CreateGameObject<GameObject>();
	BoxCollider* coll = gameObject->CreateComponent<BoxCollider>();
	coll->SetCollisionType(CollisionType::Block);
	coll->isKinemetic = false;
	gameObject->CreateComponent<Player>();

	/*GameObject* gen = scene->CreateGameObject<GameObject>();
	auto cGen = gen->CreateComponent<Generator>();
	cGen->target = gameObject->transform;
	for (int i = 0; i < 20; i++) {
		GameObject* it = scene->CreateGameObject<GameObject>();
		it->transform->m_RelativeLocation = { 0.f, 0.f };

		BoxCollider* c = it->CreateComponent<BoxCollider>();
		c->SetCollisionType(CollisionType::Block);
		c->isKinemetic = true;

		auto drop = it->CreateComponent<DropIt>();
		drop->SetTarget(gameObject->transform);
		drop->gn = cGen;

		it->isActive = false;
		cGen->pools.push(drop);
	}*/




	gameObject = scene->CreateGameObject<GameObject>();
	coll = gameObject->CreateComponent<BoxCollider>();
	gameObject->transform->m_RelativeLocation = { 300.f, 0.f };
	coll->SetCollisionType(CollisionType::Block);
	coll->SetExtent({ 0.f, 300.f });
	coll->isKinemetic = true;
	
	gameObject = scene->CreateGameObject<GameObject>();
	coll = gameObject->CreateComponent<BoxCollider>();
	gameObject->transform->m_RelativeLocation = { -300.f, 0.f };
	coll->SetCollisionType(CollisionType::Block);
	coll->SetExtent({ 0.f, 300.f });
	coll->isKinemetic = true;
	
	gameObject = scene->CreateGameObject<GameObject>();
	coll = gameObject->CreateComponent<BoxCollider>();
	gameObject->transform->m_RelativeLocation = { 0.f, -300.f };
	coll->SetCollisionType(CollisionType::Block);
	coll->SetExtent({ 300.f, 0.f });
	coll->isKinemetic = true;
}

void ColliderDemo::Run()
{
	__super::Run();
}

void ColliderDemo::Update(float deltaTime)
{
	__super::Update(deltaTime);

	scene->Update(deltaTime);
}

void ColliderDemo::Render(D2DRenderer* _render)
{
	__super::Render(_render);

	scene->Render(_render);
}

void ColliderDemo::Uninitialize()
{
	__super::Uninitialize();
}
