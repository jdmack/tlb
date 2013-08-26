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
        void register_game(TlbGame * game);
};


#endif
