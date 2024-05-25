#if !defined ASSETS_H
#define ASSETS_H

#include <map>
#include <string>
#include "texture.h"

class Assets {
public:
    static std::map<std::string, Texture> textures;

    static Texture loadTexture(Renderer& renderer, const string& filename, const string& name);

    static Texture& getTexture(const std::string& name);
    
    static void clear();

private:
    Assets() {}

    static Texture loadTextureFromFile(Renderer& renderer, const string& filename);
};

#endif
