//
//  SpriteLayer.cpp
//  MyCppGame
//
//  Created by Apple on 14-9-24.
//
//

#include <stdio.h>
#include "SpriteLayer.h"
#include "MySprite2D.h"
#include <iostream>

USING_NS_CC;
using namespace std;

bool test(SpriteLayer *layer)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    MySprite2DFactory spF;
    auto sp1 = spF.Create(_ST_Burden);
    sp1->setPosition(visibleSize.width / 2, visibleSize.height - sp1->getContentSize().height);
    //sp1->getPhysicsBody()->setVelocity(Vec2(visibleSize.width / visibleSize.height, 1) * 10);
    layer->addChild(sp1);
    
    auto sp2 = spF.Create(_ST_Hammer);
    sp2->setPosition(visibleSize * 3 / 5 + Size(0, -2));
    //sp2->getPhysicsBody()->setVelocity(Vec2(visibleSize.width / visibleSize.height, 1) * -10);
    layer->addChild(sp2);
    
    return true;
}

bool SpriteLayer::init()
{
    m_SpriteCntLimit = 40;
    
    auto visiblesize = Director::getInstance()->getVisibleSize();
    
    //玩家选择精灵事件
    auto selectItemListener = EventListenerCustom::create("remove_sprite", CC_CALLBACK_1(SpriteLayer::onCustomEvent, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(selectItemListener, this);
    
    auto contactEventListener = EventListenerPhysicsContact::create();
    contactEventListener->onContactBegin = CC_CALLBACK_1(SpriteLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactEventListener, this);
    
    auto sp = Sprite::create("Sea.jpg");
    sp->setAnchorPoint(Vec2(.5, .5));
    sp->setPosition(visiblesize/2);
    //sp->setScale(visiblesize.width / sp->getContentSize().width, visiblesize.height / sp->getContentSize().height);
    addChild(sp, -1);
    scheduleUpdate();
    
    return true;
}

void SpriteLayer::onCustomEvent(cocos2d::EventCustom *event)
{
    MySprite *sp = static_cast<MySprite*>(event->getUserData());
    removeSprite(sp);
}

void SpriteLayer::addSprite(cocos2d::MySprite *sp)
 {
     m_Sprites.insert(sp);
     addChild(sp);
 }

void SpriteLayer::removeSprite(MySprite *sp)
{
    m_Sprites.erase(sp);
    removeChild(sp);
}

bool SpriteLayer::isNeedNewSprite()
{
    ssize_t cnt = m_Sprites.size();
    return cnt < m_SpriteCntLimit;
}

void SpriteLayer::update(float dt)
{

}

bool SpriteLayer::onContactPreSolve(cocos2d::PhysicsContact &contact, cocos2d::PhysicsContactPreSolve &solve)
{
    solve.setRestitution(1);
    return true;
}

bool SpriteLayer::onContactBegin(const cocos2d::PhysicsContact &contact)
{
    try {
        MySprite *sp1 = static_cast<MySprite*>(contact.getShapeA()->getBody()->getNode());
        MySprite *sp2 = static_cast<MySprite*>(contact.getShapeB()->getBody()->getNode());
        
        if(!sp1 || !sp2)
            return true;
        MySprite *hunter = nullptr;
        MySprite *prey = nullptr;
        
        if(sp1->getType() == sp2->getType())
        {
            return false;
        }
        else if(sp1->getFood() == sp2->getType())
        {
            hunter = sp1;
            prey = sp2;
        }
        else if(sp1->getEnemy() == sp2->getType())
        {
            hunter = sp2;
            prey = sp1;
        }
        
        if(hunter && prey)
        {
            int hunterEnegyCnt = hunter->getEnegyCount();
            int preyEnegyCnt = prey->getEnegyCount();
            if(hunterEnegyCnt >= preyEnegyCnt)
            {
                hunter->addEnegyCount(preyEnegyCnt);
                removeSprite(prey);
            }
            else
            {
                hunter->addEnegyCount(hunterEnegyCnt);
                prey->addEnegyCount( -1 * hunterEnegyCnt);
            }
        }
        return true;
    } catch (...) {
        return true;
    }
}