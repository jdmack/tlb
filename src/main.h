#ifndef TEITRUS_MAIN_H_
#define TEITRUS_MAIN_H_

bool init();
void clean_up();
SDL_Surface * load_image(std::string);
SDL_Surface * load_image_alpha(std::string);
void apply_surface(int, int, SDL_Surface *, SDL_Surface *);
void handle_input(SDL_Event);

#endif
