#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
void StartScene::Start() 
{

}

void StartScene::Init()
{	
	UIBackGround* myBack = new UIBackGround(); // ��ü �׽�Ʈ
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
