#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

namespace surface
{
    SDL_Surface * load_image(std::string filename)
    {
        SDL_Surface* loadedImage    = nullptr;
        SDL_Surface* optimizedImage = nullptr;

        loadedImage = IMG_Load(filename.c_str());

        if(loadedImage != nullptr) {
            optimizedImage = SDL_DisplayFormat(loadedImage);
            SDL_FreeSurface(loadedImage);
        }

        return optimizedImage;
    }

    SDL_Surface * load_image_alpha(std::string filename)
    {
        SDL_Surface* loadedImage = nullptr;
        SDL_Surface* optimizedImage = nullptr;

        loadedImage = IMG_Load(filename.c_str());

        if(loadedImage != nullptr) {
            optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
            SDL_FreeSurface(loadedImage);
        }

        return optimizedImage;
    }

    void apply_surface(int x, int y, SDL_Surface * source, SDL_Surface * destination )
    {
        SDL_Rect offset;

        offset.x = x;
        offset.y = y;

        SDL_BlitSurface(source, nullptr, destination, &offset );
    }
}
