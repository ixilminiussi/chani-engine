#if !defined(CLOUD_H)
#define CLOUD_H

#include <actor.h>
#include <postProcessComponent.h>

class Cloud : public Actor
{
  public:
    Cloud();

    PostProcessComponent *getPostProcessComponent() const;

  private:
    PostProcessComponent *ppc;
};

#endif
