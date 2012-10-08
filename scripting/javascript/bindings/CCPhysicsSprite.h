#ifndef __CCPHYSICSSPRITE_H__
#define __CCPHYSICSSPRITE_H__

#include "sprite_nodes/CCSprite.h"
#include "chipmunk.h"

// A Cocos2D 2.0 sprite subclass that is bound to a Chipmunk body.
// It works with either regular Chipmunk or Objective-Chipmunk.
using namespace cocos2d;

class CCPhysicsSprite : public CCSprite
{
public:
    CCPhysicsSprite() {
        this->autorelease();
    }
	cpBody	*_body;
	bool	_ignoreBodyRotation;
    virtual void setPosition(const cocos2d::CCPoint &p);
    const cocos2d::CCPoint& getPosition();
    void setBody(cpBody* body) {_body = body;}
    void setIgnoreBodyRotation(bool rot) {_ignoreBodyRotation = rot;}
    inline virtual bool isDirty(void) { return true; }
    virtual cocos2d::CCAffineTransform nodeToParentTransform();
    
    float getRotation();
    virtual void setRotation(float rotation);
};

#endif /* __CCPHYSICSSPRITE_H__ */
