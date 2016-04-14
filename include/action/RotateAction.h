#ifndef TLB_ROTATE_ACTION_H_
#define TLB_ROTATE_ACTION_H_

#include <vector>
#include <string>
#include "Action.h"
#include "Point.h"
#include "Vector.h"

class Entity;
class GameObject;

class RotateAction : public Action
{
    private:
        double direction_;

    public:
        RotateAction(double direction);
        RotateAction(Entity * entity, Point mousePoint);

        // accessors
		double direction() const { return direction_; }

        // overridden
        bool update(Entity * entity, int deltaTicks);
        void stop();

        static bool facing(Entity * entity, Entity * target, double arc);

        std::string toString();
};

#endif
