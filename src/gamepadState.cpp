#include "gamepadState.h"

#include "inputSystem.h"

GamepadState::GamepadState()
    : leftStick(Vector2<float>()), rightStick(Vector2<float>()), leftTrigger(0.0f), rightTrigger(0.0f),
      isConnected(false)
{
}

bool GamepadState::getButtonValue(SDL_GamepadButton button) const
{
    return currentButtons[button] == 1;
}

ButtonState GamepadState::getButtonState(SDL_GamepadButton button) const
{
    if (previousButtons[button] == 0)
    {
        if (currentButtons[button] == 0)
        {
            return ButtonState::None;
        }
        else
        {
            return ButtonState::Pressed;
        }
    }
    else
    {
        if (currentButtons[button] == 0)
        {
            return ButtonState::Released;
        }
        else
        {
            return ButtonState::Held;
        }
    }
}

const Vector2<float> &GamepadState::getLeftStick() const
{
    return leftStick;
}

const Vector2<float> &GamepadState::getRightStick() const
{
    return rightStick;
}

float GamepadState::getLeftTrigger() const
{
    return leftTrigger;
}

float GamepadState::getRightTrigger() const
{
    return rightTrigger;
}

bool GamepadState::getIsConnected() const
{
    return isConnected;
}
