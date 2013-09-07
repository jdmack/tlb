#ifndef TLB_COORDINATE_H_
#define TLB_COORDINATE_H_

class Coordinate
{
    private:
        double x_position_;
        double y_position_;
    public:
        Coordinate();
        Coordinate(double x, double y);

        // accessors
        double x_position() const { return x_position_; }
        double y_position() const { return y_position_; }

        // mutators
        void set_x_position(double x) { x_position_ = x; }
        void set_y_position(double y) { y_position_ = y; }
};

#endif
