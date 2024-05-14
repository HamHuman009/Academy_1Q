#pragma once
#include "../stdafx.h"
#include "../GameLogic/Collider.h"
#include "../Scene/CScene.h"

class ColliderManager
{
private:
	std::vector<Collider*> colliders[(UINT)TYPE::END];
public:
	ColliderManager();
	~ColliderManager();

	void Init();
	void Update();
	
	void PushCollider(Collider* collider, TYPE type);
	void ClearColliders();

	bool CheckCollision(Collider* lhs, Collider* rhs);

	void PointCollision(Vector2 point, Collider* rhs);

	Collider* GetCurrentPointCollider(Vector2 point);

	Collider* GetCurrentPointCollider(Vector2 point, TYPE type);
};

