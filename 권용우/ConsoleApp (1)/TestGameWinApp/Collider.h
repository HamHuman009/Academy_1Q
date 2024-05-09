#pragma once
#include "Component.h"
#include "GameStruct.h"

namespace Engine {
	class Collider final : public Component
	{
	public:
		Collider();
		bool isCollision(Collider& collider);
		Bounds bounds;

		// ��ӹ޴� component ���� �ذ��ؾ���.
		/*virtual Component component const() {

		}*/
	};
}

