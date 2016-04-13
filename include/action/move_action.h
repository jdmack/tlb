#ifndef TLB_MOVE_ACTION_H_
#define TLB_MOVE_ACTION_H_

#include <vector>
#include <string>
#include "action.h"
#include "point.h"
#include "vector.h"

class Entity;
class GameObject;
class Level;
class Movement;

class MoveAction : public Action
{
    private:
		Point start_;
		Point end_;
		Level * level_;
		Vector currentMaxVelocity_;
		bool started_;

		std::vector<Movement *> * path_;
		std::vector<Movement *>::iterator current_;

    public:
        MoveAction(Point start, Point end, Level * level);

        // accessors
		Point start() const { return start_; }
		Point end() const { return end_; }
		std::vector<Movement *> * path() const { return path_; }
		Movement * current() const { return *current_; }
		Level * level() const { return level_; }

		void findPath();
		bool nextMovement();
        std::string toString();
        bool emptyPath();

        // overridden
        bool update(Entity * entity, int deltaTicks);
        void stop();

		Vector currentMaxVelocity() const { return currentMaxVelocity_; }
		void setCurrentMaxVelocity(Vector vector) { currentMaxVelocity_ = vector; }
		void removeMovementsBack(int number = 1);

};

#endif
