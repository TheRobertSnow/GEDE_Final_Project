#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{

}

void InputManager::update(const Uint8* key_state, const Uint32* mouse_state)
{	
	// Keyboard
	if (key_state[SDL_SCANCODE_ESCAPE])
	{

	}
	else if (key_state[SDL_SCANCODE_LCTRL])
	{
		if (key_state[SDL_SCANCODE_D])
		{

		}
	}

}