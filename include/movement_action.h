#ifndef TLB_MOVEMENT_ACTION_H_
#define TLB_MOVEMENT_ACTION_H_

#include <vector>
#include "action.h"

class GameObject;

class MovementAction : public Action
{
    private:
		std::vector<Movement *> path_;
		std::vector<Movement *>::iterator current_;

    public:
        MovementAction();
        MovementAction(std::vector<Movement *> path);

        // accessors
		std::vector<Movement *> path() const { return path_; }

};

#endif
