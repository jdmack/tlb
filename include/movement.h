#ifndef TLB_MOVEMENT_H_
#define TLB_MOVEMENT_H_

#include "vector.h"
#include "coordinate.h"

class Movement
{
    private:
        Vector vector_;
        Coordinate destination_;

    public:
        Movement(Vector vector); 
        Movement(); 

        // accessors
        Vector vector() const { return vector_; }
        Coordinate destination() const { return destination_; }

        // mutators
        Vector set_vector(Vector vector) { vector_ = vector; }
        Coordinate set_destination(Coordinate destination) { destination_ = destination; }

};

#define

