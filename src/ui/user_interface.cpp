#include <vector>
#include "ui/user_interface.h"
#include "ui/ui_element.h"
#include "ui/panel.h"
#include "assets.h"
#include "ui/game_timer.h"
#include "ui/text.h"
#include "ui/text_panel.h"
#include "ui/character_panel.h"
#include "util/global_timer.h"

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

    paused_panel_ = new TextPanel();
    paused_panel_->load_texture(kAssetUIPausedPanel);
    paused_panel_->set_position(Point(9, 101));
    panel->add_element(paused_panel_);
    Text * text = new Text("PAUSED");
    text->set_position(Point(22, 118));
    text->set_size(50);
    text->reload_font();
    text->update();
    paused_panel_->set_text(text);

    character_panel_[0] = new CharacterPanel();
    character_panel_[0]->set_position(Point(9, 195));

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
    character_panel_[0]->render(frame);
}

void UserInterface::update()
{
    for(std::vector<UIElement *>::iterator element_iterator = elements_.begin(); element_iterator != elements_.end(); ++element_iterator) {
        (*element_iterator)->update();
    }
    if(paused_panel_ != nullptr) {
        paused_panel_->text()->set_visible(GlobalTimer::instance()->paused());
    }
}

bool UserInterface::click(Point point)
{
    for(std::vector<UIElement *>::iterator element_iterator = elements_.begin(); element_iterator != elements_.end(); ++element_iterator) {
        bool click_return = (*element_iterator)->click(point);
        if(click_return) return click_return;
    }
    return character_panel_[0]->click(point);
}

bool UserInterface::contains_point(Point point)
{
    for(std::vector<UIElement *>::iterator element_iterator = elements_.begin(); element_iterator != elements_.end(); ++element_iterator) {
        bool value = (*element_iterator)->contains_point(point);
        if(value) return value;
    }
    return character_panel_[0]->contains_point(point);
}
