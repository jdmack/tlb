#ifndef TLB_ACTION_H_
#define TLB_ACTION_H_

class Action
{
    private:

    public:
        Action();
        virtual ~Action();
        virtual bool is_movement() const { return false; }
};

#endif
