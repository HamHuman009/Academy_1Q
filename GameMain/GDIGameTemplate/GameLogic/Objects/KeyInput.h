#pragma once
#include "Object.h"

class KeyInput : public Object
{
private:
	bool acceptKey[256];
	float m_delay = 0;
	float m_elapsedTime = 0;
	bool m_delayActive = false;

public:
	KeyInput() {
		for (int i = 0; i < 256; i++) {
			acceptKey[i] = false;
		}
	}
	KeyInput(bool _acceptKey[256]) {
		for (int i = 0; i < 256; i++) {
			acceptKey[i] = _acceptKey[i];
		}
	}

	void Init() override;
	void Init(float i);
	void Update(float delta) override;
	void OnTrigger() override;

};

