#if !defined(AUDIO_COMPONENT_H)
#define AUDIO_COMPONENT_H

#include "component.h"
#include "soundEvent.h"

#include <string>
#include <vector>

class AudioComponent : public Component
{
  public:
    AudioComponent(class Actor *owner, int updateOrder = 200);
    ~AudioComponent();

    void update(float dt) override;
    void onUpdateWorldTransform() override;

    SoundEvent playEvent(const std::string &name);
    void stopAllEvents();

  private:
    std::vector<SoundEvent> events2D;
    std::vector<SoundEvent> events3D;
};

#endif
