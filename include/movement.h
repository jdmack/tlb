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
        Vector vector_;
        Coordinate destination_;

    public:
        Movement();
        Movement(Vector vector); 
        Movement(double magnitude, double direction);
        Movement(Vector vector, Coordinate destination);

        // accessors
        double distance() const { return distance_; }
        Vector vector() const { return vector_; }
        Coordinate destination() const { return destination_; }

        // mutators
        void set_distance(double distance) { distance_ = distance; }
        void set_vector(Vector vector) { vector_ = vector; }
        void set_destination(Coordinate destination) { destination_ = destination; }

        bool is_movement() const { return true; }

        static double calculate_distance(Coordinate point1, Coordinate point2);

};

#endif
