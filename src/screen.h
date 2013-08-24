#ifndef TLB_SCREEN_H_
#define TLB_SCREEN_H

/* Screen Attributes */
const int kScreenWidth        = 800;
const int kScreenHeight       = 600;
const int kScreenBitsPerPixel = 32;

class Screen
{
    private:
        SDL_Surface * surface_;

    public:
        Screen();
        SDL_Surface * surface();

        bool init();
        void clean_up();
        void blit_surface(int, int, SDL_Surface * source);
        void clear();
        bool update();
};

#endif
