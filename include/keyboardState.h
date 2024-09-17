#if !defined(KEYBOARD_STATE_H)
#define KEYBOARD_STATE_H

#include <SDL_keyboard.h>

enum class ButtonState;

class KeyboardState
{
	friend class InputSystem;

public:
	bool getKeyValue(SDL_Scancode key) const;
	ButtonState getKeyState(SDL_Scancode key) const;

private:
	const bool* currentState;
	bool previousState[SDL_SCANCODE_COUNT];
};

#endif
