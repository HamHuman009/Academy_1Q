#pragma once
#include "CScene.h"

class ScoreScene : public CScene
{
private:

public:
    // CScene��(��) ���� ��ӵ�
    void Init() override;
    void Start() override;
    void Exit() override;

    ScoreScene();
    ~ScoreScene();
};
