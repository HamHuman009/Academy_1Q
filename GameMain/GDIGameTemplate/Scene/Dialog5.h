#pragma once
#include "CScene.h"

class Dialog5 : public CScene
{
private:

public:
    // CScene��(��) ���� ��ӵ�
    Gdiplus::Bitmap* myBitmap = nullptr;
    void Init() override;
    void Start() override;
    void Exit() override;

    Dialog5();
    ~Dialog5();
};

