#include "UIObject.h"
#include "../Event.h"
void UIObject::Init() {

}

void UIObject::Render() {

}


void UIObject::OnTrigger()
{

}

void UIImage::Init(Gdiplus::Bitmap* myBitMap, Vector2 myVector) {
	//CResourceManager* CR = CResourceManager::GetInstance();
	//m_BackGround = CR->LoadBitmapResouce(L"image1",L"image1.png");
	//m_BackGround = Gdiplus::Bitmap::FromFile(L"image1.png");
	m_BackGround = myBitMap;
	m_renderBounds = { {0.f, 0.f}, {myBitMap->GetWidth() / 2.f, myBitMap->GetHeight() / 2.f} };
	m_pos = myVector;
}

void UIImage::Render() {
	//0x00000147f3f723d0
	Render::DrawImage(m_pos.x, m_pos.y, m_BackGround, 0, 0, m_renderBounds.extents.x * 2, m_renderBounds.extents.y * 2);
}

void UIButton::Init(Vector2 myPos, Event* myEvent) {
	/*CResourceManager CR = CResourceManager::CResourceManager();
	m_Bitmap = CR.LoadBitmapResouce(L"��ư",L"sampleButton.png");*/
	m_pos = myPos;
	m_Event = myEvent;
	m_Bitmap = Gdiplus::Bitmap::FromFile(L"sampleButton.png");

	cx = m_Bitmap->GetWidth();
	cy = m_Bitmap->GetHeight();
	m_collider = new RectangleCollider({ 0.f,0.f }, { (float)cx, (float)cy });
	m_collider->parent = this;
}

void UIButton::Render() {
	Render::DrawImage(m_pos.x - m_renderBounds.extents.x, m_pos.y - m_renderBounds.extents.y, m_Bitmap, 0, 0, cx, cy);
}

void UIButton::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

void UIButton::Update(float delta) {
	if (Input::GetMouseState().left && !Input::GetPrevMouseState().left) {
		Vector2 temp = Vector2(Input::GetMouseState().x, Input::GetMouseState().y);
		if (m_collider->isPointColliding(temp)) {
			OnTrigger();
		}
	}
}


void UITimer::Init(Vector2 myPos, Event* myEvent) {
	/*CResourceManager CR = CResourceManager::CResourceManager();
	m_Bitmap = CR.LoadBitmapResouce(L"��ư",L"sampleButton.png");*/
	m_pos = myPos;
	m_Event = myEvent;
	//m_Bitmap = Gdiplus::Bitmap::FromFile(L"sampleButton.png");

	//cx = m_Bitmap->GetWidth();
	//cy = m_Bitmap->GetHeight();
	cx = 400;
	cy = 100;
	//m_collider = new RectangleCollider({ 0.f,0.f }, { (float)cx, (float)cy });
	//m_collider->parent = this;
	deltaCx = 400;
}
void UITimer::Update(float delta) {
	setTime -= delta;
	/*std::cout << "delta : " << delta << endl;
	std::cout << "setTime : " << setTime << endl;*/
	//�پ�� ���� ����  = (���ѽð����� delta��ũ �پ�� �ñ⳪ / ���� �ð� ) * ���� ���� ��
	if (setTime > 0) {
		deltaCx = (setTime / 60.0f) * cx;
	}
	else {
		OnTrigger();
		m_Event = nullptr;
	}
}

void UITimer::Render() {
	Render::DrawRect(m_pos.x, m_pos.y, cx, cy, RGB(255, 255, 255));
	Render::DrawRect(m_pos.x, m_pos.y, (UINT)deltaCx, cy, RGB(255, 255, 0));
}

void UITimer::OnTrigger() {
	if (m_Event != nullptr) m_Event->OnTrigger();
}

