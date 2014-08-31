#ifndef TLB_ROTATE_ACTION_H_
#define TLB_ROTATE_ACTION_H_

#include <vector>
#include <string>
#include "action.h"
#include "point.h"
#include "vector.h"

class Entity;
class GameObject;

class RotateAction : public Action
{
    private:
        double direction_;

    public:
        RotateAction(double direction);
        RotateAction(Entity * entity, Point mouse_point);

        // accessors
		double direction() const { return direction_; }

        // overridden
        bool update(Entity * entity, int delta_ticks);
        void stop();

        static bool facing(Entity * entity, Entity * target);

        std::string to_string();
};

#endif
