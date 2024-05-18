#include "KeyInput.h"
#include "../../System/InputSystem.h"
#include "../Event.h"
void KeyInput::Init()
{
}

void KeyInput::Update(float delta)
{
	if (Input::IsKeyDown(' '))
	{
		m_Event->OnTrigger();
	}
}

void KeyInput::OnTrigger()
{

}
