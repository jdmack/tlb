#pragma once


#include "EventDispatcher.h"

// The event structure
struct Event {
  int Type;
  int arg1, arg2;
};


// Defination of all the different type of events
enum EventType
{
   // Mouse button events. Each of the next six events gets passed
  // the absolute position of the mouse
  E_MOUSELEFTBUTTONPRESS, 
  E_MOUSELEFTBUTTONRELEASE,

  // Start new games
  E_NEWGAMEEASY,
  E_NEWGAMENORMAL,
  E_NEWGAMEHARD,

  // Game play related
  E_INCREMENTSCORE,
  E_PAUSEGAME,
  E_CONTINUEGAME,
  E_GAMEOVER,

  // Close the App
  E_APPCLOSE
};


class IEventHandler
{

    public:
        virtual void EventHandler(const Event &e) = 0;

      // Mutator and selector
      IEventHandler * GetNextHandler(void) {return _nextHandler;}
      void SetNextHandler(IEventHandler *next) {_nextHandler = next;}

      IEventHandler() : _nextHandler(0) {
          EventDispatcher::Get()->RegisterHandler(this);
      }

    protected:
        void SendEvent(int eventType, int arg1 = 0, int arg2 = 0) {
            EventDispatcher::Get()->SendEvent(eventType, arg1, arg2);
        }

    private:
        IEventHandler *_nextHandler;
};
