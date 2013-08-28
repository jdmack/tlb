#include <cmath>
#include "vector.h"
#include "util/logger.h"

Vector::Vector()
{
    Logger::write(Logger::string_stream << "creating vector (0)");
    x_component_ = 0;
    y_component_ = 0;

    direction_ = 0;
    magnitude_ = 0;
}

Vector::Vector(double x1, double y1, double x2, double y2)
{
    Logger::write(Logger::string_stream << "creating vector (1) - (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")");

    x_component_ = x1 - x2;
    y_component_ = y1 - y2;

    magnitude_ = sqrt(pow(x_component_,2) + pow(y_component_,2));
    direction_ = acos(x_component_ / magnitude_);

    Logger::write(Logger::string_stream << "vector(magnitude: " << magnitude_ << ", direction: " << direction_ << ")");
    Logger::write(Logger::string_stream << "      (x_component: " << x_component_ << ", y_component: " << y_component_ << ")");
    Logger::write(Logger::string_stream << "      (" << x1 << "," << y1 << ") & (" << x2 << "," << y2 << ")");
}

Vector::Vector(double magnitude, double direction)
{

    x_component_ = magnitude * cos(direction);
    y_component_ = magnitude * sin(direction);

    magnitude_ = magnitude;
    direction_ = direction;

    Logger::write(Logger::string_stream << "vector(magnitude: " << magnitude_ << ", direction: " << direction_ << ")");
    Logger::write(Logger::string_stream << "      (x_component: " << x_component_ << ", y_component: " << y_component_ << ")");
}

double Vector::radians_to_degrees(double radians)
{

}

double Vector::degrees_to_radians(double degrees)
{

}
