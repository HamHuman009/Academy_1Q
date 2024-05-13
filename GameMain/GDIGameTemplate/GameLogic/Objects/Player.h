#pragma once
#include "../GameLogic/Objects/Object.h"

class Player : public Object
{
private:
	float moveSpeed;
public:
	void Init() override;
	void Update(float delta) override;
	void Render() override;
	void OnTrigger() override;
};

