#include <cmath>
#include "vector.h"
#include "point.h"
#include "utils/logger.h"

Vector::Vector()
{
    x_component_ = 0;
    y_component_ = 0;

    direction_ = 0;
    magnitude_ = 0;

    //Logger::write(Logger::string_stream << "creating vector (0)");
}
Vector::Vector(Point start, Point end)
{
    if(start == end) {
        x_component_ = 0;
        y_component_ = 0;

        direction_ = 0;
        magnitude_ = 0;

        return;
    }
    //x_component_ = std::abs(end.x() - start.x());
    //y_component_ = std::abs(end.y() - start.y());
    x_component_ = end.x() - start.x();
    y_component_ = end.y() - start.y();

    magnitude_ = sqrt(pow(x_component_, 2) + pow(y_component_, 2));

    if(x_component_ == 0) {
        if(y_component_ > 0) {
            direction_ = 90;
        }
        else {
            direction_ = 270;
        }

    }
    else if(y_component_ == 0) {
        if(x_component_ > 0) {
            direction_ = 0;
        }
        else {
            direction_ = 180;
        }
    }
    else {

        int quadrant = determine_quadrant(start, end);
        double theta = radians_to_degrees(acos(x_component_ / magnitude_));
        direction_ = determine_direction(quadrant, theta);
    }

    set_component_signs(direction_);

    Logger::write(Logger::string_stream << "creating vector: " <<
        "magnitude: " << magnitude_ <<
        ", direction: " << direction_ <<
        ", x_component: " << x_component_ <<
        ", y_component: " << y_component_ <<
        ", (" << start.x() << "," << start.y() << ") & (" << end.x() << "," << end.y() << ")");
}

Vector::Vector(double magnitude, double direction)
{

    x_component_ = magnitude * cos(degrees_to_radians(direction));
    y_component_ = magnitude * sin(degrees_to_radians(direction));

    if(std::abs(x_component_) == magnitude) {
        y_component_ = 0;
    }
    if(std::abs(y_component_) == magnitude) {
        x_component_ = 0;
    }

    set_component_signs(direction);

    magnitude_ = magnitude;
    direction_ = direction;

    Logger::write(Logger::string_stream << "creating vector: " <<
    "magnitude: " << magnitude_ <<
    ", direction: " << direction_ <<
    ", x_component: " << x_component_ <<
    ", y_component: " << y_component_);
}

double Vector::radians_to_degrees(double radians)
{
    return radians / kPi * 180;
}

double Vector::degrees_to_radians(double degrees)
{
    return degrees * kPi / 180;
}

int Vector::determine_quadrant(Point start, Point end)
{
    if(end.x() > start.x()) {
        if(end.y() > start.y()) {
            return kQuadrantIV;
        }
        else if(end.y() < start.y()) {
            return kQuadrantI;
        }
    }
    else if(end.x() < start.x()) {
        if(end.y() > start.y()) {
            return kQuadrantIII;
        }
        else if(end.y() < start.y()) {
            return kQuadrantII;
        }
    }
    return 0;
}

void Vector::set_component_signs(double direction)
{
    // Quadrant IV (+,-)
    if(direction > 270.0) {
        Logger::write(Logger::string_stream << "set_component_signs - quadrant: IV");
        //make_positive(x_component_);
        //make_positive(y_component_);
        make_positive(x_component_);
        make_negative(y_component_);
    }
    // Quadrant III (-,-)
    else if(direction > 180.0) {
        Logger::write(Logger::string_stream << "set_component_signs - quadrant: III");
        //make_negative(x_component_);
        //make_positive(y_component_);
        make_negative(x_component_);
        make_negative(y_component_);
    }
    // Quadrant II (-,+)
    else if(direction > 90.0) {
        Logger::write(Logger::string_stream << "set_component_signs - quadrant: II");
        //make_negative(x_component_);
        //make_negative(y_component_);
        make_negative(x_component_);
        make_positive(y_component_);
    }
    // Quadrant I (+,+)
    else  {
        Logger::write(Logger::string_stream << "set_component_signs - quadrant: I");
        //make_positive(x_component_);
        //make_negative(y_component_);
        make_positive(x_component_);
        make_positive(y_component_);
    }
}

double Vector::determine_direction(int quadrant, double theta)
{
    Logger::write(Logger::string_stream << "determine_direction - quadrant: " << quadrant << " theta: " << theta);
    switch(quadrant) {
        case kQuadrantI:
            return theta;
            break;
        case kQuadrantII:
            return 180.0 - theta;
            break;
        case kQuadrantIII:
            return 180.0 + theta;
            break;
        case kQuadrantIV:
            return 360.0 - theta;
            break;
        default:
            return theta;
    }
}

void Vector::make_positive(double & number)
{
    number = std::abs(number);
}

void Vector::make_negative(double & number)
{
    number = std::abs(number) * -1;
}
