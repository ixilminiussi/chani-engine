#if !defined(GAMEPAD_STATE_H)
#define GAMEPAD_STATE_H

#include "vector2.h"

#include <SDL_stdinc.h>
#include <SDL_gamepad.h>

enum class ButtonState;

class GamepadState
{
public:
	friend class InputSystem;

	GamepadState();

	bool getButtonValue(SDL_GamepadButton button) const;
	ButtonState getButtonState(SDL_GamepadButton button) const;

	const Vector2& getLeftStick() const { return leftStick; }
	const Vector2& getRightStick() const { return rightStick; }
	float getLeftTrigger() const { return leftTrigger; }
	float getRightTrigger() const { return rightTrigger; }
	bool getIsConnected() const { return isConnected; }


private:
	Uint8 currentButtons[SDL_GAMEPAD_BUTTON_COUNT];
	Uint8 previousButtons[SDL_GAMEPAD_BUTTON_COUNT];
	Vector2 leftStick;
	Vector2 rightStick;
	float leftTrigger;
	float rightTrigger;
	bool isConnected;
};

#endif
