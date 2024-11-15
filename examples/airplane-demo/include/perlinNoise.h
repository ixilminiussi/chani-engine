#if !defined(PERLIN_NOISE_H)
#define PERLIN_NOISE_H

#include <computeShader.h>
#include <vector3.h>

struct PerlinSettings
{
    uint cellScale;
    Vector3<uint> gridSize;
    Vector3<float> *shift;
};

struct PaddedVector3
{
    uint x, y, z, padding;
};

class PerlinNoise
{
  public:
    PerlinNoise() = default;
    PerlinNoise(const PerlinSettings &settings);

    void load(const PerlinSettings &settings);
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
    bool initialized = false;
};

#endif
