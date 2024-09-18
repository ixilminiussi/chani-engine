#if !defined(FPS_CAMERA_COMPONENT_H)
#define FPS_CAMERA_COMPONENT_H

#include "actor.h"
#include "cameraComponent.h"

class FPSCameraComponent : public CameraComponent {
  public:
    FPSCameraComponent(class Actor *ownerP);

    void update(float dt) override;

    float getPitch() const { return pitch; }
    float getPitchSpeed() const { return pitchSpeed; }
    float getMaxPitch() const { return maxPitch; }

    void setPitchSpeed(float speed);
    void setMaxPitch(float pitch);

  private:
    // Rotation/sec speed of pitch
    float pitchSpeed;
    // Maximum pitch deviation from forward
    float maxPitch;
    // Current pitch
    float pitch;
};

#endif
