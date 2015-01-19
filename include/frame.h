#ifndef TLB_FRAME_H_
#define TLB_FRAME_H_

#include <string>

class Frame
{
    private:
        int x_;
        int y_;
        int width_;
        int height_;
        Frame * parent_;

    public:
        Frame(Frame * parent = nullptr);
        Frame(int x, int y, int width, int height, Frame * parent = nullptr);
        ~Frame();

        // accessors
        int x() const;
        int y() const;
        int width() const { return width_; }
        int height() const { return height_; }
        Frame * parent() const { return parent_; }

        // mutators
        void set_x(int x) { x_ = x; }
        void set_y(int y) { y_ = y; }
        void set_width(int width) { width_ = width; }
        void set_height(int height) { height_ = height; }
        void set_parent(Frame * parent) { parent_ = parent; }

        bool contains_point(double x, double y);
        std::string to_string();

};

#endif
