//
//  MySprite2D.cpp
//  Tutorial1
//
//  Created by Apple on 14-8-15.
//
//

#include <stdio.h>
#include "MySprite2D.h"
#include <random>


USING_NS_CC;
using namespace std;

MySprite::MySprite()
: m_Color(cocos2d::Color3B(255,255,255)), m_EnegyCount(1), m_Count(0)
{
    
}

MySprite *MySprite::create(MySprite *fish)
{
    if(fish && fish->initWithFile(fish->m_ModelFile))
    {
        fish->autorelease();
        return fish;
    }
    CC_SAFE_DELETE(fish);
    return nullptr;
}

bool MySprite::initWithFile(std::string file)
{
    Sprite::initWithFile(file);
    setColor(m_Color);
    
    default_random_engine generator(clock());
    static uniform_int_distribution<int> dis(1,100);
    m_EnegyCount = dis(generator);
    
    if(m_SpriteType <= _ST_Burden)
    {
        Texture2D *texture = Director::getInstance()->getTextureCache()->getTextureForKey("/cc_fps_images");
        
        m_Count = LabelAtlas::create();
        m_Count->initWithString("0000", texture, 12, 32 , '.');
        m_Count->setPosition(Vec2::ZERO);
        updateEnegy();
        addChild(m_Count);
        
        auto body = PhysicsBody::createCircle(getContentSize().width/4);
        body->getShape(0)->setRestitution(1.0f);
        //设置物体的摩擦力
        body->getShape(0)->setFriction(0.0f);
        //设置物体密度
        body->getShape(0)->setDensity(1.0f);
        setPhysicsBody(body);
        setBodyContactMask();
    }
    
    scheduleUpdate();
    return true;
}

void MySprite::update(float dt)
{
    updateEnegy();
}

void MySprite::updateEnegy()
{
    if(m_Count)
    {
        char str[3] = {0};
        sprintf(str, "%d", m_EnegyCount);
        
        m_Count->setString(str);
    }
}

void MySprite::setBodyContactMask()
{
    auto body = getPhysicsBody();
    body->setCategoryBitmask(m_SpriteType);
    body->setContactTestBitmask(_ST_End);
    body->setCollisionBitmask(_ST_End);
    
}

Scissor::Scissor()
{
    m_ModelFile = "scissor.png";
    m_SpriteType = _ST_Scissor;
    m_Color = Color3B(242,88,77);
}

Hummer::Hummer()
{
    m_ModelFile = "hammer.png";
    m_SpriteType = _ST_Hummer;
    m_Color = Color3B(250, 203, 118);
}

Burden::Burden()
{
    m_ModelFile = "burden.png";
    m_SpriteType = _ST_Burden;
    m_Color = Color3B(73,145,1);
}

MySprite *MySprite2DFactory::Create(int type)
{
    MySprite *ret = nullptr;
    switch (type) {
        case _ST_Scissor:
            ret = new Scissor();
            break;
        case _ST_Hummer:
            ret = new Hummer();
            break;
        case _ST_Burden:
            ret = new Burden();
            break;
        default:
            break;
    }
    if(ret)
        MySprite::create(ret);
    return ret;
}