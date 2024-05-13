#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
void StartScene::Start() 
{

}

void StartScene::Init()
{	
	UIBackGround* myBack = new UIBackGround(); // 객체 테스트
	SelectScnEvent* nextScnEvent = new SelectScnEvent(2); // 씬전환 이벤트 테스트
	UIButton* gameStartButton = new UIButton(Vector2{1600.0f,800.0f},nextScnEvent); // 객체 테스트
	
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
