/****************************************************************************
Copyright (c) 2012 cocos2d-x.org

http://www.cocos2d-x.org

Created by Jung Sang-Taik on 12. 3. 16..
Copyright (c) 2012 Neofect. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCScale9Sprite_H__
#define __CCScale9Sprite_H__

#include "cocos2d.h"
#include "../../ExtensionMacros.h"

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/**
 * A 9-slice sprite for cocos2d.
 *
 * 9-slice scaling allows you to specify how scaling is applied
 * to specific areas of a sprite. With 9-slice scaling (3x3 grid),
 * you can ensure that the sprite does not become distorted when
 * scaled.
 *
 * @see http://yannickloriot.com/library/ios/cccontrolextension/Classes/CCScale9Sprite.html
 */
class CCScale9Sprite : public CCNodeRGBA
{
public:
    CCScale9Sprite();
    virtual ~CCScale9Sprite();

public:
    /** Original sprite's size. */
    CC_SYNTHESIZE_READONLY(CCSize, m_originalSize, OriginalSize);
    /** Prefered sprite's size. By default the prefered size is the original size. */

    //if the preferredSize component is given as -1, it is ignored
    CC_PROPERTY(CCSize, m_preferredSize, PreferredSize); 
    /** 
     * The end-cap insets. 
     * On a non-resizeable sprite, this property is set to CGRectZero; the sprite 
     * does not use end caps and the entire sprite is subject to stretching. 
     */
    CC_PROPERTY(CCRect, m_capInsets, CapInsets);
    /** Sets the left side inset */
    CC_PROPERTY(float, m_insetLeft, InsetLeft);
    /** Sets the top side inset */
    CC_PROPERTY(float, m_insetTop, InsetTop);
    /** Sets the right side inset */
    CC_PROPERTY(float, m_insetRight, InsetRight);
    /** Sets the bottom side inset */
    CC_PROPERTY(float, m_insetBottom, InsetBottom);

protected:
    bool m_bSpritesGenerated;
    CCRect m_spriteRect;
    bool   m_bSpriteFrameRotated;
    CCRect m_capInsetsInternal;
    bool m_positionsAreDirty;
    
    CCSpriteBatchNode* _scale9Image;
    CCSprite* _topLeft;
    CCSprite* _top;
    CCSprite* _topRight;
    CCSprite* _left;
    CCSprite* _centre;
    CCSprite* _right;
    CCSprite* _bottomLeft;
    CCSprite* _bottom;
    CCSprite* _bottomRight;

    bool _opacityModifyRGB;
    GLubyte _opacity;
    ccColor3B _color;
    
    void updateCapInset();
    void updatePositions();

public:
    
    virtual void setContentSize(const CCSize & size);
    virtual void visit();
    
    virtual bool init();

    virtual bool initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets);
    virtual bool initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, CCRect capInsets);
    /**
     * Initializes a 9-slice sprite with a texture file, a delimitation zone and
     * with the specified cap insets.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @param file The name of the texture file.
     * @param rect The rectangle that describes the sub-part of the texture that
     * is the whole image. If the shape is the whole texture, set this to the 
     * texture's full rect.
     * @param capInsets The values to use for the cap insets.
     */
    virtual bool initWithFile(const char* file, CCRect rect,  CCRect capInsets);
    
    /** 
     * Creates a 9-slice sprite with a texture file, a delimitation zone and
     * with the specified cap insets.
     *
     * @see initWithFile:rect:centerRegion:
     */
    static CCScale9Sprite* create(const char* file, CCRect rect,  CCRect capInsets);

    /**
     * Initializes a 9-slice sprite with a texture file and a delimitation zone. The
     * texture will be broken down into a 3×3 grid of equal blocks.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @param file The name of the texture file.
     * @param rect The rectangle that describes the sub-part of the texture that
     * is the whole image. If the shape is the whole texture, set this to the 
     * texture's full rect.
     */
    virtual bool initWithFile(const char* file, CCRect rect);
    
     /** 
     * Creates a 9-slice sprite with a texture file and a delimitation zone. The
     * texture will be broken down into a 3×3 grid of equal blocks.
     *
     * @see initWithFile:rect:
     */
    static CCScale9Sprite* create(const char* file, CCRect rect);

    /**
     * Initializes a 9-slice sprite with a texture file and with the specified cap
     * insets.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @param file The name of the texture file.
     * @param capInsets The values to use for the cap insets.
     */
    virtual bool initWithFile(CCRect capInsets, const char* file);

    /** 
     * Creates a 9-slice sprite with a texture file. The whole texture will be
     * broken down into a 3×3 grid of equal blocks.
     *
     * @see initWithFile:capInsets:
     */
    static CCScale9Sprite* create(CCRect capInsets, const char* file);

    
    /**
     * Initializes a 9-slice sprite with a texture file. The whole texture will be
     * broken down into a 3×3 grid of equal blocks.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @param file The name of the texture file.
     */
    virtual bool initWithFile(const char* file);

    /** 
     * Creates a 9-slice sprite with a texture file. The whole texture will be
     * broken down into a 3×3 grid of equal blocks.
     *
     * @see initWithFile:
     */
    static CCScale9Sprite* create(const char* file);
    
    /**
     * Initializes a 9-slice sprite with an sprite frame and with the specified 
     * cap insets.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @param spriteFrame The sprite frame object.
     * @param capInsets The values to use for the cap insets.
     */
    virtual bool initWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets);

    /**
     * Creates a 9-slice sprite with an sprite frame and the centre of its zone.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @see initWithSpriteFrame:centerRegion:
     */
    static CCScale9Sprite* createWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets); 
    /**
     * Initializes a 9-slice sprite with an sprite frame.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @param spriteFrame The sprite frame object.
     */
    virtual bool initWithSpriteFrame(CCSpriteFrame* spriteFrame);

    /**
     * Creates a 9-slice sprite with an sprite frame.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @see initWithSpriteFrame:
     */
    static CCScale9Sprite* createWithSpriteFrame(CCSpriteFrame* spriteFrame);  

    /**
     * Initializes a 9-slice sprite with an sprite frame name and with the specified 
     * cap insets.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @param spriteFrameName The sprite frame name.
     * @param capInsets The values to use for the cap insets.
     */
    virtual bool initWithSpriteFrameName(const char*spriteFrameName, CCRect capInsets);

    /**
     * Creates a 9-slice sprite with an sprite frame name and the centre of its
     * zone.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @see initWithSpriteFrameName:centerRegion:
     */
    static CCScale9Sprite* createWithSpriteFrameName(const char*spriteFrameName, CCRect capInsets); 

    /**
     * Initializes a 9-slice sprite with an sprite frame name.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @param spriteFrameName The sprite frame name.
     */
    virtual bool initWithSpriteFrameName(const char*spriteFrameName);

    /**
     * Creates a 9-slice sprite with an sprite frame name.
     * Once the sprite is created, you can then call its "setContentSize:" method
     * to resize the sprite will all it's 9-slice goodness intract.
     * It respects the anchorPoint too.
     *
     * @see initWithSpriteFrameName:
     */
    static CCScale9Sprite* createWithSpriteFrameName(const char*spriteFrameName);
    
    /**
     * Creates and returns a new sprite object with the specified cap insets.
     * You use this method to add cap insets to a sprite or to change the existing
     * cap insets of a sprite. In both cases, you get back a new image and the 
     * original sprite remains untouched.
     *
     * @param capInsets The values to use for the cap insets.
     */
    CCScale9Sprite* resizableSpriteWithCapInsets(CCRect capInsets);
    
    static CCScale9Sprite* create();

    // optional
    
    /** sets the premultipliedAlphaOpacity property.
     If set to NO then opacity will be applied as: glColor(R,G,B,opacity);
     If set to YES then oapcity will be applied as: glColor(opacity, opacity, opacity, opacity );
     Textures with premultiplied alpha will have this property by default on YES. Otherwise the default value is NO
     @since v0.8
     */
    virtual void setOpacityModifyRGB(bool bValue);
    
    /** returns whether or not the opacity will be applied using glColor(R,G,B,opacity) or glColor(opacity, opacity, opacity, opacity);
     @since v0.8
     */
    virtual bool isOpacityModifyRGB(void);
    virtual void setOpacity(GLubyte opacity);
	virtual GLubyte getOpacity();
    virtual void setColor(const ccColor3B& color);
	virtual const ccColor3B& getColor();

    virtual bool updateWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, bool rotated, CCRect capInsets);

    virtual void setSpriteFrame(CCSpriteFrame * spriteFrame);
    
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual void updateDisplayedColor(const cocos2d::ccColor3B& parentColor);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif // __CCScale9Sprite_H__
