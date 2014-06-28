#pragma once

#include "cocos2d.h"
#include "TextSprite.h"
#include "Configuration.h"

USING_NS_CC;

class MenuItemImageLabel : public MenuItemImage
{
public:
   static MenuItemImageLabel* create(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback,
       const std::string& text = "", const std::string& font = GameConfig::defaultFontName, int fontSize = GameConfig::defaultFontSize);

   static MenuItemImageLabel* createWithFrameName(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback,
       const std::string& text = "", const std::string& font = GameConfig::defaultFontName, int fontSize = GameConfig::defaultFontSize);

   virtual void selected();
   virtual void unselected();

   bool initWithNormalFrameName(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback);

   void setTextColor(const Color3B& norColor,const Color3B& selColor = DIY_COLOR_BLUE2);

   void setText(const std::string& text, const std::string& fontName, int fontSize);
   void setText(const std::string& text);

private:
    MenuItemImageLabel();

    Color3B _norTextColor;
    Color3B _selTextColor;
    TextSprite * _label;
};
