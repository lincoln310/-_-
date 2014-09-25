//
//  MyEdge.h
//  MyCppGame
//
//  Created by Apple on 14-9-24.
//
//

#ifndef MYEDGELAYER_H
#define MYEDGELAYER_H

#include "cocos2d.h"
#include "MySprite2D.h"

NS_CC_BEGIN

class MyEdgeLayer : public Layer
{
public:
    CREATE_FUNC(MyEdgeLayer);
    
    bool init();
    
    MySprite *getNewSprite(int A_Type = 0);
    
protected:
    Vec2 GetRandPos();
    
    bool initOuterEdge();
    bool initInnerEdge();
    
    bool onContactBegin(const PhysicsContact &contact);
    
    std::vector<Vec2>   m_Origs;
    
    float   m_outerRate;
    float   m_innerRate;
    
    Vec2    m_outerLeftDown;
    Vec2    m_OuterRightUp;
    
    Vec2    m_innerLeftDown;
    Vec2    m_innerRightUp;
};


NS_CC_END


#endif //MYEDGELAYER_H