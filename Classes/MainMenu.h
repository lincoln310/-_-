//
//  LevelSelectLayer.h
//  MyCppGame
//
//  Created by Apple on 14-9-26.
//
//

#ifndef MAINMENU_H
#define MAINMENU_H

#include "cocos2d.h"
#include "MainPlayLayer.h"

NS_CC_BEGIN


class MainMenu : public Menu
{
public:
    static Menu *create();
    
    bool init();
};

class LevelMenuItem : public MenuItemFont
{
public:
    static MenuItemFont *create(LevelMenuItem *item)
    {
        if(item && item->init())
        {
            item->autorelease();
            return item;
        }
        CC_SAFE_DELETE(item);
        return nullptr;
    }
    
    bool init()
    {
        bool ret = false;
        ret = MenuItemFont::initWithString(m_LabelStr, CC_CALLBACK_0(LevelMenuItem::onClick, this));
        
        return ret;
    }
    
    virtual void onClick() {}
    
protected:
    std::string m_LabelStr;
};

class Level1 : public LevelMenuItem
{
public:
    Level1()
    {
        m_LabelStr = "LV1";
    }
    
    void onClick()
    {
        MainPlayLayer::runThis();
    }
};


NS_CC_END

#endif //MAINMENU_H