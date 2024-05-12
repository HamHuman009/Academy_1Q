#pragma once
#include "Object.h"

class Fish : public Object {
private:
	float speed;
	Vector2 m_moveDirection;
	Vector2 m_AngulerDirection;
	void Move(float delta);
	void AngularVelocity(float delta);

public:
	void Init() override;
	void Update(float delta) override;
	void Render() override;
	void OnTrigger() override;
};