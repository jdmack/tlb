/* Entity Agent */

#include "entigent.h"
#include "screen.h"
#include "tlb_game.h"
#include "game_object.h"
#include "util/logger.h"

Entigent::Entigent()
{
    game_ = nullptr;
    objects_ = new std::vector<GameObject *>();
    selected_ = new std::vector<GameObject *>();
}

void Entigent::add_object(GameObject * object)
{
    objects_->push_back(object);
    game_->screen()->init_object(object);

    // TODO(2013-08-24/JM): Add function to remove object from the vector
    // or add an "active" field to distinguish elements that haven't been deleted yet
}

GameObject * Entigent::get_object_at(double x, double y)
{
    for(std::vector<GameObject *>::iterator object_iterator = objects_->begin(); object_iterator != objects_->end(); ++object_iterator) {
        if((*object_iterator)->contains_point(x, y)) {
            return *object_iterator;
        }
    }

    return nullptr;
}

void Entigent::select(GameObject * object)
{
    object->select();
    selected_->push_back(object);
}

void Entigent::deselect(GameObject * object)
{
    object->deselect();
    for(std::vector<GameObject *>::iterator selected_iterator = selected_->begin(); selected_iterator != selected_->end(); ++selected_iterator) {
        if((*selected_iterator)->object_id() == object->object_id()) {
            (*selected_iterator)->deselect();
            selected_->erase(selected_iterator);
            break;
        }
    }
}

void Entigent::deselect_all()
{
    if(!selected_->empty()) {
        for(std::vector<GameObject *>::iterator selected_iterator = selected_->begin(); selected_iterator < selected_->end(); ++selected_iterator) {
            (*selected_iterator)->deselect();
            selected_->erase(selected_iterator);
        }
    }
}
