#include "DemoGame.h"
#include "../D2DEngine/TestObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Action.h"
#include <string>

//std::vector<GameObject*> gs;
GameObject* gq;

ActionWithParam<GameObject, std::string> action;
D2D1_VECTOR_2F trPos = { 0.f, 0.f };
void DemoGame::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	// 재정의를 하지만 부모 클래스의 Initialize()는 호출한다.
	__super::Initialize(hInstance, nCmdShow);	 // 윈도우 생성 , Direct2D 초기화
	scene = new Scene();

	// 이후에 할일을 작성한다. 예 게임 리소스 로딩,

	/*SpriteAnimationAsset a;
	a.LoadAnimation(L"../Resource/background.txt");*/

	Texture* t = nullptr;
	ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/midnight.png", &t);

	gq = scene->CreateGameObject<GameObject>();
	SpriteAnimation* spranim = gq->CreateComponent<SpriteAnimation>();
	//spranim->SetOwner(gq);
	//spranim->m_pTransform = gq->transform;
	spranim->m_pTexture = t;
	spranim->LoadAnimationAsset(L"../Resource/midnight.txt");
	spranim->SetAnimation(1, rand() % 2 == 0 ? true : false);
	//gq->spriteAnim = spranim;
	gq->transform->m_RelativeLocation = { 0, 0 };
	//gs.push_back(gq);

	gq = scene->CreateGameObject<GameObject>();
	gq->transform->m_RelativeLocation = { 0, 0 };
	//gq->transform->m_RelativeScale = { 2.f, 2.f };
	//gs.push_back(gq);
	scene->cam = gq;
	/*testObj[0] = new TestObject(L"../Resource/Sun.png");
	testObj[1] = new TestObject(L"../Resource/Earth.png");
	testObj[2] = new TestObject(L"../Resource/Moon.png");

	testObj[1]->transform->SetParent(testObj[0]->transform);
	testObj[2]->transform->SetParent(testObj[1]->transform);

	testObj[0]->transform->m_RelativeLocation = { 640, 160 };
	testObj[1]->transform->m_RelativeLocation = { 200, 0 };
	testObj[2]->transform->m_RelativeLocation = { 150, 0 };

	testObj[0]->transform->m_CenterTransform = { -100, -100 };
	testObj[1]->transform->m_CenterTransform = { -100, -100 };
	testObj[2]->transform->m_CenterTransform = { -50, -50 };*/

	//testObj[0]->transform->m_RelativeScale = { 0.5f, 0.5f };
	//testObj[1]->transform->m_RelativeScale = { 0.5f, 0.5f };
	//testObj[2]->transform->m_RelativeScale = { 0.5f, 0.5f };

	/*testObj[0]->transform->UpdateTrasnform();
	testObj[1]->transform->UpdateTrasnform();
	testObj[2]->transform->UpdateTrasnform();*/

	//action.AddAction(gq, &GameObject::Print);

	srand(NULL);
}
void temp(Scene* scene, bool randomPos = true, float x = 0.f, float y = 0.f) {

	Texture* t = nullptr;
	ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/run.png", &t);

	GameObject* g = scene->CreateGameObject<GameObject>();
	SpriteAnimation* spranim = g->CreateComponent<SpriteAnimation>();
	//spranim->SetOwner(g);
	//spranim->m_pTransform = g->transform;
	spranim->m_pTexture = t;
	spranim->LoadAnimationAsset(L"../Resource/background.txt");
	spranim->SetAnimation(0, rand() % 2 == 0 ? true : false);
	//g->spriteAnim = spranim;
	g->transform->m_RelativeLocation = { randomPos ? float(rand() % 6400) / 10.f: x, 
		randomPos ? float(rand() & 3600) / 10.f : y};
	g->transform->m_RelativeRotation = float(rand() % 360);
	//gs.push_back(g);
}

void DemoGame::Run()
{
	__super::Run();
}

bool preKeyUp = false;
bool preKeyDown = false;

D2D1_MATRIX_3X2_F cameraMat;

void DemoGame::Update(float deltaTime)
{
	__super::Update(deltaTime);
	scene->Update(deltaTime);

	if (GetKeyState(VK_LBUTTON) < 0/* && !preKeyUp*/) {
		temp(scene);
	}
	if (GetKeyState(VK_RBUTTON) < 0 /*&& !preKeyDown*/) {
		//if(gs.size() > 2)
		//	gs.erase(--gs.end());
	}

	/*for (auto g : gs) {
		g->Update(deltaTime);
	}*/
	//testObj[0]->transform->m_RelativeRotation += deltaTime * 30.f;
	//testObj[1]->transform->m_RelativeRotation -= deltaTime * 70.f;
	//testObj[2]->transform->m_RelativeRotation += deltaTime * 150.f;
	preKeyUp = false;
	preKeyDown = false;
	preKeyUp = GetKeyState(VK_LBUTTON) < 0 ? true : false;
	preKeyDown = GetKeyState(VK_RBUTTON) < 0 ? true : false;

	float speed = GetKeyState(VK_LSHIFT) < 0 ? 200.f : 100.f;

	if (GetKeyState(0x44) < 0) {
		//g->transform->m_RelativeLocation.x += deltaTime * 100.f;
		trPos.x += deltaTime * speed;
	}
	if (GetKeyState(0x41) < 0) {
		//g->transform->m_RelativeLocation.x += deltaTime * -100.f;
		trPos.x += deltaTime * -speed;
	}
	if (GetKeyState(0x57) < 0) {
		//g->transform->m_RelativeLocation.y += deltaTime * 100.f;
		trPos.y += deltaTime * speed;
		
	}	
	if (GetKeyState(0x53) < 0) {
		//g->transform->m_RelativeLocation.y += deltaTime * -100.f;
		trPos.y += deltaTime * -speed;
		action.Excute("아 이게된다고????");
	}

	float cameraSpeed = deltaTime * 5.f;
	float x = gq->transform->m_RelativeLocation.x * (1.f - cameraSpeed) + trPos.x * cameraSpeed;
	float y = gq->transform->m_RelativeLocation.y * (1.f - cameraSpeed) + trPos.y * cameraSpeed;

	gq->transform->m_RelativeLocation.x = x;
	gq->transform->m_RelativeLocation.y = y;

	//cameraMat = 
	//	D2D1::Matrix3x2F::Scale(D2D1::SizeF(1.f, 1.f)) *
	//	D2D1::Matrix3x2F::Translation(pos.x, pos.y);
	//cameraMat = gq->transform->m_WorldTransform;
	//D2D1InvertMatrix(&cameraMat);
}
void DemoGame::Render(D2DRenderer* _render)
{
	__super::Render(_render);

	/*testObj[0]->transform->UpdateTrasnform();
	testObj[1]->transform->UpdateTrasnform();
	testObj[2]->transform->UpdateTrasnform();*/

	_render->DrawRectangle(20.f, 20.f, 50.f, 50.f, D2D1::ColorF::White);
	//_render->DrawBitmap();
	/*testObj[0]->Render();
	testObj[1]->Render();
	testObj[2]->Render();*/
	/*_render->DrawBitmap(testObj[0]->m_pBitmap, testObj[0]->transform->m_WorldTransform);
	_render->DrawBitmap(testObj[1]->m_pBitmap, testObj[1]->transform->m_WorldTransform);
	_render->DrawBitmap(testObj[2]->m_pBitmap, testObj[2]->transform->m_WorldTransform);*/
	//_render->DrawStringText(L"안녕!, 세계! Abg\n 어암ㅈ");

	/*count = 0;

	D2D1_MATRIX_3X2_F c = gq->transform->m_WorldTransform;
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
	ab.m_Extent = extentPos;*/

	//auto temp = D2D1::Matrix3x2F::Translation(gq->transform->m_RelativeLocation.x, gq->transform->m_RelativeLocation.y) * gq->transform->m_WorldTransform;
	// 카메라 센터 * 카메라 월드매트릭스 = 카메라 센터인 벡터? 뭐라하지 테스트해봐야함


	//for (auto g : gs) {
	//	if (!g->spriteAnim) continue;
	//	AABB lab = g->spriteAnim->GetBound();
	//	bool check = ab.CheckIntersect(lab);
	//	if (check) {
	//		g->Render(cameraMat);
	//		count++;
	//	}
	//}

	//D2DRenderer::getIncetance().DrawLine({ ab.GetMinX() + 100, ab.GetMinY()+ 100}, { ab.GetMinX()+ 100, ab.GetMaxY()- 100 }, 200.f, D2D1::ColorF::Green,  D2D1::Matrix3x2F::Identity());
	//D2DRenderer::getIncetance().DrawLine({ ab.GetMaxX() - 100, ab.GetMaxY()- 100}, { ab.GetMinX()+ 100, ab.GetMaxY()- 100 }, 200.f, D2D1::ColorF::Green,  D2D1::Matrix3x2F::Identity());
	//D2DRenderer::getIncetance().DrawLine({ ab.GetMaxX() - 100, ab.GetMaxY()- 100}, { ab.GetMaxX()- 100, ab.GetMinY()+ 100 }, 200.f, D2D1::ColorF::Green,  D2D1::Matrix3x2F::Identity());
	//D2DRenderer::getIncetance().DrawLine({ ab.GetMinX() + 100, ab.GetMinY()+ 100}, { ab.GetMaxX()- 100, ab.GetMinY()+ 100 }, 200.f, D2D1::ColorF::Green,  D2D1::Matrix3x2F::Identity());
	D2DRenderer::getIncetance().DrawLine({ 0.f, 0.f}, { 100.f, 100.f }, 2.f, D2D1::ColorF::Green, D2D1::Matrix3x2F::Identity());

	/*for (auto g : gs) {
		g->Render(cameraMat);
	}*/

	

	/*D2DRenderer::getRenderTarget().SetTransform(D2D1::Matrix3x2F::Identity());
	std::wstring tempS = std::to_wstring(_render->GetUsedVRAM()).c_str();
	tempS += L" Byte \n좌클릭 생성, 우클릭 삭제, wasd이동, shift 2배속\n";
	tempS += std::to_wstring(gq->transform->m_RelativeLocation.x).c_str();
	tempS += L"\n";
	tempS += std::to_wstring(gq->transform->m_RelativeLocation.y).c_str();
	tempS += L"\n카운트 수: ";
	tempS += std::to_wstring(count);

	_render->DrawStringText(tempS.c_str());*/
}

void DemoGame::Uninitialize()
{
	__super::Uninitialize();

}
