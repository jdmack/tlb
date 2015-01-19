#ifndef TLB_GAME_STATE_H_
#define TLB_GAME_STATE_H_

enum GameStateType {
    GS_BLANK,
    GS_LEVEL
};

class Game;

class GameState
{
    protected:
        GameStateType type_;
        Game * game_;

    public:
        GameState();
        virtual ~GameState();

        // accessors
        GameStateType type() const { return type_; }
        virtual Game * game() { return game_; }

        virtual int init();
        virtual bool update(int delta_ticks);
        virtual void render();
        virtual void end();
};

#endif
