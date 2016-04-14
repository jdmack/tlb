#ifndef TLB_DURATION_H_
#define TLB_DURATION_H_

#include "util/Timer.h"

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
        void setLength(double length) { length_ = length; }

        void start();
        void reset();

        bool isComplete();
};

#endif
