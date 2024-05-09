#pragma once
#include "Component.h"
#include "GameStruct.h"

namespace Engine {
	class Transform : public Component
	{
	public:
		Transform();
		Vector2 position;
	};
}

