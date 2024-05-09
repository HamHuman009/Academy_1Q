#include <iostream>
#include "GameObject.h"
#include "Transform.h"
#include "Collider.h"

namespace Engine {
	GameObject::GameObject() {
		//transform = new Transform();
		//collider = new Collider();
		parent = nullptr;

		//transform->thisGameObject = this;
		//collider->thisGameObject = this;
		this->name = new char[11];	//�� strlen(name)�� �ϸ� 15�ϱ�. �ϴ� const���̷� ��ȯ.
		strcpy_s(this->name, strlen("GameObject") + 1, "GameObject");
	}

	Transform* GameObject::GetTransform() {
		DoubleLinkedList<Component*>::Iterator iter = components.begin();
		for (; iter != components.end(); ++iter) {
			if (typeid(iter.pCurr->data) == typeid(Transform))
			{
				Transform* tr = dynamic_cast<Transform*>(iter.pCurr->data);
				return tr;
			}
		}
		return nullptr;
	}
}