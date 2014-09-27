//
//  PlayerLayer.cpp
//  MyCppGame
//
//  Created by Apple on 14-9-26.
//
//

#include <stdio.h>
#include "PlayerLayer.h"

USING_NS_CC;
using namespace std;

PlayerLayer *PlayerLayer::create(cocos2d::PhysicsWorld *A_World)
{
    PlayerLayer *layer = new PlayerLayer(A_World);
    if(layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void PlayerLayer::drawBack(Node *tar)
{
    m_DrawBack = true;
    m_CurItem->getPhysicsBody()->setLinearDamping(5);
}
void PlayerLayer::Launch(Node *tar)
{
    m_DrawBack = false;
    m_CurItem->getPhysicsBody()->setLinearDamping(0);
    Vec2 l_curPos = m_CurItem->getPosition();
    m_Joint->setMax(l_curPos.distance(m_TouchPos));
}

bool PlayerLayer::init()
{
    m_DrawBack = false;
    auto vsbSize = Director::getInstance()->getVisibleSize();
    
    MySprite2DFactory spf;
    
    m_boat = Sprite::create();
    auto l_boatBody = PhysicsBody::create();
    l_boatBody->setCollisionBitmask(0);
    l_boatBody->setDynamic(false);
    m_boat->setPhysicsBody(l_boatBody);
    m_boat->setPosition(vsbSize.width / 2, vsbSize.height - 20);
    m_boat->setVisible(false);
    addChild(m_boat);


    m_CurItem = spf.Create(_ST_Hammer);
    m_CurItem->setPosition(m_boat->getPosition());
    m_CurItem->setColor(Color3B::BLACK);
    m_CurItem->getPhysicsBody()->setLinearDamping(0.5);
    addChild(m_CurItem);
    
    m_Joint = PhysicsJointLimit::construct(m_boat->getPhysicsBody(), m_CurItem->getPhysicsBody(), Vec2::ZERO, Vec2::ZERO, 0, 1000);
    m_World->addJoint(m_Joint);
    
    auto eventTouchListenner = EventListenerTouchOneByOne::create();//create();
    eventTouchListenner->onTouchBegan = CC_CALLBACK_2(PlayerLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventTouchListenner, this);
    
    
    scheduleUpdate();
    return true;
}

void PlayerLayer::update(float dt)
{
    if(m_DrawBack)
    {
        float l_max = m_Joint->getMax();
        if(l_max > 0)
        {
            float l_delta = dt * 100;
            if(l_max > l_delta)
                m_Joint->setMax(l_max - l_delta);
            else
            {
                m_Joint->setMax(0);
                m_DrawBack = false;
            }
        }
    }
}

bool PlayerLayer::onTouchBegan(Touch *touch, Event *event)
{
    m_TouchPos = touch->getLocation();
    auto l_pushFunc = CallFuncN::create(CC_CALLBACK_1(PlayerLayer::Launch, this));
    auto l_act = MoveTo::create(2, m_TouchPos);
    //auto l_act = EaseExponentialOut::create(l_act1);
    auto l_drawBackFunc = CallFuncN::create(CC_CALLBACK_1(PlayerLayer::drawBack, this));
    
    m_CurItem->runAction(Sequence::create(l_pushFunc, l_act, l_drawBackFunc, NULL));

    return false;
}