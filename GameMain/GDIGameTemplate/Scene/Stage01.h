#pragma once
#include "CScene.h"
class Stage01 : public CScene
{
	// CScene��(��) ���� ��ӵ�
	void Init() override;
	void Update() override;
	void Render() override;
	void FixedUpdate() override;
	void Start() override;
	void Exit() override;
};

