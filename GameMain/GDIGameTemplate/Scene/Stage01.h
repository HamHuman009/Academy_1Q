#pragma once
#include "CScene.h"
class Stage01 : public CScene
{
	// CScene을(를) 통해 상속됨
	void Init() override;
	void Update() override;
	void Render() override;
	void FixedUpdate() override;
	void Start() override;
	void Exit() override;
};

