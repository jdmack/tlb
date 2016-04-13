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
        void setTotal(int total) { total_= total; }
        void setCurrent(int current) { current_ = current; }

        void addPoints(int points);
        void minusPoints(int points);

        bool empty();

        std::string toString();
};

#endif
