#ifndef TLB_COOLDOWN_H_
#define TLB_COOLDOWN_H_

#include "utils/timer.h"

class Cooldown
{
    private:
        Timer timer_;
        double duration_;

    public:
        Cooldown();
        Cooldown(double duration);

        // accessors
        double duration() const { return duration_; }

        // mutators
        void set_duration(double duration) { duration_ = duration; }

        void start();
        void reset();

        bool ready();
        bool is_complete();
        bool is_running();
};

#endif
