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

Color3B g_red(236,68,67);
Color3B g_blue(64,135,194);
Color3B g_green(60,184,89);
Color3B g_yellow(253,209,70);


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
    
    m_Count = this->initLabel();
    if(m_Count)
    {
        updateEnegy();
        addChild(m_Count);
    }
    
    auto body = this->initPhyBody();
    if(body)
    {
        setPhysicsBody(body);
        setBodyContactMask();
    }
    
    scheduleUpdate();
    return true;
}

PhysicsBody *MySprite::initPhyBody()
{
    auto body = PhysicsBody::createCircle(getContentSize().width/2);
    body->getShape(0)->setRestitution(1.0f);
    //设置物体的摩擦力
    body->getShape(0)->setFriction(0.0f);
    //设置物体密度
    body->getShape(0)->setDensity(1.0f);
    
    return body;
}

LabelAtlas *MySprite::initLabel()
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->getTextureForKey("/cc_fps_images");
    
    m_Count = LabelAtlas::create();
    m_Count->initWithString("0000", texture, 12, 32 , '.');
    m_Count->setPosition(Vec2::ZERO);
    m_Count->setColor(m_EnegyColor);
    
    return m_Count;
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
    if(body)
    {
        body->setCategoryBitmask(m_SpriteType);
        body->setContactTestBitmask(_ST_End);
        body->setCollisionBitmask(_ST_End);
    }
}

Scissor::Scissor()
{
    m_ModelFile = "scissor.png";
    m_SpriteType = _ST_Scissor;
    m_Color = g_red;
    m_EnegyColor = g_yellow;
}

Hammer::Hammer()
{
    m_ModelFile = "hammer.png";
    m_SpriteType = _ST_Hammer;
    m_Color = g_green;
    m_EnegyColor = g_red;
}

Burden::Burden()
{
    m_ModelFile = "burden.png";
    m_SpriteType = _ST_Burden;
    m_Color = g_yellow;
    m_EnegyColor = g_green;
}

Chain::Chain()
{
    m_ModelFile = "chain.png";
    m_SpriteType = _ST_Chain;
    m_Color = g_blue;
}

PhysicsBody *Chain::initPhyBody()
{
    auto size = getContentSize();
    auto body = PhysicsBody::createBox(size);
    body->getShape(0)->setRestitution(1.0f);
    //设置物体的摩擦力
    body->getShape(0)->setFriction(0.0f);
    //设置物体密度
    body->getShape(0)->setDensity(1.0f);
    
    return body;
}

void Chain::setBodyContactMask()
{
    auto body = getPhysicsBody();
    if(body)
    {
        body->setCategoryBitmask(m_SpriteType);
        body->setContactTestBitmask(_ST_End);
        body->setCollisionBitmask(_ST_End);
    }
}

MySprite *MySprite2DFactory::Create(int type)
{
    MySprite *ret = nullptr;
    switch (type) {
        case _ST_Scissor:
            ret = new Scissor();
            break;
        case _ST_Hammer:
            ret = new Hammer();
            break;
        case _ST_Burden:
            ret = new Burden();
            break;
        case _ST_Chain:
            ret = new Chain();
            break;
        default:
            break;
    }
    if(ret)
        MySprite::create(ret);
    return ret;
}