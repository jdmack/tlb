#ifndef TLB_GAME_H_
#define TLB_GAME_H_

#include "SDL2/SDL.h"
#include "util/timer.h"

class Camera;
class EntityManager;
class EventManager;
class Level;
class Renderer;
class GameState;

class Game
{
    private:
        int exit_code_;
        bool quit_;

        Timer delta_timer_;
        Renderer * renderer_;
        EntityManager * entity_manager_;
        EventManager * event_manager_;
        Camera * camera_;
        Level * level_;
        GameState * current_state_;
        GameState * next_state_;

        static Game * instance_;

        Game();
        bool change_state();

    public:
        Game(const Game &) = delete;
        Game& operator=(const Game &) = delete;
        ~Game();

        static Game * instance();

        int run();
        void game_loop();
        void process_arguments(int argc, char * argv[]);

        // accessors
        Renderer * renderer() const { return renderer_; }
        EntityManager * entity_manager() const { return entity_manager_; }
        EventManager * event_manager() const { return event_manager_; }
        Camera * camera() const { return camera_; }
        Level * level() const { return level_; }
        GameState * state() const { return current_state_; }

        // mutators
        void set_quit(bool quit) { quit_ = quit; }
        void set_level(Level * level) { level_ = level; }
        void set_next_state(GameState * state) { next_state_ = state; }

};

#endif
