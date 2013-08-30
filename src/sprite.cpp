#include "sprite.h"
#include "screen.h"
#include "game_object.h"
#include "util/logger.h"

Sprite::Sprite(GameObject * object, std::string asset, std::string select_asset)
{
    frame_ = kSpriteNorthLow;
    object_ = object;
    rotation_ = object->rotation();
    art_asset_ = asset;
    select_art_asset_ = select_asset;
    surface_ = nullptr;
    screen_ = nullptr;
    setup_sprites();
}

void Sprite::select()
{
    SDL_Surface * select_surface = screen_->load_image_alpha(select_art_asset_);

    screen_->apply_surface(0, 0, select_surface, surface_);
    SDL_FreeSurface(select_surface);
}

void Sprite::deselect()
{
    SDL_FreeSurface(surface_);
    surface_ = nullptr;
    surface_ = screen_->load_image_alpha(art_asset_);
}

void Sprite::draw()
{
    if(rotation_ != object_->rotation()) {
        set_rotation(object_->rotation());
    }
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = object_->width();
    clip.h = object_->height();


    //frame_ = kSpriteNorthLow;
    //frame_ = kSpriteNorthEastLow;
    //frame_ = kSpriteEastLow;
    //frame_ = kSpriteSouthEastLow;
    //frame_ = kSpriteSouthLow;
    //frame_ = kSpriteSouthWestLow;
    //frame_ = kSpriteWestLow;
    //frame_ = kSpriteNorthWestLow;
    screen_->blit_surface(object_->x_position() - (object_->width() / 2), object_->y_position() - (object_->height() / 2), surface_, &sprites_[frame_]);
    //screen_->blit_surface(object_->x_position() - (object_->width() / 2), object_->y_position() - (object_->height() / 2), surface_, &clip);
}

void Sprite::set_rotation(double rotation)
{
    //surface_ = screen_->rotate_surface(surface_, rotation - rotation_);
    rotation_ = rotation;

    // set frame
    /*
    if((rotation_ < 2 * kPi / 3) && (rotation_ >= kPi / 3)) { frame_ = kSpriteNorthLow; }
    else if((rotation_ < kPi / 3) && (rotation_ >= kPi / 6)) { frame_ = kSpriteNorthEastLow; }
    else if((rotation_ < kPi / 6) && (rotation_ >= 11 * kPi / 6)) { frame_ = kSpriteEastLow; }
    else if((rotation_ < 11 * kPi / 6) && (rotation_ >= 5 * kPi / 3)) { frame_ = kSpriteSouthEastLow; }
    else if((rotation_ < 5 * kPi / 3) && (rotation_ >= 4 * kPi / 3)) { frame_ = kSpriteSouthLow; }
    else if((rotation_ < 4 * kPi / 3) && (rotation_ >= 7 * kPi / 6)) { frame_ = kSpriteSouthWestLow; }
    else if((rotation_ < 7 * kPi / 6) && (rotation_ >= 5 * kPi / 6)) { frame_ = kSpriteWestLow; }
    else if((rotation_ < 5 * kPi / 6) && (rotation_ >= 2 * kPi / 3)) { frame_ = kSpriteNorthWestLow; }
    else { frame_ = kSpriteNorthHigh; }
    */

    double degrees = rotation_ / kPi * 180;
    Logger::write(Logger::string_stream << "degrees`: " << degrees);

    if((degrees < 120) && (degrees >= 60)) { frame_ = kSpriteNorthLow; }
    else if((degrees < 60) && (degrees >= 30)) { frame_ = kSpriteNorthEastLow; }

    else if((degrees < 30) || (degrees >= 330)) { frame_ = kSpriteEastLow; }
    else if((degrees < 330) && (degrees >= 300)) { frame_ = kSpriteSouthEastLow; }

    else if((degrees < 300) && (degrees >= 240)) { frame_ = kSpriteSouthLow; }
    else if((degrees < 240) && (degrees >= 210)) { frame_ = kSpriteSouthWestLow; }
    else if((degrees < 210) && (degrees >= 150)) { frame_ = kSpriteWestLow; }
    else if((degrees < 150) && (degrees >= 120)) { frame_ = kSpriteNorthWestLow; }
    else { frame_ = kSpriteNorthMedium; }

    Logger::write(Logger::string_stream << "frame: " << frame_);


}


void Sprite::setup_sprites()
{
    /*
    for(int i = 0; i < 8; i++) {
        for(int j = 0; i < 3; j++) {
            sprites_[3 * i + j].x = 0 + (kSpriteOffsetX * i);
            sprites_[3 * i + j].y = 0 + (kSpriteOffsetY * j);
            sprites_[3 * i + j].w = object_->width();
            sprites_[3 * i + j].h = object_->height();
        }
    }
    */

    sprites_[kSpriteNorthLow].x = kSpriteOffsetX;
    sprites_[kSpriteNorthLow].y = 0;
    sprites_[kSpriteNorthLow].w = object_->width();
    sprites_[kSpriteNorthLow].h = object_->height();

    sprites_[kSpriteNorthEastLow].x = kSpriteOffsetX;
    sprites_[kSpriteNorthEastLow].y = kSpriteOffsetY;
    sprites_[kSpriteNorthEastLow].w = object_->width();
    sprites_[kSpriteNorthEastLow].h = object_->height();

    sprites_[kSpriteEastLow].x = kSpriteOffsetX;
    sprites_[kSpriteEastLow].y = kSpriteOffsetY * 2;
    sprites_[kSpriteEastLow].w = object_->width();
    sprites_[kSpriteEastLow].h = object_->height();

    sprites_[kSpriteSouthEastLow].x = kSpriteOffsetX;
    sprites_[kSpriteSouthEastLow].y = kSpriteOffsetY * 3;
    sprites_[kSpriteSouthEastLow].w = object_->width();
    sprites_[kSpriteSouthEastLow].h = object_->height();

    sprites_[kSpriteNorthWestLow].x = kSpriteOffsetX;
    sprites_[kSpriteNorthWestLow].y = kSpriteOffsetY * 4;
    sprites_[kSpriteNorthWestLow].w = object_->width();
    sprites_[kSpriteNorthWestLow].h = object_->height();

    sprites_[kSpriteWestLow].x = kSpriteOffsetX;
    sprites_[kSpriteWestLow].y = kSpriteOffsetY * 5;
    sprites_[kSpriteWestLow].w = object_->width();
    sprites_[kSpriteWestLow].h = object_->height();

    sprites_[kSpriteSouthWestLow].x = kSpriteOffsetX;
    sprites_[kSpriteSouthWestLow].y = kSpriteOffsetY * 6;
    sprites_[kSpriteSouthWestLow].w = object_->width();
    sprites_[kSpriteSouthWestLow].h = object_->height();

    sprites_[kSpriteSouthLow].x = kSpriteOffsetX;
    sprites_[kSpriteSouthLow].y = kSpriteOffsetY * 7;
    sprites_[kSpriteSouthLow].w = object_->width();
    sprites_[kSpriteSouthLow].h = object_->height();
}
