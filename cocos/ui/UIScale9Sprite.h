/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 Copyright (c) 2013-2015 zilongshanren

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
#include "ui/GUIExport.h"
#include "renderer/CCTrianglesCommand.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN
namespace ui {
    /**
     *   Type::Sliced Sprite can't be added as children of SpriteBatchNode
     */
    class CC_GUI_DLL Scale9Sprite : public cocos2d::Sprite
    {
    public:
        /**
         * - Simple: The classical cocos2d sprite type, you can't change content size to stretch,
         *           use scale instead.
         *
         * - Sliced: Sliced aka 9-slice scaling which allows you to specify
         *           how scaling is applied to specific areas of a sprite.
         *           With 9-slice scaling (3x3 grid),
         *           you can ensure that the sprite does not become distorted when scaled.
         */
        enum class Type
        {
            Simple,
            Sliced
        };

        enum class State
        {
            NORMAL,
            GRAY
        };
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
         * to resize the sprite will all it's 9-slice goodness intract.
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
         * to resize the sprite will all it's 9-slice goodness intract.
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
         * to resize the sprite will all it's 9-slice goodness intract.
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
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrameName(const char *spriteFrameName, const Rect& capInsets)
         * @param spriteFrameName A sprite frame name.
         * @param capInsets A delimitation zone.
         * @return A Scale9Sprite instance.
         */
        static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);


        /**
         * @brief Change inner sprite's sprite frame.
         *
         * @param spriteFrame A sprite frame pointer.
         * @param capInsets The values to use for the cap insets.
         */
        virtual void setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets);
        using Sprite::setSpriteFrame;
        /**
         * @brief Toggle 9-slice feature.
         * If Scale9Sprite is 9-slice disabled, the Scale9Sprite will rendered as a normal sprite.
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
        bool isScale9Enabled()const;
        /**
         * @brief Get the original no 9-sliced sprite
         *
         * @return A sprite instance.
         */
        Scale9Sprite* getSprite();

        /**
         * @brief Change the prefered size of Scale9Sprite.
         *
         * @param size A delimitation zone.
         */
        void setPreferredSize(const Size& size);

        /**
         * @brief Query the  Scale9Sprite's prefered size.
         *
         * @return Scale9Sprite's prefered size.
         */
        Size getPreferredSize() const;

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
         * @param originalSize The origial size of the sprite.
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
         * @param sprite A sprite pointer.
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
         * @brief Initializes a 9-slice sprite with a sprite batch node.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
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
         * Initializes a 9-slice sprite with an sprite frame and with the specified
         * cap insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @param spriteFrame The sprite frame object.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);
        using Sprite::initWithSpriteFrame;

        /**
         * Initializes a 9-slice sprite with an sprite frame name and with the specified
         * cap insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @param spriteFrameName The sprite frame name.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);
        using Sprite::initWithSpriteFrameName;

        /**
         * Initializes a 9-slice sprite with a texture file and with the specified cap
         * insets.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @param file The name of the texture file.
         * @param capInsets The values to use for the cap insets.
         * @return True if initializes success, false otherwise.
         */
        virtual bool initWithFile(const Rect& capInsets, const std::string& file);
        using Sprite::initWithFile;

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
         * @return True if initialize success, false otherwise.
         */
        virtual bool initWithFile(const std::string& file, const Rect& rect,  const Rect& capInsets);

        Scale9Sprite();
        virtual ~Scale9Sprite();

        /**
         *@brief Change the rendering type of sprite
         *@param type  @see Sprite::Type
         */
        void setType(Type type);

        /**
         * Return the rendering type of sprite
         *@return The actual rendering type of sprite.
         */
        Type getType()const;
        /**
         * Sets whether the widget should be flipped horizontally or not.
         *
         * @param flippedX true if the widget should be flipped horizontally, false otherwise.
         */
        virtual void setFlippedX(bool flippedX);

        /**
         * Returns the flag which indicates whether the widget is flipped horizontally or not.
         *
         * It only flips the texture of the widget, and not the texture of the widget's children.
         * Also, flipping the texture doesn't alter the anchorPoint.
         * If you want to flip the anchorPoint too, and/or to flip the children too use:
         * widget->setScaleX(sprite->getScaleX() * -1);
         *
         * @return true if the widget is flipped horizontally, false otherwise.
         */
        virtual bool isFlippedX()const;

        /**
         * Sets whether the widget should be flipped vertically or not.
         *
         * @param flippedY true if the widget should be flipped vertically, false otherwise.
         */
        virtual void setFlippedY(bool flippedY) ;

        /**
         * Return the flag which indicates whether the widget is flipped vertically or not.
         *
         * It only flips the texture of the widget, and not the texture of the widget's children.
         * Also, flipping the texture doesn't alter the anchorPoint.
         * If you want to flip the anchorPoint too, and/or to flip the children too use:
         * widget->setScaleY(widget->getScaleY() * -1);
         *
         * @return true if the widget is flipped vertically, false otherwise.
         */
        virtual bool isFlippedY()const;

        /**
         * @brief Change the cap inset size.
         *
         * @param rect A delimitation zone.
         */
        void setCapInsets(const Rect& rect);

        /**
         * @brief Query the Scale9Sprite's prefered size.
         *
         * @return Scale9Sprite's cap inset.
         */
        Rect getCapInsets()const;
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
         * @since v3.4
         */
        State getState()const;

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
        float getInsetLeft()const;

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
        float getInsetTop()const;

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
        float getInsetRight()const;

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
        float getInsetBottom()const;
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
        
        virtual void setContentSize(const Size & size) override;
        /**
         * Returns the untransformed size of the node when type is Simple.
         *
         * @see `setContentSize(const Size&)`
         *
         * @return The untransformed size of the node. When type is sliced, the content size is the
         *         prefered size.
         */
        virtual const Size& getContentSize() const override;
    protected:
        void caculatePolygonInfo();
        std::vector<Vec2> caculateUV(Texture2D *tex, const Rect& capInsets,
                                     const Size& spriteRectSize);
        std::vector<Vec2> caculateVertices(const Rect& capInsets, const Size& spriteRectSize);
        TrianglesCommand::Triangles caculateTriangles(const std::vector<Vec2>& uv,
                                                      const std::vector<Vec2>& vertices);
        
        void updateCapInset();

        Type _type;
        float _insetLeft;
        float _insetRight;
        float _insetBottom;
        float _insetTop;
        Rect _capInsetsInternal;
        State _brightState;
        V3F_C4B_T2F* _sliceVertices;
        unsigned short* _sliceIndices;
        Size _preferredSize;
        bool _isPatch9;

    };
} //end of ui namespace
// end of ui group
/// @}
NS_CC_END


#endif /* defined(__cocos2d_libs__UIScale9Sprite__) */
