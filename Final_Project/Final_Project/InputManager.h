#pragma once
using namespace Ogre;
using namespace OgreBites;

#define IL_KEY_DOWN true
#define IL_KEY_UP false

enum KeyState
{
	KEY_STATIC = 0,
	KEY_DOWN = 1,
	KEY_PRESSED = 2,
	KEY_UP = 3
};

class InputManager
{
public:
	InputManager();
	~InputManager();
	void update(const Uint8* key_state, const Uint32* mouse_state);

	KeyState l_ctrl_ = KEY_STATIC;
	KeyState key_d_ = KEY_STATIC;
};

