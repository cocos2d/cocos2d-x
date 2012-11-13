/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __PHYSICSNODES_CCPHYSICSSPRITE_H__
#define __PHYSICSNODES_CCPHYSICSSPRITE_H__

#include "ccConfig.h"
#include "sprite_nodes/CCSprite.h"

NS_CC_BEGIN

#if CC_ENABLE_CHIPMUNK_INTEGRATION
#include chipmunk.h

#elif CC_ENABLE_BOX2D_INTEGRATION
class b2Body;
#endif // CC_ENABLE_BOX2D_INTEGRATION

/** A CCSprite subclass that is bound to a physics body.
 It works with:
 - Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Objective-Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Box2d: Preprocessor macro CC_ENABLE_BOX2D_INTEGRATION should be defined
 
 Features and Limitations:
 - Scale and Skew properties are ignored.
 - Position and rotation are going to updated from the physics body
 - If you update the rotation or position manually, the physics body will be updated
 - You can't eble both Chipmunk support and Box2d support at the same time. Only one can be enabled at compile time
 */
class CC_DLL CCPhysicsSprite : public CCSprite
{
protected:
    bool    m_bIgnoreBodyRotation;
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    cpBody  *m_pBody;
    
#elif CC_ENABLE_BOX2D_INTEGRATION
    b2Body  *m_pBody;
    
    // Pixels to Meters ratio
    float   m_fPTMRation;
#endif // CC_ENABLE_CHIPMUNK_INTEGRATION
    
public:
    static CCPhysicsSprite* create();
    
    virtual bool isDirty();
    
    /** Keep the sprite's rotation separate from the body. */
    bool isIgnoreBodyRotation() const;
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);
    
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    
    virtual const CCPoint& getPosition();
    virtual void setPosition(const CCPoint &position);
    virtual float getRotation();
    virtual void setRotation(float fRotation);
    virtual CCAffineTransform nodeToParentTransform();
    
    /** Body accessor when using regular Chipmunk */
    cpBody* getBody() const;
    void setBody(cpBody *pBody);
    
    /** Body accessor when using Objective-Chipmunk */
    ChipmunkBody* getChipmunkBody() const;
    void setChipmunkBody(ChipmunkBody *pChipmunkBody);
    
#elif CC_ENABLE_BOX2D_INTEGRATION
    
    virtual CCPoint getPosition();
    virtual void setPosition(const CCPoint &position);
    virtual float getRotation();
    virtual void setRotation(float fRotation);
    virtual CCAffineTransform nodeToParentTransform();
    
    /** Body accessor when using box2d */
    b2Body* getBody() const;
    void setBody(b2Body *pBody);
    
    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);
    
#endif // CC_ENABLE_BOX2D_INTEGRATION
    
protected:
    CCPhysicsSprite();
};

NS_CC_END

#endif // __PHYSICSNODES_CCPHYSICSSPRITE_H__
