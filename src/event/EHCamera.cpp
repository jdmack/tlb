#include <list>
#include "event/EHLevel.h"
#include "event/Event.h"
#include "event/EKeyPress.h"
#include "event/EMouseClick.h"
#include "Game.h"
#include "GameObject.h"
#include "Entity.h"
#include "util/GlobalTimer.h"
#include "GameState.h"
#include "GSLevel.h"
#include "util/Logger.h"
#include "EntityManager.h"
#include "ui/UserInterface.h"


EHLevel::EHLevel()
{
    toggleKey_ = KEY_NONE;
}

EHLevel::~EHLevel()
{

}

void EHLevel::handleEvent(Event * event)
{
    switch(event->type()) {
        case EVENT_MOUSE_CLICK:    
            EMouseClick * mouseEvent = static_cast<EMouseClick *>(event);
            Logger::write(Logger::ss << "Mouse Click " << mouseEvent->point().toString());

            if(mouseEvent->button() == MOUSE_LEFT) {
                mouseLeftClick(mouseEvent->point());
            }
            else if(mouseEvent->button() == MOUSE_RIGHT) {
                mouseRightClick(mouseEvent->point());
            }
            break;

        case EVENT_MOUSE_MOTION:

            break;
        
        case EVENT_KEY_PRESS:

            EKeyPress * keyEvent = static_cast<EKeyPress *>(event);
            keyPress(keyEvent->keyType());

            break;

    }

}

void EHLevel::mouseLeftClick(Point point)
{
    Logger::write("Mouse Left Click");

    GSLevel * gsLevel = static_cast<GSLevel *>(Game::instance()->state());
    UserInterface * ui = gsLevel->userInterface();

    // POINT IS ON UI ELEMENT
    if(ui->containsPoint(point)) {
        ui->click(point);
    }
    // POINT IS IN LEVEL AREA
    else {
        // adjust point for being in level area
        Frame * levelArea = gsLevel->levelArea();
        point = Point(point.x() - levelArea->x(), point.y() - levelArea->y());

        // Check if an entity is selected and R is being held down
        if(toggleKey_ == KEY_R) {
            Entity * entity = Game::instance()->entityManager()->selected();
            if(entity != nullptr) {
                entity->rotate(point);
            }
        }
        // Check if an entity is selected and A is being held down
        else if(toggleKey_ == KEY_A) {
            Entity * entity = Game::instance()->entityManager()->selected();

            GameObject * targetObject = Game::instance()->entityManager()->getObjectAt(point.x(), point.y());

            if((targetObject != nullptr) && (targetObject->isEntity())) {
                Entity * targetEntity = static_cast<Entity *>(targetObject);
                entity->attack(targetEntity);
            }

        }
        else {
            // 2 cases
            GameObject * clickedOn = Game::instance()->entityManager()->getObjectAt(point.x(), point.y());
            // 1. clicking on nothing
            if(clickedOn == nullptr) {
                // NOTE: left clicking on anything deselectsAll with current functionality
                Logger::write("Deselecting");
                Game::instance()->entityManager()->deselectAll();
            }
            // 2. clicking on something
            else {
                if(!clickedOn->selected() || Game::instance()->entityManager()->objects()->size() != 1) {
                    Game::instance()->entityManager()->deselectAll();
                    Game::instance()->entityManager()->select(clickedOn);
                }
            }
        }

    }

    toggleKey_ = KEY_NONE;
}

void EHLevel::mouseRightClick(Point point)
{
    Logger::write("Mouse Right Click");

    GSLevel * gsLevel = static_cast<GSLevel *>(Game::instance()->state());
    UserInterface * ui = gsLevel->userInterface();

    // POINT IS ON UI ELEMENT
    if(ui->containsPoint(point)) {
        //ui->click(point); // DON'T CLICK ON RIGHT CLICK
    }
    // POINT IS IN LEVEL AREA
    else {
        // adjust point for being in level area
        Frame * levelArea = gsLevel->levelArea();
        point = Point(point.x() - levelArea->x(), point.y() - levelArea->y());

        Entity * entity = Game::instance()->entityManager()->selected();

        // If nothing selected, do nothing
        if(entity == nullptr) {
            return;
        }

        // Check if right click was on an entity
        GameObject * targetObject = Game::instance()->entityManager()->getObjectAt(point.x(), point.y());

        if((targetObject != nullptr) && (targetObject->isEntity())) {
            Entity * targetEntity = static_cast<Entity *>(targetObject);
            entity->attack(targetEntity);
        }

        // Clicked on empty space, issue move command
        else {
            entity->move(point);
        }
    }
}

void EHLevel::keyPress(KeyType key)
{
    toggleKey_ = key;
    Entity * entity;

    switch(key) {

        case KEY_ESCAPE:
            Game::instance()->setQuit(true);
            break;

        case KEY_SPACE:
            GlobalTimer::instance()->togglePause();
            break;

        case KEY_S:
            entity = Game::instance()->entityManager()->selected();
            if(entity != nullptr) {
            // something is selected, can now give it an order
                entity->stop();
            }
            break;
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_A:
            break;
        case KEY_B:
            break;
        case KEY_C:
        case KEY_D:
        case KEY_E:
        case KEY_F:
        case KEY_G:
        case KEY_H:
        case KEY_I:
        case KEY_J:
        case KEY_K:
        case KEY_L:
        case KEY_M:
        case KEY_N:
        case KEY_O:
        case KEY_P:
        case KEY_Q:
        case KEY_R:
        case KEY_T:
        case KEY_U:
        case KEY_V:
        case KEY_W:
        case KEY_X:
        case KEY_Y:
        case KEY_Z:
        case KEY_NONE:
            break;
    }
}
