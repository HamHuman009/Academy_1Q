#include "Stage01.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../System/TimeSystem.h"

void Stage01::Init()
{
	myBack = new UIBackGround();
	AddObject(myBack);
	m_Player = new Player();
	AddObject(m_Player);
}

void Stage01::Update()
{
	//m_Player->Update(High_Resolution_Time::GetDeltaTime() / 1000.0f);
}


void Stage01::FixedUpdate()
{
}

void Stage01::Start()
{
}

void Stage01::Exit()
{
	
}
