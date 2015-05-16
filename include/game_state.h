#ifndef TLB_GAME_STATE_H_
#define TLB_GAME_STATE_H_

enum GameStateType {
    GS_BLANK,
    GS_LEVEL
};

class GameState
{
    protected:
        GameStateType type_;

    public:
        //GameState();
        virtual ~GameState() {}

        // accessors
        GameStateType type() const { return type_; }

        virtual bool init() = 0;
        virtual bool update(int delta_ticks) = 0;
        virtual void render() = 0;
        virtual void end() = 0;
};

#endif
