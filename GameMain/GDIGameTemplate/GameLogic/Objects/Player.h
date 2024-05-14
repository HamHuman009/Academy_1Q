#pragma once
#include "Object.h"

class Player : public Object
{
private:
	float moveSpeed;
	float radius;
	Vector2 moveDirection;
	Event* pauseEvent;
public:
	Player();
	~Player();

	void Init() override;
	void Update(float delta) override;
	void Render() override;
	void OnTrigger() override;

	void movePlayer(float delta);

	void Up(float delta);
	void Down(float delta);
	void Left(float delta);
	void Right(float delta);
};

