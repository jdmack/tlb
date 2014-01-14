#ifndef TLB_MOVEMENT_H_
#define TLB_MOVEMENT_H_

#include "vector.h"
#include "point.h"
#include "action.h"

class GameObject;

class Movement : public Action
{
    private:
        double distance_;
        bool clockwise_;
        double degrees_;
        Vector vector_;
        Point start_;
        Point destination_;
        Vector maximum_velocity_;

    public:
        Movement(Vector vector, Point start, Point destination);

        // accessors
        double distance() const { return distance_; }
        bool clockwise() const { return clockwise_; }
        double degrees() const { return degrees_; }
        Vector vector() const { return vector_; }
        Point start() const { return start_; }
        Point destination() const { return destination_; }
        Vector maximum_velocity() const { return maximum_velocity_; }

        // mutators
        void set_distance(double distance) { distance_ = distance; }
        void set_clockwise(bool clockwise) { clockwise_ = clockwise; }
        void set_degrees(double degrees) { degrees_ = degrees; }
        void set_vector(Vector vector) { vector_ = vector; }
        void set_start(Point start) { start_ = start; }
        void set_destination(Point destination) { destination_ = destination; }
        void set_maximum_velocity(Vector maximum_velocity) { maximum_velocity_ = maximum_velocity; }


        static double calculate_distance(Point point1, Point point2);

};

#endif
