#pragma once
#include "CScene.h"
#include "../GameLogic/Objects/Object.h"
class UIBackGround;
class Stage01 : public CScene
{
	// CScene을(를) 통해 상속됨
	void Init() override;
	void Update() override;

	void FixedUpdate() override;
	void Start() override;
	void Exit() override;
private:
	UIBackGround* myBack;
};

