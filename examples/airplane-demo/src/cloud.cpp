#include "cloud.h"

#include "cloudMaterial.h"
#include <assets.h>
#include <mesh.h>
#include <postProcessComponent.h>

Cloud::Cloud() : Actor()
{
    ppc = new PostProcessComponent(this);
    ppc->setMaterial(dynamic_cast<CloudMaterial *>(Assets::getMaterial("Material_Cloud")));
}

PostProcessComponent *Cloud::getPostProcessComponent() const
{
    return ppc;
}
