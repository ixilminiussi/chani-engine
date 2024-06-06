#if !defined(NAV_COMPONENT_H)
#define NAV_COMPONENT_H

#include "moveComponent.h"
#include "actor.h"
#include "tile.h"
#include "vector2.h"

class NavComponent : public MoveComponent {
public:
    NavComponent(Actor* owner, int updateOrder = 10);
    NavComponent() = delete;
    NavComponent(NavComponent const&) = delete;
    NavComponent& operator=(NavComponent const&) = delete;

    void update(float dt) override;
    void startPath(const Tile& start);
    void turnTo(Vector2 const& targetPosition);

private:
    const Tile* nextNode;
};

#endif
