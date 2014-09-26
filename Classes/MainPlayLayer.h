//
//  MainPlayLayer.h
//  MyCppGame
//
//  Created by Apple on 14-9-26.
//
//

#ifndef MAINPLAYLAYER_H
#define MAINPLAYLAYER_H

#include "cocos2d.h"
#include "PlayerLayer.h"
#include "MySprite2D.h"
#include "MyEdgeLayer.h"
#include "SpriteLayer.h"

NS_CC_BEGIN

class MainPlayLayer : public Layer
{
public:
    static Scene *scene();
    
    static MainPlayLayer *create();
    
    static void runThis();
    
    virtual bool init();
    
    void update(float dt);
    
    cocos2d::PhysicsWorld *getPhyWorld() {return m_World;}
    
protected:
    
    Scene *getScene() {return m_Scene;}
    PhysicsWorld *m_World;
    
    Scene           *m_Scene;
    
    SpriteLayer             *m_SpriteLayer;
    MyEdgeLayer             *m_Edgelayer;
    PlayerLayer             *m_PlayerLayer;
};

NS_CC_END

#endif //MAINPLAYLAYER_H