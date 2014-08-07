#ifndef TLB_GAME_STATE_H_
#define TLB_GAME_STATE_H_


class Game;

class GameState
{
    protected:
        Game * game_;

    public:
        GameState();
        virtual ~GameState();

        // accessors
        virtual Game * game() { return game_; }

        virtual int init();
        virtual bool update(int delta_ticks);
        virtual void render();
        virtual void end();
};

#endif
