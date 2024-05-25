#if !defined(COMPONENT_H)
#define COMPONENT_H

class Actor;

class Component {
public:
    Component(Actor* ownerP, int updateOrderP = 100);
    Component() = delete;
    virtual ~Component();
    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    int getUpdateOrder() const { return updateOrder; }

    virtual void update(float dt);

protected:
    Actor& owner;
    int updateOrder;
};

#endif
