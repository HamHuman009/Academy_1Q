#pragma once
#include "Object.h"
//#include "../Event.h"
#define BACK_GROUND_ANIM_FRAME 60
#define INTRO_ANIM_FRAME 20

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
	void Init(Vector2 myPos, Event* myEvent, const std::wstring& _strkey, const std::wstring& _extention);


	UIButton(Vector2 myPos, Event* myEvent, const std::wstring& _strkey, const std::wstring& _extention) {
		Init(myPos, myEvent, _strkey, _extention);
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
	Gdiplus::Bitmap* m_Bitmap_On;
	Gdiplus::Bitmap* m_Bitmap_Off;
	Gdiplus::Bitmap* m_CurBitMap;
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

	Event* remainningTimeEvent;
	bool isOn = false;
	Event* gameOverTimerEvent;
	bool isGameOverOn = false;

	Event* tutorialEvent2;
	Event* tutorialEvent3;
	Event* tutorialEvent4;
	Event* tutorialEvent5;
	bool istutorial2 = false;
	bool istutorial3 = false;
	bool istutorial4 = false;
	bool istutorial5 = false;
private:
	Gdiplus::Bitmap* m_BitmapClock;
	Gdiplus::Bitmap* m_BitmapBack;
	Gdiplus::Bitmap* m_BitmapBar;
	Gdiplus::Bitmap* m_BitmapLeft;
	Gdiplus::Bitmap* m_BitmapRight;
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
	WCHAR string[255];
	WCHAR t_str[255];
	int strCount;
	float timer;
	const float maxTime = 0.1f;
	COLORREF m_Color;
	int fontSize;
public:
	~UIDialog()override {
		//delete[] string;
	};
	void Init(Vector2 myPos, Vector2 endPos, WCHAR* _string, int _fontSize = 24, COLORREF _Color = RGB(0,0,0));
	//void Init(Vector2 myPos, Vector2)
	void Update(float delta) override;
	void Render(float alpha) override;
	void OnTrigger() override;
};

class UICrossDissolve : public UIObject {
	Gdiplus::Bitmap* m_BackGround;
	float alphaValue;
	bool isClickable;
public:
	UICrossDissolve(Vector2 position, Gdiplus::Bitmap* bitmap, float alphatime = 1.f, bool _isClickable = false);
	void Init();
	void Update(float delta) override;
	void Render(float alpha) override;
};

class UIFace : public UIObject
{
	// Object을(를) 통해 상속됨
public:

	UIFace(Vector2 myPos, Gdiplus::Bitmap* normalFace, Gdiplus::Bitmap* sadFace, Gdiplus::Bitmap* smileFace, Gdiplus::Bitmap* happyFace) {
		m_Bitmap = normalFace;
		m_faceImage[0] = normalFace;
		m_faceImage[1] = sadFace;
		m_faceImage[2] = smileFace;
		m_faceImage[3] = happyFace;

		Init(myPos, m_Bitmap);
	}

	void Init(Vector2 myPos, Gdiplus::Bitmap* myBitMap);
	void Update(float delta) override;
	void Render(float alpha) override;

	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;

	void OnTrigger() override;
	~UIFace() override {} /*{
		delete m_Bitmap;
	}*/

	void SetFace(int faceNumber, float duration); // 0 노멀, 1 슬픔, 2 웃음, 3 행복
private:
	Gdiplus::Bitmap* m_Bitmap;
	Gdiplus::Bitmap* m_faceImage[4];
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 120;
	UINT y = 90;

	float timer = 0.f;
};

class In_ScoreBoard : public UIObject
{
public:
	~In_ScoreBoard()override 
	{
		/*delete string;*/
	};
	void Init(CResourceManager* CRM, Vector2 myPos, Vector2 endPos, Gdiplus::Bitmap* _bitmap, Gdiplus::Bitmap* _targetGray, std::wstring _string);
	void Update(float delta) override;
	void Render(float alpha) override;

	void OnTrigger() override;

	void SwapBitmap();
private:
	Gdiplus::Bitmap* m_bitmapBack;
	Gdiplus::Bitmap* m_bitmapTarget;
	Gdiplus::Bitmap* m_bitmapTargetGray;
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

enum Speechenum {
	TUTORIALONE_Explanation_Control,
	TUTORIALTWO_Explanation_Scoop,
	TUTORIALTHREE_Explanation_Boss,
	TUTORIALFOUR_Explanation_REMAINNINGTIME,
	TUTORIALFIVE_Explanation_CRAW,

	IfCrawCaptureScoreZero,
	IfCrawCaptureScoreOne,
	CaptureBossFish,
	CaptureFish,
	RemainningTime,
	CrawAppear,
	OneCaptureTwoKill,
	SevenScore,
	TenSecNothingAnd14sec,
	Encouragement,
	StageStart
};

class UISpeech : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init(Vector2 myPos, Gdiplus::Bitmap* myBitMap, Event* myEvent = nullptr);

	UISpeech(Vector2 myPos, Gdiplus::Bitmap* myBitMap) {
		Init(myPos, myBitMap);
		m_renderBounds = { {0.f, 0.f }, { (float)cx, (float)cy } };
		feedbackSort.push_back(Speechenum::StageStart);
		elepsedTime = 1.6f;
	}

	UISpeech(Vector2 myPos, Event* myEvent, Gdiplus::Bitmap* myBitMap) {
		Init(myPos, myBitMap, myEvent);
		m_renderBounds = { {0.f, 0.f }, { (float)cx, (float)cy } };
		feedbackSort.push_back(Speechenum::StageStart);
		elepsedTime = 1.6f;
	}

	void Update(float delta) override;
	void Render(float alpha) override;

	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;

	void OnTrigger() override;
	~UISpeech() override {}

	void AddFeedback(Speechenum feedbackNumber) {
		if (elepsedTime > 1.5f || (UINT)feedbackNumber < 5) {
			feedbackSort.push_back(feedbackNumber);
			nothingTimer = 10.f;
		}

		std::cout << "button click" << std::endl;
	}

	UIFace* face;
	bool isTutorial = false;
private:
	Gdiplus::Bitmap * m_Bitmap;
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 120;
	UINT y = 90;
	WCHAR string[500];
	WCHAR t_str[500];
	int strCount;
	float timer;
	const float maxTime = 0.1f;
	float elepsedTime;
	bool textEnd = false;

	float nothingTimer = 10.f;

	float ignoreTimer = 0.f;
	std::vector<Speechenum> feedbackSort;
	void GetFeedBack(Speechenum feedbackNumber, WCHAR* out);

};


class UIIntroBack : public UIObject
{
private:
	std::wstring m_fileName[INTRO_ANIM_FRAME];
	Gdiplus::Bitmap* m_bitmap[INTRO_ANIM_FRAME] = { nullptr, };
	int backGroundFrame;
	int backGroundFrameFlag;

public:
	
	void Init(const WCHAR* fileName, CResourceManager* CRM);

	void Update(float delta) override;
	void Render(float alpha) override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;
	~UIIntroBack() override {};
	void LoadAnimImage(const WCHAR* fileName, CResourceManager* CRM);
	UICrossDissolve* Cross;
};