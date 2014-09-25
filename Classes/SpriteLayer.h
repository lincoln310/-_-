//
//  SpriteLayer.h
//  MyCppGame
//
//  Created by Apple on 14-9-21.
//
//

#ifndef SPRITELAYER_H
#define SPRITELAYER_H

#include "cocos2d.h"
#include "MySprite2D.h"
#include <vector>

NS_CC_BEGIN

class SpriteLayer : public Layer
{
public:
    CREATE_FUNC(SpriteLayer);
    
    bool init();
    
    void addSprite(MySprite *sp);
    void removeSprite(MySprite *sp);
    
    void update(float dt);
    
    bool isNeedNewSprite();
    
protected:
    
    bool onContactBegin(const PhysicsContact& contact);
    bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
    
    void onCustomEvent(EventCustom *event);
    std::set<MySprite*>   m_Sprites;
    
    int         m_SpriteCntLimit;
};

NS_CC_END

#endif //SPRITELAYER_H