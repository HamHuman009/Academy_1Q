#include "InputSystem.h"

namespace Input
{
    bool isKeyDown[256];
    bool isKeyUp[256];
    bool isKey[256];

    MouseState curMouse;
    MouseState prevMouse;

    TCHAR buffer[255] = {0};
    int length = 0;
    bool isInputKey = false;

    void ResetInput()
    {
        for (int i = 0; i < 256; i++)
        {
            isKeyDown[i] = false;
            isKeyUp[i] = false;
        }
    }

    void KeyDown(unsigned int key)
    {
        isKeyDown[key] = true;
        isKey[key] = true;
    }

    void KeyUp(unsigned int key)
    {
        isKeyUp[key] = true;
        isKey[key] = false;
    }

    bool IsKeyDown(unsigned int key)
    {
        return isKeyDown[key];
    }

    bool IsKeyUp(unsigned int key)
    {
        return isKeyUp[key];
    }

    bool IsKey(unsigned int key)
    {
        return isKey[key];
    }

    void InitMouse()
    {
        curMouse.x = global::GetWinApp().GetWidth() / 2;
        curMouse.y = global::GetWinApp().GetHeight() / 2;
        curMouse.wheel = 0;

        curMouse.left = false;
        curMouse.right = false;
        curMouse.middle = false;

        prevMouse = curMouse;

        SetCursorPos(curMouse.x, curMouse.y);
    }

    void UpdateMouse()
    {
        prevMouse = curMouse;

        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(global::GetWinApp().GetWindow(), &pt);

        curMouse.x = pt.x;
        curMouse.y = pt.y;
        curMouse.wheel = 0;

        curMouse.left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
        curMouse.right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
        curMouse.middle = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;
    }

    const MouseState& GetMouseState()
    {
        return curMouse;
    }

    const MouseState& GetPrevMouseState()
    {
        return prevMouse;
    }

    void AddBuffer(TCHAR _buffer)
    {
        if (isInputKey == true) {
            buffer[length++] = _buffer;
        }
    }
    void SetInputState(bool on) {
        isInputKey = on;
    }
    // in은 바꿀 str, count는 in의 길이, maxlength는 in 최대길이
    int GetInputBuffer(TCHAR* in, int count, int maxLength) {
        for (int i = count; i < maxLength - 1; i++) {
            in[i] = buffer[i - count];
        }
        in[maxLength - 1] = L'\0';
        for (int i = 0; i < 255; i++) buffer[i] = L'\0';
        int a = length;
        length = 0;
        if (a + count > maxLength - 1)
            return maxLength - 1;

        return a + count;
    }

    void InitInput()
    {
        for (int i = 0; i < 256; i++)
        {
            isKeyDown[i] = false;
            isKeyUp[i] = false;
            isKey[i] = false;
        }
        memset(buffer, '\0', 255);
        InitMouse();
    }

    bool IsSame(const MouseState& a, const MouseState& b)
    {
        return a.x == b.x && a.y == b.y && a.wheel == b.wheel && a.left == b.left && a.right == b.right && a.middle == b.middle;
    }
}