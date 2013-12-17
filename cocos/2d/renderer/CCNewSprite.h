//
//  CCNewSprite.h
//  cocos2d_libs
//
//  Created by NiTe Luo on 10/31/13.
//
//

#ifndef __CCNEWSPRITE_H_
#define __CCNEWSPRITE_H_

#include "CCSprite.h"
#include "CCPlatformMacros.h"

NS_CC_BEGIN

class NewSprite : public Sprite
{
    
public:
    static NewSprite* create();
    static NewSprite* create(const char *filename);

    NewSprite(void);
    ~NewSprite();

    virtual bool initWithTexture(Texture2D *texture, const Rect& rect, bool rotated);
    
    virtual void updateQuadVertices();
    virtual void draw(void) override;
    
    bool culling() const;
    
protected:
};

NS_CC_END

#endif /* defined(__CCNEWSPRITE_H_) */
