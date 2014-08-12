/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot. All rights reserved.
 * http://yannickloriot.com
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Converted to c++ / cocos2d-x by Angus C
 */


#ifndef __CCCONTROL_BUTTON_H__
#define __CCCONTROL_BUTTON_H__

#include "CCControl.h"
#include "CCInvocation.h"
#include "CCScale9Sprite.h"
#include "base/CCMap.h"
#include "extensions/ExtensionExport.h"

NS_CC_EXT_BEGIN

/* Define the button margin for Left/Right edge */
#define ControlButtonMarginLR 8 // px
/* Define the button margin for Top/Bottom edge */
#define ControlButtonMarginTB 2 // px


/**
 * @addtogroup GUI
 * @{
 * @addtogroup control_extension
 * @{
 */

/** @class ControlButton Button control for Cocos2D. */
class CC_EX_DLL ControlButton : public Control
{        
public:
    static ControlButton* create();
    static ControlButton* create(Scale9Sprite* sprite);
    static ControlButton* create(Node* label, Scale9Sprite* backgroundSprite);
    static ControlButton* create(const std::string& title, const std::string& fontName, float fontSize);

    virtual void needsLayout(void);

    virtual void setEnabled(bool enabled);
    virtual void setSelected(bool enabled);
    virtual void setHighlighted(bool enabled);

    bool isPushed() const { return _isPushed; }

    /**
     * Returns the title used for a state.
     *
     * @param state The state that uses the title. Possible values are described in
     * "CCControlState".
     *
     * @return The title for the specified state.
     */
    virtual std::string getTitleForState(State state);

    /**
     * Sets the title string to use for the specified state.
     * If a property is not specified for a state, the default is to use
     * the ButtonStateNormal value.
     *
     * @param title The title string to use for the specified state.
     * @param state The state that uses the specified title. The values are described
     * in "CCControlState".
     */
    virtual void setTitleForState(const std::string& title, State state);

    /**
     * Returns the title color used for a state.
     *
     * @param state The state that uses the specified color. The values are described
     * in "CCControlState".
     *
     * @return The color of the title for the specified state.
     */

    virtual Color3B getTitleColorForState(State state) const;

    /**
     * Sets the color of the title to use for the specified state.
     *
     * @param color The color of the title to use for the specified state.
     * @param state The state that uses the specified color. The values are described
     * in "CCControlState".
     */
    virtual void setTitleColorForState(const Color3B& color, State state);

    /**
     * Returns the title label used for a state.
     *
     * @param state The state that uses the title label. Possible values are described
     * in "CCControlState".
     */
    virtual Node* getTitleLabelForState(State state);

    /**
     * Sets the title label to use for the specified state.
     * If a property is not specified for a state, the default is to use
     * the ButtonStateNormal value.
     *
     * @param label The title label to use for the specified state.
     * @param state The state that uses the specified title. The values are described
     * in "CCControlState".
     */
    virtual void setTitleLabelForState(Node* label, State state);

    virtual void setTitleTTFForState(const std::string& fntFile, State state);
    virtual const std::string& getTitleTTFForState(State state);

    virtual void setTitleTTFSizeForState(float size, State state);
    virtual float getTitleTTFSizeForState(State state);

    /**
     * Sets the font of the label, changes the label to a BMFont if neccessary.
     * @param fntFile The name of the font to change to
     * @param state The state that uses the specified fntFile. The values are described
     * in "CCControlState".
     */
    virtual void setTitleBMFontForState(const std::string& fntFile, State state);
    virtual const std::string& getTitleBMFontForState(State state);

    /**
     * Returns the background sprite used for a state.
     *
     * @param state The state that uses the background sprite. Possible values are
     * described in "CCControlState".
     */
    virtual Scale9Sprite* getBackgroundSpriteForState(State state);

    /**
     * Sets the background sprite to use for the specified button state.
     *
     * @param sprite The background sprite to use for the specified state.
     * @param state The state that uses the specified image. The values are described
     * in "CCControlState".
     */
    virtual void setBackgroundSpriteForState(Scale9Sprite* sprite, State state);

    /**
     * Sets the background spriteFrame to use for the specified button state.
     *
     * @param spriteFrame The background spriteFrame to use for the specified state.
     * @param state The state that uses the specified image. The values are described
     * in "CCControlState".
     */
    virtual void setBackgroundSpriteFrameForState(SpriteFrame * spriteFrame, State state);

    //set the margins at once (so we only have to do one call of needsLayout)
    virtual void setMargins(int marginH, int marginV);

    /** Adjust the background image. YES by default. If the property is set to NO, the
     background will use the prefered size of the background image. */
    bool doesAdjustBackgroundImage();
    void setAdjustBackgroundImage(bool adjustBackgroundImage);

    // Overrides
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    virtual void onTouchMoved(Touch *touch, Event *event) override;
    virtual void onTouchEnded(Touch *touch, Event *event) override;
    virtual void onTouchCancelled(Touch *touch, Event *event) override;

    virtual void setOpacity(GLubyte var) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
	virtual void setColor(const Color3B&) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;

    const std::string& getCurrentTitle() const { return _currentTitle; };
    std::string getCurrentTitle() { return _currentTitle; };
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    ControlButton();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlButton();
    
    virtual bool init() override;
    virtual bool initWithLabelAndBackgroundSprite(Node* label, Scale9Sprite* backgroundSprite);
    virtual bool initWithBackgroundSprite(Scale9Sprite* sprite);
    virtual bool initWithTitleAndFontNameAndFontSize(const std::string& title, const std::string& fontName, float fontSize);
    
protected:
    bool _isPushed;
    bool _parentInited;
    bool _doesAdjustBackgroundImage;

    /** The current title that is displayed on the button. */
    std::string _currentTitle;

    /** The current color used to display the title. */
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(Color3B, _currentTitleColor, CurrentTitleColor);

    /** The current title label. */
    CC_SYNTHESIZE_RETAIN(Node*, _titleLabel, TitleLabel);

    /** The current background sprite. */
    CC_SYNTHESIZE_RETAIN(Scale9Sprite*, _backgroundSprite, BackgroundSprite);

    /** The prefered size of the button, if label is larger it will be expanded. */
    CC_PROPERTY_PASS_BY_REF(Size, _preferredSize, PreferredSize);

    /** Adjust the button zooming on touchdown. Default value is YES. */
    CC_PROPERTY(bool, _zoomOnTouchDown, ZoomOnTouchDown);
    /** Scale ratio button on touchdown. Default value 1.1f */
    CC_SYNTHESIZE(float, _scaleRatio, ScaleRatio);

    CC_PROPERTY_PASS_BY_REF(Vec2, _labelAnchorPoint, LabelAnchorPoint);

    std::unordered_map<int, std::string> _titleDispatchTable;
    std::unordered_map<int, Color3B> _titleColorDispatchTable;

    Map<int, Node*> _titleLabelDispatchTable;
    Map<int, Scale9Sprite*> _backgroundSpriteDispatchTable;

    /* Define the button margin for Top/Bottom edge */
    CC_SYNTHESIZE_READONLY(int, _marginV, VerticalMargin);
    /* Define the button margin for Left/Right edge */
    CC_SYNTHESIZE_READONLY(int, _marginH, HorizontalOrigin);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ControlButton);
};

// end of GUI group
/// @}
/// @}

NS_CC_EXT_END

#endif
