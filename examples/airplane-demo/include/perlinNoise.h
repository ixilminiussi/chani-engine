#if !defined(PERLIN_NOISE_H)
#define PERLIN_NOISE_H

#include <computeShader.h>
#include <vector3.h>

struct PerlinSettings
{
    uint cellScale;
    Vector3<uint> gridSize;
};

class PerlinNoise
{
  public:
    PerlinNoise() = default;
    PerlinNoise(const PerlinSettings &settings);

    void reload();
    void generate();
    GLuint getNoiseTexture() const;
    const PerlinSettings &getSettings() const;
    const Vector3<uint> &getTextureDimensions() const;

    ~PerlinNoise() = default;

  private:
    Vector3<uint> textureDimensions;
    PerlinSettings settings;
    ComputeShader perlinNoiseCS;
    GLuint inputBuffer, outputTexture;
};

#endif
