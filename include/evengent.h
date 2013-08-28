/* Event Agent */

#ifndef TLB_EVENGENT_H_
#define TLB_EVENGENT_H_

class TlbGame;

class Evengent
{
    private:
        TlbGame * game_;
    public:
        Evengent();
        void handle_events();

        // mutators
        void set_game(TlbGame * game) { game_ = game; }
};

#endif
