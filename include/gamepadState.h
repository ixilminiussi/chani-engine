#if !defined(GAMEPAD_STATE_H)
#define GAMEPAD_STATE_H

#include "vector2.h"

#include <SDL_gamepad.h>
#include <SDL_stdinc.h>

enum class ButtonState;

class GamepadState
{
  public:
    friend class InputSystem;

    GamepadState();

    bool getButtonValue(SDL_GamepadButton button) const;
    ButtonState getButtonState(SDL_GamepadButton button) const;

    const Vector2<float> &getLeftStick() const;
    const Vector2<float> &getRightStick() const;
    float getLeftTrigger() const;
    float getRightTrigger() const;
    bool getIsConnected() const;

  private:
    Uint8 currentButtons[SDL_GAMEPAD_BUTTON_COUNT];
    Uint8 previousButtons[SDL_GAMEPAD_BUTTON_COUNT];
    Vector2<float> leftStick;
    Vector2<float> rightStick;
    float leftTrigger;
    float rightTrigger;
    bool isConnected;
};

#endif
