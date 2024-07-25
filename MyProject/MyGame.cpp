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

#include "../D2DEngine/InputManager.h"

SpriteAnimation* sprite;

void MyGame::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);

	scene = new Scene();
	scene->cam = scene->CreateGameObject<GameObject>();
	//scene->cam->transform->m_RelativeScale = { 0.5f, 0.5f };

	auto background = scene->CreateGameObject<GameObject>();
	auto spr = background->CreateComponent<SpriteRenderer>();
	spr->LoadTexture(L"../Resource/BG/BG.png");

	Texture* t = nullptr;
	ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/Animations/TheBullet.png", &t);

	auto animObj = scene->CreateGameObject<GameObject>();
	animObj->transform->m_RelativeLocation = { 710.f, 10.f };
	sprite = animObj->CreateComponent<SpriteAnimation>();
	sprite->m_pTexture = t;
	sprite->LoadAnimationAsset(L"TheBullet");
	sprite->SetAnimation(0, false);
	
	animObj = scene->CreateGameObject<GameObject>();
	animObj->transform->m_RelativeLocation = { -710.f, 10.f };
	sprite = animObj->CreateComponent<SpriteAnimation>();
	sprite->m_pTexture = t;
	sprite->LoadAnimationAsset(L"TheBullet");
	sprite->SetAnimation(0, false);
	
	animObj = scene->CreateGameObject<GameObject>();
	animObj->transform->m_RelativeLocation = { 0.f, 10.f };
	sprite = animObj->CreateComponent<SpriteAnimation>();
	//sprite->SetSortingLayer(-1);
	sprite->m_pTexture = t;
	sprite->LoadAnimationAsset(L"TheBullet");
	sprite->SetAnimation(0, false);
	
}

void MyGame::Run()
{
	__super::Run();
}

void MyGame::Update(float deltaTime)
{
	__super::Update(deltaTime);
	scene->Update(deltaTime);

	if (GetKeyState(0x44) < 0) {
		sprite->SetAnimation(9, false, true);
	}
	else if (GetKeyState(0x41) < 0) {
		sprite->SetAnimation(10, false, true);
	}
	if (GetKeyState(0x57) < 0) {
		sprite->SetAnimation(11, false, true);
	}
	else if (GetKeyState(0x53) < 0) {
		sprite->SetAnimation(8, false, true);
	}

	if (GetKeyState(VK_RIGHT) < 0) {
		///scene->cam->transform->m_RelativeLocation.y += 100.f * deltaTime;
	}
	else if (GetKeyState(VK_LEFT) < 0) {
		//scene->cam->transform->m_RelativeLocation.y -= 100.f * deltaTime;
	}

	if (InputManager::GetInstance().IsKeyDown(1)) {
		scene->cam->transform->m_RelativeLocation.x += 100.f;
		float x = InputManager::GetInstance().GetMouseState().x;
		float y = InputManager::GetInstance().GetMouseState().y;
		std::cout << "X : " << x << ", Y : " << y << std::endl;
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
