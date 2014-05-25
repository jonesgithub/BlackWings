#include "TextSprite.h"

TextSprite* TextSprite::create(const std::string& text, const std::string& fontName /* = "Arial" */, int fontSize /* = 30 */, const Size& dimensions /* = Size::ZERO */,TextHAlignment hAlignment /* = TextHAlignment::LEFT */,TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    auto ret = new TextSprite;

    if (ret)
    {
        ret->setText(text,fontName,fontSize,dimensions,hAlignment,vAlignment);

        ret->autorelease();        
    }

    return ret;
}

void TextSprite::setText(const std::string& text)
{
    auto texture = new Texture2D;
    texture->initWithString(text.c_str(),_fontName.c_str(),_fontSize,_dimensions,_hAlignment,_vAlignment);

    setTexture(texture);
    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    setTextureRect(rect, false, rect.size);
    _dirty = true;
    _recursiveDirty = true;
    texture->release();
}

void TextSprite::setText(const std::string& text, const std::string& fontName, int fontSize, const Size& dimensions,TextHAlignment hAlignment,TextVAlignment vAlignment)
{
    auto texture = new Texture2D;
    texture->initWithString(text.c_str(),fontName.c_str(),fontSize,dimensions,hAlignment,vAlignment);
    this->initWithTexture(texture);
    texture->release();

    _fontName = fontName;
    _fontSize = fontSize;
    _dimensions.width = dimensions.width;
    _dimensions.height = dimensions.height;
    _hAlignment = hAlignment;
    _vAlignment = vAlignment;
}