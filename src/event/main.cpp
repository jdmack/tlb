// For defining class A and B
#include "event_handler.h"

// for the main function
#include "EventDispatcher.h"
#include <iostream>
using namespace std;


class A : public EventHandler {

public:
  void EventHandler(const Event &e) {
    switch (e.Type) {
      case E_NEWGAMEEASY:
        cout << "Class A handling E_NEWGAMEEASY event" << endl;
        cout << "Class A sending a E_INCREMENTSCORE event" << endl;
        SendEvent(E_INCREMENTSCORE);
        break;
      case E_PAUSEGAME:
        cout << "Class A handling E_PAUSEGAME event" << endl;
        break;
    }
  }
};

class B : public EventHandler {

public:
  void EventHandler(const Event &e) {
    switch (e.Type) {
      case E_INCREMENTSCORE:
        cout << "Class B handling E_INCREMENTSCORE event" << endl;
        break;
      case E_PAUSEGAME:
        cout << "Class B handling E_PAUSEGAME event" << endl;
        break;
    }
  }
};


void event_main () {
  A a1;
  B b1;

  cout << "Main fct sending E_NEWGAMEEASY event" << endl;
  EventDispatcher::Get()->SendEvent(E_NEWGAMEEASY);
  cout << "Main fct sending E_PAUSEGAME event" << endl;
  EventDispatcher::Get()->SendEvent(E_PAUSEGAME);

  char c;
  cout << "Press any key followed by [Enter] to exit" << endl;
  cin >> c;

  exit(0);
}
