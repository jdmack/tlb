#include <vector>
#include "ui/user_interface.h"
#include "ui/ui_element.h"
#include "ui/panel.h"

UserInterface::UserInterface()
{
    elements_ = std::vector<UIElement *>();

    // setup UI elements
    Panel * panel = new Panel();

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

