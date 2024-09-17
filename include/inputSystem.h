#if !defined(INPUT_SYSTEM_H)
#define INPUT_SYSTEM_H

#include "gamepadState.h"
#include "keyboardState.h"
#include "mouseState.h"

#include <SDL_events.h>

enum class ButtonState { None, Pressed, Released, Held };

struct InputState {
    KeyboardState keyboard;
    MouseState mouse;
    GamepadState gamepad;
};

class InputSystem {
  public:
    InputSystem();

    bool initialize();
    void close();

    const InputState getInputState() const { return inputState; }

    bool processEvent(SDL_Event &event); // Returns isRunning status
    void preUpdate();
    void update();

    bool getIsCursorDisplayed() const { return isCursorDisplayed; }
    void setMouseCursor(bool isCursorDisplayedP);
    void setMouseRelativeMode(SDL_Window *window, bool isMouseRelativeOnP);

  private:
    float filter1D(int input);
    Vector2 filter2D(int inputX, int inputY);

    InputState inputState;
    bool isCursorDisplayed;
    SDL_Gamepad *gamepad;
};

constexpr int GAMEPAD_DEAD_ZONE_1D = 250;
constexpr float GAMEPAD_DEAD_ZONE_2D = 8000.0f;
constexpr int GAMEPAD_MAX_VALUE = 30000;

#endif
