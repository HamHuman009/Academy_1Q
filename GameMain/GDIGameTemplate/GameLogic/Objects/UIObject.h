#pragma once
#include "Object.h"
//#include "../Event.h"
#define BACK_GROUND_ANIM_FRAME 60

class UIObject : public Object
{
	// Object을(를) 통해 상속됨
	void Init() override;
	//void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;

public:
	float alpha = 1.f;
};

class UIImage : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Gdiplus::Bitmap* myBitMap, Vector2 myVector);
	UIImage() {};
	~UIImage() override {};//{ delete m_BackGround; }
	//void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	//void OnTrigger() override;
private:
	Gdiplus::Bitmap* m_BackGround;
};

class UIButton : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Vector2 myPos, Event* myEvent, Gdiplus::Bitmap* myBitMap);


	UIButton(Vector2 myPos, Event* myEvent, Gdiplus::Bitmap* myBitMap) {
		Init(myPos, myEvent, myBitMap);
		m_Event = myEvent;
		m_renderBounds = { {0.f, 0.f },{(float)x,(float)y} };
	}
	void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;
	~UIButton() override {}; /*{
		delete m_Bitmap;
	}*/

private:
	Gdiplus::Bitmap* m_Bitmap;
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 120;
	UINT y = 90;
};

// scnene init
//sceneTimer = new UITimer(Vector2{ x, y });
// scenen update 
//sceneTimer->Update(High_Resolution_Time::GetDeltaTime() / 1000.0f);
class UITimer : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(CResourceManager* CRM, Vector2 myPos, Event* myEvent, float _setTime);


	UITimer(CResourceManager* CRM, Vector2 myPos, Event* myEvent, float _setTime) {
		Init(CRM, myPos, myEvent, _setTime);
		//m_Event = myEvent;
		//m_renderBounds = { {(float)cx,(float)cy},{(float)x,(float)y} };
	}
	void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;
	~UITimer() override {}; /*{
		delete m_Bitmap;
	}*/

private:
	Gdiplus::Bitmap* m_BitmapClock;
	Gdiplus::Bitmap* m_BitmapBack;
	Gdiplus::Bitmap* m_BitmapBar;
	UINT cx;
	UINT cy;
	UINT x;
	UINT y;
	float deltaCx;
	float setTime;
	float deltaTime;
};

class UIBackGround : public UIObject
{
private:
	std::wstring m_fileName[BACK_GROUND_ANIM_FRAME];
	Gdiplus::Bitmap* m_bitmap[BACK_GROUND_ANIM_FRAME] = { nullptr, };
	int backGroundFrame;
	int backGroundFrameFlag;
	const static int backGroundFrameInterval = 10;

	float time = 0.f;
	float maxTime = 0.2f;
public:
	// Object을(를) 통해 상속됨
	void Init(const WCHAR* fileName, CResourceManager* CRM);
	void Update(float delta) override;
	void Render(float alpha) override;
	void FixedUpdate();
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	//void OnTrigger() override;
	~UIBackGround() override {};
	void LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM);


};

class UIDialog : public UIObject {
private:
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 0;
	UINT y = 0;
	WCHAR* string;
	WCHAR t_str[255];
	int strCount;
	float timer;
	const float maxTime = 0.1f;
public:
	~UIDialog()override {
		//delete[] string;
	};
	void Init(Vector2 myPos, Vector2 endPos, WCHAR* _string);
	//void Init(Vector2 myPos, Vector2)
	void Update(float delta) override;
	void Render(float alpha)override;
	void OnTrigger() override;
};

class UICrossDissolve : public UIObject {
	Gdiplus::Bitmap* m_BackGround;
	float alphaValue;
public:
	UICrossDissolve(Vector2 position, Gdiplus::Bitmap* bitmap, float alphatime = 1.f);
	void Init();
	void Update(float delta) override;
	void Render(float alpha) override;
};

class UIFace : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Vector2 myPos, Gdiplus::Bitmap* myBitMap, Event* myEvent = nullptr);

	UIFace(Vector2 myPos, Gdiplus::Bitmap* myBitMap) {
		Init(myPos, myBitMap);
		m_renderBounds = { {0.f, 0.f }, { (float)cx, (float)cy } };
	}

	UIFace(Vector2 myPos, Event* myEvent, Gdiplus::Bitmap* myBitMap) {
		Init(myPos, myBitMap, myEvent);
		m_renderBounds = { {0.f, 0.f }, { (float)cx, (float)cy } };
	}

	void Update(float delta) override;
	void Render(float alpha) override;

	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;

	void OnTrigger() override;
	~UIFace() override {}; /*{
		delete m_Bitmap;
	}*/

private:
	Gdiplus::Bitmap* m_Bitmap;
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 120;
	UINT y = 90;
};

class In_ScoreBoard : public UIObject
{
public:
	~In_ScoreBoard()override 
	{
		/*delete string;*/
	};
	void Init(Vector2 myPos, Vector2 endPos, std::wstring _string);
	void Update(float delta) override;
	void Render(float alpha) override;

	void OnTrigger() override;
private:
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 0;
	UINT y = 0;
	std::wstring string;
	

};

class UIInputField : public UIObject {
public:
	UIInputField(Vector2 position, float width, float height);
	~UIInputField() override {}
	void Init();
	void Update(float delta) override;
	void Render(float alpha) override;
	void OnTrigger() override;
	bool isInput;
	
private:
	int strCount;
	WCHAR inputStr[9]; // 8글자까지 9번째는 \0
	float timer;
};

class UISpeech : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Vector2 myPos, Gdiplus::Bitmap* myBitMap, Event* myEvent = nullptr);

	UISpeech(Vector2 myPos, Gdiplus::Bitmap* myBitMap) {
		Init(myPos, myBitMap);
		m_renderBounds = { {0.f, 0.f }, { (float)cx, (float)cy } };
	}

	UISpeech(Vector2 myPos, Event* myEvent, Gdiplus::Bitmap* myBitMap) {
		Init(myPos, myBitMap, myEvent);
		m_renderBounds = { {0.f, 0.f }, { (float)cx, (float)cy } };
	}

	void Update(float delta) override;
	void Render(float alpha) override;

	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;

	void OnTrigger() override;
	~UISpeech() override {}

	void AddFeedback(int feedbackNumber) {
		if (elepsedTime > 1.5f)
			feedbackQueue.push(feedbackNumber);

		std::cout << "button click" << std::endl;
	}

private:
	Gdiplus::Bitmap * m_Bitmap;
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 120;
	UINT y = 90;
	WCHAR string[255];
	WCHAR t_str[255];
	int strCount;
	float timer;
	const float maxTime = 0.1f;
	float elepsedTime;
	bool textEnd = false;

	float ignoreTimer = 0.f;
	std::vector<int> feedbackSort;

	std::vector<int> ignoreQueue;

	std::queue<int> feedbackQueue;
	void GetFeedBack(int feedbackNumber, WCHAR* out);
};