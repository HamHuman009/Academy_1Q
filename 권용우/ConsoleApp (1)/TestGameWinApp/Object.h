#pragma once
namespace Engine {

	class Object
	{
	public:
		static unsigned int staticInstanceID;
		unsigned int instanceID;
		char* name;

		Object();
		Object(char* name);
		~Object();

		const bool Equals(Object* other) const;
	};
}

