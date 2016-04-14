#include <vector>
#include "ui/UserInterface.h"
#include "ui/UIElement.h"
#include "ui/Panel.h"
#include "Assets.h"
#include "ui/GameTimer.h"
#include "ui/Text.h"
#include "ui/TextPanel.h"
#include "ui/CharacterPanel.h"
#include "util/GlobalTimer.h"

UserInterface::UserInterface()
{
    elements_ = std::vector<UIElement *>();

    // setup UI elements
    Panel * panel = new Panel();
    panel->loadTexture(kAssetUIBackgroundPanel);
    panel->setPosition(Point(0, 0));
    addElement(panel);

    GameTimer * timer = new GameTimer();
    timer->loadTexture(kAssetUIGameTimerPanel);
    timer->setPosition(Point(9, 9));
    panel->addElement(timer);

    pausedPanel_ = new TextPanel();
    pausedPanel_->loadTexture(kAssetUIPausedPanel);
    pausedPanel_->setPosition(Point(9, 101));
    panel->addElement(pausedPanel_);
    Text * text = new Text("PAUSED");
    text->setPosition(Point(22, 118));
    text->setSize(50);
    text->reloadFont();
    text->update();
    pausedPanel_->setText(text);

    characterPanel_[0] = new CharacterPanel();
    characterPanel_[0]->setPosition(Point(9, 195));

    /*
    UIElement * element = new UIElement();
    element->loadTexture(kAssetUIGameTimerPanel);
    element->setPosition(Point(9, 9));
    panel->addElement(element);
    */

    //element
}

UserInterface::~UserInterface()
{
    for(std::vector<UIElement *>::iterator elementIterator = elements_.begin(); elementIterator != elements_.end(); ++elementIterator) {
        delete *elementIterator;
    }
}

void UserInterface::addElement(UIElement * element)
{
    elements_.push_back(element);
}

void UserInterface::render(Frame * frame)
{
    for(std::vector<UIElement *>::iterator elementIterator = elements_.begin(); elementIterator != elements_.end(); ++elementIterator) {
        (*elementIterator)->render(frame);
    }
    characterPanel_[0]->render(frame);
}

void UserInterface::update()
{
    for(std::vector<UIElement *>::iterator elementIterator = elements_.begin(); elementIterator != elements_.end(); ++elementIterator) {
        (*elementIterator)->update();
    }
    if(pausedPanel_ != nullptr) {
        pausedPanel_->text()->setVisible(GlobalTimer::instance()->paused());
    }
}

bool UserInterface::click(Point point)
{
    for(std::vector<UIElement *>::iterator elementIterator = elements_.begin(); elementIterator != elements_.end(); ++elementIterator) {
        bool clickReturn = (*elementIterator)->click(point);
        if(clickReturn) return clickReturn;
    }
    return characterPanel_[0]->click(point);
}

bool UserInterface::containsPoint(Point point)
{
    for(std::vector<UIElement *>::iterator elementIterator = elements_.begin(); elementIterator != elements_.end(); ++elementIterator) {
        bool value = (*elementIterator)->containsPoint(point);
        if(value) return value;
    }
    return characterPanel_[0]->containsPoint(point);
}
