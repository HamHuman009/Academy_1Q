#include "KeyInput.h"
#include "../../System/InputSystem.h"
#include "../Event.h"
void KeyInput::Init()
{
}

// 모든 키 입력 받음 (마우스 제외)
void KeyInput::Update(float delta)
{
    for (int key = 0; key <= 255; ++key) {
        if (Input::IsKeyDown(key)) {
            m_Event->OnTrigger();
            break; 
        }
    }
}

void KeyInput::OnTrigger()
{

}
