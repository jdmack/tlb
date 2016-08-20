#ifndef TLB_UTIL_MATH_VECTOR2F_H_
#define TLB_UTIL_MATH_VECTOR2F_H_

#include <string>

class Vector2f
{
    private:
        float x_;
        float y_;
    public:
        Vector2f();
        Vector2f(float x, float y);

        // accessors
        float x() const { return x_; }
        float y() const { return y_; }

        // mutators
        void setX(float x) { x_= x; }
        void setY(float y) { y_= y; }

        bool operator==(const Vector2f &other) const;
        bool operator!=(const Vector2f &other) const;

        float distanceFrom(Vector2f point);

        std::string toString();
        friend std::ostream & operator<<(std::ostream & os, const Vector2f & v);

};

#endif
