//
//  MainMenu.cpp
//  MyCppGame
//
//  Created by Apple on 14-9-26.
//
//

#include <stdio.h>
#include "MainMenu.h"
#include "MainPlayLayer.h"

USING_NS_CC;

Menu *MainMenu::create()
{
    auto menu = new MainMenu();
    if(menu && menu->init())
    {
        menu->autorelease();
        return menu;
    }
    CC_SAFE_DELETE(menu);
    return nullptr;
}

bool MainMenu::init()
{
    Menu::init();
    setAnchorPoint(Vec2(.5, .5));
    
    auto level1 = new Level1();
    auto layerItem = LevelMenuItem::create(level1);
    addChild(layerItem);
    
    return true;
}