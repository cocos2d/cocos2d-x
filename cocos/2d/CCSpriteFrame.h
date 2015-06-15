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
 * @addtogroup _2d
 * @{
 */

/** @class SpriteFrame
 * @brief @~english A SpriteFrame has:
 *   - texture: A Texture2D that will be used by the Sprite
 *   - rectangle: A rectangle of the texture
 *
 *
 * You can modify the frame of a Sprite by doing:
 *  @code
 *   SpriteFrame *frame = SpriteFrame::createWithTexture(texture, rect);
 *   sprite->setSpriteFrame(frame);
 *  @endcode
 * @~chinese 一个 SpriteFrame 包含:
 * - 纹理: 会被 Sprite 使用的 Texture2D 对象。
 * - 矩形: 在纹理中的矩形区域。
 * 
 * 
 * 可以这样来修改 Sprite 使用的 SpriteFrame:
 * 
 *  @code
 *   SpriteFrame *frame = SpriteFrame::createWithTexture(texture, rect);
 *   sprite->setSpriteFrame(frame);
 *  @endcode
 */
class CC_DLL SpriteFrame : public Ref, public Clonable
{
public:

    /** @~english Create a SpriteFrame with a texture filename, rect in points.
     It is assumed that the frame was not trimmed.
     *
     * @~chinese 使用指定的图片文件与矩形区域创建一个 SpriteFrame。
     * 这个方法假设 SpriteFrame 没有进行修剪。
     * 
     * @param filename @~english Texture file name.
     * @~chinese 图片文件路径。
     * @param rect @~english A specified rect.
     * @~chinese 指定的矩形区域。
     * @return @~english An autoreleased SpriteFrame object.
     * @~chinese 一个 SpriteFrame 实例（已被 autorelease）。
     */
    static SpriteFrame* create(const std::string& filename, const Rect& rect);
    
    /** @~english Create a SpriteFrame with a texture filename, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in pixels of the frame before being trimmed.
     *
     * @~chinese 使用指定的图片文件，矩形区域，是否旋转，偏移量与原始大小创建一个 SpriteFrame。
     * originalSize 是 SpriteFrame 被修剪之前的大小(以像素为单位)。
     * 
     * @param filename @~english Texture filename
     * @~chinese 图片文件路径
     * @param rect @~english A specified rect.
     * @~chinese 指定的矩形区域。
     * @param rotated @~english Is rotated if true.
     * @~chinese 是否旋转。
     * @param offset @~english A specified offset.
     * @~chinese 指定的偏移量。
     * @param originalSize @~english A specified original size.
     * @~chinese 指定的原始大小。
     * @return @~english An autoreleased SpriteFrame object.
     * @~chinese 一个 SpriteFrame 实例（已被 autorelease）。
     */
    static SpriteFrame* create(const std::string& filename, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
    
    /** @~english Create a SpriteFrame with a texture, rect in points.
     It is assumed that the frame was not trimmed.
     * @~chinese 使用指定的纹理与矩形区域创建一个 SpriteFrame。
     * 此方法假设 SpriteFrame 没有修剪。
     * @param pobTexture @~english The texture pointer.
     * @~chinese 指定的纹理实例。
     * @param rect @~english A specified rect.
     * @~chinese 指定的矩形区域。
     * @return @~english An autoreleased SpriteFrame object.
     * @~chinese 一个 SpriteFrame 实例（已被 autorelease）。
     */
    static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect);

    /** @~english Create a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in points of the frame before being trimmed.
     * @~chinese 使用指定的纹理，矩形区域，是否旋转，偏移量与原始大小创建一个 SpriteFrame。
     * originalSize 是 SpriteFrame 被修剪之前的大小(以像素为单位)。
     * @param pobTexture @~english The texture pointer.
     * @~chinese 指定的纹理实例。
     * @param rect @~english A specified rect.
     * @~chinese 指定的矩形区域。
     * @param rotated @~english Is rotated if true.
     * @~chinese 是否旋转。
     * @param offset @~english A specified offset.
     * @~chinese 指定的偏移量。
     * @param originalSize @~english A specified original size.
     * @~chinese 指定的原始大小。
     * @return @~english An autoreleased SpriteFrame object.
     * @~chinese 一个 SpriteFrame 实例（已被 autorelease）。
     */
    static SpriteFrame* createWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);

    // attributes
    /** @~english Get rect of the sprite frame.
     *
     * @~chinese 获取 SpriteFrame 的纹理矩形区域。
     * 
     * @return @~english The rect of the sprite frame, in pixels.
     * @~chinese SpriteFrame 的纹理矩形区域，以像素为单位。
     */
    inline const Rect& getRectInPixels() const { return _rectInPixels; }
    /** @~english Set rect of the sprite frame.
     *
     * @~chinese 设置 SpriteFrame 的纹理矩形区域。。
     * 
     * @param rectInPixels @~english The rect of the sprite frame, in pixels.
     * @~chinese SpriteFrame 的纹理矩形区域，以像素为单位。
     */
    void setRectInPixels(const Rect& rectInPixels);

    /**@~english Is the sprite frame rotated or not.
     *
     * @~chinese 获取 SpriteFrame 是否旋转。
     * 
     * @return @~english Is rotated if true.
     * @~chinese 如果旋转则返回 true；否则返回 false。
     */
    inline bool isRotated() const { return _rotated; }
    /** @~english Set rotated of the sprite frame.
     *
     * @~chinese 设置 SpriteFrame 是否旋转。
     * 
     * @param rotated @~english Rotated the sprite frame if true.
     * @~chinese 如果为 true，则旋转；否则不旋转。
     */
    inline void setRotated(bool rotated) { _rotated = rotated; }

    /** @~english Get rect of the frame.
     *
     * @~chinese 获取 SpriteFrame 的纹理矩形区域。
     * 
     * @return @~english The rect of the sprite frame.
     * @~chinese SpriteFrame 的纹理矩形区域。
     */
    inline const Rect& getRect() const { return _rect; }
    /** @~english Set rect of the frame.
     *
     * @~chinese 设置 SpriteFrame 的纹理矩形区域。
     * 
     * @param rect @~english The rect of the sprite.
     * @~chinese SpriteFrame 的纹理矩形区域。
     */
    void setRect(const Rect& rect);

    /** @~english Get offset of the frame.
     * 
     * @~chinese 获取 SpriteFrame 的偏移量。
     * 
     * @return @~english The offset of the sprite frame, in pixels.
     * @~chinese SpriteFrame 的偏移量。
     */
    const Vec2& getOffsetInPixels() const;
    /** @~english Set offset of the frame.
     * 
     * @~chinese 设置 SpriteFrame 的偏移量。
     * 
     * @param offsetInPixels @~english The offset of the sprite frame, in pixels.
     * @~chinese SpriteFrame 的偏移量。
     */
    void setOffsetInPixels(const Vec2& offsetInPixels);

    /** @~english Get original size of the trimmed image.
     *
     * @~chinese 获取修剪前的原始大小。
     * 
     * @return @~english The original size of the trimmed image, in pixels.
     * @~chinese 修剪前的原始大小，以像素为单位。
     */
    inline const Size& getOriginalSizeInPixels() const { return _originalSizeInPixels; }
    /** @~english Set original size of the trimmed image.
     *
     * @~chinese 设置修剪前的原始大小。
     * 
     * @param sizeInPixels @~english The original size of the trimmed image, in pixels.
     * @~chinese 修剪前的原始大小，以像素为单位。
     */
    inline void setOriginalSizeInPixels(const Size& sizeInPixels) { _originalSizeInPixels = sizeInPixels; }

    /** @~english Get original size of the trimmed image.
     *
     * @~chinese 获取修剪前的原始大小。
     * 
     * @return @~english The original size of the trimmed image.
     * @~chinese 修剪前的原始大小。
     */
    inline const Size& getOriginalSize() const { return _originalSize; }
    /** @~english Set original size of the trimmed image.
     *
     * @~chinese 设置修剪前的原始大小。
     * 
     * @param sizeInPixels @~english The original size of the trimmed image.
     * @~chinese 修剪前的原始大小。
     */
    inline void setOriginalSize(const Size& sizeInPixels) { _originalSize = sizeInPixels; }

    /** @~english Get texture of the frame.
     *
     * @~chinese 获取使用的纹理实例。
     * 
     * @return @~english The texture of the sprite frame.
     * @~chinese 使用的纹理实例。
     */
    Texture2D* getTexture();
    /** @~english Set texture of the frame, the texture is retained.
     *
     * @~chinese 设置使用的纹理实例，会被 retain。
     * 
     * @param pobTexture @~english The texture of the sprite frame.
     * @~chinese 纹理实例。
     */
    void setTexture(Texture2D* pobTexture);

    /** @~english Get offset of the frame.
     *
     * @~chinese 获取偏移量。
     * 
     * @return @~english The offset of the sprite frame.
     * @~chinese 偏移量。
     */
    const Vec2& getOffset() const;
    /** @~english Set offset of the frame.
     *
     * @~chinese 设置偏移量。
     * 
     * @param offsets @~english The offset of the sprite frame.
     * @~chinese 偏移量。
     */
    void setOffset(const Vec2& offsets);

    // Overrides
	virtual SpriteFrame *clone() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @lua NA
     */
    SpriteFrame();
    
    /**
     * @lua NA
     */
    virtual ~SpriteFrame();
    
    /** @~english Initializes a SpriteFrame with a texture, rect in points.
     It is assumed that the frame was not trimmed.
     * @~chinese 使用指定的纹理与矩形区域初始化一个 SpriteFrame。
     * 此方法假设 SpriteFrame 没有修剪。
     */
    bool initWithTexture(Texture2D* pobTexture, const Rect& rect);
    
    /** @~english Initializes a SpriteFrame with a texture filename, rect in points;
     It is assumed that the frame was not trimmed.
     * @~chinese 使用指定的图片文件与矩形区域初始化一个 SpriteFrame。
     * 此方法假设 SpriteFrame 没有修剪。
     */
    bool initWithTextureFilename(const std::string& filename, const Rect& rect);
    
    /** @~english Initializes a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in points of the frame before being trimmed.
     * @~chinese 使用指定的纹理，矩形区域，是否旋转，偏移量与原始大小初始化一个 SpriteFrame。
     * originalSize 是 SpriteFrame 被修剪之前的大小(以像素为单位)。
     */
    bool initWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Vec2& offset, const Size& originalSize);
    
    /** @~english Initializes a SpriteFrame with a texture, rect, rotated, offset and originalSize in pixels.
     The originalSize is the size in pixels of the frame before being trimmed.
     
     * @~chinese 使用指定的图片文件，矩形区域，是否旋转，偏移量与原始大小初始化一个 SpriteFrame。
     * originalSize 是 SpriteFrame 被修剪之前的大小(以像素为单位)。
     * 
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

// end of _2d group
/// @}

NS_CC_END

#endif //__SPRITE_CCSPRITE_FRAME_H__
