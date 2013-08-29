#include <cmath>
#include "vector.h"
#include "util/logger.h"

Vector::Vector()
{
    x_component_ = 0;
    y_component_ = 0;

    direction_ = 0;
    magnitude_ = 0;

    Logger::write(Logger::string_stream << "creating vector (0)");
}

Vector::Vector(double x1, double y1, double x2, double y2)
{
    x_component_ = std::abs(x2 - x1);
    y_component_ = std::abs(y2 - y1);

    int quadrant = determine_quadrant(x1, y1, x2, y2);

    magnitude_ = sqrt(pow(x_component_, 2) + pow(y_component_, 2));
    double theta = acos(x_component_ / magnitude_);
    direction_ = determine_direction(quadrant, theta);

    set_component_signs(direction_);

    Logger::write(Logger::string_stream << "creating vector:");
    Logger::write(Logger::string_stream << "\t\tmagnitude: " << magnitude_);
    Logger::write(Logger::string_stream << "\t\tdirection: " << direction_ << "(" << radians_to_degrees(direction_) << ")");
    Logger::write(Logger::string_stream << "\t\tx_component: " << x_component_);
    Logger::write(Logger::string_stream << "\t\ty_component: " << y_component_);
    Logger::write(Logger::string_stream << "\t\tquadrant: " << quadrant);
    Logger::write(Logger::string_stream << "\t\t(" << x1 << "," << y1 << ") & (" << x2 << "," << y2 << ")");
}

Vector::Vector(double magnitude, double direction)
{

    x_component_ = magnitude * cos(direction);
    y_component_ = magnitude * sin(direction);
    set_component_signs(direction);

    magnitude_ = magnitude;
    direction_ = direction;

    Logger::write(Logger::string_stream << "creating vector:");
    Logger::write(Logger::string_stream << "\t\tmagnitude: " << magnitude_);
    Logger::write(Logger::string_stream << "\t\tdirection: " << direction_ << "(" << radians_to_degrees(direction_) << ")");
    Logger::write(Logger::string_stream << "\t\tx_component: " << x_component_);
    Logger::write(Logger::string_stream << "\t\ty_component: " << y_component_);
}

double Vector::radians_to_degrees(double radians)
{
    return radians / kPi * 180;
}

double Vector::degrees_to_radians(double degrees)
{
    return degrees * kPi / 180;
}

int Vector::determine_quadrant(double x1, double y1, double x2, double y2)
{
    if(x2 > x1) {
        if(y2 > y1) {
            return kQuadrantIV;
        }
        else if(y2 < y1) {
            return kQuadrantI;
        }
    }
    else if(x2 < x1) {
        if(y2 > y1) {
            return kQuadrantIII;
        }
        else if(y2 < y1) {
            return kQuadrantII;
        }
    }
    return 0;
}

void Vector::set_component_signs(double direction)
{
    // Quadrant IV
    if(direction > k270Degrees) {
        Logger::write(Logger::string_stream << "set_component_signs - quadrant: IV");
        make_positive(x_component_);
        make_positive(y_component_);
    }
    // Quadrant III
    else if(direction > k180Degrees) {
        Logger::write(Logger::string_stream << "set_component_signs - quadrant: III");
        make_negative(x_component_);
        make_positive(y_component_);
    }
    // Quadrant II
    else if(direction > k90Degrees) {
        Logger::write(Logger::string_stream << "set_component_signs - quadrant: II");
        make_negative(x_component_);
        make_negative(y_component_);
    }
    // Quadrant I
    else  {
        Logger::write(Logger::string_stream << "set_component_signs - quadrant: I");
        make_positive(x_component_);
        make_negative(y_component_);
    }
}

double Vector::determine_direction(int quadrant, double theta)
{
    Logger::write(Logger::string_stream << "determine_direction - quadrant: " << quadrant << " theta: " << theta << "(" << radians_to_degrees(theta) << ")");
    switch(quadrant) {
        case kQuadrantI:
            return theta;
            break;
        case kQuadrantII:
            return kPi - theta;
            break;
        case kQuadrantIII:
            return kPi + theta;
            break;
        case kQuadrantIV:
            return (2 * kPi) - theta;
            break;
        default:
            return 0;
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
