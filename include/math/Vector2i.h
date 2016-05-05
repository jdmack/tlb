#ifndef TLB_UTIL_MATH_VECTOR2I_H_
#define TLB_UTIL_MATH_VECTOR2I_H_

#include <string>

class Vector2i
{
    private:
        int x_;
        int y_;
    public:
        Vector2i();
        Vector2i(int x, int y);

        // accessors
        int x() const { return x_; }
        int y() const { return y_; }

        // mutators
        void setX(int x) { x_= x; }
        void setY(int y) { y_= y; }

        bool operator==(const Vector2i &other) const;
        bool operator!=(const Vector2i &other) const;

        int distanceFrom(Vector2i point);

        std::string toString();
};

#endif
