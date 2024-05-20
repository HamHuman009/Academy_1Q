#include "KeyInput.h"
#include "../../System/InputSystem.h"
#include "../Event.h"
void KeyInput::Init()
{
}

// 모든 키 입력 받음 (마우스 제외)
void KeyInput::Update(float delta)
{
    bool temp = false;
    for (int key = 0; key <= 255; ++key) {
        if (Input::IsKeyDown(key)) {
            temp = true;
            //m_Event->OnTrigger();
            break; 
        }
    }
    if (temp) {
        m_Event->OnTrigger();
    }
}

void KeyInput::OnTrigger()
{

}
