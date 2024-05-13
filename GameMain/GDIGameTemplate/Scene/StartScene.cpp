#include "StartScene.h"
#include "../System/InputSystem.h"

void StartScene::Start() 
{

}

void StartScene::Init()
{	
	myBack = new UIBackGround();
	//SelectScnEvent* nextScnEvent = new SelectScnEvent(2);
	gameStartButton = new UIButton();
	gameStartButton->Init();
	//myButton->m_collider = new RectangleCollider(Vector2(0.0f,0.0f),myButton->m_renderBounds.extents.x, myButton->m_renderBounds.extents.y);
	//myButton->m_collider->parent = myButton;
	AddObject(myBack);
	AddObject(gameStartButton);
	
}

void StartScene::Render() //이 부분 고칠 것.
{	
	for (int i = 0; i < m_arrObj.size(); i++) {
		m_arrObj[i]->Render();

	}
}

void StartScene::Update() {
	if ((Input::GetMouseState().left && !Input::GetPrevMouseState().left)) {
		CircleCollider temp = { Vector2(Input::GetMouseState().x,Input::GetMouseState().y), 1.0f };
		
		if (coll.CheckCollision(&temp, gameStartButton->m_collider)) {
			gameStartButton->OnTrigger();
		}
	}
}

void StartScene::FixedUpdate() {

}

void StartScene::Exit() 
{
	
}
