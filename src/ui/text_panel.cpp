#include "ui/textPanel.h"
#include "point.h"
#include "util/logger.h"
#include "frame.h"
#include "util/globalTimer.h"
#include "ui/text.h"

TextPanel::TextPanel()
{
    position_ = Point(0, 0);
    width_ = 0;
    height_ = 0;

    texture_ = nullptr;
    visible_ = true;

    text_ = nullptr;

}

TextPanel::~TextPanel()
{

}


void TextPanel::render(Frame * frame)
{
    UIElement::render(frame);
    if(text_ != nullptr) {
        text_->render(frame);
    }
}

void TextPanel::update()
{
}
