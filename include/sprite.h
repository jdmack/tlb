#ifndef TLB_SPRITE_H_
#define TLB_SPRITE_H_

#include <string>
#include "SDL/SDL.h"

class GameObject;
class Screen;

const int kNumOfSprites  = 24;
const int kSpriteOffsetX = 64;
const int kSpriteOffsetY = 64;

const int kSpriteNorthHigh = 0;
const int kSpriteNorthLow = 1;
const int kSpriteNorthMedium = 2;

const int kSpriteNorthEastHigh = 3;
const int kSpriteNorthEastLow = 4;
const int kSpriteNorthEastMedium = 5;

const int kSpriteEastHigh = 6;
const int kSpriteEastLow = 7;
const int kSpriteEastMedium = 8;

const int kSpriteSouthEastHigh = 9;
const int kSpriteSouthEastLow = 10;
const int kSpriteSouthEastMedium = 11;

const int kSpriteNorthWestHigh = 12;
const int kSpriteNorthWestLow = 13;
const int kSpriteNorthWestMedium = 14;

const int kSpriteWestHigh = 15;
const int kSpriteWestLow = 16;
const int kSpriteWestMedium = 17;

const int kSpriteSouthWestHigh = 18;
const int kSpriteSouthWestLow = 19;
const int kSpriteSouthWestMedium = 20;

const int kSpriteSouthHigh = 21;
const int kSpriteSouthLow = 22;
const int kSpriteSouthMedium = 23;

class Sprite
{
    private:
        int frame_;
        double rotation_;
        double width_;
        double height_;
        SDL_Texture * texture_;
        Screen * screen_;
        std::string art_asset_;
        std::string select_art_asset_;
        GameObject * object_;
        SDL_Rect sprites_[kNumOfSprites];

    public:
        Sprite(GameObject * object, std::string asset, std::string select_asset);

        // accessors
        double width() const { return width_; }
        double height() const { return height_; }
        double rotation() const { return rotation_; }
        std::string art_asset() const { return art_asset_; }
        SDL_Texture * texture() const { return texture_; }
        Screen * screen() const { return screen_; }

        // mutators
        void set_rotation(double rotation);
        void set_texture(SDL_Texture * texture) { texture_ = texture; }
        void set_screen(Screen * screen) { screen_ = screen; }
        void set_object(GameObject * object) { object_ = object; }

        void draw();
        void select();
        void deselect();
        void setup_sprites();

};

#endif
