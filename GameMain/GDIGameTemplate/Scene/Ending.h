#pragma once
#include "CScene.h"

enum class EndRoot
{
    Poor = 1,
    Normal = 2,
    Maniac = 3,
    Great = 4,
    Professional = 5,
    Best = 6
};

class Ending : public CScene
{
public:
    Gdiplus::Bitmap* myBitmap = nullptr;
    Gdiplus::Bitmap* backBitmap = nullptr;
    void Init() override;
    void Start() override;
    void Exit() override;
    int getRoot();
    Ending();
    ~Ending();

    int root;

    UINT Score;
    UINT bossCount;
};

