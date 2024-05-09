#pragma once
#include "Object.h"
#include <typeinfo>

namespace Engine {
	class GameObject;
	class Transform;
	/// <summary>
	/// ������Ʈ�� �׻� ���ӿ�����Ʈ�� ����Ǿ�߸� ����� ��.
	/// </summary>
	class Component : public Object
	{
	public:
		Component();
		GameObject* thisGameObject;
		Transform* GetTransform();
		
		bool Compare(const Component& component);
		virtual Component* component() const;
		/*virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void FixedUpdate() = 0;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnQuit() = 0;*/
	};
}

