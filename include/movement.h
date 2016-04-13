#ifndef TLB_MOVEMENT_H_
#define TLB_MOVEMENT_H_

#include <string>
#include "vector.h"
#include "point.h"
#include "action/action.h"

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
        void setClockwise(bool clockwise) { clockwise_ = clockwise; }
        void setDegrees(double degrees) { degrees_ = degrees; }
        void setVector(Vector vector) { vector_ = vector; }
        void setStart(Point start) { start_ = start; }
        void setDestination(Point destination) { destination_ = destination; }

        std::string toString();
};

#endif
