#if !defined(SPHERE_H)
#define SPHERE_H

#include <actor.h>
#include <meshComponent.h>

class Sphere : public Actor
{
  public:
    Sphere();

    MeshComponent *getMeshComponent() const;

  private:
    MeshComponent *mc;
};

#endif
