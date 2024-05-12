#include "UIObject.h"

void UIObject::Init() {
	
}

void UIObject::Render() {

}


void UIObject::OnTrigger()
{

}

void UIBackGround::Init() {
	m_BackGround = Gdiplus::Bitmap::FromFile(L"image1.png");
}

void UIBackGround::Render() {
	
	cx = m_BackGround->GetWidth();
	cy = m_BackGround->GetHeight();
	Render::DrawImage(100,100,m_BackGround,0,0,cx,cy);
}

void UIButton::Init() {
	/*CResourceManager CR = CResourceManager::CResourceManager();
	m_Bitmap = CR.LoadBitmapResouce(L"¹öÆ°",L"sampleButton.png");*/
	m_pos = { 1600.f, 800.f };
	
	m_Bitmap = Gdiplus::Bitmap::FromFile(L"sampleButton.png");

	cx = m_Bitmap->GetWidth();
	cy = m_Bitmap->GetHeight();
	m_collider = new RectangleCollider({ 0,0 }, { cx, cy });
	m_collider->parent = this;
}

void UIButton::Render() {
	Render::DrawImage(m_pos.x, m_pos.y, m_Bitmap, 0, 0, cx, cy);
}

void UIButton::OnTrigger() {

}