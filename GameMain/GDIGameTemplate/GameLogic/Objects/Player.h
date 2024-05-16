#pragma once
#include "Object.h"
class Event;

class Player : public Object
{
private:
	float moveSpeed;
	float radius;
	Vector2 moveDirection;
	bool flag;

	Gdiplus::Bitmap* playerBitmap;

	bool isScoopUp = false;
	float scoopUpTime = 0.f;
	float scale = 1.f;
	bool isOnScoopUpSound;

	//bool r = false;
public:
	Event* pauseEvent;
	Player();
	~Player();

	void Init() override;
	void Update(float delta) override;
	void Render(float alpha) override;
	void OnTrigger() override;

	void movePlayer(float delta);
	void ScoopUp(float delta);

	void Up(float delta);
	void Down(float delta);
	void Left(float delta);
	void Right(float delta);

	void SetStatus();
};

