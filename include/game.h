#ifndef TLB_TLB_GAME_H_
#define TLB_TLB_GAME_H_

#include "SDL2/SDL.h"
#include "utils/timer.h"

class Camera;
class EntityManager;
class EventManager;
class Level;
class Renderer;

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

    public:
        Game();
        ~Game();
        int run();
        void game_loop();
        void process_arguments(int argc, char * argv[]);

        // accessors
        Renderer * renderer() const { return renderer_; }
        EntityManager * entity_manager() const { return entity_manager_; }
        EventManager * event_manager() const { return event_manager_; }
        Camera * camera() const { return camera_; }
        Level * level() const { return level_; }

        // mutators
        void set_quit(bool quit) { quit_ = quit; }
        void level(Level * level) { level_ = level; }
};

#endif
