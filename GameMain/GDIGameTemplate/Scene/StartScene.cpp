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
	UIImage* myBack = new UIImage(); // 객체 테스트
	myBack->Init(myBitmap, { 100.f,100.f });

	SelectScnEvent* nextScnEvent = new SelectScnEvent(2); // 씬전환 이벤트 테스트
	UIButton* gameStartButton = new UIButton(Vector2{1600.0f,800.0f},nextScnEvent); // 객체 테스트
	
	AddObject(myBack);
	AddObject(gameStartButton);
}

StartScene::~StartScene() {

}

void StartScene::Exit() 
{

}
