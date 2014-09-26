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

    
    //发射精灵
    void Launch(Vec2 A_TarPos);
protected:
    bool onTouchBegan(Touch *touch, Event *event);
    
    MySprite *m_CurItem;
    std::set<MySprite*> m_AllItems;
    
    PhysicsJointPin *m_JointPin;
    PhysicsJointSpring  *m_JointSpring;
    bool        m_AddedJoints;
    PhysicsWorld *m_World;
    
    Node        *m_DefaultItem;
    Node        *m_Orig;
    MySprite    *m_Chain;
};

NS_CC_END

#endif //PLAYERLAYER_H