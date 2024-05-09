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

		// 상속받는 component 문제 해결해야함.
		/*virtual Component component const() {

		}*/
	};
}

