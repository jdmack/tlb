#include "ui/TextPanel.h"
#include "Point.h"
#include "util/Logger.h"
#include "Frame.h"
#include "util/GlobalTimer.h"
#include "ui/Text.h"

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
