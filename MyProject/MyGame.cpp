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

SpriteAnimation* sprite[3];

void MyGame::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);

	scene = new Scene();
	scene->cam = scene->CreateGameObject<GameObject>();
	scene->cam->CreateComponent<Camera>();
	//scene->cam->transform->m_RelativeScale = { 0.5f,0.5f };

	auto background = scene->CreateGameObject<GameObject>();
	auto spr = background->CreateComponent<SpriteRenderer>();
	spr->LoadTexture(L"../Resource/BG/BG.png");

	Texture* t = nullptr;
	ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/Animations/TheBullet.png", &t);

	auto animObj = scene->CreateGameObject<GameObject>();
	animObj->transform->m_RelativeLocation = { 710.f, 0.f };
	sprite[0] = animObj->CreateComponent<SpriteAnimation>();
	sprite[0]->m_pTexture = t;
	sprite[0]->LoadAnimationAsset(L"TheBullet");
	sprite[0]->SetAnimation(0, false);
	
	animObj = scene->CreateGameObject<GameObject>();
	animObj->transform->m_RelativeLocation = { -710.f, 0.f };
	sprite[1] = animObj->CreateComponent<SpriteAnimation>();
	sprite[1]->m_pTexture = t;
	sprite[1]->LoadAnimationAsset(L"TheBullet");
	sprite[1]->SetAnimation(0, false);
	
	animObj = scene->CreateGameObject<GameObject>();
	animObj->transform->m_RelativeLocation = { 0.f, 0.f };
	sprite[2] = animObj->CreateComponent<SpriteAnimation>();
	//sprite->SetSortingLayer(-1);
	sprite[2]->m_pTexture = t;
	sprite[2]->LoadAnimationAsset(L"TheBullet");
	sprite[2]->SetAnimation(0, false);
	
}

//void MyGame::Run()
//{
//	__super::Run();
//}

void MyGame::Update(float deltaTime)
{
	__super::Update(deltaTime);
	scene->Update(deltaTime);

	if (GetKeyState(0x44) < 0) {
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
	}

	if (GetKeyState(VK_RIGHT) < 0) {
		///scene->cam->transform->m_RelativeLocation.y += 100.f * deltaTime;
	}
	else if (GetKeyState(VK_LEFT) < 0) {
		//scene->cam->transform->m_RelativeLocation.y -= 100.f * deltaTime;
	}

	if (InputManager::GetInstance().IsKeyDown(1)) {
		scene->cam->transform->m_RelativeLocation.x += 100.f;
		/*float x = InputManager::GetInstance().GetMouseState().x;
		float y = InputManager::GetInstance().GetMouseState().y;*/

		auto cam = scene->cam->GetComponent<Camera>();
		Vector2 mPos = cam->ScreenToWorldPosition(InputManager::GetInstance().GetMousePosition());

		std::cout << "X : " << mPos.x << ", Y : " << mPos.y << std::endl;
	}
	else if (InputManager::GetInstance().IsKeyDown(2)) {
		scene->cam->transform->m_RelativeLocation.x -= 100.f;
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
