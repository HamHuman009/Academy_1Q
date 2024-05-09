#include "Component.h"
#include "GameObject.h"
#include <typeinfo>
#include "Transform.h"
namespace Engine {
	Component::Component() {
		thisGameObject = nullptr;
	}
	Transform* Component::GetTransform() {
		if (thisGameObject != nullptr)
		{
			//return thisGameObject->transform;
			DoubleLinkedList<Component*>::Iterator iter = thisGameObject->components.begin();
			for (; iter != thisGameObject->components.end(); ++iter) {
				if (typeid(iter.pCurr->data) == typeid(Transform))
				{
					Transform* tr = dynamic_cast<Transform*>(iter.pCurr->data);
					return tr;
				}
				//auto temp = dynamic_cast<Transform*>(iter.pCurr->data)
			}
			//return thisGameObject->components.;
		}
		else {
			return nullptr;
		}
	}

	bool Component::Compare(const Component& component) {
		return typeid(component).name() == typeid(this).name();
	}

	Component* Component::component() const {
		return nullptr;
	}
}











/*
#include <Functional>

////////////////////////////////////////////////////////////
namespace a {
	struct Vector2 {
		float x;
		float y;
	};


	class Component {
	public:
		virtual void Update(float deltaTime) = 0;
	};



	class ComponentB final : public Component {
	public:
		void Update(float deltaTime) override {

		}
	};

	class ComponentA final : public Component {
	public:
		void Update(float deltaTime) override {
			ComponentB* cb = _GetComponentB();
		}

		void BindGetComponentB(std::function<ComponentB* ()> getComponentB) {
			_GetComponentB = getComponentB;
		}

	private:
		std::function<ComponentB* ()> _GetComponentB;
	};
	class TransformComponenet final : public Component {
	public:
		Vector2 GetTransform() const {
			return _transform;
		}
		void Update(float deltaTime) override {

		}
	private:
		Vector2 _transform;
	};

	class MovementComponent final : public Component {
		void Update(float deltaTime) override {
			*_worldTransform += _direction * _speed * deltaTime;
		}

	private:
		float _speed;
		Vector2 _direction;
		Vector2* _worldTransform;
	};


	class GameObject {
	public:
		Vector2 GetTransform() const {
			return _transformComponent->GetTransform();
		}
		void AddComponent(Component* component) {
			_components.PushBack(component);
		}
		void AddComponent(TransformComponenet* transformComponent) {
			_transformComponent = transformComponent;
			AddComponent((Component*)transformComponent);
		}

		void Update(float deltaTime) {
			for (const auto& component : _components) {
				component->Update(deltaTime);
			}
		}

		template<typename T>
		T*& GetComponentByType() {
			for (auto& component : _components) {
				if (T*& targetComponent = dynamic_cast<T*>(component)) return targetComponent;
			}
		}

	private:
		DoubleLinkedList<Component*> _components;
		TransformComponenet* _transformComponent;
	};

	class AObject final : public GameObject {
	public:
		AObject() {
			ComponentA* ca = new ComponentA;
			ca->BindGetComponentB([this]() {
				return GameObject::GetComponentByType<ComponentB>
				}
			);
		}
	};

	class Scene {
	public:
		void Update(float deltaTime) {
			for (const auto& object : _objects) {
				object->Update(deltaTime);
			}
		}
	private:
		DoubleLinkedList<GameObject*> _objects;
	};

	class Engine {
	public:
		void Update() {
			_scene->Update(Time::GetDeltaTime());
		}
	private:
		Scene* _scene;

	};
}
*/