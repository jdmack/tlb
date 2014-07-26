#ifndef TLB_MOVEMENT_H_
#define TLB_MOVEMENT_H_

#include <string>
#include "vector.h"
#include "point.h"
#include "actions/action.h"

class GameObject;

class Movement : public Action
{
    private:
        bool clockwise_;
        double degrees_;
        Vector vector_;
        Point start_;
        Point destination_;

    public:
        Movement(Vector vector, Point start, Point destination);

        // accessors
        bool clockwise() const { return clockwise_; }
        double degrees() const { return degrees_; }
        Vector vector() const { return vector_; }
        Point start() const { return start_; }
        Point destination() const { return destination_; }

        // mutators
        void set_clockwise(bool clockwise) { clockwise_ = clockwise; }
        void set_degrees(double degrees) { degrees_ = degrees; }
        void set_vector(Vector vector) { vector_ = vector; }
        void set_start(Point start) { start_ = start; }
        void set_destination(Point destination) { destination_ = destination; }

        std::string to_string();
};

#endif
