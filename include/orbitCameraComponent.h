#if !defined(ORBIT_CAMERA_COMPONENT_H)
#define ORBIT_CAMERA_COMPONENT_H

#include "cameraComponent.h"

class OrbitCameraComponent : public CameraComponent
{
  public:
    OrbitCameraComponent(class Actor *owner);

    void update(float dt) override;

    float getPitchSpeed() const;
    float getYawSpeed() const;

    void setPitchSpeed(float pitchSpeedP);
    void setYawSpeed(float yawSpeedP);

    void zoom(float factor);
    void unzoom(float factor);

    void setDistance(float newDistance);
    float getDistance();

  private:
    // Offset from target
    Vector3<float> offset;
    // Up vector of camera
    Vector3<float> up;

    float pitchSpeed;
    float yawSpeed;
};

#endif
