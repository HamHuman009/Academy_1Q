#include "KeyInput.h"
#include "../../System/InputSystem.h"
#include "../Event.h"
void KeyInput::Init() {
    m_delay = 0;
    m_delayActive = false;
    m_elapsedTime = 0.f;
}

void KeyInput::Init(float i)
{
    m_delay = i;
    m_delayActive = true;
    m_elapsedTime = 0.f;
}

// 모든 키 입력 받음 (마우스 제외)
void KeyInput::Update(float delta)
{
    if (m_isActive == false) return;

    if (m_delay != 0) {
        m_elapsedTime += delta;
    }
    if (m_delayActive == false || (m_delayActive == true && m_elapsedTime > m_delay)) {
        bool temp = false;
        for (int key = 0; key <= 255; ++key) {

            if (acceptKey[key] == false) continue;

            if (Input::IsKeyDown(key)) {
                if (key == VK_ESCAPE)
                {
                    continue;
                }
                else
                {
                    temp = true;
                }
                //m_Event->OnTrigger();
                break;
            }
        }
        if (temp) {
            m_Event->OnTrigger();
        }
    }
}

void KeyInput::OnTrigger()
{

}
