#ifndef TLB_VECTOR_H_
#define TLB_VECTOR_H_

const double kPi = 3.141592653589793;
const double k90Degrees  = kPi / 2;
const double k180Degrees = kPi;
const double k270Degrees = 3 * k90Degrees;
const double k360Degrees = 2 * kPi;

const int kQuadrantI   = 1;
const int kQuadrantII  = 2;
const int kQuadrantIII = 3;
const int kQuadrantIV  = 4;

class Point;

class Vector
{
    private:
        double direction_;
        double magnitude_;
        double xComponent_;
        double yComponent_;

    public:
        Vector();
        Vector(Point start, Point end);
        Vector(double magnitude, double direction);

        // accessors
        double xComponent() const { return xComponent_; }
        double yComponent() const { return yComponent_; }
        double direction() const { return direction_; }
        double magnitude() const { return magnitude_; }

        double directionR() { return direction_; }
        double directionD() { return radiansToDegrees(direction_); }
        double radiansToDegrees(double radians);
        double degreesToRadians(double degrees);

        int determineQuadrant(Point start, Point end);
        void setComponentSigns(double direction);
        double determineDirection(int quadrant, double theta);
        void makePositive(double & number);
        void makeNegative(double & number);


};

#endif
