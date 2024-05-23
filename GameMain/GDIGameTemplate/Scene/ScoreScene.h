#pragma once
#include "CScene.h"

class ScoreScene : public CScene
{
private:

public:
    // CScene을(를) 통해 상속됨
    void Init() override;
    void Start() override;
    void Exit() override;

    ScoreScene();
    ~ScoreScene();
};
