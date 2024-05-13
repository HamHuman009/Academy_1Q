#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
void StartScene::Start() 
{

}

void StartScene::Init()
{	
	SelectScnEvent* nextScnEvent = new SelectScnEvent(2);
	/*gameStartButton->m_collider = new RectangleCollider(Vector2(0.0f, 0.0f), gameStartButton->m_renderBounds.extents.x, gameStartButton->m_renderBounds.extents.y);
	gameStartButton->m_collider->parent = gameStartButton;*/
	auto a = new UIBackGround();
	auto t = new UIButton(Vector2{ 1600.0f,800.0f }, nextScnEvent);
	AddObject(a);
	AddObject(t);
	coll.PushCollider(a->m_collider);
	coll.PushCollider(t->m_collider);
}


void StartScene::Update() {
	if ((Input::GetMouseState().left && !Input::GetPrevMouseState().left)) {
		CircleCollider temp = { Vector2(Input::GetMouseState().x,Input::GetMouseState().y), 1.0f };
		if (m_arrObj[1]->m_collider->isPointColliding(Vector2(Input::GetMouseState().x, Input::GetMouseState().y))) {
			dynamic_cast<UIButton*>(m_arrObj[1])->OnTrigger();
		}
	}
}

void StartScene::FixedUpdate() {

}

StartScene::~StartScene() {
	delete myBack;
	delete gameStartButton->m_collider;
	delete gameStartButton;
	
	
}

void StartScene::Exit() 
{

}
