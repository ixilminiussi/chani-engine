#if !defined(COMPONENT_H)
#define COMPONENT_H

#include <SDL2/SDL_stdinc.h>

class Actor;

class Component {
public:
    Component(Actor* ownerP, int updateOrderP = 100);
    Component() = delete;
    virtual ~Component();
    Component(Component const&) = delete;
    Component& operator=(Component const&) = delete;

    int getUpdateOrder() const { return updateOrder; }

    virtual void update(float dt);

    virtual void processInput(Uint8 const* keyState);

protected:
    Actor& owner;
    int updateOrder;
};

#endif
