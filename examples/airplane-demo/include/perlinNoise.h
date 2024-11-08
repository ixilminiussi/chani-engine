#if !defined(PERLIN_NOISE_H)
#define PERLIN_NOISE_H

#include <computeShader.h>
#include <vector3.h>

struct PerlinSettings
{
    Vector3 subDivisions;
    Vector3 dimensions;
};

class PerlinNoise
{
  public:
    PerlinNoise() = default;
    PerlinNoise(const PerlinSettings &settings);

    void reload();
    void generate();
    GLuint getNoiseTexture() const;
    const Vector3 &getDimensions() const;
    const Vector3 &getSubDivisions() const;

    ~PerlinNoise() = default;

  private:
    Vector3 dimensions;
    Vector3 subDivisions;
    Vector3 cellSize;
    ComputeShader perlinNoiseCS;
    GLuint inputBuffer, outputTexture;
};

#endif
