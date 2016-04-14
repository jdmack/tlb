#ifndef TLB_GAME_H_
#define TLB_GAME_H_

#include "SDL2/SDL.h"
#include "util/Timer.h"

class Camera;
class EntityManager;
class EventManager;
class Level;
class Renderer;
class GameState;

class Game
{
    private:
        int exitCode_;
        bool quit_;

        Timer deltaTimer_;
        Renderer * renderer_;
        EntityManager * entityManager_;
        EventManager * eventManager_;
        Camera * camera_;
        Level * level_;
        GameState * currentState_;
        GameState * nextState_;

        static Game * instance_;

        Game();
        bool changeState();

    public:
        Game(const Game &) = delete;
        Game& operator=(const Game &) = delete;
        ~Game();

        static Game * instance();

        int run();
        void gameLoop();
        void processArguments(int argc, char * argv[]);

        // accessors
        Renderer * renderer() const { return renderer_; }
        EntityManager * entityManager() const { return entityManager_; }
        EventManager * eventManager() const { return eventManager_; }
        Camera * camera() const { return camera_; }
        Level * level() const { return level_; }
        GameState * state() const { return currentState_; }

        // mutators
        void setQuit(bool quit) { quit_ = quit; }
        void setLevel(Level * level) { level_ = level; }
        void setNextState(GameState * state) { nextState_ = state; }

};

#endif
