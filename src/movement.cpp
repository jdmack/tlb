#include "movement.h"

Movement::Movement()
{
    vector_ = nullptr;
}

Movement::Movement(Vector * vector)
{
    vector_ = vector;
}

Movement::Movement(double magnitude, double direction)
{
    vector_ = new Vector(magnitude, direction);
}
