#pragma once
#include "Object.h"
class UIObject : public Object
{
	// Object��(��) ���� ��ӵ�
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
	// Object��(��) ���� ��ӵ�
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
};

