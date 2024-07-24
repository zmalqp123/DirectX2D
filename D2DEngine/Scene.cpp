#include "pch.h"
#include "Scene.h"
#include "D2DRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "SpriteAnimation.h"
#include "Rigidbody2D.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Start()
{
}
void Scene::Update(float deltaTime)
{
	/*std::vector<Collider*> collider;
	for (auto& g : m_GameObjects) {
		for (auto& coll : g->components) {
			if (Collider* c = dynamic_cast<Collider*>(coll)) {
				collider.push_back(c);
			}
			else {
				continue;
			}
		}
	}
	for (int i = 0; i < collider.size(); i++) {
		collider[i]->prevPosition = collider[i]->gameObject->transform->m_RelativeLocation;
	}*/

	for (auto gameObject : m_GameObjects) {
		gameObject->Update(deltaTime);
	}
	cameraMat = cam->transform->m_WorldTransform;
	D2D1InvertMatrix(&cameraMat);

	// collider
	std::vector<Collider*> colliders;
	for (auto& g : m_GameObjects) {
		for (auto& coll : g->components) {
			if (Collider* c = dynamic_cast<Collider*>(coll)) {
				c->ClearAndBackupCollideState();
				colliders.push_back(c);
			}
			else {
				continue;
			}
		}
	}

	for (int i = 0; i < colliders.size(); i++) {

		for (int target = i + 1; target < colliders.size(); target++) {
			Vector2 resolution;
			if (colliders[i]->gameObject == colliders[target]->gameObject) continue;
			if (!colliders[i]->isCollide(colliders[target], resolution)) continue;

			if (colliders[i]->GetCollisionType() == CollisionType::Block &&
				colliders[target]->GetCollisionType() == CollisionType::Block)
			{
				Vector2 aVelocity, bVelocity; // 이동량 구하기
				aVelocity = colliders[i]->gameObject->transform->m_RelativeLocation - colliders[i]->prevPosition;
				bVelocity = colliders[target]->gameObject->transform->m_RelativeLocation - colliders[target]->prevPosition;

				if (!colliders[i]->isKinemetic && !colliders[target]->isKinemetic) {
					colliders[i]->AddPosition({ resolution.x / 2 , resolution.y / 2 });
					colliders[target]->AddPosition({ -resolution.x / 2 , -resolution.y / 2 });
				}
				else if (!colliders[i]->isKinemetic) {
					colliders[i]->AddPosition({ resolution.x , resolution.y });
				}
				else if (!colliders[target]->isKinemetic) {
					colliders[target]->AddPosition({ -resolution.x , -resolution.y });
				}

				Vector2 collisionNormal = { resolution.x != 0 ? resolution.x : 0, resolution.y != 0 ? resolution.y : 0 };
				float length = std::sqrt(collisionNormal.x * collisionNormal.x + collisionNormal.y * collisionNormal.y);
				if (length != 0) {
					collisionNormal.x /= length;
					collisionNormal.y /= length;
				}

				float dotProduct1 = aVelocity.x * collisionNormal.x + aVelocity.y * collisionNormal.y;
				float dotProduct2 = bVelocity.x * collisionNormal.x + bVelocity.y * collisionNormal.y;

				Vector2 projection1 = { dotProduct1 * collisionNormal.x, dotProduct1 * collisionNormal.y };
				Vector2 projection2 = { dotProduct2 * collisionNormal.x, dotProduct2 * collisionNormal.y };

				if (!colliders[i]->isKinemetic) {
					colliders[i]->AddPosition(projection1 * -1.f);
				}

				if (!colliders[target]->isKinemetic) {
					colliders[target]->AddPosition(projection2 * -1.f);
				}

				colliders[i]->ProcessBlock(colliders[target]);
				colliders[target]->ProcessBlock(colliders[i]);
			}
			else {
				colliders[i]->InsertCollideState(colliders[target]);
				colliders[target]->InsertCollideState(colliders[i]);
			}
		}
	}

	for (auto& pColl : colliders) {
		pColl->ProcessOverlap();
	}
}

void Scene::Render(D2DRenderer* _render)
{
	D2D1_MATRIX_3X2_F c = cam->transform->m_WorldTransform;
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

	AABB camAABB;
	camAABB.m_Center = centerPos;
	camAABB.m_Extent = extentPos;

	//auto temp = D2D1::Matrix3x2F::Translation(gq->transform->m_RelativeLocation.x, gq->transform->m_RelativeLocation.y) * gq->transform->m_WorldTransform;
	// 카메라 센터 * 카메라 월드매트릭스 = 카메라 센터인 벡터? 뭐라하지 테스트해봐야함


	for (auto g : m_GameObjects) {
		/*if (!g->spriteAnim) continue;
		AABB lab = g->spriteAnim->GetBound();
		bool check = camAABB.CheckIntersect(lab);
		if (check) {
			g->Render(cameraMat);
		}*/

		for (auto cRender : g->components) {
			cRender->Render(cameraMat);
		}
	}
}

void Scene::Clear()
{
	for (auto gameObject : m_GameObjects) {
		delete gameObject;
	}
	m_GameObjects.clear();
}

void Scene::SetCullingBound(AABB* pBound)
{
}
