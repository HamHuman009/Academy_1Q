#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
void StartScene::Start() 
{

}

void StartScene::Init()
{	
	myBack = new UIBackGround();
	SelectScnEvent* nextScnEvent = new SelectScnEvent(2);
	gameStartButton = new UIButton(Vector2{1600.0f,800.0f},nextScnEvent);
	
	gameStartButton->m_collider = new RectangleCollider(Vector2(0.0f,0.0f), gameStartButton->m_renderBounds.extents.x, gameStartButton->m_renderBounds.extents.y);
	gameStartButton->m_collider->parent = gameStartButton;
	AddObject(myBack);
	AddObject(gameStartButton);
	
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
