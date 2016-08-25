#ifndef TLB_GFX_RESOURCE_MANAGER_H_
#define TLB_GFX_RESOURCE_MANAGER_H_

#include <map>
#include <string>

class Texture;

class ResourceManager
{
    public:
        ResourceManager();

        Texture * getTexture(std::string filename);
        

    private:
        std::map<std::string, Texture *> textures_;
        std::map<std::string, unsigned int> count_;

};


#endif

