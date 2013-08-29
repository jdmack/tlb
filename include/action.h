#ifndef TLB_ACTION_H_
#define TLB_ACTION_H_

class Action
{
    private:
        bool movement_;

    public:
        Action();
        bool movement() const { return movement_; }
};

#endif
