#include "movement.h"

Movement::Movement()
{
}

Movement::Movement(Vector vector)
{
    vector_ = vector;
}

Movement::Movement(double magnitude, double direction)
{
    vector_ = Vector(magnitude, direction);
}
