#include "Object.h"
namespace Engine {

	const bool Object::Equals(Object* other) const {
		return this->instanceID == other->instanceID;
	}
	Object::Object() {
		this->name = nullptr;
		this->instanceID = staticInstanceID;
		staticInstanceID++;
	}
	Object::Object(char* name) {
		this->name = name;
		this->instanceID = staticInstanceID;
		staticInstanceID++;
	}
	Object::~Object() {
		if(name != nullptr)
			delete[] name;
	}
	unsigned int Object::staticInstanceID = 0;
}