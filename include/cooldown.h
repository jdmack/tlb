#ifndef TLB_COOLDOWN_H_
#define TLB_COOLDOWN_H_

#include "util/timer.h"

class Cooldown
{
    private:
        Timer timer_;
        double length_;

    public:
        Cooldown();
        Cooldown(double length);

        // accessors
        double length() const { return length_; }

        // mutators
        void set_length(double length) { length_ = length; }

        void start();
        void reset();

        bool ready();
        bool is_complete();
        bool is_running();
};

#endif
