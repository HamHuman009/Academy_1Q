#pragma once
#include "Object.h"

class KeyInput : public Object
{
private:
	float m_delay = 0;
	float m_elapsedTime = 0;
	bool m_delayActive = false;
public:
	void Init() override;
	void Init(float i);
	void Update(float delta) override;
	void OnTrigger() override;

};

