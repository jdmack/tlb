#ifndef TLB_UTIL_MATH_VECTOR4_H_
#define TLB_UTIL_MATH_VECTOR4_H_
#include <iostream>

class Matrix4f;

class Vector4f
{
    private:
        float m_[4];

    public:
        // constructors
        Vector4f();
        // A constructor with three parameters for point coordinates
        Vector4f(float x, float y, float z);
        // A constructor with four parameters
        Vector4f(float x, float y, float z, float w);

        // accessors
        // Element access 'get': return one of the four coordinates
        float x() const { return m_[0]; }
        float y() const { return m_[1]; }
        float z() const { return m_[2]; }
        float w() const { return m_[3]; }
        float get(int coordinate) const;
        float get(char coordinate) const;

        // mutators
        // Element access 'set': set each coordinate separately
        void setX(float x) { m_[0] = x; }
        void setY(float y) { m_[1] = y; }
        void setZ(float z) { m_[2] = z; }
        void setW(float w) { m_[3] = w; }
        void setCoordinates(float x, float y, float z, float w);
        void set(int coordinate, float value);

        // Overload operator '[]' as alternative to 'get' method
        float operator[](int coordinate) const;
        float operator[](char coordinate) const;

        // Vector addition
        void add(Vector4f param);

        // Overload operator '+' for addition
        Vector4f operator+(Vector4f param);

        // Vector subtraction
        void subtract(Vector4f param);

        // Overload operator '-' for subtraction
        Vector4f operator-(Vector4f param);

        float dotProduct(Vector4f param);
        float operator*(Vector4f & param);

        Vector4f multiply(Matrix4f param);
        Vector4f operator*(Matrix4f & param);

        // Dehomogenize (make fourth component equal to 1)
        void dehomogenize();
        const float * pointer();
        
        friend std::ostream & operator<<(std::ostream & os, const Vector4f & v);

};

#endif
