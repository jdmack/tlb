
#include <list>
#include "event/EHLevel.h"
#include "event/Event.h"
#include "event/EKeyPress.h"
#include "event/EMouse.h"
#include "event/EventDispatcher.h"
#include "event/EHCamera.h"
#include "Game.h"
#include "GameObject.h"
#include "Entity.h"
#include "util/GlobalTimer.h"
#include "GameState.h"
#include "GSLevel.h"
#include "util/Logger.h"
#include "EntityManager.h"
#include "ui/UserInterface.h"
#include "gfx/Renderer.h"
#include "gfx/Camera.h"

#include <iostream>

EHLevel::EHLevel() : EventHandler()
{
    toggleKey_ = KEY_NONE;
    cameraHandlerId_ = 0;
    cameraOn_ = false;
}

EHLevel::~EHLevel()
{

}

bool EHLevel::handleEvent(Event * event)
{
    bool ret = false;

    switch(event->type()) {
        case EVENT_MOUSE_CLICK:
        {
            EMouse * mouseEvent = static_cast<EMouse *>(event);
            //Logger::write(Logger::ss << "Mouse Click " << mouseEvent->position().toString());
            if(mouseEvent->button() == MOUSE_BUTTON_LEFT) {
                mouseLeftClick(mouseEvent->position());
            }
            else if(mouseEvent->button() == MOUSE_BUTTON_RIGHT) {
                mouseRightClick(mouseEvent->position());
            }

            ret = true;
            break;
        }
        case EVENT_MOUSE_MOTION:
        {
            //EMouse * mouseEvent = static_cast<EMouse *>(event);
            //ret = true;
            break;
        }
        case EVENT_GAME_QUIT:
        {
            Game::instance()->setQuit(true);

            ret = true;
            break;
        }

        case EVENT_KEY_PRESS:
        {
            EKeyPress * keyEvent = static_cast<EKeyPress *>(event);
            keyPress(keyEvent->keyType());

            ret = true;
            break;
        }
    }
    return ret;
}

void EHLevel::mouseLeftClick(Vector2i position)
{
    Logger::write("Mouse Left Click");

    /*
    GSLevel * gsLevel = static_cast<GSLevel *>(Game::instance()->state());
    UserInterface * ui = gsLevel->userInterface();

    // POINT IS ON UI ELEMENT
    if(ui->contains(point)) {
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
    */
}

void EHLevel::mouseRightClick(Vector2i position)
{
    Logger::write("Mouse Right Click");

    /*
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
    */
}

void EHLevel::keyPress(KeyType key)
{
    toggleKey_ = key;

    switch(key) {

        case KEY_ESCAPE:
            Game::instance()->setQuit(true);
            break;

        case KEY_SPACE:
            GlobalTimer::instance()->togglePause();
            break;

        case KEY_S:
        {
            Entity * entity = Game::instance()->entityManager()->selected();
            if (entity != nullptr) {
                // something is selected, can now give it an order
                entity->stop();
            }
            break;
        }
        case KEY_LEFT_CTRL:
        {
            if (cameraOn_) {
                std::cout << "Camera OFF" << std::endl;
                EventDispatcher::instance()->removeHandler(cameraHandlerId_);
                cameraHandlerId_ = 0;
                cameraOn_ = false;
                Game::instance()->renderer()->showCursor(true);
            }

            else {
                std::cout << "Camera ON" << std::endl;
                EHCamera * cameraHandler = new EHCamera();
                cameraHandlerId_ = cameraHandler->id();
                EventDispatcher::instance()->registerHandler(cameraHandler);
                cameraOn_ = true;
                Game::instance()->renderer()->showCursor(false);
                Game::instance()->renderer()->warpMouse(Vector2i(Game::instance()->renderer()->screenWidth() / 2,
                    Game::instance()->renderer()->screenHeight() / 2));
            }
            break;
        }
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

