#pragma once
#include "CScene.h"

class Dialog2 : public CScene
{
private:

public:
    // CScene을(를) 통해 상속됨
    Gdiplus::Bitmap* myBitmap = nullptr;
    void Init() override;
    void Start() override;
    void Exit() override;

    Dialog2();
    ~Dialog2();
};

