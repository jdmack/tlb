#include <cmath>
#include "vector.h"

Vector::Vector()
{
    x_component_ = 0;
    y_component_ = 0;

    direction_ = 0;
    magnitude_ = 0;
}

Vector::Vector(double x1, double y1, double x2, double y2)
{
    x_component_ = x2 - x1;
    y_component_ = y2 - y1;

    magnitude_ = sqrt(pow(x_component_,2) + pow(y_component_,2));
    direction_ = acos(x_component_ / direction_);
}

Vector::Vector(double magnitude, double direction)
{
    x_component_ = magnitude * cos(direction);
    y_component_ = magnitude * sin(direction);

    magnitude_ = magnitude;
    direction_ = direction;
}
