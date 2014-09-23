#include <vector>
#include "ui/user_interface.h"
#include "ui/ui_element.h"
#include "ui/panel.h"
#include "assets.h"
#include "ui/game_timer.h"

UserInterface::UserInterface()
{
    elements_ = std::vector<UIElement *>();

    // setup UI elements
    Panel * panel = new Panel();
    panel->load_texture(kAssetUIBackgroundPanel);
    panel->set_position(Point(0, 0));
    add_element(panel);

    GameTimer * timer = new GameTimer();
    timer->load_texture(kAssetUIGameTimerPanel);
    timer->set_position(Point(9, 9));
    panel->add_element(timer);

    /*
    UIElement * element = new UIElement();
    element->load_texture(kAssetUIGameTimerPanel);
    element->set_position(Point(9, 9));
    panel->add_element(element);
    */

    //element
}

UserInterface::~UserInterface()
{
    for(std::vector<UIElement *>::iterator element_iterator = elements_.begin(); element_iterator != elements_.end(); ++element_iterator) {
        delete *element_iterator;
    }
}

void UserInterface::add_element(UIElement * element)
{
    elements_.push_back(element);
}

void UserInterface::render(Frame * frame)
{
    for(std::vector<UIElement *>::iterator element_iterator = elements_.begin(); element_iterator != elements_.end(); ++element_iterator) {
        (*element_iterator)->render(frame);
    }
}

void UserInterface::update()
{
    for(std::vector<UIElement *>::iterator element_iterator = elements_.begin(); element_iterator != elements_.end(); ++element_iterator) {
        (*element_iterator)->update();
    }
}

