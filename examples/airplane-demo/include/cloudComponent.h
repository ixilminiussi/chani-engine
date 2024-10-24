#if !defined(CLOUD_H)
#define CLOUD_H

#include <actor.h>
#include <postProcessComponent.h>
#include <shader.h>
#include <shapes.h>

class CloudComponent : public PostProcessComponent
{
  public:
    CloudComponent(Actor *owner, Cuboid *cuboid);

  private:
    bool loadCompute(const std::string &filename);
    void generatePerlinNoise();

    GLuint computeShader, computeProgram;
    Vector3 perlinResolution;
};

#endif
