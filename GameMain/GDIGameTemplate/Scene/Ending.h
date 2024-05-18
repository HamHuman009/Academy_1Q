#pragma once
#include "../Scene/CScene.h"

class Ending : public CScene
{
public:
    Gdiplus::Bitmap* myBitmap = nullptr;
    void Init() override;
    void Start() override;
    void Exit() override;

    Ending();
    ~Ending();

    int num;
};

