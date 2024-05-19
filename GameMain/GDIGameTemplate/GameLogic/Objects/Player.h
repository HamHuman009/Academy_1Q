#pragma once
#include "Object.h"

class Event;

class Player : public Object
{
private:
	float moveSpeed;
	float radius;
	Vector2 moveDirection;
	Vector2 up = { 0.f, -1.f };
	Vector2 down = { 0.f, 1.f };
	Vector2 left = { -1.f, 0.f };
	Vector2 right = { 1.f, 0.f };

	Gdiplus::Bitmap* playerBitmap;

	bool isScoopUp = false;
	float scoopUpTime = 0.f;
	float scale = 1.f;
	bool isOnScoopUpSound;

	bool isAwake;
	float awakeTime;
public:
	Event* pauseEvent;
	Player();
	~Player() override { delete playerBitmap; }

	void Init() override;
	void Update(float delta) override;
	void Render(float alpha) override;
	void OnTrigger() override;

	void movePlayer(float delta);
	void ScoopUp(float delta);
	void SetMoveDirection(Vector2 _up, Vector2 _down, Vector2 _left, Vector2 _right);
	void SoberUp();
	void CancelSoberUp();
	UINT cnt;
};

