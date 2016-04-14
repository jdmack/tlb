#include "SDL2/SDL.h"
#include "gfx/Graphic.h"
#include "Point.h"
#include "util/Logger.h"
#include "gfx/Renderer.h"
#include "Game.h"


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
    renderer->renderTextureFrame(texture_, frame, &offset);
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
    if(containsPoint(point)) {
        return true;
    }
    else {
        return false;
    }
}

bool Graphic::containsPoint(Point point)
{
    if((point.x() < position_.x()) || (point.x() > position_.x() + width_)) {
        return false;
    }
    else if((point.y() < position_.y()) || (point.y() > position_.y() + height_)) {
        return false;
    }

    return true;
}
bool Graphic::loadTexture(std::string artAsset)
{
    artAsset_ = artAsset;
    Renderer * renderer = Game::instance()->renderer();

    texture_ = renderer->loadTexture(artAsset_);
    if(texture_ == nullptr) {
        Logger::write(Logger::ss << "Error loading asset: " << artAsset);
        return false;
    }

    SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);

    return true;
}
