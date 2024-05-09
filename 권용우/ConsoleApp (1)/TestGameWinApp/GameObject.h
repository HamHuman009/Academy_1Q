#pragma once
#include "Object.h"
#include "DataStruct.h"


namespace Engine {
	class Transform;
	class Collider;
	class Component;
	class GameObject : public Object
	{
	public:
		GameObject();
		//Transform* transform;
		//Collider* collider;

		GameObject* parent;
		DoubleLinkedList<GameObject*> child;
		DoubleLinkedList<Component*> components;

		Transform* GetTransform();
	};
}

