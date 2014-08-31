#ifndef TLB_DURATION_H_
#define TLB_DURATION_H_

#include "util/timer.h"

class Duration
{
    private:
        Timer timer_;
        double length_;

    public:
        Duration();
        Duration(double length);

        // accessors
        double length() const { return length_; }

        // mutators
        void set_length(double length) { length_ = length; }

        void start();
        void reset();

        bool is_complete();
};

#endif
