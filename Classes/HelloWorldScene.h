#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SpriteLayer.h"
#include "MyEdgeLayer.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float dt);
    
    
    void setPhyWorld(cocos2d::PhysicsWorld *A_world) {m_world = A_world;}
    cocos2d::PhysicsWorld *getPhyWorld() {return m_world;}
protected:
    cocos2d::PhysicsWorld    *m_world;
    
    cocos2d::SpriteLayer             *m_SpriteLayer;
    cocos2d::MyEdgeLayer             *m_Edgelayer;
};

#endif // __HELLOWORLD_SCENE_H__
