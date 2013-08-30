#ifndef TLB_SCREEN_H_
#define TLB_SCREEN_H_

#include "SDL/SDL.h"
#include "constants.h"

class GameObject;

/* Screen Attributes */
//const int kScreenWidth        = 800;
//const int kScreenHeight       = 600;
const int kScreenWidth        = 1600;
const int kScreenHeight       = 900;
const int kScreenBitsPerPixel = 32;

//const int kDefaultClearColor = kColorWhite;
const int kDefaultClearColor = kColorBlack;

class Screen
{
    private:
        SDL_Surface * surface_;

    public:
        Screen();
        SDL_Surface * surface() const { return surface_; }

        bool init();
        void blit_surface(int, int, SDL_Surface * source, SDL_Rect * clip = nullptr);
        bool update();
        void clear();
        void clear(Uint32 clear_color);
        void clean_up();
        SDL_Surface * load_image(std::string);
        SDL_Surface * load_image_alpha(std::string);
        void apply_surface(int, int, SDL_Surface *, SDL_Surface *, SDL_Rect * clip = nullptr);
        void init_object(GameObject * object);
        SDL_Surface * rotate_surface(SDL_Surface * surface, double rotation);

};

#endif
