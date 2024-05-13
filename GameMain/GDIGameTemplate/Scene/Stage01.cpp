#include "Stage01.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../System/TimeSystem.h"

void Stage01::Init()
{
	AddObject(new UIBackGround());
	AddObject(new Player());
}

void Stage01::Update()
{
	//m_Player->Update(High_Resolution_Time::GetDeltaTime() / 1000.0f);
	for (int i = 0; i < m_arrObj.size(); i++) {
		m_arrObj[i]->Update(High_Resolution_Time::GetDeltaTime()/1000.f);
	}
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
