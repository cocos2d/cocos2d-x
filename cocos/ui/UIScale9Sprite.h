/****************************************************************************
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

#ifndef __cocos2d_libs__UIScale9Sprite__
#define __cocos2d_libs__UIScale9Sprite__

#include "2d/CCNode.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteBatchNode.h"
#include "platform/CCPlatformMacros.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN
namespace ui {
    
    /**
     * @class Scale9Sprite
     * @brief @~english A 9-slice sprite for cocos2d-x.
     *
     * 9-slice scaling allows you to specify how scaling is applied
     * to specific areas of a sprite. With 9-slice scaling (3x3 grid),
     * you can ensure that the sprite does not become distorted when
     * scaled.
     * @~chinese 九宫格精灵，九宫格缩放能让你指定精灵指定区域的缩放，通过设置九宫格(3*3网格)，便可确保
     * 精灵在缩放时不错位
     * Note: @~english When you set _scale9Enabled to false,
     * then you could call `scale9Sprite->getSprite()` to return the inner Sprite pointer.
     * Then you could call any methods of Sprite class with the return pointers.
     * @~chinese 当你设置_scale9Enabled为false之后，你就可以通过调用`scale9Sprite->getSprite()`获得内部的Sprite对象指针，
     * 并可用该指针进行任何Sprite对象支持的操作
     */
    class CC_GUI_DLL Scale9Sprite : public Node , public cocos2d::BlendProtocol
    {
    public:
        /**
         * @~english Default constructor.
         * @~chinese 默认构造函数
         * @js ctor
         * @lua new
         */
        Scale9Sprite();

        /**
         * @~english Default destructor.
         * @~chinese 默认析构函数
         * @js NA
         * @lua NA
         */
        virtual ~Scale9Sprite();
        
        /**
         * @~english Builtin shader state.
         * Currenly support Normal and Gray state.
         * @~chinese 内建着色器状态，目前支持普通着色以及灰阶着色
         */
        enum class State
        {
            NORMAL,
            GRAY
        };
        
    public:
        
        /**
         * @brief @~english Create an empty Scale9Sprite.
         * @~chinese 创建一个空的九宫格精灵
         * @return @~english A Scale9Sprite instance.
         * @~chinese 九宫格精灵示例
         */
        static Scale9Sprite* create();
        
        /**
         * @~english Creates a 9-slice sprite with a texture file, a delimitation zone and
         * with the specified cap insets.
         * @~chinese 通过给定的纹理文件路径，定界区以及指定的cap insets来创建九宫格精灵
         * @see initWithFile(const char *file, const Rect& rect, const Rect& capInsets)
         * @param file @~english A texture file name.
         * @~chinese 纹理文件的路径
         * @param rect @~english A delimitation zone.
         * @~chinese 定界区
         * @param capInsets @~english A specified cap insets.
         * @~chinese 指定的cap insets
         * @return @~english A Scale9Sprite instance.
         * @~chinese 被创建的九宫格对象
         */
        static Scale9Sprite* create(const std::string& file, const Rect& rect,  const Rect& capInsets);
        
        /**
         * @~english Creates a 9-slice sprite with a texture file. The whole texture will be
         * broken down into a 3×3 grid of equal blocks.
         * @~chinese 通过指定的纹理文件以及capInsests，创建一个九宫格精灵，整个纹理将会被分割成
         * 3*3等大网格
         * @see initWithFile(const Rect& capInsets, const char *file)
         * @param capInsets @~english A specified cap insets.
         * @~chinese 指定的cap insets
         * @param file @~english A texture file name.
         * @~chinese 纹理文件路径
         * @return @~english A Scale9Sprite instance.
         * @~chinese 被创建的九宫格精灵对象
         */
        static Scale9Sprite* create(const Rect& capInsets, const std::string& file);
        
        /**
         * @~english Creates a 9-slice sprite with a texture file and a delimitation zone. The
         * texture will be broken down into a 3×3 grid of equal blocks.
         * @~chinese 通过指定纹理文件已经定界区去创建九宫格精灵，纹理将会被分割成
         * 3*3的等大网格
         * @see initWithFile(const char *file, const Rect& rect)
         * @param file @~english A texture file name.
         * @~chinese 指定纹理文件的路径
         * @param rect A delimitation zone.
         * @~chinese 分割区域
         * @return A Scale9Sprite instance.
         * @~chinese 九宫格精灵对象
         */
        static Scale9Sprite* create(const std::string& file, const Rect& rect);
        
        /**
        * @~english Creates a 9-slice sprite with a texture file. The whole texture will be
        * broken down into a 3×3 grid of equal blocks.
        * @~chinese 通过指定的纹理文件，创建一个九宫格精灵，整个纹理将会被分割成
        * 3*3等大网格
        * @see initWithFile( const char *file)
        * @param file @~english A texture file name.
        * @~chinese 纹理文件路径
        * @return @~english A Scale9Sprite instance.
        * @~chinese 被创建的九宫格精灵对象
        */
        static Scale9Sprite* create(const std::string& file);
        
        /**
         * @~english Creates a 9-slice sprite with an sprite frame.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinese 通过指定的精灵帧来创建九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * @see initWithSpriteFrame(SpriteFrame *spriteFrame)
         * @param spriteFrame  @~english A sprite frame pointer.
         * @~chinese 精灵帧指针
         * @return @~english A Scale9Sprite instance.
         * @~chinese 被创建的九宫格对象
         */
        static Scale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame);
        
        /**
        * @~english Creates a 9-slice sprite with an sprite frame and capInsets.
        * Once the sprite is created, you can then call its "setContentSize:" method
        * to resize the sprite will all it's 9-slice goodness intract.
        * It respects the anchorPoint too.
        * @~chinese 通过指定的精灵帧以及capInsets来创建九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
        * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
        * @see initWithSpriteFrame(SpriteFrame *spriteFrame)
        * @param spriteFrame  @~english A sprite frame pointer.
        * @~chinese 精灵帧指针
        * @param capInsets @~english The capInsets
        * @~chinese capInsets
        * @return @~english A Scale9Sprite instance.
        * @~chinese 被创建的九宫格对象
        */
        static Scale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);
        
        /**
        * @~english Creates a 9-slice sprite with an sprite frame's name.
        * Once the sprite is created, you can then call its "setContentSize:" method
        * to resize the sprite will all it's 9-slice goodness intract.
        * It respects the anchorPoint too.
        * @~chinese 通过指定的精灵帧的名称来创建九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
        * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
        * @see initWithSpriteFrame(SpriteFrame *spriteFrame)
        * @param spriteFrameName  @~english A sprite frame pointer.
        * @~chinese 精灵帧的名称
        * @return @~english A Scale9Sprite instance.
        * @~chinese 被创建的九宫格对象
        */
        static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);
        
        /**
        * @~english Creates a 9-slice sprite with an sprite frame's name and capInsets.
        * Once the sprite is created, you can then call its "setContentSize:" method
        * to resize the sprite will all it's 9-slice goodness intract.
        * It respects the anchorPoint too.
        * @~chinese 通过指定的精灵帧的名称以及capInsets来创建九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
        * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
        * @see initWithSpriteFrame(SpriteFrame *spriteFrame)
        * @param spriteFrameName  @~english A sprite frame pointer.
        * @~chinese 精灵帧指针
        * @param capInsets @~english The values to use for the cap insets.
        * @~chinese 指定的 capinsets
        * @return @~english A Scale9Sprite instance.
        * @~chinese 被创建的九宫格对象
        */
        static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);
        
        /**
         * @~english Initializes a 9-slice sprite with a texture file, a delimitation zone and
         * with the specified cap insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinese 通过指定的纹理文件以及capInsets以及界定区来初始化九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * @param file @~english The name of the texture file.
         * @~chinese 纹理文件名称
         * @param rect @~english The rectangle that describes the sub-part of the texture that
         * is the whole image. If the shape is the whole texture, set this to the
         * texture's full rect.
         * @~chinese 纹理的子矩形，用以界定需要渲染的部分，如果需要渲染整张纹理，则设置成纹理尺寸的大小
         * @param capInsets @~english The values to use for the cap insets.
         * @~chinese 指定的 capinsets
         * @return @~english True if initialize success, false otherwise.
         * @~chinese 初始化成功返回true，反之返回false
         */
        virtual bool initWithFile(const std::string& file, const Rect& rect,  const Rect& capInsets);
        
        /**
        * @~english Initializes a 9-slice sprite with a texture file, a delimitation zone.
        * Once the sprite is created, you can then call its "setContentSize:" method
        * to resize the sprite will all it's 9-slice goodness intract.
        * It respects the anchorPoint too.
        * @~chinese 通过指定的纹理文件以及界定区来初始化九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
        * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
        * @param file @~english The name of the texture file.
        * @~chinese 纹理文件名称
        * @param rect @~english The rectangle that describes the sub-part of the texture that
        * is the whole image. If the shape is the whole texture, set this to the
        * texture's full rect.
        * @~chinese 纹理的子矩形，用以界定需要渲染的部分，如果需要渲染整张纹理，则设置成纹理尺寸的大小
        * @return @~english True if initialize success, false otherwise.
        * @~chinese 初始化成功返回true，反之返回false
        */
        virtual bool initWithFile(const std::string& file, const Rect& rect);
        
        /**
        * @~english Initializes a 9-slice sprite with a texture file and
        * with the specified cap insets.
        * Once the sprite is created, you can then call its "setContentSize:" method
        * to resize the sprite will all it's 9-slice goodness intract.
        * It respects the anchorPoint too.
        * @~chinese 通过指定的纹理文件以及capInsets以及界定区来初始化九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
        * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
        * @param file @~english The name of the texture file.
        * @~chinese 纹理文件名称
        * @param capInsets @~english The values to use for the cap insets.
        * @~chinese 指定的 capinsets
        * @return @~english True if initialize success, false otherwise.
        * @~chinese 初始化成功返回true，反之返回false
        */
        virtual bool initWithFile(const Rect& capInsets, const std::string& file);
        
        /**
         * @~english Initializes a 9-slice sprite with a texture file. The whole texture will be
         * broken down into a 3×3 grid of equal blocks.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinese 通过指定的纹理文件来初始化九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * @param file @~english The name of the texture file.
         * @~chinese 纹理文件的路径
         * @return @~english True if initializes success, false otherwise.
         * @~chinese 如果初始化成功返回true，反之返回false
         */
        virtual bool initWithFile(const std::string& file);
        
        /**
         * @~english Initializes a 9-slice sprite with an sprite frame and with the specified
         * cap insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinese 通过指定的精灵帧以及指定的cap insets，来初始化一个九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * @param spriteFrame @~english The sprite frame object.
         * @~chinese 指定的精灵帧对象
         * @param capInsets @~english The values to use for the cap insets.
         * @~chinese 指定的cap insets
         * @return @~english True if initializes success, false otherwise.
         * @~chinese 初始化成功返回true，反之返回false
         */
        virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);
        
        /**
         * @~english Initializes a 9-slice sprite with an sprite frame.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinese 通过指定的精灵帧来初始化一个九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * @param spriteFrame @~english The sprite frame object.
         * @~chinese 指定的精灵帧对象
         * @return @~english True if initializes success, false otherwise.
         * @~chinese 初始化成功返回true，反之返回false
         */
        virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame);
        
        /**
         * @~english Initializes a 9-slice sprite with an sprite frame name and with the specified
         * cap insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinese 通过精灵帧的名称以及指定的cap insets来初始化一个九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * @param spriteFrameName @~english The sprite frame name.
         * @~chinese 指定的精灵帧对象的名称
         * @param capInsets @~english The values to use for the cap insets.
         * @~chinese 指定的cap insets
         * @return @~english True if initializes success, false otherwise.
         * @~chinese 初始化成功返回true，反之返回false
         */
        virtual bool initWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);
        
        /**
         * @~english Initializes a 9-slice sprite with an sprite frame name.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinese 通过一个精灵帧的名称来初始化九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * @param spriteFrameName @~english The sprite frame name.
         * @~chinese 指定的精灵帧名称
         * @return @~english True if initializes success, false otherwise.
         * @~chinese 初始化成功返回true，反之返回false
         */
        virtual bool initWithSpriteFrameName(const std::string& spriteFrameName);
        
        //override function
        virtual bool init() override;

        /**
         * @brief @~english Initializes a 9-slice sprite with an sprite instance.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinese 通过一个精灵对象来初始化一个九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * @param sprite @~english The sprite instance.
         * @~chinese 精灵的实例
         * @param rect @~english A delimitation zone.
         * @~chinese 定界区
         * @param rotated @~english Whether the sprite is rotated or not.
         * @~chinese 这个精灵是否旋转
         * @param capInsets @~english The values to use for the cap insets.
         * @~chinese 指定的cap insets
         * @return @~english True if initializes success, false otherwise.
         * @~chinese 初始化成功返回true，反之返回false
         */
        virtual bool init(Sprite* sprite, const Rect& rect, bool rotated, const Rect& capInsets);

        /**
         * @brief @~english Initializes a 9-slice sprite with an sprite instance.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinses 通过一个指定的精灵以及capInsets来创建九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         *
         * @param sprite @~english The sprite instance.
         * @~chinese 精灵的实例
         * @param rect @~english A delimitation zone.
         * @~chinese 定界区
         * @param capInsets @~english The values to use for the cap insets.
         * @~chinese 指定的cap insets
         * @return @~english True if initializes success, false otherwise.
         * @~chinese 初始化成功返回true，反之返回false
         */
        virtual bool init(Sprite* sprite, const Rect& rect, const Rect& capInsets);

        /**
         * @brief @~english Initializes a 9-slice sprite with an sprite instance and several parameters
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinses 通过一个精灵对象以及其他相关参数来初始化一个九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点
         * 
         * @param sprite @~english The sprite instance.
         * @~chinese 精灵对象
         * @param rect @~english A delimitation zone.
         * @~chinese 定界区
         * @param rotated @~english Whether the sprite is rotated or not.
         * @~chinese 确定精灵是否旋转
         * @param offset @~english The offset when slice the sprite.
         * @~chinese 切割精灵时的偏移量
         * @param originalSize @~english The original size of sprite.
         * @~chinese 精灵的原始大小
         * @param capInsets @~english The values to use for the cap insets.
         * @~chinese 指定的cap insets
         * @return @~english True if initializes success, false otherwise.
         * @~chinese 初始化成功返回true，反之返回false
         */
        virtual bool init(Sprite* sprite,
                          const Rect& rect,
                          bool rotated,
                          const Vec2 &offset,
                          const Size &originalSize,
                          const Rect& capInsets);
        
        /**
         * @brief Initializes a 9-slice sprite with a sprite batchnode.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @deprecated Use @see `init` instead.
         * @param batchnode A batch node pointer.
         * @param rect A delimitation zone.
         * @param rotated Whether the sprite in batch node is rotated or not.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
         CC_DEPRECATED(v3) virtual bool initWithBatchNode(SpriteBatchNode* batchnode,
                                                          const Rect& rect,
                                                          bool rotated,
                                                          const Rect& capInsets);
        /**
         * @brief @~english Initializes a 9-slice sprite with a sprite batch node.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         * @~chinsese 通过一个SpriteBatchNode对象来创建一个九宫格精灵，当精灵被创建后，调用"setContentSize:"方法时，
         * 将会受到九宫格缩放的影响，当然缩放同时也会遵从精灵的锚点，该方法已被废弃，不推荐使用
         * @deprecated Use @see `init` instead.
         * @param batchnode A batch node pointer.
         * @param rect A delimitation zone.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        CC_DEPRECATED(v3) virtual bool initWithBatchNode(SpriteBatchNode* batchnode, const Rect& rect, const Rect& capInsets);
        
        /**
         * @~english Sets the source blending function.
         * @~chinese 设置混合函数
         * @param blendFunc @~english A structure with source and destination factor to specify pixel arithmetic. e.g. {GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.
         * @~chinese 指定混合函数的结构体
         * @js NA
         * @lua NA
         */
        virtual void setBlendFunc(const BlendFunc &blendFunc) override;
        
        /**
         * @~english Returns the blending function that is currently being used.
         * @~chinese 获取当前使用的混合函数
         * @return @~english A BlendFunc structure with source and destination factor which specified pixel arithmetic.
         * @~chinese 当前使用混合函数的结构体
         * @js NA
         * @lua NA
         */
        virtual const BlendFunc &getBlendFunc() const override;

        /**
         * @~english Creates and returns a new sprite object with the specified cap insets.
         * You use this method to add cap insets to a sprite or to change the existing
         * cap insets of a sprite. In both cases, you get back a new image and the
         * original sprite remains untouched.
         * @~chinese 通过指定cap insets值创建并返回一个新的九宫格精灵，你可以使用这个方法向精灵添加
         * cap insets 或者是改变精灵中已有的cap insets，这两种情况下，你都会获得一个新的精灵，且原来的精灵
         * 将会保持无法触摸
         * @param capInsets @~english The values to use for the cap insets.
         * @~chinese 指定的capInsets
         * @return @~english A Scale9Sprite instance.
         * @~chinese 被创建的九宫格精灵
         */
        Scale9Sprite* resizableSpriteWithCapInsets(const Rect& capInsets) const;
        
        
        /**
         * @brief @~english Update Scale9Sprite with a specified sprite.
         * @~chinese 通过指定的精灵更新九宫格精灵
         * @param sprite @~english A sprite pointer.
         * @~chinese 精灵的指针
         * @param rect @~english A delimitation zone.
         * @~chinese 界定区域
         * @param rotated @~english Whether the sprite is rotated or not.
         * @~chinese 精灵是否旋转
         * @param capInsets @~english The Values to use for the cap insets.
         * @~chinese 指定的 capInsets 
         * @return @~english True if update success, false otherwise.
         * @~chinese 更新成功返回true，反之返回false
         * @js NA
         */
        virtual bool updateWithSprite(Sprite* sprite,
                                      const Rect& rect,
                                      bool rotated,
                                      const Rect& capInsets);

        /**
         * @brief @~english Update Scale9Sprite with a specified sprite.
         * @~chinese 通过指定的精灵更新九宫格精灵
         * @param sprite @~english A sprite pointer.
         * @~chinese 精灵的指针
         * @param rect @~english A delimitation zone.
         * @~chinese 限定区域
         * @param rotated @~english Whether the sprite is rotated or not.
         * @~chinese 决定精灵是否旋转
         * @param offset @~english The offset when slice the sprite.
         * @~chinese 分割精灵时的偏移量
         * @param originalSize @~english The origial size of the sprite.
         * @~chinese 精灵的原始尺寸
         * @param capInsets @~english The Values to use for the cap insets.
         * @~chinese 指定的cap insets
         * @return @~english True if update success, false otherwise.
         * @~chinese 更形成功返回true，反之返回false
         * @js NA
         */
        virtual bool updateWithSprite(Sprite* sprite,
                                      const Rect& rect,
                                      bool rotated,
                                      const Vec2 &offset,
                                      const Size &originalSize,
                                      const Rect& capInsets);

        /**
         * @brief @~english Update Scale9Sprite with a specified sprite.
         * @~chinese 通过指定的精灵更新九宫格精灵
         * @deprecated @~english Use @see `updateWithSprite` instead.
         * @~chinese 已废弃，请使用updateWithSprite 代替
         * @param sprite @~english A sprite pointer.
         * @~chinese 精灵的指针
         * @param originalRect @~english A delimitation zone.
         * @~chinese 限定区域的大小
         * @param rotated @~english Whether the sprite is rotated or not.、
         * @~chinese 精灵是否旋转
         * @param capInsets @~english The Values to use for the cap insets.
         * @~chinese 指定的cap insets
         * @return @~english True if update success, false otherwise.
         * @~chinese 如果更新成功返回true，反之返回false
         */
        CC_DEPRECATED(v3) bool updateWithBatchNode(SpriteBatchNode* batchnode,
                                                   const Rect& originalRect,
                                                   bool rotated,
                                                   const Rect& capInsets);

        
        /**
         * @brief @~english Change inner sprite's sprite frame.
         * @~chinese 改变内部精灵的精灵帧
         * @param spriteFrame @~english A sprite frame pointer.
         * @~chinese 精灵帧指针
         * @param capInsets @~english The values to use for the cap insets.
         * @~chinese 指定的cap insets
         */
        virtual void setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets = Rect::ZERO);
        
        // overrides
        virtual void setContentSize(const Size & size) override;
        virtual void setAnchorPoint(const Vec2& anchorPoint) override;
        
        /**
         * @~english Change the state of 9-slice sprite.
         * @~chinese  更改九宫格精灵的状态
         * @see `State`
         * @param state A enum value in State.
         * @~chinese 状态的枚举值
         * @since v3.4
         */
        void setState(State state);
        
        /**
         * @brief @~english Query the sprite's original size.
         * @~chinese 获取精灵的原始尺寸
         * @return @~english Sprite size.
         * @~chinese 精灵的尺寸
         */
        Size getOriginalSize() const;
        
        /**
         * @brief @~english Change the prefered size of Scale9Sprite.
         * @~chinese 改变九宫格的显示尺寸
         * @param size @~english A delimitation zone.
         * @~chinese 显示尺寸的界定区域
         */
        void setPreferredSize(const Size& size);
        
        /**
         * @brief @~english Query the  Scale9Sprite's prefered size.
         * @~chinese 获取九宫格精灵的显示尺寸
         * @return @~english Scale9Sprite's prefered size.
         * @~chinese 九宫格精灵的显示尺寸
         */
        Size getPreferredSize() const;
        
        /**
         * @brief Change the cap inset size.
         * @~chinese 改变cap inset的尺寸
         * @param rect A delimitation zone.
         * @~chinese cap inset的尺寸
         */
        void setCapInsets(const Rect& rect);
        
        /**
         * @brief @~english Query the Scale9Sprite's prefered size.
         * @~chinese 获取九宫格精灵的cap inset
         * @return @~english Scale9Sprite's cap inset.
         * @~chinese 九宫格精灵的cap insets
         */
        Rect getCapInsets()const;
        
        /**
         * @brief @~english Change the left sprite's cap inset.
         * @~chinese 设置左侧精灵的cap inset
         * @param leftInset @~english The values to use for the cap inset.
         * @~chinese 左侧精灵的cap inset
         */
        void setInsetLeft(float leftInset);
        
        /**
         * @brief @~english Query the left sprite's cap inset.
         * @~chinese 获取左侧精灵的cap inset
         * @return @~english The left sprite's cap inset.
         * @~chinese 左侧精灵的cap inset
         */
        float getInsetLeft()const;
        
        /**
         * @brief @~english Change the top sprite's cap inset.
         * @~chinese 设置顶部精灵的cap inset
         * @param topInset @~english The values to use for the cap inset.
         * @~chinese 顶部精灵的cap inset
         */
        void setInsetTop(float topInset);
        
        /**
         * @brief @~english Query the top sprite's cap inset.
         * @~chinese 获取顶部精灵的cap inset
         * @return @~english The top sprite's cap inset.
         * @~chinese 顶部精灵的cap inset
         */
        float getInsetTop()const;
        
        /**
         * @brief @~english Change the right sprite's cap inset.
         * @~chinese 设置右侧精灵的cap inset
         * @param rightInset @~english The values to use for the cap inset.
         * @~chinese 右侧精灵的cap inset
         */
        void setInsetRight(float rightInset);
        
        /**
         * @brief @~english Query the right sprite's cap inset.
         * @~chinese 获取右侧精灵的cap inset
         * @return @~english The right sprite's cap inset.
         * @~chinese 右侧精灵的cap inset
         */
        float getInsetRight()const;
        
        /**
         * @brief @~english Change the bottom sprite's cap inset.
         * @~chinese 设置底部精灵的cap inset
         * @param bottomInset @~english The values to use for the cap inset.
         * @~chinese 底部精灵的 cap insets
         */
        void setInsetBottom(float bottomInset);
        
        /**
         * @brief @~english Query the bottom sprite's cap inset.
         * @~chinese 获取底部精灵的cap inset
         * @return @~english The bottom sprite's cap inset.
         * @~chinese 底部精灵的cap inset
         */
        float getInsetBottom()const;
        
        /**
         * @brief @~english Toggle 9-slice feature.
         * If Scale9Sprite is 9-slice disabled, the Scale9Sprite will rendered as a normal sprite.
         * @~chinese 设置九宫格特性是否开启，若功能被禁用则将当成普通精灵一样的渲染
         * @param enabled @~english True to enable 9-slice, false otherwise.
         * @~chinese 设置成true将开启九宫格功能，反之设置false
         * @js NA
         */
        void setScale9Enabled(bool enabled);
        
        /**
         * @brief @~english Query whether the Scale9Sprite is enable 9-slice or not.
         * @~chinese 获取当前精灵是否开启了九宫格功能
         * @return @~english True if 9-slice is enabled, false otherwise.
         * @~chinese 开启九宫格功能返回true，反之返回false
         * @js NA
         */
        bool isScale9Enabled()const;
        
        /// @} end of Children and Parent
        
        virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
        virtual void cleanup() override;
        
        /**
         * @lua NA
         */
        virtual void onEnter() override;
        
        /** @~english Event callback that is invoked when the Node enters in the 'stage'.
         * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
         * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
         * @~chinese 当九宫格进入场景时被调用的事件回调，如果有过渡动画，则在过渡动画完成后调用
         * @js NA
         * @lua NA
         */
        virtual void onEnterTransitionDidFinish() override;
        
        /**
         * @~english Event callback that is invoked every time the Node leaves the 'stage'.
         * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
         * During onExit you can't access a sibling node.
         * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
         * @~chinese 当九宫格精灵离开场景时的事件回调，如果精灵在离开场景时有过渡动画，则在过渡动画完成后进行回调
         * @js NA
         * @lua NA
         */
        virtual void onExit() override;
        
        /**
         * @~english Event callback that is called every time the Node leaves the 'stage'.
         * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
         * @~chinese 当九宫格离开场景时触发的事件回调，如果精灵离开场景时有过渡动画，则在过渡动画开始时触发回调
         * @js NA
         * @lua NA
         */
        virtual void onExitTransitionDidStart() override;
        
        virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
        virtual void updateDisplayedColor(const Color3B& parentColor) override;
        virtual void disableCascadeColor() override;
        virtual void disableCascadeOpacity() override;
        
        
        /**
         * @brief @~english Get the original no 9-sliced sprite
         * @~chinese 获取原始的非九宫格精灵
         * @return @~english A sprite instance.
         * @~chinese 原始的精灵对象
         */
        Sprite* getSprite()const;
        
        /**
         * @~english Sets whether the widget should be flipped horizontally or not.
         * @~chinese 设置该空间是否要被水平翻转
         * @param flippedX @~english true if the widget should be flipped horizontally, false otherwise.
         * @~chinese 设置成true，则九宫格精灵将会水平翻转，反着设置为false
         */
        virtual void setFlippedX(bool flippedX);
        
        /**
         * @~english Returns the flag which indicates whether the widget is flipped horizontally or not.
         *
         * It only flips the texture of the widget, and not the texture of the widget's children.
         * Also, flipping the texture doesn't alter the anchorPoint.
         * If you want to flip the anchorPoint too, and/or to flip the children too use:
         * widget->setScaleX(sprite->getScaleX() * -1);
         * @~chinese 返回一个标志用以指明九宫格精灵是否发生了水平翻转，这个翻转仅会作用于其本身，而不会作用于其子节点，同时翻转后，不会改变精灵的锚点
         * @~chinese 如果你想将锚点也一起翻转请使用widget->setScaleX(sprite->getScaleX() * -1);
         * @return @~english True if the widget is flipped horizontally, false otherwise.
         * @~chinese 如果发生水平翻转返回true，反之返回false
         */
        virtual bool isFlippedX()const;
        
        /**
         * @~english Sets whether the widget should be flipped vertically or not.
         * @~chinese 设置该九宫格精灵是否要被竖直翻转
         * @param flippedY @~english true if the widget should be flipped vertically, false otherwise.
         * @~chinese 设置为true将发生竖直翻转，反之设置为false
         */
        virtual void setFlippedY(bool flippedY);

        /**
         * @~english Return the flag which indicates whether the widget is flipped vertically or not.
         * It only flips the texture of the widget, and not the texture of the widget's children.
         * Also, flipping the texture doesn't alter the anchorPoint.
         * If you want to flip the anchorPoint too, and/or to flip the children too use:
         * widget->setScaleY(widget->getScaleY() * -1);
         * @~chinese 返回一个标志位用以指明九宫格精灵是否发生了竖直翻转，但是不会作用到其子节点，也不会改变锚点，要改变这些请使用
         * widget->setScaleY(widget->getScaleY() * -1);
         * @return @~english True if the widget is flipped vertically, flase otherwise.
         * @~chinese 发生了竖直翻转返回true，反之返回false
         */
        virtual bool isFlippedY()const;
        
        //override the setScale function of Node
        virtual void setScaleX(float scaleX) override;
        virtual void setScaleY(float scaleY) override;
        virtual void setScale(float scale) override;
        virtual void setScale(float scaleX, float scaleY) override;
        using Node::setScaleZ;
        virtual float getScaleX() const override;
        virtual float getScaleY() const override;
        virtual float getScale() const override;
        using Node::getScaleZ;
        virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;
    protected:
        void updateCapInset();
        void updatePositions();
        void createSlicedSprites();
        void cleanupSlicedSprites();
        void adjustScale9ImagePosition();
        void applyBlendFunc();
        void updateBlendFunc(Texture2D *texture);
        /**
         * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
         * This approach can improves the performance massively.
         * @note Don't call this manually unless a child added needs to be removed in the same frame
         */
        virtual void sortAllProtectedChildren();
        
        bool _spritesGenerated;
        Rect _spriteRect;
        bool   _spriteFrameRotated;
        Rect _capInsetsInternal;
        bool _positionsAreDirty;
        
        Sprite* _scale9Image; //the original sprite
        Sprite* _topLeftSprite;
        Sprite* _topSprite;
        Sprite* _topRightSprite;
        Sprite* _leftSprite;
        Sprite* _centerSprite;
        Sprite* _rightSprite;
        Sprite* _bottomLeftSprite;
        Sprite* _bottomSprite;
        Sprite* _bottomRightSprite;
        
        bool _scale9Enabled;
        BlendFunc _blendFunc;
        
        Size _topLeftSize;
        Size _centerSize;
        Size _bottomRightSize;
        Vec2 _centerOffset;
        
        /** Original sprite's size. */
        Size _originalSize;
        Vec2 _offset;
        /** Preferred sprite's size. By default the preferred size is the original size. */
        
        //if the preferredSize component is given as -1, it is ignored
        Size _preferredSize;
        /**
         * The end-cap insets.
         * On a non-resizeable sprite, this property is set to CGRect::ZERO; the sprite
         * does not use end caps and the entire sprite is subject to stretching.
         */
        Rect _capInsets;
        /** Sets the left side inset */
        float _insetLeft;
        /** Sets the top side inset */
        float _insetTop;
        /** Sets the right side inset */
        float _insetRight;
        /** Sets the bottom side inset */
        float _insetBottom;
        
        /// helper that reorder a child
        void addProtectedChild(Node* child);
        
        Vector<Node*> _protectedChildren;        ///holds the 9 sprites
        bool _reorderProtectedChildDirty;
        
        bool _flippedX;
        bool _flippedY;
        bool _isPatch9;
    };
    
}}  //end of namespace
// end of ui group
/// @}

#endif /* defined(__cocos2d_libs__UIScale9Sprite__) */
