#pragma once
#include "Object.h"
class UIObject : public Object
{
	// Object을(를) 통해 상속됨
	void Init() override;
	//void Update(float delta) override;
	void Render()override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override;
};

class UIBackGround : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init() override;
	UIBackGround() {
		Init();
	}
	//void Update(float delta) override;
	void Render()override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	//void OnTrigger() override;
private:
	Gdiplus::Bitmap* m_BackGround;
	UINT cx = 0;
	UINT cy = 0;
};

class UIButton : public UIObject
{
	// Object을(를) 통해 상속됨
public:
	void Init() override;
	/*UIButton() {
		Init();
		m_renderBounds = { {(float)cx,(float)cy},{(float)x,(float)y} };
	}*/

	UIButton(/*Event* myEvent*/) {
		Init();
		//m_Event = myEvent;
		m_renderBounds = { {(float)cx,(float)cy},{(float)x,(float)y} };
	}
	//void Update(float delta) override;
	void Render()override;
	//void SetMotion(int index)override;
	//void UpdateAnimation(float delta)override;
	//void ChangeStatus(ObjectStatus status)override;
	void OnTrigger() override {
		//if (m_Event != nullptr) m_Event->OnTrigger();
	}

	
private:
	Gdiplus::Bitmap* m_Bitmap;
	UINT cx = 0;
	UINT cy = 0;
	UINT x = 1600;
	UINT y = 800;
};

