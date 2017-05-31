#ifndef TLB_UTIL_MATH_VECTOR3_H_
#define TLB_UTIL_MATH_VECTOR3_H_

#include <string>
#include <iostream>
#include "math/Vector4f.h"
#include "math/Matrix4f.h"


class Vector3f
{
    private:
        float m_[3];

    public:
        // constructors
        Vector3f();
        // A constructor with three parameters for the vector coordinates
        Vector3f(float x, float y, float z);

        // accessors
        // Element access 'get': return a specific coordinate of the vector
        float x() const { return m_[0]; }
        float y() const { return m_[1]; }
        float z() const { return m_[2]; }
        float get(int coordinate) const;
        float get(char coordinate) const;

        // mutators
        // Element access 'set': set the vector coordinates
        void setX(float x) { m_[0] = x; }
        void setY(float y) { m_[1] = y; }
        void setZ(float z) { m_[2] = z; }
        void set(float x, float y, float z);
        void set(int i, float val);

        // Overload operator '[]' as alternative to 'get' method
        float operator[](int coordinate) const;
        float operator[](char coordinate) const;

        // Copy assignment operator
        Vector3f & operator=(Vector3f v);

        // Vector addition
        void add(Vector3f param);

        // Overload operator '+' for addition
        Vector3f operator+(Vector3f param);

        // Vector subtraction
        void subtract(Vector3f param);

        // Overload operator '-' for subtraction
        Vector3f operator-(Vector3f param);

        // Negation
        void negate();

        // Scale (multiplication with scalar value)
        void scale(float param);
        Vector3f operator*(float param);
        Vector3f operator/(float param);

        // Dot product
        float dotProduct(Vector3f param);

        // Cross product
        Vector3f crossProduct(const Vector3f & param) const;
        Vector3f operator*(Vector3f param);

        // Magnitude (length of vector)
        float magnitude();

        // Normalize
        void normalize();

        void transform(Matrix4f param);

        void rotate(float angle, const Vector3f axis);
        
        float distanceFrom(Vector3f point);

        const float * pointer();

        std::string str();
        friend std::ostream & operator<<(std::ostream & os, const Vector3f & v);

        float angle(Vector3f v);

};

#endif
