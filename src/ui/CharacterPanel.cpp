#include "ui/CharacterPanel.h"
#include "Frame.h"
#include "Game.h"
#include "EntityManager.h"
#include "GameObject.h"
#include "Entity.h"
#include "Assets.h"
#include "gfx/Renderer.h"
#include "util/Logger.h"

CharacterPanel::CharacterPanel()
{
    frame_ = nullptr;
    entity_ = nullptr;
    portrait_ = nullptr;
    name_ = nullptr;
    role_ = nullptr;

    //texture_ = Game::instance()->renderer()->loadTexture(kAssetUICharacterPanel);
    loadTexture(kAssetUICharacterPanel);
    selectedTexture_ = Game::instance()->renderer()->loadTexture(kAssetUICharacterPanelSelected);

}

CharacterPanel::~CharacterPanel()
{

}

void CharacterPanel::render(Frame * frame)
{
    if(frame_ != nullptr) {
        frame_->setParent(frame);
    }
    UIElement::render(frame);
}

void CharacterPanel::update()
{
}

bool CharacterPanel::click(Point point)
{
    if(containsPoint(point)) {
        GameObject * object = static_cast<GameObject *>(entity_);
        Game::instance()->entityManager()->select(static_cast<GameObject *>(entity_));
        Game::instance()->entityManager()->select(entity_);
        return false;
    }
    else {
        return false;
    }
}
