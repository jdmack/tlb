#include "gfx/ResourceManager.h"
#include "gfx/Texture.h"
#include "util/Logger.h"


ResourceManager::ResourceManager()
{
    Logger::write(Logger::ss << "ResourceManager initialized");
}


Texture * ResourceManager::getTexture(std::string filename)
{
    Texture * texture = nullptr;
    if(textures_.count(filename) > 0) {
        texture = textures_[filename];
        Logger::write(Logger::ss << "Texture exists: " << filename);
    }
    else {
        Logger::write(Logger::ss << "Texture does not exist, creating: " << filename);
        texture = new Texture(filename);
        textures_.insert(std::pair<std::string, Texture *>(filename, texture));
    }

    return texture;
}
