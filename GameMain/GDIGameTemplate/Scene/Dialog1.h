#pragma once
#include "CScene.h"

class Dialog1 : public CScene
{
private:

public:
    // CScene��(��) ���� ��ӵ�
    Gdiplus::Bitmap* myBitmap = nullptr;
    void Init() override;
    void Start() override;
    void Exit() override;

    Dialog1();
    ~Dialog1();
};

