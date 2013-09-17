#ifndef TLB_MOVEMENT_ACTION_H_
#define TLB_MOVEMENT_ACTION_H_

#include <vector>
#include "action.h"
#include "point.h"

class GameObject;
class Level;
class Movement;

class MovementAction : public Action
{
    private:
		Point start_;
		Point end_;
		Level * level_;

		std::vector<Movement *> * path_;
		std::vector<Movement *>::iterator current_;

    public:
        MovementAction(Point start, Point end, Level * level);

        // accessors
		std::vector<Movement *> * path() const { return path_; }

		void find_path();
};

#endif
