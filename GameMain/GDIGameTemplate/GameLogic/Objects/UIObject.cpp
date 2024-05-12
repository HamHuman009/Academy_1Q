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
	m_Bitmap = Gdiplus::Bitmap::FromFile(L"sampleButton.png");
	m_pos = { 500.f, 300.f };
}

void UIButton::Render() {
	
	cx = m_Bitmap->GetWidth();
	cy = m_Bitmap->GetHeight();
	Render::DrawImage(m_pos.x, m_pos.y, m_Bitmap, 0, 0, cx, cy);
}

void UIButton::OnTrigger() {

}