/*
#ifndef TLB_EVENT_EVENT_HANDLER_H_
#define TLB_EVENT_EVENT_HANDLER_H_

#include "event/event_dispatcher.h"

class EventHandler
{

    protected:
        void send_event(int eventType, int arg1 = 0, int arg2 = 0) {
            EventDispatcher::Get()->SendEvent(eventType, arg1, arg2);
        }

    private:
        EventHandler * next_handler_;
    public:
        virtual void EventHandler(const Event &e) = 0;

      // Mutator and selector
      EventHandler * GetNextHandler(void) {return _nextHandler;}
      void SetNextHandler(EventHandler *next) {_nextHandler = next;}

      EventHandler() : _nextHandler(0) {
          EventDispatcher::Get()->RegisterHandler(this);
      }
};

*/
