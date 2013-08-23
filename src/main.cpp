////////////////////////////////////////////////////////////////////////////////
//  Header Files
////////////////////////////////////////////////////////////////////////////////

// Standard Library
#include <iostream>
#include <string>

// Third Party Libraries
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

// Project Files
#include "assets.h"
#include "constants.h"
#include "grid.h"
#include "main.h"
#include "score.h"
#include "tetrimino.h"
#include "timer.h"

//The surfaces
SDL_Surface *screen = nullptr;
SDL_Surface *game   = nullptr;
SDL_Surface *loader = nullptr;

int main(int argc, char* args[])
{

    //The event structure
    SDL_Event event;

    //Quit flag
    bool quit = false;

    Timer delta;
    Tetrimino * active_tetrimino = nullptr;

    if(init() == false) {
        return 1;
    }

    //While the user hasn't quit
    while(quit == false) {

        while(SDL_PollEvent(&event)) {

            // Process input

            //If the user has Xed out the window
            if(event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }

        }

        // Create new tetrimino if no active one
        if(active_tetrimino == nullptr) {
            active_tetrimino = new Tetrimino;
        }
        // Move active tetrimino down
        else {
            active_tetrimino->descend();
        }

        // Update
        //myDot.move(delta.get_ticks());

        //Restart delta timer
        delta.start();

        // Draw
        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
        apply_surface(0, 0, game, screen);
        // TODO: Need a structure to hold all "draw-able" things and iterate through it to apply_surface
        // all of them
        active_tetrimino->show(screen);


        if(SDL_Flip(screen) == -1) {
            return 1;
        }
    }

    //Clean up
    clean_up();

    return 0;
}

SDL_Surface * load_image(std::string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = nullptr;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = nullptr;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if(loadedImage != nullptr) {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old surface
        SDL_FreeSurface(loadedImage);
    }

    //Return the optimized surface
    return optimizedImage;
}

SDL_Surface * load_image_alpha(std::string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = nullptr;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = nullptr;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if(loadedImage != nullptr) {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

        //Free the old surface
        SDL_FreeSurface(loadedImage);
    }

    //Return the optimized surface
    return optimizedImage;
}

bool init()
{
    //Initialize all SDL subsystems
    if(SDL_Init( SDL_INIT_EVERYTHING) == -1) {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kScreenBitsPerPixel, SDL_SWSURFACE);

    //If there was an error in setting up the screen
    if(screen == nullptr) {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption(kName.c_str(), nullptr);

    game = SDL_CreateRGBSurface(0, kScreenWidth, kScreenHeight, kScreenBitsPerPixel, kRedMask, kGreenMask, kBlueMask, kAlphaMask);

    if(game == nullptr) {
        return false;
    }

    // Overlay
    loader = load_image(kAssetArtOverlay);
    apply_surface(0, 0, loader, game);

    // Title
    loader = load_image_alpha(kAssetArtTitle);
    apply_surface(kTitleX, kTitleY, loader, game);

    apply_surface(0, 0, game, screen);

    //If everything initialized fine
    return true;
}

void apply_surface(int x, int y, SDL_Surface * source, SDL_Surface * destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface(source, nullptr, destination, &offset );
}

void handle_input(SDL_Event event)
{
    //If a key was pressed
    if(event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch(event.key.keysym.sym )
        {
            case SDLK_UP: /*yVel -= DOT_VEL*/; break;
            case SDLK_DOWN: /*yVel += DOT_VEL*/; break;
            case SDLK_LEFT: /*xVel -= DOT_VEL*/; break;
            case SDLK_RIGHT: /*xVel += DOT_VEL*/; break;
        }
    }
    //If a key was released
    else if(event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch(event.key.keysym.sym )
        {
            case SDLK_UP: /*yVel += DOT_VEL*/; break;
            case SDLK_DOWN: /*yVel -= DOT_VEL*/; break;
            case SDLK_LEFT: /*xVel += DOT_VEL*/; break;
            case SDLK_RIGHT: /*xVel -= DOT_VEL*/; break;
        }
    }
}

void clean_up()
{
    //Free the surface
    //SDL_FreeSurface(dot);

    //Quit SDL
    SDL_Quit();
}
