#pragma once
#include "../Scene/CScene.h"

enum class EndRoot
{
    Poor = 1,
    Normal,
    Maniac,
    Great,
    Professional,
    Best
};

class Ending : public CScene
{
public:
    Gdiplus::Bitmap* myBitmap = nullptr;
    Gdiplus::Bitmap* backBitmap = nullptr;
    void Init() override;
    void Start() override;
    void Exit() override;

    Ending();
    ~Ending();

    int num;
};

