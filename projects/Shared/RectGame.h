//
//  RectDirector.h
//  ProjectBetween
//
//  Created by Andres Ortiz on 4/29/16.
//
//

#ifndef RectDirector_h
#define RectDirector_h

#include "cocos2d.h"

/**
 @brief    The Shared Rect Director.
 
 The reason for implement as private inheritance is to hide some interface call by Director.
 */
class  RectGame : public cocos2d::Layer
{
    cocos2d::Layer ParentClass;
    
public:
    RectGame();
    ~RectGame();
    
    virtual void update(float update) override;
};


#endif /* RectDirector_h */
