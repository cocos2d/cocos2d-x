/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "2d/CCSprite.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteBatchNode.h"
#include "platform/CCPlatformMacros.h"
#include "ui/GUIExport.h"
#include "renderer/CCTrianglesCommand.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN
class DrawNode;
class Texture2D;

namespace ui {

    /**
     *@brief A 9-slice sprite for cocos2d-x.
     *
     * 9-slice scaling allows you to specify how scaling is applied
     * to specific areas of a sprite. With 9-slice scaling (3x3 grid),
     * you can ensure that the sprite does not become distorted when
     * scaled.
     * Note: When you set _scale9Enabled to false,
     * then you could call `scale9Sprite->getSprite()` to return the inner Sprite pointer.
     * Then you could call any methods of Sprite class with the return pointers.
     *
     */
    class CC_GUI_DLL Scale9Sprite : public Sprite
    {
    public:
        /**
         * Default constructor.
         * @js ctor
         * @lua new
         */
        Scale9Sprite();

        /**
         * Default destructor.
         * @js NA
         * @lua NA
         */
        virtual ~Scale9Sprite();

        /**
         * Builtin shader state.
         * Currently support Normal and Gray state.
         */
        enum class State
        {
            NORMAL,
            GRAY
        };

        enum class RenderingType
        {
            SIMPLE,
            SLICE
        };

    public:

        /**
         * @brief Create an empty Scale9Sprite.
         *
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* create();

        /**
         * Creates a 9-slice sprite with a texture file, a delimitation zone and
         * with the specified cap insets.
         *
         * @see initWithFile(const char *file, const Rect& rect, const Rect& capInsets)
         * @param file A texture file name.
         * @param rect A delimitation zone.
         * @param capInsets A specified cap insets.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* create(const std::string& file, const Rect& rect,  const Rect& capInsets);

        /**
         * Creates a 9-slice sprite with a texture file. The whole texture will be
         * broken down into a 3×3 grid of equal blocks.
         *
         * @see initWithFile(const Rect& capInsets, const char *file)
         * @param capInsets A specified cap insets.
         * @param file A texture file name.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* create(const Rect& capInsets, const std::string& file);

        /**
         * Creates a 9-slice sprite with a texture file and a delimitation zone. The
         * texture will be broken down into a 3×3 grid of equal blocks.
         *
         * @see initWithFile(const char *file, const Rect& rect)
         * @param file A texture file name.
         * @param rect A delimitation zone.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* create(const std::string& file, const Rect& rect);

        /**
         * Creates a 9-slice sprite with a texture file. The whole texture will be
         * broken down into a 3×3 grid of equal blocks.
         *
         * @see initWithFile(const char *file)
         * @param file A texture file name.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* create(const std::string& file);

        /**
         * Creates a 9-slice sprite with an sprite frame.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrame(SpriteFrame *spriteFrame)
         * @param spriteFrame  A sprite frame pointer.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame);

        /**
         * Creates a 9-slice sprite with an sprite frame and the centre of its zone.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrame(SpriteFrame *spriteFrame, const Rect& capInsets)
         * @param spriteFrame A sprite frame pointer.
         * @param capInsets  A delimitation zone.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);

        /**
         * Creates a 9-slice sprite with an sprite frame name.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrameName(const char *spriteFrameName)
         * @param spriteFrameName A sprite frame name.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);

        /**
         * Creates a 9-slice sprite with an sprite frame name and the centre of its zone.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrameName(const char *spriteFrameName, const Rect& capInsets)
         * @param spriteFrameName A sprite frame name.
         * @param capInsets A delimitation zone.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);

        // overridden methods that takes different parameters
        using Sprite::initWithFile;
        using Sprite::initWithSpriteFrame;
        using Sprite::initWithSpriteFrameName;
        using Sprite::setSpriteFrame;

        /**
         * Initializes a 9-slice sprite with a texture file, a delimitation zone and
         * with the specified cap insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param file The name of the texture file.
         * @param rect The rectangle that describes the sub-part of the texture that
         * is the whole image. If the shape is the whole texture, set this to the
         * texture's full rect.
         * @param capInsets The values to use for the cap insets.
         * @return True if initialize success, false otherwise.
         */
        virtual bool initWithFile(const std::string& file, const Rect& rect,  const Rect& capInsets);

        /**
         * Initializes a 9-slice sprite with a texture file and with the specified cap
         * insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param file The name of the texture file.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithFile(const Rect& capInsets, const std::string& file);

        /**
         * Initializes a 9-slice sprite with an sprite frame and with the specified
         * cap insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param spriteFrame The sprite frame object.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);

        /**
         * Initializes a 9-slice sprite with an sprite frame name and with the specified
         * cap insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param spriteFrameName The sprite frame name.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);

        //override function

        /**
         * Initializes a 9-slice sprite with a texture file and a delimitation zone. The
         * texture will be broken down into a 3×3 grid of equal blocks.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param file The name of the texture file.
         * @param rect The rectangle that describes the sub-part of the texture that
         * is the whole image. If the shape is the whole texture, set this to the
         * texture's full rect.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithFile(const std::string& file, const Rect& rect) override;

        /**
         * Initializes a 9-slice sprite with a texture file. The whole texture will be
         * broken down into a 3×3 grid of equal blocks.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param file The name of the texture file.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithFile(const std::string& file) override;

        /**
         * Initializes a 9-slice sprite with an sprite frame name.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param spriteFrameName The sprite frame name.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithSpriteFrameName(const std::string& spriteFrameName) override;

        virtual bool init() override;

        /**
         * @brief Initializes a 9-slice sprite with an sprite instance.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param sprite The sprite instance.
         * @param rect A delimitation zone.
         * @param rotated Whether the sprite is rotated or not.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        virtual bool init(Sprite* sprite, const Rect& rect, bool rotated, const Rect& capInsets);

        /**
         * @brief Initializes a 9-slice sprite with an sprite instance.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param sprite The sprite instance.
         * @param rect A delimitation zone.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        virtual bool init(Sprite* sprite, const Rect& rect, const Rect& capInsets);

        /**
         * @brief Initializes a 9-slice sprite with an sprite instance.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @param sprite The sprite instance.
         * @param rect A delimitation zone.
         * @param rotated Whether the sprite is rotated or not.
         * @param offset The offset when slice the sprite.
         * @param originalSize The original size of sprite.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
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
         * to resize the sprite will all it's 9-slice goodness interact.
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
         * @brief Initializes a 9-slice sprite with a sprite batch node.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness interact.
         * It respects the anchorPoint too.
         *
         * @deprecated Use @see `init` instead.
         * @param batchnode A batch node pointer.
         * @param rect A delimitation zone.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        CC_DEPRECATED(v3) virtual bool initWithBatchNode(SpriteBatchNode* batchnode, const Rect& rect, const Rect& capInsets);

        /**
         * Creates and returns a new sprite object with the specified cap insets.
         * You use this method to add cap insets to a sprite or to change the existing
         * cap insets of a sprite. In both cases, you get back a new image and the
         * original sprite remains untouched.
         *
         * @param capInsets The values to use for the cap insets.
         * @return A Scale9Sprite instance.
         */
        Scale9Sprite* resizableSpriteWithCapInsets(const Rect& capInsets) const;


        /**
         * @brief Update Scale9Sprite with a specified sprite.
         *
         * @param sprite A sprite pointer.
         * @param rect A delimitation zone.
         * @param rotated Whether the sprite is rotated or not.
         * @param capInsets The Values to use for the cap insets.
         * @return True if update success, false otherwise.
         * @js NA
         */
        virtual bool updateWithSprite(Sprite* sprite,
                                      const Rect& rect,
                                      bool rotated,
                                      const Rect& capInsets);

        /**
         * @brief Update Scale9Sprite with a specified sprite.
         *
         * @param sprite A sprite pointer.
         * @param rect A delimitation zone.
         * @param rotated Whether the sprite is rotated or not.
         * @param offset The offset when slice the sprite.
         * @param originalSize The original size of the sprite.
         * @param capInsets The Values to use for the cap insets.
         * @return True if update success, false otherwise.
         * @js NA
         */
        virtual bool updateWithSprite(Sprite* sprite,
                                      const Rect& rect,
                                      bool rotated,
                                      const Vec2 &offset,
                                      const Size &originalSize,
                                      const Rect& capInsets);

        /**
         * @brief Update Scale9Sprite with a specified sprite.
         *
         * @deprecated Use @see `updateWithSprite` instead.
         * @param batchnode A sprite batch pointer.
         * @param originalRect A delimitation zone.
         * @param rotated Whether the sprite is rotated or not.
         * @param capInsets The Values to use for the cap insets.
         * @return True if update success, false otherwise.
         */
        CC_DEPRECATED(v3) bool updateWithBatchNode(SpriteBatchNode* batchnode,
                                                   const Rect& originalRect,
                                                   bool rotated,
                                                   const Rect& capInsets);


        /**
         * @brief Change inner sprite's sprite frame.
         *
         * @param spriteFrame A sprite frame pointer.
         * @param capInsets The values to use for the cap insets.
         */
        virtual void setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets);

        /**
         * Change the state of 9-slice sprite.
         * @see `State`
         * @param state A enum value in State.
         * @since v3.4
         */
        void setState(State state);

        /**
         * Query the current bright state.
         * @return @see `State`
         * @since v3.7
         */
        State getState() const;

        /**
         * @brief Query the sprite's original size.
         *
         * @return Sprite size.
         */
        Size getOriginalSize() const;

        /**
         * @brief Change the preferred size of Scale9Sprite.
         *
         * @param size A delimitation zone.
         */
        void setPreferredSize(const Size& size);

        /**
         * @brief Query the Scale9Sprite's preferred size.
         *
         * @return Scale9Sprite's preferred size.
         */
        Size getPreferredSize() const;

        /**
         * @brief Change the left sprite's cap inset.
         *
         * @param leftInset The values to use for the cap inset.
         */
        void setInsetLeft(float leftInset);

        /**
         * @brief Query the left sprite's cap inset.
         *
         * @return The left sprite's cap inset.
         */
        float getInsetLeft() const;

        /**
         * @brief Change the top sprite's cap inset.
         *
         * @param topInset The values to use for the cap inset.
         */
        void setInsetTop(float topInset);

        /**
         * @brief Query the top sprite's cap inset.
         *
         * @return The top sprite's cap inset.
         */
        float getInsetTop() const;

        /**
         * @brief Change the right sprite's cap inset.
         *
         * @param rightInset The values to use for the cap inset.
         */
        void setInsetRight(float rightInset);

        /**
         * @brief Query the right sprite's cap inset.
         *
         * @return The right sprite's cap inset.
         */
        float getInsetRight() const;

        /**
         * @brief Change the bottom sprite's cap inset.
         *
         * @param bottomInset The values to use for the cap inset.

         */
        void setInsetBottom(float bottomInset);

        /**
         * @brief Query the bottom sprite's cap inset.
         *
         * @return The bottom sprite's cap inset.
         */
        float getInsetBottom() const;

        /**
         * @brief Toggle 9-slice feature.
         * If Scale9Sprite is 9-slice disabled, the Scale9Sprite will rendered as a normal sprite.
         * @warning: Don't use setScale9Enabled(false), use setRenderingType(RenderingType::SIMPLE) instead.
         *        The setScale9Enabled(false) is kept only for back back compatibility.
         * @param enabled True to enable 9-slice, false otherwise.
         * @js NA
         */
        void setScale9Enabled(bool enabled);

        /**
         * @brief Query whether the Scale9Sprite is enable 9-slice or not.
         *
         * @return True if 9-slice is enabled, false otherwise.
         * @js NA
         */
        bool isScale9Enabled() const;

        /// @} end of Children and Parent

        /**
         * @brief Get the original no 9-sliced sprite
         *
         * @return A sprite instance.
         */
        Sprite* getSprite();

        /**
         * @brief copies self to copy
         */
        void copyTo(Scale9Sprite* copy) const;


        /**
         * Set the slice sprite rendering type.
         * When setting to SIMPLE, only 4 vertexes is used to rendering.
         * otherwise 16 vertexes will be used to rendering.
         * @see RenderingType
         */
        void setRenderingType(RenderingType type);

        /**
         * Return the slice sprite rendering type.
         */
        RenderingType getRenderingType() const;

        /**
         * Set the Cap Insets in Points using the untrimmed size as reference
         */
        void setCapInsets(const Rect& insets);
        /**
         * Returns the Cap Insets
         */
        Rect getCapInsets() const;

        void resetRender();

    protected:
        void updateCapInset();
        void setupSlice9(Texture2D* texture, const Rect& capInsets);

        bool _isPatch9;

        float _insetLeft;
        float _insetRight;
        float _insetTop;
        float _insetBottom;

        Scale9Sprite::State _brightState;
        Scale9Sprite::RenderingType _renderingType;
    };
    
}}  //end of namespace
// end of ui group
/// @}

#endif /* defined(__cocos2d_libs__UIScale9Sprite__) */
