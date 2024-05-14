#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
void StartScene::Start() 
{

}

void StartScene::Init()
{	
	CResourceManager* CR = CResourceManager::GetInstance();
	myBitmap = CR->LoadBitmapResouce(L"image1",L"image1.png");
	UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ
	myBack->Init(myBitmap, { 100.f,100.f });

	SelectScnEvent* nextScnEvent = new SelectScnEvent(2); // ����ȯ �̺�Ʈ �׽�Ʈ
	UIButton* gameStartButton = new UIButton(Vector2{1600.0f,800.0f},nextScnEvent); // ��ü �׽�Ʈ
	
	AddObject(myBack);
	AddObject(gameStartButton);
}

StartScene::~StartScene() {

}

void StartScene::Exit() 
{

}
