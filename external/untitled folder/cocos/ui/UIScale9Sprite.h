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

NS_CC_BEGIN
namespace ui {
    
    /**
     * A 9-slice sprite for cocos2d.
     *
     * 9-slice scaling allows you to specify how scaling is applied
     * to specific areas of a sprite. With 9-slice scaling (3x3 grid),
     * you can ensure that the sprite does not become distorted when
     * scaled.
     *  Note: When you set _scale9Enabled to false, then you could call scale9Sprite->getSprite() to return a new Sprite pointer.
     *         Then you could call any methods of Sprite class with the return pointers.
     *
     */
    class CC_GUI_DLL Scale9Sprite : public Node
    {
    public:
        /**
         * @js ctor
         */
        Scale9Sprite();
        /**
         * @js NA
         * @lua NA
         */
        virtual ~Scale9Sprite();
        
        
        enum class State
        {
            NORMAL,
            GRAY
        };
        
    public:
        static Scale9Sprite* create();
        
        /**
         * Creates a 9-slice sprite with a texture file, a delimitation zone and
         * with the specified cap insets.
         *
         * @see initWithFile(const char *file, const Rect& rect, const Rect& capInsets)
         */
        static Scale9Sprite* create(const std::string& file, const Rect& rect,  const Rect& capInsets);
        
        /**
         * Creates a 9-slice sprite with a texture file. The whole texture will be
         * broken down into a 3×3 grid of equal blocks.
         *
         * @see initWithFile(const Rect& capInsets, const char *file)
         */
        static Scale9Sprite* create(const Rect& capInsets, const std::string& file);
        
        /**
         * Creates a 9-slice sprite with a texture file and a delimitation zone. The
         * texture will be broken down into a 3×3 grid of equal blocks.
         *
         * @see initWithFile(const char *file, const Rect& rect)
         */
        static Scale9Sprite* create(const std::string& file, const Rect& rect);
        
        /**
         * Creates a 9-slice sprite with a texture file. The whole texture will be
         * broken down into a 3×3 grid of equal blocks.
         *
         * @see initWithFile(const char *file)
         */
        static Scale9Sprite* create(const std::string& file);
        
        /**
         * Creates a 9-slice sprite with an sprite frame.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrame(SpriteFrame *spriteFrame)
         */
        static Scale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame);
        
        /**
         * Creates a 9-slice sprite with an sprite frame and the centre of its zone.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrame(SpriteFrame *spriteFrame, const Rect& capInsets)
         */
        static Scale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);
        
        /**
         * Creates a 9-slice sprite with an sprite frame name.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrameName(const char *spriteFrameName)
         */
        static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName);
        
        /**
         * Creates a 9-slice sprite with an sprite frame name and the centre of its
         * zone.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @see initWithSpriteFrameName(const char *spriteFrameName, const Rect& capInsets)
         */
        static Scale9Sprite* createWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);
        
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
        virtual bool initWithFile(const std::string& file, const Rect& rect,  const Rect& capInsets);
        
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
        virtual bool initWithFile(const std::string& file, const Rect& rect);
        
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
        virtual bool initWithFile(const Rect& capInsets, const std::string& file);
        
        /**
         * Initializes a 9-slice sprite with a texture file. The whole texture will be
         * broken down into a 3×3 grid of equal blocks.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @param file The name of the texture file.
         */
        virtual bool initWithFile(const std::string& file);
        
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
        virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame, const Rect& capInsets);
        
        /**
         * Initializes a 9-slice sprite with an sprite frame.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @param spriteFrame The sprite frame object.
         */
        virtual bool initWithSpriteFrame(SpriteFrame* spriteFrame);
        
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
        virtual bool initWithSpriteFrameName(const std::string& spriteFrameName, const Rect& capInsets);
        
        /**
         * Initializes a 9-slice sprite with an sprite frame name.
         * Once the sprite is created, you can then call its "setContentSize:" method
         * to resize the sprite will all it's 9-slice goodness intract.
         * It respects the anchorPoint too.
         *
         * @param spriteFrameName The sprite frame name.
         */
        virtual bool initWithSpriteFrameName(const std::string& spriteFrameName);
        
        virtual bool init();
        virtual bool init(Sprite* sprite, const Rect& rect, bool rotated, const Rect& capInsets);
        virtual bool init(Sprite* sprite, const Rect& rect, const Rect& capInsets);
        virtual bool init(Sprite* sprite, const Rect& rect, bool rotated, const Vec2 &offset, const Size &originalSize, const Rect& capInsets);
        CC_DEPRECATED_ATTRIBUTE virtual bool initWithBatchNode(SpriteBatchNode* batchnode, const Rect& rect, bool rotated, const Rect& capInsets);
        CC_DEPRECATED_ATTRIBUTE virtual bool initWithBatchNode(SpriteBatchNode* batchnode, const Rect& rect, const Rect& capInsets);

        /**
         * Creates and returns a new sprite object with the specified cap insets.
         * You use this method to add cap insets to a sprite or to change the existing
         * cap insets of a sprite. In both cases, you get back a new image and the
         * original sprite remains untouched.
         *
         * @param capInsets The values to use for the cap insets.
         */
        Scale9Sprite* resizableSpriteWithCapInsets(const Rect& capInsets) const;
        
        virtual bool updateWithSprite(Sprite* sprite, const Rect& rect, bool rotated, const Rect& capInsets);
        virtual bool updateWithSprite(Sprite* sprite, const Rect& rect, bool rotated, const Vec2 &offset, const Size &originalSize, const Rect& capInsets);
        CC_DEPRECATED_ATTRIBUTE bool updateWithBatchNode(SpriteBatchNode* batchnode, const Rect& originalRect, bool rotated, const Rect& capInsets);

        virtual void setSpriteFrame(SpriteFrame * spriteFrame, const Rect& capInsets = Rect::ZERO);
        
        // overrides
        virtual void setContentSize(const Size & size) override;
        virtual void setAnchorPoint(const Vec2& anchorPoint) override;
        
        /**
         *@since v3.4
         */
        void setState(State state);
        
        Size getOriginalSize() const;
        void setPreferredSize(const Size& size);
        Size getPreferredSize() const;
        void setCapInsets(const Rect& rect);
        Rect getCapInsets()const;
        void setInsetLeft(float leftInset);
        float getInsetLeft()const;
        void setInsetTop(float topInset);
        float getInsetTop()const;
        void setInsetRight(float rightInset);
        float getInsetRight()const;
        void setInsetBottom(float bottomInset);
        float getInsetBottom()const;
        void setScale9Enabled(bool enabled);
        bool isScale9Enabled()const;
        
        
        
        /// @} end of Children and Parent
        
        virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
        
        virtual void cleanup() override;
        
        virtual void onEnter() override;
        
        /** Event callback that is invoked when the Node enters in the 'stage'.
         * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
         * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
         * @js NA
         * @lua NA
         */
        virtual void onEnterTransitionDidFinish() override;
        
        /**
         * Event callback that is invoked every time the Node leaves the 'stage'.
         * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
         * During onExit you can't access a sibling node.
         * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
         * @js NA
         * @lua NA
         */
        virtual void onExit() override;
        
        /**
         * Event callback that is called every time the Node leaves the 'stage'.
         * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
         * @js NA
         * @lua NA
         */
        virtual void onExitTransitionDidStart() override;
        
        virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
        virtual void updateDisplayedColor(const Color3B& parentColor) override;
        virtual void disableCascadeColor() override;
        virtual void disableCascadeOpacity() override;
        
        Sprite* getSprite()const;
        
        /**
         * Sets whether the widget should be flipped horizontally or not.
         *
         * @param bFlippedX true if the widget should be flipped horizaontally, false otherwise.
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
         * @return true if the widget is flipped horizaontally, false otherwise.
         */
        virtual bool isFlippedX()const;
        
        /**
         * Sets whether the widget should be flipped vertically or not.
         *
         * @param bFlippedY true if the widget should be flipped vertically, flase otherwise.
         */
        virtual void setFlippedY(bool flippedY);

        /**
         * Return the flag which indicates whether the widget is flipped vertically or not.
         *
         * It only flips the texture of the widget, and not the texture of the widget's children.
         * Also, flipping the texture doesn't alter the anchorPoint.
         * If you want to flip the anchorPoint too, and/or to flip the children too use:
         * widget->setScaleY(widget->getScaleY() * -1);
         *
         * @return true if the widget is flipped vertically, flase otherwise.
         */
        virtual bool isFlippedY()const;
        
        //override the setScale function of Node
        virtual void setScaleX(float scaleX) override;
        virtual void setScaleY(float scaleY) override;
        virtual void setScale(float scale) override;
        virtual void setScale(float scalex, float scaley) override;
        using Node::setScaleZ;
        virtual float getScaleX() const override;
        virtual float getScaleY() const override;
        virtual float getScale() const override;
        using Node::getScaleZ;
    protected:
        void updateCapInset();
        void updatePositions();
        void createSlicedSprites();
        void cleanupSlicedSprites();
        void adjustScale9ImagePosition();
        /**
         * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
         * This appraoch can improves the performance massively.
         * @note Don't call this manually unless a child added needs to be removed in the same frame
         */
        virtual void sortAllProtectedChildren();
        
        bool _spritesGenerated;
        Rect _spriteRect;
        bool   _spriteFrameRotated;
        Rect _capInsetsInternal;
        bool _positionsAreDirty;
        
        Sprite* _scale9Image; //the original sprite
        Sprite* _topLeft;
        Sprite* _top;
        Sprite* _topRight;
        Sprite* _left;
        Sprite* _centre;
        Sprite* _right;
        Sprite* _bottomLeft;
        Sprite* _bottom;
        Sprite* _bottomRight;
        
        bool _scale9Enabled;
        
        Size _topLeftSize;
        Size _centerSize;
        Size _bottomRightSize;
        Vec2 _centerOffset;
        
        /** Original sprite's size. */
        Size _originalSize;
        Vec2 _offset;
        /** Prefered sprite's size. By default the prefered size is the original size. */
        
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
    };
    
}}  //end of namespace

#endif /* defined(__cocos2d_libs__UIScale9Sprite__) */
