#include "IntroScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"

IntroScene::IntroScene()
{

}

IntroScene::~IntroScene()
{

}

void IntroScene::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"������������������������������ by passing a RectF to the DrawString method.";

	wcscpy_s(_str, 255, t_str);


	CResourceManager* CR = CResourceManager::GetInstance();
	Gdiplus::Bitmap* myBitmap = CR->LoadBitmapResouce(L"image1", L"image1.png");
	UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ
	myBack->Init(myBitmap, { 500.f,400.f });

	UIDialog* dialog = new UIDialog();
	dialog->Init({ 100.f,100.f }, { 500.f,400.f }, _str);

	SelectScnEvent* e_NextScn = new SelectScnEvent(2); // ����ȯ �̺�Ʈ �׽�Ʈ
	AddEvent(e_NextScn);
	AddObject(myBack);
	AddObject(dialog);
}


void IntroScene::Start()
{
}

void IntroScene::Exit()
{
}

