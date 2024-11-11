#include "perlinNoise.h"

#include <assets.h>
#include <computeShader.h>
#include <random.h>
#include <shader.h>

PerlinNoise::PerlinNoise(const PerlinSettings &settingsP) : settings(settingsP)
{
    perlinNoiseCS = Assets::getComputeShader("CS_PerlinNoise");

    glGenBuffers(1, &inputBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, inputBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER,
                 settings.gridSize.x * settings.gridSize.y * settings.gridSize.z * sizeof(Vector3<uint>), NULL,
                 GL_DYNAMIC_COPY);

    textureDimensions = settings.gridSize * settings.cellScale;

    glGenTextures(1, &outputTexture);
    glBindTexture(GL_TEXTURE_3D, outputTexture);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_R32F, textureDimensions.x, textureDimensions.y, textureDimensions.z, 0, GL_RED,
                 GL_FLOAT, NULL);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glBindBuffer(GL_ARRAY_BUFFER, inputBuffer);
    Vector3<uint> *coords = reinterpret_cast<Vector3<uint> *>(glMapBufferRange(
        GL_ARRAY_BUFFER, 0, settings.gridSize.x * settings.gridSize.y * settings.gridSize.z * sizeof(Vector3<uint>),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));

    // generate the input buffer data
    for (uint x = 0; x < settings.gridSize.x; x++)
    {
        for (uint y = 0; y < settings.gridSize.y; y++)
        {
            for (uint z = 0; z < settings.gridSize.z; z++)
            {
                uint index = z * settings.gridSize.y * settings.gridSize.x + y * settings.gridSize.x + x;
                coords[index] = Vector3<uint>(Random::getIntRange(0, settings.cellScale),
                                              Random::getIntRange(0, settings.cellScale),
                                              Random::getIntRange(0, settings.cellScale));
            }
        }
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void PerlinNoise::reload()
{
    perlinNoiseCS.reload();
    generate();
}

void PerlinNoise::generate()
{
    perlinNoiseCS = Assets::getComputeShader("CS_PerlinNoise");
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, inputBuffer);
    glBindImageTexture(1, outputTexture, 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_R32F);

    perlinNoiseCS.use();
    perlinNoiseCS.setUnsigned("uCellScale", settings.cellScale);
    perlinNoiseCS.setVector3ui("uGridSize", settings.gridSize.x, settings.gridSize.y, settings.gridSize.z);
    glDispatchCompute(textureDimensions.x, textureDimensions.y, textureDimensions.z);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glBindTexture(GL_TEXTURE_3D, outputTexture);

    // Create a buffer to store the texture data
    std::vector<float> textureData(textureDimensions.x * textureDimensions.y * textureDimensions.z);

    // Read the texture data into the buffer
    glGetTexImage(GL_TEXTURE_3D, 0, GL_RED, GL_FLOAT, textureData.data());

    // Unbind the texture
    glBindTexture(GL_TEXTURE_3D, 0);
}

GLuint PerlinNoise::getNoiseTexture() const
{
    return outputTexture;
}

const Vector3<uint> &PerlinNoise::getTextureDimensions() const
{
    return textureDimensions;
}

const PerlinSettings &PerlinNoise::getSettings() const
{
    return settings;
}
