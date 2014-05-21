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

#include "2d/CCNode.h"
#include "2d/CCProtocols.h"
#include "2d/CCTextureAtlas.h"
#include "base/ccTypes.h"
#include <string>
#ifdef EMSCRIPTEN
#include "CCGLBufferedNode.h"
#endif // EMSCRIPTEN
#include "physics/CCPhysicsBody.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class SpriteBatchNode;
class SpriteFrame;
class Animation;
class Rect;
class Size;
class Texture2D;
struct transformValues_;

/**
 * @addtogroup sprite_nodes
 * @{
 */

/**
 * Sprite定义为二维图像 ( 参见：http://en.wikipedia.org/wiki/Sprite_(computer_graphics) )
 *
 * 可以通过一个图像或一个图像的矩形裁剪部分创建Sprite
 *
 * 为了优化Sprite渲染，请遵循以下最佳用法：
 *
 *  - 所有Sprite放入同一个SpriteSheet (http://www.codeandweb.com/what-is-a-sprite-sheet)
 *  - 所有Sprite使用相同的渲染混合函数(BlendFunc)
 *  - 使得渲染器(Renderer)自动批量处理("batch")Sprite (将会在一次OpenGL调用内绘制完成)
 *
 *  为了获得额外5%~10%的渲染优化效果，你可以把Sprite作为子节点加入到SpriteBatchNode中，
 *  但这么做有以下限制：
 *
 *  - Alias/Antialias属性属于SpriteBatchNode，不能单独设置Sprite的Alias属性。
 *  - 渲染混合函数(BlendFunc)属于SpriteBatchNode，不能单独设置Sprite的渲染混合函数(BlendFunc)。
 *  - 不支持ParallaxNode，不过可以使用代理("proxy")Sprite模拟实现。
 *  - Sprite的子节点只能是其它Sprite(或Sprite的子类)
 *
 * Sprite的默认锚点(anchorPoint)为(0.5, 0.5)。
 */
class CC_DLL Sprite : public Node, public TextureProtocol
{
public:

    static const int INDEX_NOT_INITIALIZED = -1; /// Sprite invalid index on the SpriteBatchNode

    /// @{
    /// @name Creators

    /**
     * 创建一个无纹理Sprite，可以在创建后调用setTexture方法设置纹理。
     *
     * @return 自动释放的Sprite对象
     */
    static Sprite* create();

    /**
     * 指定图像文件名创建Sprite
     *
     * 创建之后，Sprite的尺寸大小与图像相同，且偏移被置为(0,0)。
     *
     * @param   filename 包含路径的图像文件名，比如"scene1/monster.png"
     * @return  自动释放的Sprite对象
     */
    static Sprite* create(const std::string& filename);

    /**
     * 指定图像文件名及Rect参数创建Sprite
     *
     * @param   filename 包含路径的图像文件名，比如"scene1/monster.png"
     * @param   rect     图像文件裁剪矩形框，仅位于rect矩形框内的图像内容被应用于此Sprite
     * @return  An 自动释放的Sprite对象
     */
    static Sprite* create(const std::string& filename, const Rect& rect);

    /**
     * 指定Texture2D纹理对象创建Sprite
     *
     * 创建之后，Sprite的尺寸大小与纹理对象相同，且偏移被置为(0,0)。
     *
     * @param   texture    Texture2D纹理对象指针
     * @return  自动释放的Sprite对象
     */
    static Sprite* createWithTexture(Texture2D *texture);

    /**
     * 指定Texture2D纹理对象及Rect参数创建Sprite
     *
     * 创建之后，Sprite偏移被置为(0,0)。
     *
     * @param   texture    Texture2D纹理对象指针
     *                      多个Sprite可使用同一个Texture2D纹理对象
     * @param   rect        图像文件裁剪矩形框，仅位于rect矩形框内的纹理内容被应用于此Sprite
     * @param   rotated     rect矩形框是否旋转
     * @return  自动释放的Sprite对象
     */
    static Sprite* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated=false);

    /**
     * 指定Sprite帧(SpriteFrame)创建Sprite
     *
     * @param   spriteFrame    Sprite帧，包括了纹理(texture)和裁剪矩形框(rect)属性
     * @return  自动释放的Sprite对象
     */
    static Sprite* createWithSpriteFrame(SpriteFrame *spriteFrame);

    /**
     * 指定Sprite帧名称创建Sprite
     *
     * 通过指定的spriteFrameName参数从SpriteFrameCache中提取SpriteFrame，如SpriteFrame不存在将抛出异常。
     *
     * @param   spriteFrameName Sprite帧名称，参数类型为以null结尾的字符串
     * @return  自动释放的Sprite对象
     */
    static Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);

    /// @}  end of creators group


    /// @{
    /// @name BatchNode methods

    /**
     * 根据旋转、位置、缩放比例值更新quad数据。
     */
    virtual void updateTransform(void);

    /**
     * 如果Sprite已经加入SpriteBatchNode返回SpriteBatchNode对象。
     *
     * @return 如果Sprite已经加入SpriteBatchNode返回SpriteBatchNode对象，否则返回空指针。
     */
    virtual SpriteBatchNode* getBatchNode(void);
    /**
     * 设置SpriteBatchNode对象。
     * @warning 不推荐手工调用此方法，可参照以下示例代码使用SpriteBatchNode
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

    /** 指定图像文件名重新设置Sprite纹理(texture)。
     方法内会同时调用setTextureRect设置Sprite的尺寸。
     TODO: The whole Sprite API needs to be reviewed.
     */
    virtual void setTexture(const std::string &filename );

    /** 指定Texture2D纹理对象重新设置Sprite纹理(texture)。
     纹理(texture)的矩形尺寸大小不会发生改变。
     */
    virtual void setTexture(Texture2D *texture) override;

    /** 返回Sprite当前使用的Texture2D纹理对象 */
    virtual Texture2D* getTexture() const override;

    /**
     * 设置Sprite纹理(texture)的Rect尺寸。
     * 通过调用setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize)实现，其中入参为：\p rotated = false, \p utrimmedSize = rect.size.
     */
    virtual void setTextureRect(const Rect& rect);

    /**
     * 设置Sprite纹理(texture)的Rect尺寸(rect)、 是否旋转(rotated)、裁剪尺寸(untrimmedSize)。
     * 调用此方法会修改纹理(texture)的坐标和顶点位置。
     */
    virtual void setTextureRect(const Rect& rect, bool rotated, const Size& untrimmedSize);

    /**
     * 设置Sprite的顶点Rect。
     * 此方法由setTextureRect内部调用，用于在视网膜屏(Retina Display)上显示2倍大小的标清图像。
     * 不能手工调用此方法，应该调用setTextureRect实现相应的功能。
     */
    virtual void setVertexRect(const Rect& rect);

    /**
     * 通过指定的spriteFrameName参数设置新的Sprite帧(SpriteFrame)。
     */
    virtual void setSpriteFrame(const std::string &spriteFrameName);

    /**
     * 设置新的Sprite帧(SpriteFrame)。
     */
    virtual void setSpriteFrame(SpriteFrame* newFrame);

    /** @deprecated 使用`setSpriteFrame()`方法替代 */
    CC_DEPRECATED_ATTRIBUTE virtual void setDisplayFrame(SpriteFrame *newFrame) { setSpriteFrame(newFrame); }

    /**
     * 返回指定的Sprite帧(SpriteFrame)是否正在显示。
     */
    virtual bool isFrameDisplayed(SpriteFrame *pFrame) const;

    /**
     * 返回当前正在显示的Sprite帧(SpriteFrame)。
     */
    virtual SpriteFrame* getSpriteFrame() const;
    /** @deprecated 使用`getSpriteFrame()`方法替代 */
    CC_DEPRECATED_ATTRIBUTE virtual SpriteFrame* getDisplayFrame() const { return getSpriteFrame(); }
    /** @deprecated 使用`getSpriteFrame()`方法替代 */
    CC_DEPRECATED_ATTRIBUTE virtual SpriteFrame* displayFrame() const { return getSpriteFrame(); };

    /// @} End of frames methods


    /// @{
    /// @name Animation methods
    /**
     * 指定动画名称(animationName)和帧索引(frameIndex)修改要显示的帧，动画名称从AnimationCache中获取。
     */
    virtual void setDisplayFrameWithAnimationName(const std::string& animationName, ssize_t frameIndex);
    /// @}


    /// @{
    /// @name Sprite Properties' setter/getters

    /**
     * 判断Sprite在Atlas中是否需要更新。
     *
     * @return 如Sprite在Atlas中需要更新返回true，否则返回false。
     */
    virtual bool isDirty(void) const { return _dirty; }

    /**
     * 设置Sprite在Atlas中是否需要更新
     */
    virtual void setDirty(bool dirty) { _dirty = dirty; }

    /**
     * 返回quad(纹理坐标，顶点坐标和颜色)信息。
     * @js  NA
     * @lua NA
     */
    inline V3F_C4B_T2F_Quad getQuad(void) const { return _quad; }

    /**
     * 返回纹理(texture)是否已经旋转。
     */
    inline bool isTextureRectRotated(void) const { return _rectRotated; }

    /**
     * 返回纹理集(TextureAtlas)的当前使用索引。
     */
    inline ssize_t getAtlasIndex(void) const { return _atlasIndex; }

    /**
     * 设置纹理集(TextureAtlas)的当前使用索引。
     * @warning 除非你了解调用此方法的影响，否则不要改变此值
     */
    inline void setAtlasIndex(ssize_t atlasIndex) { _atlasIndex = atlasIndex; }

    /**
     * 返回Sprite的Rect信息
     */
    inline const Rect& getTextureRect(void) { return _rect; }

    /**
     * 返回Sprite被SpriteBatchNode使用时纹理集(TextureAtlas)的弱引用
     */
    inline TextureAtlas* getTextureAtlas(void) { return _textureAtlas; }

    /**
     * 设置Sprite被SpriteBatchNode使用时纹理集(TextureAtlas)的弱引用
     */
    inline void setTextureAtlas(TextureAtlas *pobTextureAtlas) { _textureAtlas = pobTextureAtlas; }

    /**
     * 返回Sprite的偏移位置，像Zwoptex一样由编辑器自动计算。
     */
    inline const Vec2& getOffsetPosition(void) const { return _offsetPosition; }


    /**
     * 返回Sprite是否水平翻转。
     *
     * 返回结果只表明Sprite纹理(texture)是否翻转，而不是Sprite子节点的纹理(texture)是否翻转。
     * 此外，翻转纹理(texture)不会改变锚点(anchorPoint)。
     * 如果需要同时翻转锚点(anchorPoint)，和/或同时翻转Sprite子节点，可使用以下方法实现:
     * sprite->setScaleX(sprite->getScaleX() * -1);
     *
     * @return 如Sprite已水平翻转返回true，否则返回false。
     */
    bool isFlippedX(void) const;
    /**
     * 设置Sprite是否水平翻转。
     *
     * @param flippedX 如设置水平翻转传入true，否则传入false。
     */
    void setFlippedX(bool flippedX);

    /** @deprecated 使用isFlippedX()替代
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE bool isFlipX() { return isFlippedX(); };
    /** @deprecated 使用setFlippedX()替代 */
    CC_DEPRECATED_ATTRIBUTE void setFlipX(bool flippedX) { setFlippedX(flippedX); };

    /**
     * 返回Sprite是否垂直翻转。
     *
     * 返回结果只表明Sprite纹理(texture)是否翻转，而不是Sprite子节点的纹理(texture)是否翻转。
     * 此外，翻转纹理(texture)不会改变锚点(anchorPoint)。
     * 如果需要同时翻转锚点(anchorPoint)，和/或同时翻转Sprite子节点，可使用以下方法实现:
     * sprite->setScaleY(sprite->getScaleY() * -1);
     *
     * @return 如Sprite已垂直翻转返回true，否则返回false。
     */
    bool isFlippedY(void) const;
    /**
     * 设置Sprite是否垂直翻转。
     *
     * @param flippedY 如设置垂直翻转传入true，否则传入false。
     */
    void setFlippedY(bool flippedY);

    /// @} End of Sprite properties getter/setters

    /** @deprecated 使用isFlippedY()替代 */
    CC_DEPRECATED_ATTRIBUTE bool isFlipY() { return isFlippedY(); };
    /** @deprecated 使用setFlippedY()替代 */
    CC_DEPRECATED_ATTRIBUTE void setFlipY(bool flippedY) { setFlippedY(flippedY); };

    //
    // Overrides
    //
    /// @{
    /// @name Functions inherited from TextureProtocol
    /**
    *@code
    *当此函数绑定到js或lua时，函数参数将被改变
    *js函数声明: var setBlendFunc(var src, var dst)
    *lua函数声明: local setBlendFunc(local src, local dst)
    *@endcode
    */
    inline void setBlendFunc(const BlendFunc &blendFunc) override { _blendFunc = blendFunc; }
    /**
    * @js  NA
    * @lua NA
    */
    inline const BlendFunc& getBlendFunc() const override { return _blendFunc; }
    /// @}

    virtual std::string getDescription() const override;

    /// @{
    /// @name Functions inherited from Node
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
    virtual void sortAllChildren() override;
    virtual void setScale(float scale) override;
    virtual void setPositionZ(float positionZ) override;
    virtual void setAnchorPoint(const Vec2& anchor) override;
    virtual void ignoreAnchorPointForPosition(bool value) override;
    virtual void setVisible(bool bVisible) override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    virtual void setOpacityModifyRGB(bool modify) override;
    virtual bool isOpacityModifyRGB(void) const override;
    /// @}

CC_CONSTRUCTOR_ACCESS:

    Sprite(void);
    virtual ~Sprite(void);

    /** 对未初始化的空Sprite执行初始化操作。 */
    virtual bool init(void);

    /**
     * 指定Texture2D纹理初始化Sprite。
     *
     * 初始化之后，Sprite的尺寸大小与纹理对象相同，且偏移被置为(0,0)。
     *
     * @param   texture    Texture2D纹理对象指针
     *                      多个Sprite可使用同一个Texture2D纹理对象
     * @return  Sprite正确初始化返回true，否则返回false。
     */
    virtual bool initWithTexture(Texture2D *texture);

    /**
     * 指定Texture2D纹理对象及Rect参数初始化Sprite。
     *
     * 初始化之后，Sprite偏移被置为(0,0)。
     *
     * @param   texture    Texture2D纹理对象指针
     *                      多个Sprite可使用同一个Texture2D纹理对象
     * @param   rect        图像文件裁剪矩形框，仅位于rect矩形框内的纹理内容被应用于此Sprite
     * @return  Sprite正确初始化返回true，否则返回false。
     */
    virtual bool initWithTexture(Texture2D *texture, const Rect& rect);

    /**
     * 指定Texture2D纹理对象、Rect参数及是否旋转初始化Sprite。
     *
     * 初始化之后，Sprite偏移被置为(0,0)。
     * @note    这是特定用途的初始化方法。
     *
     * @param   texture    Texture2D对象，该对象纹理(texture)将用于Sprite。
     * @param   rect        指定纹理的内容的Rect矩形框。
     * @param   rotated     纹理矩形框是否旋转。
     * @return  Sprite正确初始化返回true，否则返回false。
     */
    virtual bool initWithTexture(Texture2D *texture, const Rect& rect, bool rotated);

    /**
     * 指定SpriteFrame初始化Sprite，SpriteFrame中的纹理(texture)和Rect参数将被用于此Sprite。
     *
     * @param   pSpriteFrame  SpriteFrame对象，包括了纹理(texture)和裁剪矩形框(rect)属性
     * @return  Sprite正确初始化返回true，否则返回false。
     */
    virtual bool initWithSpriteFrame(SpriteFrame *pSpriteFrame);

    /**
     * 指定Sprite帧名称初始化Sprite。
     *
     * 通过指定的spriteFrameName参数从SpriteFrameCache中提取SpriteFrame，如SpriteFrame不存在将抛出异常。
     *
     * @param   spriteFrameName  可以从SpriteFrameCache中提取SpriteFrame的关键字
     * @return  Sprite正确初始化返回true，否则返回false。
     */
    virtual bool initWithSpriteFrameName(const std::string& spriteFrameName);

    /**
     * 指定图像文件初始化Sprite。
     *
     * 此方法从本地文件系统查找该文件并使用Texture2D加载文件内容，然后使用Texture2D对象创建Sprite。
     * 初始化之后，Sprite的尺寸大小与图像相同，且偏移被置为(0,0)。
     *
     * @param   filename 本地文件系统中的含路径图像文件名
     * @return  Sprite正确初始化返回true，否则返回false。
     * @js      init
     * @lua     init
     */
    virtual bool initWithFile(const std::string& filename);

    /**
     * 指定图像文件名及Rect参数初始化Sprite。
     *
     * 此方法从本地文件系统查找该文件并使用Texture2D加载文件内容，然后使用Texture2D对象创建Sprite。
     * 初始化之后，Sprite偏移被置为(0,0)。
     *
     * @param   filename 本地文件系统中的含路径图像文件名。
     * @param   rect        指定纹理的内容区域的Rect矩形框。
     * @return  Sprite正确初始化返回true，否则返回false。
     * @js      init
     * @lua     init
     */
    virtual bool initWithFile(const std::string& filename, const Rect& rect);

protected:

    void updateColor(void);
    virtual void setTextureCoords(Rect rect);
    virtual void updateBlendFunc(void);
    virtual void setReorderChildDirtyRecursively(void);
    virtual void setDirtyRecursively(bool bValue);

    //
    // Data used when the sprite is rendered using a SpriteSheet
    //
    TextureAtlas*       _textureAtlas;      /// SpriteBatchNode纹理集(弱引用)
    ssize_t             _atlasIndex;        /// SpriteSheet绝对(实际)索引
    SpriteBatchNode*    _batchNode;         /// Sprite已加入的SpriteBatchNode(弱引用)

    bool                _dirty;             /// Sprite是否需要更新
    bool                _recursiveDirty;    /// Sprite的所有子节点是否需要更新
    bool                _shouldBeHidden;    /// 不能被绘制，因为Sprite的其中一个祖先不可见
    Mat4              _transformToBatch;

    //
    // Data used when the sprite is self-rendered
    //
    BlendFunc        _blendFunc;            /// TextureProtocol继承使用
    Texture2D*       _texture;              /// 用于渲染Sprite的Texture2D对象
    QuadCommand      _quadCommand;          /// quad命令
#if CC_SPRITE_DEBUG_DRAW
    CustomCommand   _customDebugDrawCommand;
    void drawDebugData();
#endif //CC_SPRITE_DEBUG_DRAW
    //
    // Shared data
    //

    // texture
    Rect _rect;                             /// Texture2D矩形框
    bool   _rectRotated;                    /// 纹理是否旋转

    // Offset Position (used by Zwoptex)
    Vec2 _offsetPosition;
    Vec2 _unflippedOffsetPositionFromCenter;

    // vertex coords, texture coords and color info
    V3F_C4B_T2F_Quad _quad;

    // opacity and RGB protocol
    bool _opacityModifyRGB;

    // image is flipped
    bool _flippedX;                         /// Sprite是否水平旋转
    bool _flippedY;                         /// Sprite是否垂直旋转

    bool _insideBounds;                     /// Sprite是否在前一帧的边界范围内
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Sprite);
};


// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __SPRITE_NODE_CCSPRITE_H__
