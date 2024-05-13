#pragma once
#include "CScene.h"
//#include "../GameLogic/Objects/Object.h"
#include "../GameLogic/Objects/Player.h"

class UIBackGround;
//class Player;

class Stage01 : public CScene
{
private:
	/*UIBackGround* myBack; // 이런 변수는 m_arrObj에서 관리.
	Player* m_Player; */

public:
	// CScene을(를) 통해 상속됨
	void Init() override;
	void Start() override;
	void Exit() override;

	Stage01() {};
	~Stage01();
};

