//
//  MySprite2D.h
//  Tutorial1
//
//  Created by Apple on 14-8-15.
//
//

#ifndef MYSPRITE2D_H
#define MYSPRITE2D_H

#include "cocos2d.h"

#include <iostream>

NS_CC_BEGIN

enum ActionType
{
    _AT_Start = 0,
    _AT_Swim,
    _AT_Hurt,
    _AT_End = 10000
};

enum MySpriteType
{
    _ST_Start   = 0,
    _ST_Scissor = 0x01,
    _ST_Hammer   = 0x02,
    _ST_Burden  = 0x04,
    
    _ST_Chain   = 0x08,
    _ST_End     = 0xff
};


class MySprite : public cocos2d::Sprite
{
public:
    MySprite();
    virtual bool initWithFile(std::string file);
    static MySprite *create(MySprite *fish);
    
    void update(float dt);
    
    int getType() {return m_SpriteType;}
    
    virtual PhysicsBody *initPhyBody();
    virtual LabelAtlas *initLabel();
    
    int getEnegyCount() {return m_EnegyCount;}
    void addEnegyCount(int cnt) {m_EnegyCount += cnt;}
    
    
    virtual int getEnemy() {return 0;}
    virtual int getFood() {return 0;}
    
    virtual void setBodyContactMask();
protected:
    void updateEnegy();
    std::string         m_ModelFile;
    int                 m_SpriteType;
    cocos2d::Color3B    m_Color;
    cocos2d::Map<int, cocos2d::Action*>      m_Actions;
    
    //enegy related;
    int                 m_EnegyCount;
    cocos2d::LabelAtlas *m_Count;
    cocos2d::Color3B    m_EnegyColor;
};

//对象工厂
class MySprite2DFactory
{
public:
    MySprite *Create(int type);
    
};

class Scissor : public MySprite
{
    Scissor();
public:
    int getEnemy() {return _ST_Hammer ;}
    int getFood() {return _ST_Burden;}
    
    friend class MySprite2DFactory;
};

class Hammer  : public MySprite
{
    Hammer ();
public:
    int getEnemy() {return _ST_Burden;}
    int getFood() {return _ST_Scissor;}
    
    friend class MySprite2DFactory;
};

class Burden : public MySprite
{
    Burden();
public:
    int getEnemy() {return _ST_Scissor;}
    int getFood() {return _ST_Hammer ;}
    
    friend class MySprite2DFactory;
};

class Chain : public MySprite
{
    Chain();
public:
    virtual PhysicsBody *initPhyBody();
    virtual LabelAtlas *initLabel() {return nullptr;}
    
    void setBodyContactMask();
    
    friend class MySprite2DFactory;
};

NS_CC_END

#endif //MYSPRITE2D_H
