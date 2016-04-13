#include "ui/characterPanel.h"
#include "frame.h"
#include "game.h"
#include "entityManager.h"
#include "gameObject.h"
#include "entity.h"
#include "assets.h"
#include "gfx/renderer.h"
#include "util/logger.h"

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
        GameObject * object = staticCast<GameObject *>(entity_);
        Game::instance()->entityManager()->select(staticCast<GameObject *>(entity_));
        Game::instance()->entityManager()->select(entity_);
        return false;
    }
    else {
        return false;
    }
}
