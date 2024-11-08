#include "cloudComponent.h"

#include "cloudMaterial.h"
#include <assets.h>
#include <chani.h>
#include <log.h>
#include <mesh.h>
#include <postProcessComponent.h>
#include <shader.h>

CloudComponent::CloudComponent(Actor *ownerP, Cuboid *cuboid) : PostProcessComponent(ownerP)
{
    cloudMaterial = dynamic_cast<CloudMaterial *>(Assets::getMaterial("Material_Cloud"));
    cloudMaterial->setArea(cuboid);

    setMaterial(cloudMaterial);
}

void CloudComponent::reloadNoiseShader()
{
    cloudMaterial->reload();
}
