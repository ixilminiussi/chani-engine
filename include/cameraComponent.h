#if !defined(CAMERA_COMPONENT_H)
#define CAMERA_COMPONENT_H

#include "component.h"
#include "matrix4.h"

class CameraComponent : public Component
{
public:
	CameraComponent(class Actor* owner, int updateOrder = 200);

protected:
	void setViewMatrix(const Matrix4& view);
};

#endif
