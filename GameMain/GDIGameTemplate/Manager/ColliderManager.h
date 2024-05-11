#pragma once
#include "../stdafx.h"
#include "../GameLogic/Collider.h"
class ColliderManager
{
private:
	std::vector<Collider*> colliders;

	bool CheckCollision(Collider* lhs , Collider* rhs);
public:
	ColliderManager();
	~ColliderManager();

	void Init();
	void Update();
	
	void PushCollider(Collider* collider);
	void ClearColliders();
};

