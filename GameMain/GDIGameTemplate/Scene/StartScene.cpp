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


//void StartScene::Update() {
//	//if ((Input::GetMouseState().left && !Input::GetPrevMouseState().left)) {
//	//	CircleCollider temp = { Vector2(Input::GetMouseState().x,Input::GetMouseState().y), 1.0f };
//	//	
//	//	if (coll.CheckCollision(&temp, gameStartButton->m_collider)) {
//	//		gameStartButton->OnTrigger();
//	//	}
//	//}
//
//	for (int i = 0; i < m_arrObj.size(); i++) {
//		m_arrObj[i]->Update();
//	}
//}

StartScene::~StartScene() {

}

void StartScene::Exit() 
{

}
