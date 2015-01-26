#include "ui/character_panel.h"
#include "frame.h"
#include "game.h"
#include "entity_manager.h"
#include "game_object.h"
#include "entity.h"
#include "assets.h"
#include "renderer.h"
#include "util/logger.h"

CharacterPanel::CharacterPanel()
{
    frame_ = nullptr;
    entity_ = nullptr;
    portrait_ = nullptr;
    name_ = nullptr;
    role_ = nullptr;

    //texture_ = Game::instance()->renderer()->load_texture(kAssetUICharacterPanel);
    load_texture(kAssetUICharacterPanel);
    selected_texture_ = Game::instance()->renderer()->load_texture(kAssetUICharacterPanelSelected);

}

CharacterPanel::~CharacterPanel()
{

}

void CharacterPanel::render(Frame * frame)
{
    if(frame_ != nullptr) {
        frame_->set_parent(frame);
    }
    UIElement::render(frame);
}

void CharacterPanel::update()
{
}

bool CharacterPanel::click(Point point)
{
    if(contains_point(point)) {
        return true;
        GameObject * object = static_cast<GameObject *>(entity_);
        //Game::instance()->entity_manager()->select(static_cast<GameObject *>(entity_));
        //Game::instance()->entity_manager()->select(entity_);
    }
    else {
        return false;
    }
}
