#include <cmath>
#include "vector.h"
#include "point.h"
#include "util/logger.h"

Vector::Vector()
{
    xComponent_ = 0;
    yComponent_ = 0;

    direction_ = 0;
    magnitude_ = 0;

    //Logger::write(Logger::ss << "creating vector (0)");
}
Vector::Vector(Point start, Point end)
{
    if(start == end) {
        xComponent_ = 0;
        yComponent_ = 0;

        direction_ = 0;
        magnitude_ = 0;

        return;
    }
    //xComponent_ = std::abs(end.x() - start.x());
    //yComponent_ = std::abs(end.y() - start.y());
    xComponent_ = end.x() - start.x();
    yComponent_ = end.y() - start.y();

    magnitude_ = sqrt(pow(xComponent_, 2) + pow(yComponent_, 2));

    if(xComponent_ == 0) {
        if(yComponent_ > 0) {
            direction_ = 90;
        }
        else {
            direction_ = 270;
        }

    }
    else if(yComponent_ == 0) {
        if(xComponent_ > 0) {
            direction_ = 0;
        }
        else {
            direction_ = 180;
        }
    }
    else {

        int quadrant = determineQuadrant(start, end);
        //double theta = std::round(radiansToDegrees(acos(xComponent_ / magnitude_)));
        double theta = radiansToDegrees(acos(xComponent_ / magnitude_));
        //Logger::write(Logger::ss << "Theta: " << theta);
        //direction_ = theta;
        direction_ = determineDirection(quadrant, theta);
    }

    setComponentSigns(direction_);

    //Logger::write(Logger::ss << "creating vector: " <<
    //    "magnitude: " << magnitude_ <<
    //    ", direction: " << direction_ <<
    //    ", xComponent: " << xComponent_ <<
    //    ", yComponent: " << yComponent_ <<
    //    ", start(" << start.x() << "," << start.y() << "),  end(" << end.x() << "," << end.y() << ")");
}

Vector::Vector(double magnitude, double direction)
{

    xComponent_ = magnitude * cos(degreesToRadians(direction));
    yComponent_ = magnitude * sin(degreesToRadians(direction));

    if(std::abs(xComponent_) == magnitude) {
        yComponent_ = 0;
    }
    if(std::abs(yComponent_) == magnitude) {
        xComponent_ = 0;
    }

    setComponentSigns(direction);

    magnitude_ = magnitude;
    direction_ = direction;

    //Logger::write(Logger::ss << "creating vector: " <<
    //"magnitude: " << magnitude_ <<
    //", direction: " << direction_ <<
    //", xComponent: " << xComponent_ <<
    //", yComponent: " << yComponent_);
}

double Vector::radiansToDegrees(double radians)
{
    return radians / kPi * 180;
}

double Vector::degreesToRadians(double degrees)
{
    return degrees * kPi / 180;
}

int Vector::determineQuadrant(Point start, Point end)
{
    if(end.x() > start.x()) {
        if(end.y() > start.y()) {
            // (+,+)
            //Logger::write("determineQuadrant: I");
            return kQuadrantI;
        }
        else if(end.y() < start.y()) {
            // (+,-)
            //Logger::write("determineQuadrant: IV");
            return kQuadrantIV;
        }
    }
    else if(end.x() < start.x()) {
        if(end.y() > start.y()) {
            // (+,+)
            //Logger::write("determineQuadrant: II");
            return kQuadrantII;
        }
        else if(end.y() < start.y()) {
            // (+,+)
            //Logger::write("determineQuadrant: III");
            return kQuadrantIII;
        }
    }
    return 0;
}

void Vector::setComponentSigns(double direction)
{
    // Quadrant IV (+,-)
    if(direction > 270.0) {
        //Logger::write(Logger::ss << "setComponentSigns - quadrant: IV");
        //makePositive(xComponent_);
        //makePositive(yComponent_);
        makePositive(xComponent_);
        makeNegative(yComponent_);
    }
    // Quadrant III (-,-)
    else if(direction > 180.0) {
        //Logger::write(Logger::ss << "setComponentSigns - quadrant: III");
        //makeNegative(xComponent_);
        //makePositive(yComponent_);
        makeNegative(xComponent_);
        makeNegative(yComponent_);
    }
    // Quadrant II (-,+)
    else if(direction > 90.0) {
        //Logger::write(Logger::ss << "setComponentSigns - quadrant: II");
        //makeNegative(xComponent_);
        //makeNegative(yComponent_);
        makeNegative(xComponent_);
        makePositive(yComponent_);
    }
    // Quadrant I (+,+)
    else  {
        //Logger::write(Logger::ss << "setComponentSigns - quadrant: I");
        //makePositive(xComponent_);
        //makeNegative(yComponent_);
        makePositive(xComponent_);
        makePositive(yComponent_);
    }
}

double Vector::determineDirection(int quadrant, double theta)
{
    //Logger::write(Logger::ss << "determineDirection - quadrant: " << quadrant << " theta: " << theta);
    switch(quadrant) {
        case kQuadrantI:
            return theta;
            break;
        case kQuadrantII:
            //return 180.0 - theta;
            return theta;
            break;
        case kQuadrantIII:
            //return 90.0 + theta;
            return 360.0 - theta;
            break;
        case kQuadrantIV:
            return 360.0 - theta;
            break;
        default:
            return theta;
    }
}

void Vector::makePositive(double & number)
{
    number = std::abs(number);
}

void Vector::makeNegative(double & number)
{
    number = std::abs(number) * -1;
}
