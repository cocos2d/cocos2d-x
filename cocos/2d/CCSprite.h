/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
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

#ifndef __SPRITE_NODE_CCSPRITE_H__
#define __SPRITE_NODE_CCSPRITE_H__

#include <string>
#include "2d/CCNode.h"
#include "2d/CCDrawNode.h"
#include "base/CCProtocols.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTrianglesCommand.h"
#include "renderer/CCCustomCommand.h"
#include "2d/CCAutoPolygon.h"

NS_CC_BEGIN

class SpriteBatchNode;
class SpriteFrame;
class Animation;
class Rect;
class Size;
class Texture2D;
struct transformValues_;

#ifdef SPRITE_RENDER_IN_SUBPIXEL
#undef SPRITE_RENDER_IN_SUBPIXEL
#endif

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define SPRITE_RENDER_IN_SUBPIXEL
#else
#define SPRITE_RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

/**
 * @addtogroup _2d
 * @{
 */

/**@~english
 * Sprite is a 2d image ( http://en.wikipedia.org/wiki/Sprite_(computer_graphics) ).
 *
 * Sprite can be created with an image, or with a sub-rectangle of an image.
 *
 * To optimize the Sprite rendering, please follow the following best practices:
 *  - Put all your sprites in the same spritesheet (http://www.codeandweb.com/what-is-a-sprite-sheet).
 *  - Use the same blending function for all your sprites.
 *  - ...and the Renderer will automatically "batch" your sprites (will draw all of them in one OpenGL call).
 *
 *  To gain an additional 5% ~ 10% more in the rendering, you can parent your sprites into a `SpriteBatchNode`.
 *  But doing so carries the following limitations:
 *
 *  - The Alias/Antialias property belongs to `SpriteBatchNode`, so you can't individually set the aliased property.
 *  - The Blending function property belongs to `SpriteBatchNode`, so you can't individually set the blending function property.
 *  - `ParallaxNode` is not supported, but can be simulated with a "proxy" sprite.
 *  - Sprites can only have other Sprites (or subclasses of Sprite) as children.
 *
 * The default anchorPoint in Sprite is (0.5, 0.5).
 * @~chinese 
 * Sprite 是一个2D图像节点(http://en.wikipedia.org/wiki/Sprite_(computer_graphics) ).
 * 
 * 可以使用一个图片或者图片的一个矩形区域来创建 Sprite 对象。
 * 
 * 为了优化 Sprite 的渲染,请遵循以下最佳实现:
 * - 将所有的 Sprite 放在同一个 spritesheet 中(http://www.codeandweb.com/what-is-a-sprite-sheet)。
 * - 所有的 Sprite 使用相同的混合函数。
 * - …这样渲染器就会自动“批处理”所有的 Sprite (将所有的 Sprite 放在一次OpenGL调用中渲染出来)。
 * 
 * 通过将 Sprite 放入一个 SpriteBatchNode 父节点中，可以获得额外的 5% ~ 10% 的渲染优化。
 * 但是这样做有以下限制:
 * - 只能设置 SpriteBatchNode 节点的别名，无法为每个 Sprite 设置不同的别名。
 * - 只能设置 SpriteBatchNode 节点的混合函数，无法为每个 Sprite 设置不同的混合函数。
 * - 不支持 ParallaxNode，但是可以使用代理 Sprite 来模拟。
 * - 每个 Sprite 的子节点只能是 Sprite 或者其子类的对象。
 * 
 * 默认锚点(0.5,0.5)。
 */
class CC_DLL Sprite : public Node, public TextureProtocol
{
public:
     /** @~english Sprite invalid index on the SpriteBatchNode.  @~chinese 在 SpriteBatchNode 中的无效索引值。*/
    static const int INDEX_NOT_INITIALIZED = -1;

    /// @name Creators
    /// @{

    /**@~english
     * Creates an empty sprite without texture. You can call setTexture method subsequently.
     *
     * @~chinese 
     * 创建一个没有纹理的空 Sprite。可以在稍后调用 setTexture 方法设置纹理。
     * 
     * @memberof @~english Sprite
     * @~chinese Sprite
     * @return @~english An autoreleased sprite object.
     * @~chinese 一个 Sprite 实例（已经被 autorelese）。
     */
    static Sprite* create();

    /**@~english
     * Creates a sprite with an image filename.
     *
     * After creation, the rect of sprite will be the size of the image,
     * and the offset will be (0,0).
     *
     * @~chinese 
     * 使用一个图片文件创建 Sprite。
     * 
     * 创建成功之后，Sprite 的大小与图片大小一致。偏移量为 (0,0)。
     * 
     * @param   filename @~english A path to image file, e.g., "scene1/monster.png".
     * @~chinese 图像文件的路径，例如："scene1/monster.png"
     * @return  @~english An autoreleased sprite object.
     * @~chinese 一个 Sprite 实例（已经被 autorelese）。
     */
    static Sprite* create(const std::string& filename);
    
    /** @~english
     * Creates a polygon sprite with a polygon info.
     *
     * @~chinese 
     * 使用一个PolygonInfo创建 Sprite。
     * 
     * @param polygonInfo @~english A specified polygon info, you can get that from AutoPolygon.
     * @~chinese 一个指定的polygon info。你可以从AutoPolygon类获取polygon info.
     * @return @~english An autoreleased sprite object.
     * @~chinese 一个 Sprite 实例（已经被 autorelese）。
     */
    static Sprite* create(const PolygonInfo& info);

    /**@~english
     * Creates a sprite with an image filename and a rect.
     *
     * @~chinese 
     * 使用图片文件和指定的矩形区域创建一个 Sprite。
     * 
     * @param   filename @~english A path to image file, e.g., "scene1/monster.png".
     * @~chinese 图像文件的路径，例如："scene1/monster.png"
     * @param   rect     @~english A subrect of the image file.
     * @~chinese 指定的矩形区域。
     * @return  @~english An autoreleased sprite object.
     * @~chinese 一个 Sprite 实例（已经被 autorelese）。
     */
    static Sprite* create(const std::string& filename, const Rect& rect);

    /**@~english
     * Creates a sprite with a Texture2D object.
     *
     * After creation, the rect will be the size of the texture, and the offset will be (0,0).
     *
     * @~chinese 
     * 使用指定的纹理创建 Sprite。
     * 
     * 创建后，Sprite 的大小与指定的纹理一致，并且偏移量为 (0,0)。
     * 
     * @param   texture    @~english A pointer to a Texture2D object.
     * @~chinese 指定的纹理对象。
     * @return  @~english An autoreleased sprite object.
     * @~chinese 一个 Sprite 实例（已经被 autorelese）。
     */
    static Sprite* createWithTexture(Texture2D *texture);

    /**@~english
     * Creates a sprite with a texture and a rect.
     *
     * After creation, the offset will be (0,0).
     *
     * @~chinese 
     * 使用指定的纹理与矩形区域创建 Sprite。
     * 
     * 创建后，偏移量为 (0,0)。
     * 
     * @param   texture     @~english A pointer to an existing Texture2D object.
     *                      You can use a Texture2D object for many sprites.
     * @~chinese 已有的纹理对象。
     * 一个纹理对象可以被多个 Sprite 使用。
     * @param   rect        @~english Only the contents inside the rect of this texture will be applied for this sprite.
     * @~chinese 指定的矩形区域。
     * @param   rotated     @~english Whether or not the rect is rotated.
     * @~chinese 是否旋转。
     * @return  @~english An autoreleased sprite object.
     * @~chinese 一个 Sprite 实例（已经被 autorelese）。
     */
    static Sprite* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated=false);

    /**@~english
     * Creates a sprite with an sprite frame.
     *
     * @~chinese 
     * 使用 SpriteFrame 创建一个 Sprite。
     * 
     * @param   spriteFrame    @~english A sprite frame which involves a texture and a rect.
     * @~chinese SpriteFrame 实例。
     * @return  @~english An autoreleased sprite object.
     * @~chinese 一个 Sprite 实例（已经被 autorelese）。
     */
    static Sprite* createWithSpriteFrame(SpriteFrame *spriteFrame);

    /**@~english
     * Creates a sprite with an sprite frame name.
     *
     * A SpriteFrame will be fetched from the SpriteFrameCache by spriteFrameName param.
     * If the SpriteFrame doesn't exist it will raise an exception.
     *
     * @~chinese 
     * 使用 SpriteFrame 的名称来创建 Sprite。
     * 
     * 通过指定的名称从 SpriteFrameCache 中取得 SpriteFrame 对象，然后初始化 Sprite。
     * 如果不存在 SpriteFrame 将引发一个异常。
     * 
     * @param   spriteFrameName @~english A null terminated string which indicates the sprite frame name.
     * @~chinese 指定的 SpriteFrame 名称。
     * @return  @~english An autoreleased sprite object.
     * @~chinese 一个 Sprite 实例（已经被 autorelese）。
     */
    static Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);

    //  end of creators group
    /// @}


    /// @{
    /// @name BatchNode methods

    /**@~english
     * Updates the quad according the rotation, position, scale values.
     * @~chinese 
     * 通过旋转，位置以及缩放的值来更新 Sprite 的绘制属性。
     */
    virtual void updateTransform() override;

    /**@~english
     * Returns the batch node object if this sprite is rendered by SpriteBatchNode.
     *
     * @~chinese 
     * 如果当前 Sprite 通过 SpriteBatchNode 渲染，返回 SpriteBatchNode 实例。
     * 
     * @return @~english The SpriteBatchNode object if this sprite is rendered by SpriteBatchNode,
     *         nullptr if the sprite isn't used batch node.
     * @~chinese 如果当前 Sprite 通过 SpriteBatchNode 渲染，返回 SpriteBatchNode 实例；否则返回 nullptr。
     */
    virtual SpriteBatchNode* getBatchNode() const;
    /**@~english
     * Sets the batch node to sprite.
     * @~chinese 
     * 设置渲染此 Sprite 的 SpriteBatchNode 对象。
     * @warning @~english This method is not recommended for game developers. Sample code for using batch node
     * @code
     * SpriteBatchNode *batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 15);
     * Sprite *sprite = Sprite::createWithTexture(batch->getTexture(), Rect(0, 0, 57, 57));
     * batch->addChild(sprite);
     * layer->addChild(batch);
     * @endcode
     * @~chinese 不推荐开发者直接调用这个方法。使用 SpriteBatchNode 的示例代码：
     * @code
     * SpriteBatchNode *batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 15);
     * Sprite *sprite = Sprite::createWithTexture(batch->getTexture(), Rect(0, 0, 57, 57));
     * batch->addChild(sprite);
     * layer->addChild(batch);
     * @endcode
     */
    virtual void setBatchNode(SpriteBatchNode *spriteBatchNode);

    /// @} end of BatchNode methods


    /// @{
    /// @name Texture / Frame methods

    /** @~english Sets a new texture (from a filename) to the sprite.
     *
     * @~chinese 设置一个新的纹理（使用指定的文件）。
     * 
     *  @memberof @~english Sprite
     *  It will call `setTextureRect()` with the texture's content size.
     * @~chinese Sprite
     * 此函数会获取纹理的大小并调用 `setTextureRect()`
     * @param filename @~english The file path of the image file.
     * @~chinese 图片文件的路径。
     */
    virtual void setTexture(const std::string &filename );

    /** @~english @overload
     *
     *  The Texture's rect is not changed.
     * @~chinese @overload
     * 
     * 纹理的矩形区域是没有改变的。
     */
    virtual void setTexture(Texture2D *texture) override;

    virtual Texture2D* getTexture() const override;

    /**@~english
     * Updates the texture rect of the Sprite in points.
     *
     * It will call `setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize)` with \p rotated = false, and \p utrimmedSize = rect.size.
     * @~chinese 
     * 更新纹理的矩形区域。
     * 
     * 它将调用 `setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize)` 其中 \p rotated = false, \p utrimmedSize = rect.size。
     */
    virtual void setTextureRect(const Rect& rect);

    /** @~english
     * It will update the texture coordinates and the vertex rectangle.
     * @~chinese
     * 更新 Sprite 的顶点坐标和纹理坐标。
     * @param rect @~english The used rect of the texture.
     * @~chinese 使用的纹理矩形区域。
     * @param rotated @~english Whether rotate or not.
     * @~chinese 是否旋转。
     * @param untrimmedSize @~english The size before trimmed.
     * @~chinese 裁剪前的大小。
     */
    virtual void setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize);

    /**@~english
     * Sets the vertex rect.
     *
     * It will be called internally by setTextureRect.
     * Useful if you want to create 2x images from SD images in Retina Display.
     * Do not call it manually. Use setTextureRect instead.
     * @~chinese 
     * 设置顶点坐标。
     * 
     * 此方法被 setTextureRect 调用。
     * 如果需要从图片文件创建 2x 的 Retina 屏幕纹理，则需要使用这个函数。
     * 不要手动调用它。使用setTextureRect来代替。
     */
    virtual void setVertexRect(const Rect& rect);

    /** @{@~english
     * Sets a new SpriteFrame to the Sprite.
     * @~chinese 
     * 设置一个新的SpriteFrame。
     */
    virtual void setSpriteFrame(const std::string &spriteFrameName);
    virtual void setSpriteFrame(SpriteFrame* newFrame);
    /** @} */

    /** @deprecated Use `setSpriteFrame()` instead. */
    CC_DEPRECATED_ATTRIBUTE virtual void setDisplayFrame(SpriteFrame *newFrame) { setSpriteFrame(newFrame); }

    /**@~english
     * Returns whether or not a SpriteFrame is being displayed.
     * @~chinese 
     * 返回 SpriteFrame 是否被显示了。
     */
    virtual bool isFrameDisplayed(SpriteFrame *frame) const;

    /**@~english
     * Returns the current displayed frame.
     * @~chinese 
     * 返回当前显示的 SpriteFrame 实例。
     */
    virtual SpriteFrame* getSpriteFrame() const;
    /** @deprecated Use `getSpriteFrame()` instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual SpriteFrame* getDisplayFrame() const { return getSpriteFrame(); }
    /** @deprecated Use `getSpriteFrame()` instead. */
    CC_DEPRECATED_ATTRIBUTE virtual SpriteFrame* displayFrame() const { return getSpriteFrame(); };

    /// @} End of frames methods


    /// @{
    /// @name Animation methods
    /**@~english
     * Changes the display frame with animation name and index.
     * The animation name will be get from the AnimationCache.
     * @~chinese 
     * 从帧动画中选取指定的帧用于当前显示。
     * 帧动画是根据名称从 AnimationCache 获取的。
     */
    virtual void setDisplayFrameWithAnimationName(const std::string& animationName, ssize_t frameIndex);
    /// @}


    /// @{
    /// @name Sprite Properties' setter/getters.

    /**@~english
     * Whether or not the Sprite needs to be updated in the Atlas.
     *
     * @~chinese 
     * Sprite是否需要在atlas里面更新。
     * 
     * @return @~english True if the sprite needs to be updated in the Atlas, false otherwise.
     * @~chinese 如果需要更新，返回 true；否则返回 false
     */
    virtual bool isDirty() const { return _dirty; }

    /**@~english
     * Makes the Sprite to be updated in the Atlas.
     * @~chinese 
     * 设置 Sprite 的 Atlas 是否需要更新。
     */
    virtual void setDirty(bool dirty) { _dirty = dirty; }

    /**@~english
     * Returns the quad (tex coords, vertex coords and color) information.
     * @~chinese 
     * 获取 Sprite 的 顶点坐标，纹理坐标以及颜色信息。
     * @js  NA
     * @lua NA
     */
    inline V3F_C4B_T2F_Quad getQuad() const { return _quad; }

    /**@~english
     * Returns whether or not the texture rectangle is rotated.
     * @~chinese 
     * 返回纹理矩形是否旋转。
     */
    inline bool isTextureRectRotated() const { return _rectRotated; }

    /**@~english
     * Returns the index used on the TextureAtlas.
     * @~chinese 
     * 返回 TextureAtlas 的索引值。
     */
    inline ssize_t getAtlasIndex() const { return _atlasIndex; }

    /**@~english
     * Sets the index used on the TextureAtlas.
     *
     * @~chinese 
     * 设置 TextureAtlas 的索引值。
     * 
     * @warning @~english Don't modify this value unless you know what you are doing.
     * @~chinese 不要随意修改这个值，除非你知道你在做什么。
     */
    inline void setAtlasIndex(ssize_t atlasIndex) { _atlasIndex = atlasIndex; }

    /**@~english
     * Returns the rect of the Sprite in points.
     * @~chinese 
     * 返回 Sprite 的矩形区域。
     */
    inline const Rect& getTextureRect() const { return _rect; }

    /**@~english
     * Gets the weak reference of the TextureAtlas when the sprite is rendered using via SpriteBatchNode.
     * @~chinese 
     * 当使用 SpriteBatchNode 进行渲染时，此方法可以获取使用的 TextureAtlas 实例。
     */
    inline TextureAtlas* getTextureAtlas() const { return _textureAtlas; }

    /**@~english
     * Sets the weak reference of the TextureAtlas when the sprite is rendered using via SpriteBatchNode.
     * @~chinese 
     * 当使用 SpriteBatchNode 进行渲染时，通过此方法可以设置使用的 TextureAtlas 实例。
     */
    inline void setTextureAtlas(TextureAtlas *textureAtlas) { _textureAtlas = textureAtlas; }

    /**@~english
     * Gets the offset position of the sprite. Calculated automatically by editors like Zwoptex.
     * @~chinese 
     * 获取 Sprite 的偏移位置。Zwoptex 等编辑器可以自动计算这个值。
     */
    inline const Vec2& getOffsetPosition() const { return _offsetPosition; }


    /**@~english
     * Returns the flag which indicates whether the sprite is flipped horizontally or not.
     *
     * It only flips the texture of the sprite, and not the texture of the sprite's children.
     * Also, flipping the texture doesn't alter the anchorPoint.
     * If you want to flip the anchorPoint too, and/or to flip the children too use:
     * sprite->setScaleX(sprite->getScaleX() * -1);
     *
     * @~chinese 
     * 返回 Sprite 是否水平翻转。
     * 
     * 它只翻转当前 Sprite 纹理，而不影响子节点。
     * 此外，翻转纹理不改变锚点。
     * 如果你想翻转锚点，并且/或者翻转子节点，请使用：
     * sprite->setScaleX(sprite->getScaleX() * -1);
     * 
     * @return @~english true if the sprite is flipped horizontally, false otherwise.
     * @~chinese 如果是水平翻转，返回 true；否则返回 false。
     */
    bool isFlippedX() const;
    /**@~english
     * Sets whether the sprite should be flipped horizontally or not.
     *
     * @~chinese 
     * 设置是否进行水平翻转。
     * 
     * @param flippedX @~english true if the sprite should be flipped horizontally, false otherwise.
     * @~chinese true 表示要水平翻转；否则表示不水平翻转。
     */
    void setFlippedX(bool flippedX);

    /** @deprecated Use isFlippedX() instead.
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated Use setFlippedX() instead
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flippedX) { setFlippedX(flippedX); };

    /**@~english
     * Return the flag which indicates whether the sprite is flipped vertically or not.
     *
     * It only flips the texture of the sprite, and not the texture of the sprite's children.
     * Also, flipping the texture doesn't alter the anchorPoint.
     * If you want to flip the anchorPoint too, and/or to flip the children too use:
     * sprite->setScaleY(sprite->getScaleY() * -1);
     *
     * @~chinese 
     * 返回是否垂直翻转。
     * 
     * 它只翻转当前 Sprite 纹理，而不影响子节点。
     * 此外，纹理翻转不改变锚点。
     * 如果你想翻转锚点，并且/或者翻转子节点，请使用：
     * sprite->setScaleY(sprite->getScaleY() * -1);
     * 
     * @return @~english true if the sprite is flipped vertically, false otherwise.
     * @~chinese 如果是垂直翻转返回 true；否则返回 false。
     */
    bool isFlippedY() const;
    /**@~english
     * Sets whether the sprite should be flipped vertically or not.
     *
     * @~chinese 
     * 设置是否进行垂直翻转。
     * 
     * @param flippedY @~english true if the sprite should be flipped vertically, false otherwise.
     * @~chinese true 表示要垂直翻转；否则表示不垂直翻转。
     */
    void setFlippedY(bool flippedY);

    /// @} End of Sprite properties getter/setters

    /** @deprecated Use isFlippedY() instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated Use setFlippedY() instead.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flippedY) { setFlippedY(flippedY); };

    //
    // Overrides
    //
    /// @{
    /// @name Functions inherited from TextureProtocol.
    /**
     * @~english
     * @code
     * When this function bound into js or lua,the parameter will be changed.
     * In js: var setBlendFunc(var src, var dst).
     * In lua: local setBlendFunc(local src, local dst).
     * @endcode
     * @~chinese 
     * @code
     * 当这个函数绑定到js或lua,参数将被改变。
     * 在js 中: var setBlendFunc(var src, var dst)。
     * 在lua中: local setBlendFunc(local src, local dst)。
     * @endcode
    */
    inline void setBlendFunc(const BlendFunc &blendFunc) override { _blendFunc = blendFunc; }
    /**
    * @js  NA
    * @lua NA
    */
    inline const BlendFunc& getBlendFunc() const override { return _blendFunc; }
    /// @}

    /**
     * @js NA
     */
    virtual std::string getDescription() const override;

    /// @{
    /// @name Functions inherited from Node.
    virtual void setScaleX(float scaleX) override;
    virtual void setScaleY(float scaleY) override;
    virtual void setScale(float scaleX, float scaleY) override;
    /**
    * @js  NA
    * @lua NA
    */
    virtual void setPosition(const Vec2& pos) override;
    virtual void setPosition(float x, float y) override;
    virtual void setRotation(float rotation) override;
    virtual void setRotationSkewX(float rotationX) override;
    virtual void setRotationSkewY(float rotationY) override;
    virtual void setSkewX(float sx) override;
    virtual void setSkewY(float sy) override;
    virtual void removeChild(Node* child, bool cleanup) override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void reorderChild(Node *child, int zOrder) override;
    using Node::addChild;
    virtual void addChild(Node *child, int zOrder, int tag) override;
    virtual void addChild(Node *child, int zOrder, const std::string &name) override;
    virtual void sortAllChildren() override;
    virtual void setScale(float scale) override;
    virtual void setPositionZ(float positionZ) override;
    virtual void setAnchorPoint(const Vec2& anchor) override;
    virtual void ignoreAnchorPointForPosition(bool value) override;
    virtual void setVisible(bool bVisible) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void setOpacityModifyRGB(bool modify) override;
    virtual bool isOpacityModifyRGB() const override;
    /// @}

CC_CONSTRUCTOR_ACCESS:
	/**
     * @js ctor
     */
    Sprite();
    virtual ~Sprite();

    /* @~english Initializes an empty sprite with nothing init.  @~chinese 初始化一个空的Sprite。*/
    virtual bool init() override;

    /**@~english
     * Initializes a sprite with a texture.
     *
     * After initialization, the rect used will be the size of the texture, and the offset will be (0,0).
     *
     * @~chinese 
     * 使用指定的纹理初始化一个Sprite。
     * 
     * 初始化后，Sprite 的大小与纹理一致，偏移量为 (0,0)。
     * 
     * @param   texture    @~english A pointer to an existing Texture2D object.
     *                      You can use a Texture2D object for many sprites.
     * @~chinese 已有的 Texture2D 对象的指针。一个纹理可以被多个 Sprite 使用。
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    virtual bool initWithTexture(Texture2D *texture);
    
    
    /**
     * Initializes a sprite with a PolygonInfo.
     *
     * After initialization, the rect used will be the size of the texture, and the offset will be (0,0).
     *
     * @param   PolygonInfo    a Polygon info contains the structure of the polygon.
     * @return  True if the sprite is initialized properly, false otherwise.
     */
    virtual bool initWithPolygon(const PolygonInfo& info);

    /**@~english
     * Initializes a sprite with a texture and a rect.
     *
     * After initialization, the offset will be (0,0).
     *
     * @~chinese 
     * 使用指定的纹理与矩形区域初始化一个 Sprite。
     * 
     * 初始化后，偏移量为 (0,0)。
     * 
     * @param   texture    @~english A pointer to an exisiting Texture2D object.
     *                      You can use a Texture2D object for many sprites.
     * @~chinese 已有的 Texture2D 对象的指针。一个纹理可以被多个 Sprite 使用。
     * @param   rect        @~english Only the contents inside rect of this texture will be applied for this sprite.
     * @~chinese 需要从指定的纹理中截取的矩形区域。
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    virtual bool initWithTexture(Texture2D *texture, const Rect& rect);

    /**@~english
     * Initializes a sprite with a texture and a rect in points, optionally rotated.
     *
     * After initialization, the offset will be (0,0).
     * @~chinese 
     * 使用指定的纹理，矩形区域和是否旋转初始化一个Sprite。
     * 
     * 初始化后，偏移量为 (0,0)。
     * @note    @~english This is the designated initializer.
     *
     * @~chinese 这是特定的初始化方法。
     * 
     * @param   texture    @~english A Texture2D object whose texture will be applied to this sprite.
     * @~chinese 已有的 Texture2D 对象的指针。
     * @param   rect        @~english A rectangle assigned the contents of texture.
     * @~chinese 需要从指定的纹理中截取的矩形区域。
     * @param   rotated     @~english Whether or not the texture rectangle is rotated.
     * @~chinese 是否旋转纹理。
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    virtual bool initWithTexture(Texture2D *texture, const Rect& rect, bool rotated);

    /**@~english
     * Initializes a sprite with an SpriteFrame. The texture and rect in SpriteFrame will be applied on this sprite.
     *
     * @~chinese 
     * 使用指定的 SpriteFrame 初始化一个 Sprite。
     * 
     * @param   spriteFrame  @~english A SpriteFrame object. It should includes a valid texture and a rect.
     * @~chinese SpriteFrame 对象。它包括一个有效的纹理和矩形区域。
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    virtual bool initWithSpriteFrame(SpriteFrame *spriteFrame);

    /**@~english
     * Initializes a sprite with an sprite frame name.
     *
     * A SpriteFrame will be fetched from the SpriteFrameCache by name.
     * If the SpriteFrame doesn't exist it will raise an exception.
     *
     * @~chinese 
     * 使用指定的 SpriteFrame 名称初始化一个 Sprite。
     * 
     * 首先从 SpriteFrameCache 中获取指定名称的 SpriteFrame。
     * 然后使用这个 SpriteFrame 初始化 Sprite。
     * 
     * @param   spriteFrameName  @~english A key string that can fected a valid SpriteFrame from SpriteFrameCache.
     * @~chinese 一个字符串，用于从 SpriteFrameCache 中获取 SpriteFrame 对象。
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     */
    virtual bool initWithSpriteFrameName(const std::string& spriteFrameName);

    /**@~english
     * Initializes a sprite with an image filename.
     *
     * This method will find filename from local file system, load its content to Texture2D,
     * then use Texture2D to create a sprite.
     * After initialization, the rect used will be the size of the image. The offset will be (0,0).
     *
     * @~chinese 
     * 使用指定的图片文件初始化一个 Sprite。
     * 
     * 该方法将从本地文件系统中找到文件，将其加载为 Texture2D 对象，
     * 然后使用 Texture2D 对象初始化 Sprite。
     * 初始化后，Sprite 大小与图片大小一致，偏移量为 (0,0)。
     * 
     * @param   filename @~english The path to an image file in local file system.
     * @~chinese 图片文件的路径。
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     * @lua     init
     */
    virtual bool initWithFile(const std::string& filename);

    /**@~english
     * Initializes a sprite with an image filename, and a rect.
     *
     * This method will find filename from local file system, load its content to Texture2D,
     * then use Texture2D to create a sprite.
     * After initialization, the offset will be (0,0).
     *
     * @~chinese 
     * 使用指定图片文件的特定矩形区域初始化一个 Sprite。
     * 
     * 该方法将从本地文件系统中找到文件，将其加载为 Texture2D 对象，
     * 然后使用 Texture2D 对象初始化 Sprite。
     * 初始化后，Sprite 大小与图片大小一致，偏移量为 (0,0)。
     * 
     * @param   filename @~english The path to an image file in local file system.
     * @~chinese 图片文件的路径。
     * @param   rect        @~english The rectangle assigned the content area from texture.
     * @~chinese 需要从图片中截取的矩形区域。
     * @return  @~english True if the sprite is initialized properly, false otherwise.
     * @~chinese 如果初始化成功，返回 true；否则返回 false。
     * @lua     init
     */
    virtual bool initWithFile(const std::string& filename, const Rect& rect);

    void debugDraw(bool on);
    
    /**
     * returns a copy of the polygon information associated with this sprite
     * because this is a copy process it is slower than getting the reference, so use wisely
     *
     * @return a copy of PolygonInfo
     */
    PolygonInfo getPolygonInfo() const;
    
    /**
     * set the sprite to use this new PolygonInfo
     *
     * @param PolygonInfo the polygon information object
     */
    void setPolygonInfo(const PolygonInfo& info);
protected:

    void updateColor() override;
    virtual void setTextureCoords(Rect rect);
    virtual void updateBlendFunc();
    virtual void setReorderChildDirtyRecursively();
    virtual void setDirtyRecursively(bool value);


    
    //
    // Data used when the sprite is rendered using a SpriteSheet
    //
    TextureAtlas*       _textureAtlas;      /// SpriteBatchNode texture atlas (weak reference)
    ssize_t             _atlasIndex;        /// Absolute (real) Index on the SpriteSheet
    SpriteBatchNode*    _batchNode;         /// Used batch node (weak reference)

    bool                _dirty;             /// Whether the sprite needs to be updated
    bool                _recursiveDirty;    /// Whether all of the sprite's children needs to be updated
    bool                _shouldBeHidden;    /// should not be drawn because one of the ancestors is not visible
    Mat4              _transformToBatch;

    //
    // Data used when the sprite is self-rendered
    //
    BlendFunc        _blendFunc;            /// It's required for TextureProtocol inheritance
    Texture2D*       _texture;              /// Texture2D object that is used to render the sprite
    SpriteFrame*     _spriteFrame;
    TrianglesCommand _trianglesCommand;     ///


    //
    // Shared data
    //

    // texture
    Rect _rect;                             /// Retangle of Texture2D
    bool   _rectRotated;                    /// Whether the texture is rotated

    // Offset Position (used by Zwoptex)
    Vec2 _offsetPosition;
    Vec2 _unflippedOffsetPositionFromCenter;

    // vertex coords, texture coords and color info
    V3F_C4B_T2F_Quad _quad;
    PolygonInfo  _polyInfo;

    // opacity and RGB protocol
    bool _opacityModifyRGB;

    // image is flipped
    bool _flippedX;                         /// Whether the sprite is flipped horizontally or not
    bool _flippedY;                         /// Whether the sprite is flipped vertically or not

    bool _insideBounds;                     /// whether or not the sprite was inside bounds the previous frame
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Sprite);
};


// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __SPRITE_NODE_CCSPRITE_H__
