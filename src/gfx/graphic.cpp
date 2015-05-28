#include "SDL2/SDL.h"
#include "gfx/graphic.h"
#include "point.h"
#include "util/logger.h"
#include "gfx/renderer.h"
#include "game.h"


Graphic::Graphic()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;
    visible_ = true;

    texture_ = nullptr;
}

Graphic::~Graphic()
{
    SDL_DestroyTexture(texture_);
}


void Graphic::render(Frame * frame)
{
    Renderer * renderer = Game::instance()->renderer();
    SDL_Rect offset = { position_.x(), position_.y(), width_, height_ };
    renderer->render_texture_frame(texture_, frame, &offset);
}

bool Graphic::toggle()
{
    visible_ = !visible_;
    return visible_;
}

void Graphic::update()
{

}

bool Graphic::click(Point point)
{
    return false;
    if(contains_point(point)) {
        return true;
    }
    else {
        return false;
    }
}

bool Graphic::contains_point(Point point)
{
    if((point.x() < position_.x()) || (point.x() > position_.x() + width_)) {
        return false;
    }
    else if((point.y() < position_.y()) || (point.y() > position_.y() + height_)) {
        return false;
    }

    return true;
}
bool Graphic::load_texture(std::string art_asset)
{
    art_asset_ = art_asset;
    Renderer * renderer = Game::instance()->renderer();

    texture_ = renderer->load_texture(art_asset_);
    if(texture_ == nullptr) {
        return false;
    }

    SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);


    return true;
}
