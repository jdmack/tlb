#ifndef TLB_UTIL_MATH_VECTOR4_H_
#define TLB_UTIL_MATH_VECTOR4_H_

class Matrix4f;

class Vector4f
{
    private:
        float x_;
        float y_;
        float z_;
        float w_;

    public:
        // constructors
        Vector4f();
        // A constructor with three parameters for point coordinates
        Vector4f(float x, float y, float z);
        // A constructor with four parameters
        Vector4f(float x, float y, float z, float w);

        // accessors
        // Element access 'get': return one of the four coordinates
        float x() const { return x_; }
        float y() const { return y_; }
        float z() const { return z_; }
        float w() const { return w_; }
        float get(int coordinate) const;
        float get(char coordinate) const;

        // mutators
        // Element access 'set': set each coordinate separately
        void setX(float x) { x_ = x; }
        void setY(float y) { y_ = y; }
        void setZ(float z) { z_ = z; }
        void setW(float w) { w_ = w; }
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
        
        // Print (display the point's components numerically on the screen)
        void print();
};

#endif
