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

void PlayerLayer::Launch(cocos2d::Vec2 A_TarPos)
{
    if(m_JointSpring)
    {
        if(m_JointSpring->getRestLength() != 0)
            return;
        //float l_dis = A_TarPos.distance(m_CurItem->getPosition());
        m_Chain->getPhysicsBody()->applyForce(A_TarPos - m_Chain->getPosition());
    }
    
}

bool PlayerLayer::init()
{
    auto vsbSize = Director::getInstance()->getVisibleSize();
    
    MySprite2DFactory spf;
    //m_Chain = spf.Create(_ST_Chain);
    //m_Chain->setPosition(vsbSize.width / 2, vsbSize.height - m_Chain->getContentSize().height * 2);
    //addChild(m_Chain);
    
    m_Orig = Node::create();
    auto l_origBody = PhysicsBody::createCircle(10);
    l_origBody->setContactTestBitmask(0);
    m_Orig->setPhysicsBody(l_origBody);
    m_Orig->setPosition(vsbSize.width / 2, vsbSize.height - 20);

    if(m_CurItem == nullptr)
    {
        //m_CurItem = m_DefaultItem;
        m_CurItem = spf.Create(_ST_Hammer);
        m_CurItem->setPosition(m_Orig->getPosition());
        m_CurItem->setColor(Color3B::BLACK);
        addChild(m_CurItem);
    }
    
    //m_JointSpring = PhysicsJointSpring::construct(m_Orig->getPhysicsBody(), m_CurItem->getPhysicsBody(), Vec2::ZERO, Vec2::ZERO, 500.f, 0.3f);
    //m_World->addJoint(m_JointSpring);
    
    //m_JointPin = PhysicsJointPin::construct(m_Chain->getPhysicsBody(), m_CurItem->getPhysicsBody(), Vec2::ZERO);
    //m_World->addJoint(m_JointPin);

    
    auto eventTouchListenner = EventListenerTouchOneByOne::create();//create();
    eventTouchListenner->onTouchBegan = CC_CALLBACK_2(PlayerLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventTouchListenner, this);
    
    return true;
}

bool PlayerLayer::onTouchBegan(Touch *touch, Event *event)
{
    Launch(touch->getLocation());
    return false;
}