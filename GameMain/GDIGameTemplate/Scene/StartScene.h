#pragma once
#include "CScene.h"
#include "../GameLogic/Objects/UIObject.h"

#include "../System/RenderSystem.h"

#include "../Manager/ColliderManager.h"
class StartScene : public CScene
{	
private:
	ColliderManager coll;
	UIBackGround* myBack;
	UIButton* gameStartButton;
	UIButton* gameExitButton;
	// CScene을(를) 통해 상속됨
public:

	virtual void Start() override;

	void Init() override;
	void Update() override;
	void FixedUpdate() override;
	virtual void Exit() override;

	StartScene() {};
	~StartScene() {};

};

