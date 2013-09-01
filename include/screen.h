#ifndef TLB_SCREEN_H_
#define TLB_SCREEN_H_

#include "SDL/SDL.h"
#include "constants.h"
#include "color.h"

class GameObject;

/* Screen Attributes */
//const int kScreenWidth        = 800;
//const int kScreenHeight       = 600;
const int kScreenWidth        = 1600;
const int kScreenHeight       = 900;

//const int kDefaultClearColor = kColorWhite;
const Color kDefaultClearColor = kColorBlack;

class Screen
{
    private:
        SDL_Window * window_;
        SDL_Renderer * renderer_;

    public:
        Screen();

        // accessors
        SDL_Window * window() const { return window_; }
        SDL_Renderer * renderer() const { return renderer_; }

        bool init();
        void update();
        void clear();
        void clear(Color color);
        void clean_up();
        void init_object(GameObject * object);

        void render_texture(SDL_Texture * source, SDL_Rect * offset, SDL_Rect * clip = nullptr);
        void apply_surface(SDL_Surface * source, SDL_Surface * destination, int x, int y, SDL_Rect * clip = nullptr);

        SDL_Surface * load_image(std::string);
        SDL_Surface * load_image_alpha(std::string);
        SDL_Texture * load_texture(std::string);
        SDL_Texture * load_texture_alpha(std::string);
};

#endif
