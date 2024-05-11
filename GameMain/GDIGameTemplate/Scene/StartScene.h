#pragma once
#include "CScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../System/RenderSystem.h"
class StartScene : public CScene
{	
	
	// CScene��(��) ���� ��ӵ�
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

