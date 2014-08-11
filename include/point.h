#ifndef TLB_Point_H_
#define TLB_Point_H_

#include <string>

class Point
{
    private:
        double x_;
        double y_;
    public:
        Point();
        Point(double x, double y);

        // accessors
        double x() const { return x_; }
        double y() const { return y_; }

        // mutators
        void set_x(double x) { x_= x; }
        void set_y(double y) { y_= y; }

        bool operator==(const Point &other) const;
        bool operator!=(const Point &other) const;

        double distance_from(Point point);

        std::string to_string();
};

#endif
