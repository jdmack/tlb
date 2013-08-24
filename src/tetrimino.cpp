#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

#include "assets.h"
#include "constants.h"
#include "grid.h"
#include "main.h"
#include "tetrimino.h"
#include "timer.h"
/*

Tetrimino::Tetrimino()
{
    type_ = rand() % kNumberOfTetroTypes;
    switch(type_) {
        case kTetroI: art_asset_ = kAssetArtTetroI; break;
        case kTetroJ: art_asset_ = kAssetArtTetroJ; break;
        case kTetroL: art_asset_ = kAssetArtTetroL; break;
        case kTetroO: art_asset_ = kAssetArtTetroO; break;
        case kTetroS: art_asset_ = kAssetArtTetroS; break;
        case kTetroT: art_asset_ = kAssetArtTetroT; break;
        case kTetroZ: art_asset_ = kAssetArtTetroZ; break;
    }

    surface_ = load_image_alpha(art_asset_);

    //Initialize the offsets
    x_position_= kSpawnX;
    y_position_= kSpawnY;

    rotation_ = 0;

    active_ = true;
    descent_delta_.start();
}
void Tetrimino::descend()
{
    // If enough time has passed, move down 1 block
    if(descent_delta_.get_ticks() >= kTetroDescentRate) {
        descent_delta_.start();
        y_position_ += kBlockHeight * kBlocksPerDescent;
    }
    // TODO: Handle hitting the bottom of grid or other blocks

}

void Tetrimino::move(int delta_ticks)
{
    //Move the dot left or right
    //x_position_+= x_velocity_ * (delta_ticks / 1000.f);

    //If the dot went too far to the left
    if(x_position_< 0) {
        //Move back
        x_position_= 0;
    }
    //or the right
    else if(x_position_+ kBlockWidth > kScreenWidth) {
        //Move back
        x_position_= kScreenWidth - kBlockWidth;
    }

    //Move the dot up or down
    //y_position_+= y_velocity_ * (delta_ticks / 1000.f);

    //If the dot went too far up
    if(y_position_< 0) {
        //Move back
        y_position_= 0;
    }
    //or down
    else if(y_position_+ kBlockHeight > kScreenHeight) {
        //Move back
        y_position_= kScreenHeight - kBlockHeight;
    }
}

void Tetrimino::rotate(int direction, int number_of_turns)
{
    SDL_Surface * rotated_surface = nullptr;

    rotated_surface = rotateSurface90Degrees(surface_, number_of_turns);
    SDL_FreeSurface(surface_);
    surface_ = rotated_surface;
}

void Tetrimino::show(SDL_Surface * screen)
{
    apply_surface(x_position_, y_position_, surface_, screen);
}
*/
