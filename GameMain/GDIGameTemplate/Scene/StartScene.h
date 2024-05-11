#pragma once
#include "CScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../System/RenderSystem.h"
class StartScene : public CScene
{	
	
	// CScene을(를) 통해 상속됨
public:
	virtual void Start() override;

	void Init() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	virtual void Exit() override;
	StartScene() { Init(); };
	~StartScene() {};
};

