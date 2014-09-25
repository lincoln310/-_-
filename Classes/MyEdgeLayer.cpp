//
//  MyEdgeArea.cpp
//  MyCppGame
//
//  Created by Apple on 14-9-25.
//
//

#include <stdio.h>
#include "MyEdgeLayer.h"
#include <random>

USING_NS_CC;
using namespace std;

bool MyEdgeLayer::init()
{
    m_outerRate = 1.15;
    m_innerRate = 1.1;
    
    //设置两个边界，在夹层间创建新的精灵，向内进入玩家领域
    initOuterEdge();
    initInnerEdge();
    
    //监听碰撞
    auto elpc = EventListenerPhysicsContact::create();
    elpc->onContactBegin = CC_CALLBACK_1(MyEdgeLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(elpc, this);
    
    return true;
}

bool MyEdgeLayer::onContactBegin(const PhysicsContact &contact)
{
    auto sp1 = contact.getShapeA()->getBody();
    auto sp2 = contact.getShapeB()->getBody();
    
    auto size = Director::getInstance()->getVisibleSize();
    auto rect = Rect(m_innerLeftDown.x, m_innerLeftDown.y, size.width * m_innerRate, size.height * m_innerRate);
    
    Node *l_remove = nullptr;

    //内边界允许从外部进入，不允许从内部离开
    if(sp1->getTag() == -1)
    {
        if(rect.containsPoint(sp2->getPosition()))
            l_remove = sp2->getNode();
    }
    else if(sp2->getTag() == -1)
    {
        if(rect.containsPoint(sp1->getPosition()))
            l_remove = sp1->getNode();
    }
    else //交给其他layer处理
        return true;
    
    if(l_remove != nullptr)
    {
        auto l_event = EventCustom("remove_sprite");
        l_event.setUserData(l_remove);
        _eventDispatcher->dispatchEvent(&l_event);
    }
    //已经处理，不再交给其他layer处理
    return false;
}

MySprite *MyEdgeLayer::getNewSprite(int A_Type)
{
    MySprite2DFactory spf;
    if(A_Type == 0)
    {
        default_random_engine generator(clock());
        static uniform_int_distribution<int> dis(0,2);
        A_Type = dis(generator);
        A_Type = 1 << A_Type;
    }
    
    auto sp = spf.Create(A_Type);
    if(sp)
    {
        Vec2 pos = GetRandPos();
        sp->setPosition(pos);
    
        Vec2 dir= GetRandPos();
    
        dir = dir / dir.length() * 20;
        sp->getPhysicsBody()->setVelocity(dir);
    }
    return sp;
}

Vec2 MyEdgeLayer::GetRandPos()
{
    default_random_engine generator(clock());
    static uniform_int_distribution<int> dis(0,3);
    static Vec2 vMin = (m_outerLeftDown + m_innerLeftDown) / 2;
    static Vec2 vMax = (m_OuterRightUp + m_innerRightUp) / 2;
    static uniform_real_distribution<float> xdis(vMin.x, vMax.x);
    static uniform_real_distribution<float> ydis(vMin.y, vMax.y);
    
    
    Vec2 ret(0, 0);
    int t = dis(generator);
    switch(t)
    {
        case 0:
            ret.x = vMin.x;
            ret.y = ydis(generator);
            break;
        case 1:
            ret.x = vMax.x;
            ret.y = ydis(generator);
            break;
        case 2:
            ret.y = vMin.y;
            ret.x = xdis(generator);
            break;
        case 3:
            ret.y = vMax.y;
            ret.x = xdis(generator);
            break;
        default:
            cout << "wrong random : " << t << endl;
            break;
    }
    return ret;
}

bool MyEdgeLayer::initOuterEdge()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origen = Director::getInstance()->getVisibleOrigin();
    
    m_outerLeftDown = visibleSize / 2 - visibleSize * m_outerRate / 2;
    m_OuterRightUp = visibleSize / 2 + visibleSize * m_outerRate / 2;
    
    //外边界
    auto Bound = PhysicsBody::createEdgeBox(visibleSize * m_outerRate);
    Bound->setTag(-2);
    //全碰撞反射
    Bound->getShape(0)->setRestitution(1);
    Bound->getShape(0)->setFriction(0);
    Bound->getShape(0)->setDensity(1);
    Bound->setCollisionBitmask(_ST_End);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(visibleSize/2);
    edgeNode->setPhysicsBody(Bound);
    addChild(edgeNode);
    
    return true;
}

bool MyEdgeLayer::initInnerEdge()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origen = Director::getInstance()->getVisibleOrigin();
    
    m_innerLeftDown = visibleSize / 2 - visibleSize * m_innerRate / 2;
    m_innerRightUp = visibleSize / 2 + visibleSize * m_innerRate / 2;
    
    //内边界
    //精灵可以从外部穿过内边界进入，但是从内部碰到内边界，就消失
    auto innerBound = PhysicsBody::createEdgeBox(visibleSize * m_innerRate);
    innerBound->setTag(-1);
    //全碰撞检测
    innerBound->setCollisionBitmask(_ST_End);
    innerBound->setContactTestBitmask(_ST_End);
    
    auto innerEdge = Node::create();
    innerEdge->setPosition(visibleSize/2);
    innerEdge->setPhysicsBody(innerBound);
    addChild(innerEdge);
    
    return true;
}