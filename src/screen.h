#ifndef TLB_SCREEN_H_
#define TLB_SCREEN_H_

#include <vector>
#include "constants.h"

class GameObject;

/* Screen Attributes */
const int kScreenWidth        = 800;
const int kScreenHeight       = 600;
const int kScreenBitsPerPixel = 32;

const int kDefaultClearColor = kColorWhite;
//const int kDefaultClearColor = kColorBlack;

class Screen
{
    private:
        SDL_Surface * surface_;
        std::vector<GameObject *> objects;

    public:
        Screen();
        SDL_Surface * surface();

        bool init();
        void blit_surface(int, int, SDL_Surface * source);
        bool update();
        void clear();
        void clear(Uint32 clear_color);
        void clean_up();
        SDL_Surface * load_image(std::string);
        SDL_Surface * load_image_alpha(std::string);
        void apply_surface(int, int, SDL_Surface *, SDL_Surface *);
        void addObject(GameObject * object);
};

#endif
