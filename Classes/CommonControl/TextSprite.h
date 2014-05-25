#pragma once

#include "cocos2d.h"
#include "Configuration.h"

USING_NS_CC;

class TextSprite : public Sprite
{
public:
    static TextSprite* create(const std::string& text, const std::string& fontName = GameConfig::defaultFontName, int fontSize = GameConfig::defaultFontSize, 
        const Size& dimensions = Size::ZERO,TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    void setText(const std::string& text);
    void setText(const std::string& text, const std::string& fontName, int fontSize,
        const Size& dimensions,TextHAlignment hAlignment,TextVAlignment vAlignment);

private:
    std::string _fontName;
    int _fontSize;
    Size _dimensions;
    TextHAlignment _hAlignment;
    TextVAlignment _vAlignment;
};
