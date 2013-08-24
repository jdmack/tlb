#ifndef TLB_SURFACE_H_
#define TLB_SURFACE_H_

SDL_Surface * load_image(std::string);
SDL_Surface * load_image_alpha(std::string);
void apply_surface(int, int, SDL_Surface *, SDL_Surface *);

#endif
