#include "FSMDemo.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/BoxCollider.h"

#include "EnemyIdle.h"
#include "EnemyTracking.h"
#include "EnemyAttack.h"
#include "PlayerIdle.h"
#include "PlayerMoving.h"
#include "../D2DEngine/Scene.h"
#include "Player.h"

std::vector<GameObject*> objs;
GameObject* cam;
GameObject* enemy;
GameObject* player;
D2D1_MATRIX_3X2_F cameraMat;
D2D1_VECTOR_2F trPos = { 0.f, 0.f };
void FSMDemo::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);
	scene = new Scene();

	Texture* t = nullptr;
	ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/midnight.png", &t);
	GameObject* gq = scene->CreateGameObject<GameObject>();
	//GameObject* gq = new GameObject();
	SpriteAnimation* spranim = gq->CreateComponent<SpriteAnimation>();
	//spranim->SetOwner(gq);
	spranim->m_pTransform = gq->transform;
	spranim->m_pTexture = t;
	spranim->LoadAnimationAsset(L"../Resource/midnight.txt");
	spranim->SetAnimation(1, rand() % 2 == 0 ? true : false);
	gq->spriteAnim = spranim;
	gq->transform->m_RelativeLocation = { 0, 0 };
	gq->transform->m_RelativeScale = { 1.f, 1.f };
	//objs.push_back(gq);
	
	
	ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/ken.png", &t);

	enemy = scene->CreateGameObject<GameObject>();
	SpriteAnimation* spr = enemy->CreateComponent<SpriteAnimation>();
	//spr->SetOwner(enemy);
	spr->m_pTransform = enemy->transform;
	spr->m_pTexture = t;
	spr->LoadAnimationAsset(L"Ken");
	spr->SetAnimation(0, false);
	enemy->spriteAnim = spr;
	enemy->transform->m_RelativeLocation = { -300, 0 };

	FiniteStateMachine* fsm = enemy->CreateComponent<FiniteStateMachine>();
	//fsm->SetOwner(enemy);
	EnemyIdle* eIdle = fsm->CreateState<EnemyIdle>("Idle");
	EnemyTracking* eTrack = fsm->CreateState<EnemyTracking>("Tracking");
	EnemyAttack* eAttack = fsm->CreateState<EnemyAttack>("Attack");
	fsm->SetState("Idle");
	//enemy->AddComponent(fsm);
	//objs.push_back(enemy);

	auto eColl = enemy->CreateComponent<BoxCollider>();
	eColl->SetCollisionType(CollisionType::Overlap);

	player = scene->CreateGameObject<GameObject>();
	spr = player->CreateComponent<SpriteAnimation>();
	//spr->SetOwner(player);
	spr->m_pTransform = player->transform;
	spr->m_pTexture = t;
	spr->LoadAnimationAsset(L"Ken");
	spr->SetAnimation(0, false);
	player->spriteAnim = spr;
	player->transform->m_RelativeLocation = { 0, 0 };

	fsm = player->CreateComponent<FiniteStateMachine>();
	//fsm->SetOwner(player);
	fsm->CreateState<PlayerIdle>("Idle");
	fsm->CreateState<PlayerMoving>("Tracking");
	fsm->SetState("Idle");

	auto coll = player->CreateComponent<BoxCollider>();
	coll->SetCollisionType(CollisionType::Overlap);

	player->CreateComponent<Player>();

	//player->AddComponent(fsm);
	//objs.push_back(player);

	eIdle->target = player;
	eTrack->target = player;
	eAttack->target = player;

	//cam = player;
	scene->cam = scene->CreateGameObject<GameObject>();//player;
	
	/*cam->transform->m_RelativeLocation = { 0, 0 };
	objs.push_back(cam);*/
}

void FSMDemo::Run()
{
	__super::Run();
}

void FSMDemo::Update(float deltaTime)
{
	__super::Update(deltaTime);

	if (GetKeyState(VK_RIGHT) < 0) {
		//g->transform->m_RelativeLocation.x += deltaTime * 100.f;
		scene->cam->transform->m_RelativeLocation.x += 1.f;
	}
	else if (GetKeyState(VK_LEFT) < 0) {
		//g->transform->m_RelativeLocation.x += deltaTime * -100.f;
		scene->cam->transform->m_RelativeLocation.x += -1.f;
	}
	if (GetKeyState(VK_UP) < 0) {
		//g->transform->m_RelativeLocation.y += deltaTime * 100.f;
		scene->cam->transform->m_RelativeLocation.y += 1.f;
	}
	else if (GetKeyState(VK_DOWN) < 0) {
		//g->transform->m_RelativeLocation.y += deltaTime * -100.f;
		scene->cam->transform->m_RelativeLocation.y += -1.f;
	}

	scene->Update(deltaTime);
	/*for (auto g : objs) {
		g->Update(deltaTime);
	}

	cameraMat = cam->transform->m_WorldTransform;
	D2D1InvertMatrix(&cameraMat);*/
}

void FSMDemo::Render(D2DRenderer* _render)
{
	__super::Render(_render);
	scene->Render(_render);

	/*D2D1_MATRIX_3X2_F c = cam->transform->m_WorldTransform;
	D2D1_VECTOR_2F center = { 0.f, 0.f };
	D2D1_VECTOR_2F extent = { 640.f, 360.f };
	D2D1_VECTOR_2F centerPos = {
		c.m[2][0],
		c.m[2][1]
	};
	D2D1_VECTOR_2F extentPos = {
		c.m[0][0] * extent.x + c.m[1][0] * extent.y,
		c.m[0][1] * extent.x + c.m[1][1] * extent.y
	};

	AABB ab;
	ab.m_Center = centerPos;
	ab.m_Extent = extentPos;

	auto temp = D2D1::Matrix3x2F::Translation(gq->transform->m_RelativeLocation.x, gq->transform->m_RelativeLocation.y) * gq->transform->m_WorldTransform;
	 카메라 센터 * 카메라 월드매트릭스 = 카메라 센터인 벡터? 뭐라하지 테스트해봐야함


	for (auto g : objs) {
		if (!g->spriteAnim) continue;
		AABB lab = g->spriteAnim->GetBound();
		bool check = ab.CheckIntersect(lab);
		if (check) {
			g->Render(cameraMat);
		}
	}*/
}

void FSMDemo::Uninitialize()
{
	__super::Uninitialize();
}
