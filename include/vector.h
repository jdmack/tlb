#ifndef TLB_VECTOR_H_
#define TLB_VECTOR_H_

const double kPi = 3.141592653589793;

class Vector
{
    private:
        double direction_;
        double magnitude_;
        double x_component_;
        double y_component_;

    public:
        Vector();
        Vector(double x1, double y1, double x2, double y2);
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

};

#endif
