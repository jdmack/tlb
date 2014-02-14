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
        double x_component_;
        double y_component_;

    public:
        Vector();
        Vector(Point start, Point end);
        Vector(double magnitude, double direction);

        // accessors
        double x_component() const { return x_component_; }
        double y_component() const { return y_component_; }
        double direction() const { return direction_; }
        double magnitude() const { return magnitude_; }

        double direction_r() { return direction_; }
        double direction_d() { return radians_to_degrees(direction_); }
        double radians_to_degrees(double radians);
        double degrees_to_radians(double degrees);

        int determine_quadrant(Point start, Point end);
        void set_component_signs(double direction);
        double determine_direction(int quadrant, double theta);
        void make_positive(double & number);
        void make_negative(double & number);


};

#endif
