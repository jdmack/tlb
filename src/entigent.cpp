/* Entity Agent */

#include "entigent.h"
#include "screen.h"
#include "tlb_game.h"
#include "game_object.h"

Entigent::Entigent()
{
    game_ = nullptr;
}


void Entigent::add_object(GameObject * object)
{
    objects_.push_back(object);
    game_->screen()->init_object(object);

    // TODO(2013-08-24/JM): Add function to remove object from the vector
    // or add an "active" field to distinguish elements that haven't been deleted yet
}

void Entigent::register_game(TlbGame * game)
{
    game_ = game;
}

GameObject * Entigent::get_object_at(float x, float y)
{
    for(std::vector<GameObject *>::iterator object_iterator = objects_.begin(); object_iterator != objects_.end(); ++object_iterator) {
        if((**object_iterator).contains_point(x, y)) {
            return *object_iterator;
        }
    }

    return nullptr;
}

void Entigent::deselect_all()
{
    for(std::vector<GameObject *>::iterator selected_iterator = selected_.begin(); selected_iterator != selected_.end(); ++selected_iterator) {
        (**selected_iterator).deselect();

    }
}
