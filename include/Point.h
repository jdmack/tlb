#ifndef TLB_POINT_H_
#define TLB_POINT_H_

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
        void setX(double x) { x_= x; }
        void setY(double y) { y_= y; }

        bool operator==(const Point &other) const;
        bool operator!=(const Point &other) const;

        double distanceFrom(Point point);

        std::string toString();
};

#endif
