//
//  PlayerLayer.h
//  MyCppGame
//
//  Created by Apple on 14-9-26.
//
//

#ifndef PLAYERLAYER_H
#define PLAYERLAYER_H

#include "cocos2d.h"
#include "MySprite2D.h"
#include <set>

NS_CC_BEGIN

class PlayerLayer : public Layer
{
public:
    PlayerLayer(PhysicsWorld *A_World) : m_World(A_World) {}
    
    static PlayerLayer *create(PhysicsWorld *A_World);
    
    virtual bool init();
    
    void setPhyWorld(PhysicsWorld *A_World) { m_World = A_World;}
    //更换要使用的精灵
    void ChangeItem(MySprite *A_TarItem);

    void update(float dt);
    
protected:
    bool onTouchBegan(Touch *touch, Event *event);
    
    //收回精灵
    void drawBack(Node *tar);
    //发射精灵
    void Launch(Node *tar);
    
    MySprite *m_CurItem;
    std::set<MySprite*> m_AllItems;
    
    PhysicsJoint *m_JointPin;
    PhysicsJointLimit *m_Joint;
    bool        m_AddedJoints;
    PhysicsWorld *m_World;
    
    Sprite      *m_boat;
    Vec2        m_OrigPos;
    
    Vec2        m_TouchPos;
    bool        m_DrawBack;
};

NS_CC_END

#endif //PLAYERLAYER_H