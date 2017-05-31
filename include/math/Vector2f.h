#ifndef TLB_UTIL_MATH_VECTOR2F_H_
#define TLB_UTIL_MATH_VECTOR2F_H_

#include <string>

class Vector2f
{
    private:
        float m_[2];

    public:
        Vector2f();
        Vector2f(float x, float y);

        // accessors
        float x() const { return m_[0]; }
        float y() const { return m_[1]; }

        // mutators
        void setX(float x) { m_[0]= x; }
        void setY(float y) { m_[1]= y; }

        // copy assignment operator
        Vector2f & operator=(Vector2f v);

        bool operator==(const Vector2f &other) const;
        bool operator!=(const Vector2f &other) const;

        float distanceFrom(Vector2f point);

        const float * pointer();

        std::string toString();
        friend std::ostream & operator<<(std::ostream & os, const Vector2f & v);

};

#endif
