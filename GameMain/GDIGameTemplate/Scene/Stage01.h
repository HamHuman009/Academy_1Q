#pragma once
#include "CScene.h"
//#include "../GameLogic/Objects/Object.h"
#include "../GameLogic/Objects/Player.h"

class UIBackGround;
//class Player;

class Stage01 : public CScene
{
	// CScene��(��) ���� ��ӵ�
	void Init() override;
	void Update() override;

	void FixedUpdate() override;
	void Start() override;
	void Exit() override;

	
private:

	UIBackGround* myBack;
	Player* m_Player;
};

