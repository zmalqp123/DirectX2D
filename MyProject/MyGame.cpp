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

void MyGame::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	__super::Initialize(hInstance, nCmdShow);

	scene = new Scene();
	scene->cam = scene->CreateGameObject<GameObject>();
}

void MyGame::Run()
{
	__super::Run();
}

void MyGame::Update(float deltaTime)
{
	__super::Update(deltaTime);
	scene->Update(deltaTime);
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
