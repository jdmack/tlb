#include "assets.h"
#include "action/action.h"
#include "gfx/sprite.h"
#include "gfx/renderer.h"
#include "gameObject.h"
#include "util/logger.h"
#include "rapidxml/rapidxml.hpp"
#include "entity.h"
#include "frame.h"

Sprite::Sprite(GameObject * object, std::string asset, std::string selectAsset)
{
    object_ = object;
    artAsset_ = asset;
    selectArtAsset_ = selectAsset;
    texture_ = nullptr;
    renderer_ = nullptr;
    height_ = object->height();
    width_ = object->width();

    currentAction_ = ACTION_IDLE;
    currentDirection_ = object_->rotation();

    // open xml doc
    rapidxml::xml_document<> doc;
    //std::ifstream file(kAssetSpriteXMLZombie);
    std::ifstream file(kAssetSpriteXMLHuman);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());
    doc.parse<0>(&content[0]);

    rapidxml::xml_node<> *sprite = doc.first_node();     // this is the sprite element

    // Iterate through animations
    for(rapidxml::xml_node<> *animation = sprite->first_node("animation"); animation; animation = animation->nextSibling()) {

        std::string animationKey;
        int animationTime;

        for (rapidxml::xmlAttribute<> *attribute = animation->first_attribute(); attribute; attribute = attribute->nextAttribute()) {

                std::string attributeName = attribute->name();

                if(attributeName.compare("key") == 0) {
                    animationKey = attribute->value();
                }
                else if(attributeName.compare("time") == 0) {
                    animationTime = atoi(attribute->value());
                }

        }
        //Logger::write(Logger::ss << "Reading Animation: " << animationKey);
        Animation thisAnimation(animationKey, animationTime);

        // Iterate through frames
        for(rapidxml::xml_node<> *frame = animation->first_node("frame"); frame; frame = frame->nextSibling()) {

            std::string frameKey;
            int frameX, frameY, frameWidth, frameHeight;

            // Iterate through attributes
            for (rapidxml::xmlAttribute<> *attribute = frame->first_attribute(); attribute; attribute = attribute->nextAttribute()) {

                std::string attributeName = attribute->name();

                if(attributeName.compare("key") == 0) {
                    frameKey = attribute->value();
                }
                else if(attributeName.compare("x") == 0) {
                    frameX = atoi(attribute->value());
                }
                else if(attributeName.compare("y") == 0) {
                    frameY = atoi(attribute->value());
                }
                else if(attributeName.compare("width") == 0) {
                    frameWidth = atoi(attribute->value());
                }
                else if(attributeName.compare("height") == 0) {
                    frameHeight = atoi(attribute->value());
                }
            }

            SDL_Rect thisFrame = { frameX, frameY, frameWidth, frameHeight };
            thisAnimation.insertFrame(animationKey + frameKey, thisFrame);
        }

    animations_.insert(std::pair<std::string, Animation>(animationKey, thisAnimation));

    }

    animationTimer_.start();
    currentAnimation_ = animations_["idleRight"];

    double rotation = object_->rotation();

    if((rotation >= 45) && (rotation <= 135)) {
        currentAnimation_ = animations_["idleDown"];
    }
    else if((rotation >= 135) && (rotation <= 225)) {
        currentAnimation_ = animations_["idleLeft"];
    }
    else if((rotation >= 225) && (rotation <= 315)) {
        currentAnimation_ = animations_["idleUp"];
    }
    else {
        currentAnimation_ = animations_["idleRight"];
    }
}

void Sprite::select()
{
    /*
    SDL_DestroyTexture(texture_);

    SDL_Surface * surface = renderer_->loadImageAlpha(artAsset_);
    SDL_Surface * selectSurface = renderer_->loadImageAlpha(selectArtAsset_);

    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    offset.w = width_;
    offset.h = height_;

    renderer_->applySurface(selectSurface, surface, &offset);

    texture_ = SDL_CreateTextureFromSurface(renderer_->renderer(), surface);
    SDL_FreeSurface(selectSurface);
    */
}

void Sprite::deselect()
{
    /*
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    texture_ = renderer_->loadTextureAlpha(artAsset_);
    */
}

void Sprite::render(Frame * frame)
{
    update();

    // convert floating-point positions to integers for drawing
    SDL_Rect offset = { (int)object_->xPosition() - ((int)object_->width() / 2), (int)object_->yPosition() - ((int)object_->height() / 2), height_, width_ };
    SDL_Rect clip = currentAnimation_.currentFrame();
    renderer_->renderTextureFrame(texture_, frame, &offset, &clip);

    if(object_->selected()) {

        Color color = Color(255, 0, 255);
        SDL_Rect rect = {
            (int)(object_->xPosition() + frame->x() - width_ / 2),
            (int)(object_->yPosition() + frame->y() - height_ / 2),
            width_,
            height_
        };

        renderer_->drawRectangle(rect, color);

    }
}

void Sprite::update()
{
    // update current animation based on current action
    ActionType actionType;
    Entity * entity;
    std::string animation = "";

    if(object_->isEntity()) {
        entity = staticCast<Entity *>(object_);

        actionType = entity->actionType();

        // TODO(2014-09-09/JM): Remember "last action" in a way so we don't have to always recheck this
        if((actionType != currentAction_) || (currentDirection_ != object_->rotation())) {
            currentAction_ = actionType;

            switch(actionType) {
                case ACTION_ATTACK:
                    animation += "attack";
                    break;
                case ACTION_DEAD:
                    animation += "dead";
                    break;
                case ACTION_IDLE:
                    animation += "idle";
                    break;
                case ACTION_MOVE:
                    animation += "walk";
                    break;
                default:
                    animation += "idle";
                    break;
                }

            animation += "_";

            // TODO(2014-09-09/JM): Remember "last rotation" as a string or enum so we don't have to always check these regions
            //if(currentDirection_ != object_->rotation()) {
            currentDirection_ = object_->rotation();

            // determine direction
            double rotation = object_->rotation();

            if((rotation >= 45) && (rotation <= 135)) {
                animation += "down";
            }
            else if((rotation >= 135) && (rotation <= 225)) {
                animation += "left";
            }
            else if((rotation >= 225) && (rotation <= 315)) {
                animation += "up";
            }
            else {
                animation += "right";
            }
            //}
            currentAnimation_ = animations_[animation];
        }
    }
    else {
        // This is for regular GameObjects. 
        // TODO(2014-09-09/JM): Decide how to handle animations for GameObjects (i.e. a "default" animation)
        animation = "idleRight";
        currentAnimation_ = animations_[animation];
    }

    // update frame of current animation
    if(animationTimer_.getTicks() >= currentAnimation_.time()) {
        currentAnimation_.nextFrame();
        animationTimer_.start();
    }
}
