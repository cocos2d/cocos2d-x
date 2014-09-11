/****************************************************************************
Copyright (c) 2008-2011 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

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

#ifndef __SPRITE_CCSPRITE_FRAME_H__
#define __SPRITE_CCSPRITE_FRAME_H__

#include "2d/CCNode.h"
#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

class Texture2D;

/**
 * @addtogroup sprite_nodes
 * @{
 */

/** @brief A SpriteFrame has:
    - texture: A Texture2D that will be used by the Sprite
    - rectangle: A rectangle of the texture


 You can modify the frame of a Sprite by doing:
 
    SpriteFrame *frame = SpriteFrame::frameWithTexture(texture, rect, offset);
    sprite->setDisplayFrame(frame);
 */
class CC_DLL SpriteFrame : public Ref, public Clonable
{
public:

    /** Create a SpriteFrame with a texture filename, rect in points.
     It is assumed that the frame was not trimmed.
     */
    static SpriteFrame* create(const std::string& filename, const Rect& rect);
    
    /** Create a SpriteFrame with a texture filename, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in pixels of the frame before being trimmed.
     */
    static SpriteFrame* create(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
    
    /** Create a SpriteFrame with a texture, rect in points.
     It is assumed that the frame was not trimmed.
     */
    static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect);

    /** Create a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in points of the frame before being trimmed.
     */
    static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);

    // attributes
    inline const Rect& getRectInPixels() const { return _rectInPixels; }
    void setRectInPixels(const Rect& rectInPixels);

    inline bool isRotated(void) const { return _rotated; }
    inline void setRotated(bool rotated) { _rotated = rotated; }

    /** get rect of the frame */
    inline const Rect& getRect(void) const { return _rect; }
    /** set rect of the frame */
    void setRect(const Rect& rect);

    /** get offset of the frame */
    const Vec2& getOffsetInPixels(void) const;
    /** set offset of the frame */
    void setOffsetInPixels(const Vec2& offsetInPixels);

    /** get original size of the trimmed image */
    inline const Size& getOriginalSizeInPixels(void) const { return _originalSizeInPixels; }
    /** set original size of the trimmed image */
    inline void setOriginalSizeInPixels(const Size& sizeInPixels) { _originalSizeInPixels = sizeInPixels; }

    /** get original size of the trimmed image */
    inline const Size& getOriginalSize(void) const { return _originalSize; }
    /** set original size of the trimmed image */
    inline void setOriginalSize(const Size& sizeInPixels) { _originalSize = sizeInPixels; }

    /** get texture of the frame */
    Texture2D* getTexture(void);
    /** set texture of the frame, the texture is retained */
    void setTexture(Texture2D* pobTexture);

    const Vec2& getOffset(void) const;
    void setOffset(const Vec2& offsets);

    // Overrides
	virtual SpriteFrame *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @lua NA
     */
    SpriteFrame(void);
    
    /**
     * @lua NA
     */
    virtual ~SpriteFrame(void);
    
    /** Initializes a SpriteFrame with a texture, rect in points.
     It is assumed that the frame was not trimmed.
     */
    bool initWithTexture(Texture2D* pobTexture, const Rect& rect);
    
    /** Initializes a SpriteFrame with a texture filename, rect in points;
     It is assumed that the frame was not trimmed.
     */
    bool initWithTextureFilename(const std::string& filename, const Rect& rect);
    
    /** Initializes a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in points of the frame before being trimmed.
     */
    bool initWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
    
    /** Initializes a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in pixels of the frame before being trimmed.
     
     @since v1.1
     */
    bool initWithTextureFilename(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);

protected:
    Vec2 _offset;
    Size _originalSize;
    Rect _rectInPixels;
    bool   _rotated;
    Rect _rect;
    Vec2 _offsetInPixels;
    Size _originalSizeInPixels;
    Texture2D *_texture;
    std::string  _textureFilename;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif //__SPRITE_CCSPRITE_FRAME_H__
