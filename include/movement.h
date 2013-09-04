#ifndef TLB_MOVEMENT_H_
#define TLB_MOVEMENT_H_

#include "vector.h"
#include "coordinate.h"
#include "action.h"

class GameObject;

class Movement : public Action
{
    private:
        double distance_;
        bool clockwise_;
        double degrees_;
        Vector vector_;
        Coordinate destination_;
        Vector maximum_velocity_;

    public:
        Movement();
        Movement(Vector vector); 
        Movement(double magnitude, double direction);
        Movement(Vector vector, Coordinate destination);

        // accessors
        double distance() const { return distance_; }
        bool clockwise() const { return clockwise_; }
        double degrees() const { return degrees_; }
        Vector vector() const { return vector_; }
        Coordinate destination() const { return destination_; }
        Vector maximum_velocity() const { return maximum_velocity_; }

        // mutators
        void set_distance(double distance) { distance_ = distance; }
        void set_clockwise(bool clockwise) { clockwise_ = clockwise; }
        void set_degrees(double degrees) { degrees_ = degrees; }
        void set_vector(Vector vector) { vector_ = vector; }
        void set_destination(Coordinate destination) { destination_ = destination; }
        void set_maximum_velocity(Vector maximum_velocity) { maximum_velocity_ = maximum_velocity; }

        bool is_movement() const { return true; }

        static double calculate_distance(Coordinate point1, Coordinate point2);

};

#endif
