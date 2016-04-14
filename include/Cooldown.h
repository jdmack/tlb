#ifndef TLB_COOLDOWN_H_
#define TLB_COOLDOWN_H_

#include "util/Timer.h"

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
        void setLength(double length) { length_ = length; }

        void start();
        void reset();

        bool ready();
        bool isComplete();
        bool isRunning();
};

#endif
