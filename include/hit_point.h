#ifndef TLB_HitPoint_H_
#define TLB_HitPoint_H_

#include <string>

class HitPoint
{
    private:
        int total_;
        int current_;

    public:
        HitPoint();
        HitPoint(int total);

        // accessors
        int total() const { return total_; }
        int current() const { return current_; }

        // mutators
        void set_total(int total) { total_= total; }
        void set_current(int current) { current_ = current; }

        void add_points(int points);
        void minus_points(int points);

        std::string to_string();
};

#endif
