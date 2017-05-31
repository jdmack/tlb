#ifndef TLB_UTIL_MATH_VECTOR2I_H_
#define TLB_UTIL_MATH_VECTOR2I_H_

#include <string>

class Vector2i
{
    private:
        int m_[2];

    public:
        Vector2i();
        Vector2i(int x, int y);

        // accessors
        int x() const { return m_[0]; }
        int y() const { return m_[1]; }

        // mutators
        void setX(int x) { m_[0]= x; }
        void setY(int y) { m_[1]= y; }

        bool operator==(const Vector2i &other) const;
        bool operator!=(const Vector2i &other) const;

        int distanceFrom(Vector2i point);

        std::string toString();
        friend std::ostream & operator<<(std::ostream & os, const Vector2i & v);

};

#endif
