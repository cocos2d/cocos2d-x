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

#include "2d/CCSprite.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "base/CCEventListenerCustom.h"

#if (CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION)

struct cpBody;
class b2Body;

NS_CC_EXT_BEGIN

/** A Sprite subclass that is bound to a physics body.
 It works with:
 - Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Objective-Chipmunk: Preprocessor macro CC_ENABLE_CHIPMUNK_INTEGRATION should be defined
 - Box2d: Preprocessor macro CC_ENABLE_BOX2D_INTEGRATION should be defined

 Features and Limitations:
 - Scale and Skew properties are ignored.
 - Position and rotation are going to updated from the physics body
 - If you update the rotation or position manually, the physics body will be updated
 - You can't enble both Chipmunk support and Box2d support at the same time. Only one can be enabled at compile time
 * @lua NA
 */
class CC_EX_DLL PhysicsSprite : public Sprite
{
public:

    static PhysicsSprite* create();
    /** Creates an sprite with a texture.
     The rect used will be the size of the texture.
     The offset will be (0,0).
     */
    static PhysicsSprite* createWithTexture(Texture2D *pTexture);

    /** Creates an sprite with a texture and a rect.
     The offset will be (0,0).
     */
    static PhysicsSprite* createWithTexture(Texture2D *pTexture, const Rect& rect);

    /** Creates an sprite with an sprite frame. */
    static PhysicsSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);

    /** Creates an sprite with an sprite frame name.
     An SpriteFrame will be fetched from the SpriteFrameCache by name.
     If the SpriteFrame doesn't exist it will raise an exception.
     @since v0.9
     */
    static PhysicsSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

    /** Creates an sprite with an image filename.
     The rect used will be the size of the image.
     The offset will be (0,0).
     */
    static PhysicsSprite* create(const char *pszFileName);

    /** Creates an sprite with an image filename and a rect.
     The offset will be (0,0).
     */
    static PhysicsSprite* create(const char *pszFileName, const Rect& rect);

    PhysicsSprite();

    virtual bool isDirty() const override;

    /** Keep the sprite's rotation separate from the body. */
    bool isIgnoreBodyRotation() const;
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

    //
    // Chipmunk specific
    //
    /** Body accessor when using regular Chipmunk */
    cpBody* getCPBody() const;
    void setCPBody(cpBody *pBody);

    //
    // Box2d specific
    //
    /** Body accessor when using box2d */
    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);

    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);
    virtual void syncPhysicsTransform() const;

    // overrides
    virtual const Vec2& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual float getPositionX() const override;
    virtual float getPositionY() const override;
    virtual Vec3 getPosition3D() const override;
    virtual void setPosition(const Vec2 &position) override;
    virtual void setPosition(float x, float y) override;
    virtual void setPositionX(float x) override;
    virtual void setPositionY(float y) override;
    virtual void setPosition3D(const Vec3& position) override;
    virtual float getRotation() const override;
    virtual void setRotation(float fRotation) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    const Vec2& getPosFromPhysics() const;
    void afterUpdate(EventCustom *event);

protected:
    bool    _ignoreBodyRotation;

    // chipmunk specific
    cpBody  *_CPBody;

    // box2d specific
    b2Body  *_pB2Body;
    float   _PTMRatio;
    
    // Event for update synchronise physic transform
    cocos2d::EventListenerCustom* _syncTransform;
};

NS_CC_EXT_END

#endif // CC_ENABLE_CHIPMUNK_INTEGRATION || CC_ENABLE_BOX2D_INTEGRATION

#endif // __PHYSICSNODES_CCPHYSICSSPRITE_H__
