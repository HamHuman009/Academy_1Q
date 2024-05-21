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

	Gdiplus::Bitmap* Default_playerBitmap;
	Gdiplus::Bitmap* Default_playerBitmap_Paper;
	Gdiplus::Bitmap* Target_playerBitmap;
	Gdiplus::Bitmap* Target_playerBitmap_Paper;
	Gdiplus::Bitmap* TimeOver_playerBitmap;

	bool isScoopUp = false;
	float scoopUpTime = 0.f;
	float scale = 1.f;
	bool isOnScoopUpSound;

	bool isAwake;
	float awakeTime;
	
public:
	Event* pauseEvent;
	Player();
	~Player() override { 
		delete Default_playerBitmap;
		delete Default_playerBitmap_Paper;
		delete Target_playerBitmap;
		delete Target_playerBitmap_Paper;
		delete TimeOver_playerBitmap;
	}

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
	UINT BossCnt;
	WCHAR name[9];

	Event* feedbackEvent1_ifCrawCaptureScoreZero;
	Event* feedbackEvent2_ifCrawCaptureScoreOne;
	Event* feedbackEvent3_CaptureBossFish;
	Event* feedbackEvent4_CaptureFish;
	float event4timer = 0.f;
	float event4timerMax = 8.f;
	Event* feedbackEvent5_OneCaptureTwoKill;
	float event5timer = 0.f;
	float event5timerMax = 1.f;
	int event5count = 0;
	Event* feedbackEvent6_SevenScore;
	bool isSevenScore = false;

	Event* feedbackEvent9_10secNothingAnd14sec;
	float event9timer = 10.f;
	float event9timerMax = 10.f;
	float event9timerMaxAfter = 14.f;
	int prevCnt = 0;
	Event* feedbackEvent10_10secNothingAndRemain10sec;

	float alphaValue = 1.f;
	Event* temp;
	bool gameOver = false;

	Event* CatchBossFish;
};

