#pragma once
#include "Object.h"

class KeyInput : public Object
{
public:
	void Init() override;
	void Update(float delta) override;
	void OnTrigger() override;

};

