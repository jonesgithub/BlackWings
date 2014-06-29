#include "MenuItemImageLabel.h"
#include "TextSprite.h"

USING_NS_CC;

MenuItemImageLabel* MenuItemImageLabel::create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const std::string& text /* = "" */, const std::string& font /* = GameConfig::defaultFontName */, int fontSize /* = GameConfig::defaultFontSize */)
{
    auto ret = new MenuItemImageLabel();

    if (ret && ret->initWithNormalImage(normalImage, selectedImage, "", callback))
    {
        ret->setText(text,font,fontSize);
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

MenuItemImageLabel* MenuItemImageLabel::createWithFrameName(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback, const std::string& text /* = "" */, const std::string& font /* = GameConfig::defaultFontName */, int fontSize /* = GameConfig::defaultFontSize */)
{
    auto ret = new MenuItemImageLabel();

    if (ret && ret->initWithNormalFrameName(normalImage, selectedImage, "", callback))
    {
        ret->setText(text,font,fontSize);
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

MenuItemImageLabel::MenuItemImageLabel()
: _selTextColor(DIY_COLOR_BLUE4)
, _norTextColor(Color3B::WHITE)
, _label(nullptr)
{
    
}

bool MenuItemImageLabel::initWithNormalFrameName(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback)
{
    Node *normalSprite = nullptr;
    Node *selectedSprite = nullptr;
    Node *disabledSprite = nullptr;

    if (normalImage.size() >0)
    {
        normalSprite = Sprite::createWithSpriteFrameName(normalImage);
    }

    if (selectedImage.size() >0)
    {
        selectedSprite = Sprite::createWithSpriteFrameName(selectedImage);
    }

    if(disabledImage.size() >0)
    {
        disabledSprite = Sprite::createWithSpriteFrameName(disabledImage);
    }

    return initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
}

void MenuItemImageLabel::setText(const std::string& text, const std::string& fontName, int fontSize)
{
    if (text.length() > 0)
    {
        _label = TextSprite::create(text.c_str(),fontName.c_str(),fontSize);
        if (_label)
        {
            _label->setPosition(Point(_contentSize.width/2 , _contentSize.height/2));
            this->addChild(_label);
        }
    }
}

void MenuItemImageLabel::setText(const std::string& text)
{
    if (_label)
    {
        _label->setText(text);
    }
    else
    {
        setText(text,GameConfig::defaultFontName,GameConfig::defaultFontSize);
    }
}

void MenuItemImageLabel::setTextColor(const Color3B& norColor,const Color3B& selColor)
{
    _norTextColor = norColor;
    _selTextColor = selColor;
    if (_label)
    {
        _label->setColor(_norTextColor);
    }
}

void MenuItemImageLabel::selected()
{
    MenuItemSprite::selected();
    _cascadeColorEnabled = false;
    if (_label)
    {
        _label->setColor(_selTextColor);
    }
    _cascadeColorEnabled = true;
}

void MenuItemImageLabel::unselected()
{
    MenuItemSprite::unselected();
    if (_label)
    {
        _label->setColor(_norTextColor);
    }
}
