#include "perlinNoise.h"

#include <assets.h>
#include <computeShader.h>
#include <random.h>
#include <shader.h>

PerlinNoise::PerlinNoise(const PerlinSettings &settings)
    : dimensions(settings.dimensions), subDivisions(settings.subDivisions)
{
    perlinNoiseCS = Assets::getComputeShader("CS_PerlinNoise");
    cellSize = dimensions / subDivisions;

    glGenBuffers(1, &inputBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, inputBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, subDivisions.x * subDivisions.y * subDivisions.z * sizeof(Vector3), NULL,
                 GL_DYNAMIC_COPY);

    glGenTextures(1, &outputTexture);
    glBindTexture(GL_TEXTURE_3D, outputTexture);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_R32F, dimensions.x, dimensions.y, dimensions.z, 0, GL_RED, GL_FLOAT, NULL);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glBindBuffer(GL_ARRAY_BUFFER, inputBuffer);
    Vector3 *coords = reinterpret_cast<Vector3 *>(
        glMapBufferRange(GL_ARRAY_BUFFER, 0, subDivisions.x * subDivisions.y * subDivisions.z * sizeof(Vector3),
                         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));

    // generate the input buffer data
    for (int x = 0; x < subDivisions.x; x++)
    {
        for (int y = 0; y < subDivisions.y; y++)
        {
            for (int z = 0; z < subDivisions.z; z++)
            {
                int index = z * subDivisions.y * subDivisions.x + y * subDivisions.x + x;
                coords[index] = (cellSize * Vector3(Random::getFloat(), Random::getFloat(), Random::getFloat())) +
                                (cellSize * Vector3(float(x), float(y), float(z)));
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
    perlinNoiseCS.setVector3f("uCellSize", cellSize);
    glDispatchCompute(dimensions.x, dimensions.y, dimensions.z);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glBindTexture(GL_TEXTURE_3D, outputTexture);

    // Create a buffer to store the texture data
    std::vector<float> textureData(dimensions.x * dimensions.y * dimensions.z);

    // Read the texture data into the buffer
    glGetTexImage(GL_TEXTURE_3D, 0, GL_RED, GL_FLOAT, textureData.data());

    // Unbind the texture
    glBindTexture(GL_TEXTURE_3D, 0);
}

GLuint PerlinNoise::getNoiseTexture() const
{
    return outputTexture;
}

const Vector3 &PerlinNoise::getDimensions() const
{
    return dimensions;
}

const Vector3 &PerlinNoise::getSubDivisions() const
{
    return subDivisions;
}
