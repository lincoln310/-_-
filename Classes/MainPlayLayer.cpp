//
//  MainPlayLayer.cpp
//  MyCppGame
//
//  Created by Apple on 14-9-26.
//
//

#include <stdio.h>
#include "MainPlayLayer.h"

USING_NS_CC;
using namespace std;

void MainPlayLayer::runThis()
{
    auto scene = MainPlayLayer::scene();
    
    auto director = Director::getInstance();
    
    auto running = director->getRunningScene();
    if(running)
    {
        director->pushScene(running);
        director->replaceScene(scene);
    }
    else
        director->runWithScene(scene);
}

Scene *MainPlayLayer::scene()
{
    // 'layer' is an autorelease object
    auto layer = MainPlayLayer::create();
    if(layer)
        return layer->getScene();
    
    return nullptr;
}

MainPlayLayer *MainPlayLayer::create()
{
    auto ret = new MainPlayLayer();
    if(ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MainPlayLayer::init()
{
    m_Scene = Scene::createWithPhysics();
    
    m_World = m_Scene->getPhysicsWorld();
    //m_World->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    m_World->setGravity(Vec2(0, 0));
    
    m_Scene->addChild(this);
    
    m_Edgelayer = MyEdgeLayer::create();
    addChild(m_Edgelayer);
    
    m_SpriteLayer = SpriteLayer::create();
    addChild(m_SpriteLayer);
    
    m_PlayerLayer = PlayerLayer::create(m_World);
    addChild(m_PlayerLayer);
    
    scheduleUpdate();
    
    return true;
}

void MainPlayLayer::update(float dt)
{
    if(m_SpriteLayer->isNeedNewSprite())
    {
        auto sp = m_Edgelayer->getNewSprite();
        if(sp)
            m_SpriteLayer->addSprite(sp);
    }
}