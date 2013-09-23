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

#include "cocos2d.h"
#include "ExtensionMacros.h"

#if CC_ENABLE_CHIPMUNK_INTEGRATION
#include "chipmunk.h"
#elif CC_ENABLE_BOX2D_INTEGRATION
class b2Body;
#else // CC_ENABLE_BOX2D_INTEGRATION
#error "You must define either CC_ENABLE_CHIPMUNK_INTEGRATION or CC_ENABLE_BOX2D_INTEGRATION to use CCPhysicsSprite.h"
#endif

NS_CC_EXT_BEGIN
/** A CCSprite subclass that is bound to a physics body.
 It works with:
 - Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Objective-Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Box2d: Preprocessor macro CC_ENABLE_BOX2D_INTEGRATION should be defined

 Features and Limitations:
 - Scale and Skew properties are ignored.
 - Position and rotation are going to updated from the physics body
 - If you update the rotation or position manually, the physics body will be updated
 - You can't enble both Chipmunk support and Box2d support at the same time. Only one can be enabled at compile time
 * @js NA
 * @lua NA
 */
class CCPhysicsSprite : public CCSprite
{
protected:
    bool    m_bIgnoreBodyRotation;
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    cpBody  *m_pCPBody;

#elif CC_ENABLE_BOX2D_INTEGRATION
    b2Body  *m_pB2Body;

    // Pixels to Meters ratio
    float   m_fPTMRatio;
#endif // CC_ENABLE_CHIPMUNK_INTEGRATION
public:
    CCPhysicsSprite();

    static CCPhysicsSprite* create();
    /** Creates an sprite with a texture.
     The rect used will be the size of the texture.
     The offset will be (0,0).
     */
    static CCPhysicsSprite* createWithTexture(CCTexture2D *pTexture);

    /** Creates an sprite with a texture and a rect.
     The offset will be (0,0).
     */
    static CCPhysicsSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);

    /** Creates an sprite with an sprite frame. */
    static CCPhysicsSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

    /** Creates an sprite with an sprite frame name.
     An CCSpriteFrame will be fetched from the CCSpriteFrameCache by name.
     If the CCSpriteFrame doesn't exist it will raise an exception.
     @since v0.9
     */
    static CCPhysicsSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

    /** Creates an sprite with an image filename.
     The rect used will be the size of the image.
     The offset will be (0,0).
     */
    static CCPhysicsSprite* create(const char *pszFileName);

    /** Creates an sprite with an image filename and a rect.
     The offset will be (0,0).
     */
    static CCPhysicsSprite* create(const char *pszFileName, const CCRect& rect);

    virtual bool isDirty();

    /** Keep the sprite's rotation separate from the body. */
    bool isIgnoreBodyRotation() const;
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

    virtual const CCPoint& getPosition();
    virtual void getPosition(float* x, float* y);
    virtual float getPositionX();
    virtual float getPositionY();
    virtual void setPosition(const CCPoint &position);
    virtual float getRotation();
    virtual void setRotation(float fRotation);
    virtual CCAffineTransform nodeToParentTransform();

#if CC_ENABLE_CHIPMUNK_INTEGRATION
    /** Body accessor when using regular Chipmunk */
    cpBody* getCPBody() const;
    void setCPBody(cpBody *pBody);
#elif CC_ENABLE_BOX2D_INTEGRATION
    /** Body accessor when using box2d */
    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);

    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);
#endif // CC_ENABLE_BOX2D_INTEGRATION

protected:
    void updatePosFromPhysics();
};

NS_CC_EXT_END

#endif // __PHYSICSNODES_CCPHYSICSSPRITE_H__
