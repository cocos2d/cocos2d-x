/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2012 Stewart Hamilton-Arrandale.
 * http://creativewax.co.uk
 *
 * Modified by Yannick Loriot.
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
 * converted to c++ / cocos2d-x by Angus C
 */

#include "CCControlColourPicker.h"
#include "2d/CCSpriteFrameCache.h"
#include "2d/CCSpriteBatchNode.h"

NS_CC_EXT_BEGIN

ControlColourPicker::ControlColourPicker()
: _colourPicker(nullptr)
, _huePicker(nullptr)
, _background(nullptr)
{

}

ControlColourPicker::~ControlColourPicker()
{
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_huePicker);
    CC_SAFE_RELEASE(_colourPicker);
}

bool ControlColourPicker::init()
{
    if (Control::init())
    {
        // Cache the sprites
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("extensions/CCControlColourPickerSpriteSheet.plist");
        
        // Create the sprite batch node
        SpriteBatchNode *spriteSheet  = SpriteBatchNode::create("extensions/CCControlColourPickerSpriteSheet.png");
        addChild(spriteSheet);
        
        // MIPMAP
//        ccTexParams params  = {GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
		/* Comment next line to avoid something like mosaic in 'ControlExtensionTest',
		   especially the display of 'huePickerBackground.png' when in 800*480 window size with 480*320 design resolution and hd(960*640) resources.
	    */
//        spriteSheet->getTexture()->setAliasTexParameters();
//         spriteSheet->getTexture()->setTexParameters(&params);
//         spriteSheet->getTexture()->generateMipmap();

        // Init default color
        _hsv.h = 0;
        _hsv.s = 0;
        _hsv.v = 0;
        
        // Add image
        _background=ControlUtils::addSpriteToTargetWithPosAndAnchor("menuColourPanelBackground.png", spriteSheet, Vector2::ZERO, Vector2(0.5f, 0.5f));
        CC_SAFE_RETAIN(_background);
        
        Vector2 backgroundPointZero = _background->getPosition() - Vector2(_background->getContentSize().width / 2, _background->getContentSize().height / 2);
        
        // Setup panels
        float hueShift                = 8;
        float colourShift             = 28;
        
        _huePicker = new ControlHuePicker();
        _huePicker->initWithTargetAndPos(spriteSheet, Vector2(backgroundPointZero.x + hueShift, backgroundPointZero.y + hueShift));
        _colourPicker = new ControlSaturationBrightnessPicker();
        _colourPicker->initWithTargetAndPos(spriteSheet, Vector2(backgroundPointZero.x + colourShift, backgroundPointZero.y + colourShift));
        
        // Setup events
        _huePicker->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlColourPicker::hueSliderValueChanged), Control::EventType::VALUE_CHANGED);
        _colourPicker->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlColourPicker::colourSliderValueChanged), Control::EventType::VALUE_CHANGED);
       
        // Set defaults
        updateHueAndControlPicker();
        addChild(_huePicker);
        addChild(_colourPicker);

        // Set content size
        setContentSize(_background->getContentSize());
        return true;
    }
    else
        return false;
}

ControlColourPicker* ControlColourPicker::create()
{
    ControlColourPicker *pRet = new ControlColourPicker();
    pRet->init();
    pRet->autorelease();
    return pRet;
}


void ControlColourPicker::setColor(const Color3B& color)
{
    // XXX fixed me if not correct
    Control::setColor(color);
    
    RGBA rgba;
    rgba.r      = color.r / 255.0f;
    rgba.g      = color.g / 255.0f;
    rgba.b      = color.b / 255.0f;
    rgba.a      = 1.0f;
    
    _hsv=ControlUtils::HSVfromRGB(rgba);
    updateHueAndControlPicker();
}

void ControlColourPicker::setEnabled(bool enabled)
{
    Control::setEnabled(enabled);
    if (_huePicker != NULL)
    {
        _huePicker->setEnabled(enabled);
    }
    if (_colourPicker)
    {
        _colourPicker->setEnabled(enabled);
    } 
}


//need two events to prevent an infinite loop! (can't update huePicker when the huePicker triggers the callback due to Control::EventType::VALUE_CHANGED)
void ControlColourPicker::updateControlPicker()
{
    _huePicker->setHue(_hsv.h);
    _colourPicker->updateWithHSV(_hsv);
}

void ControlColourPicker::updateHueAndControlPicker()
{
    _huePicker->setHue(_hsv.h);
    _colourPicker->updateWithHSV(_hsv);
    _colourPicker->updateDraggerWithHSV(_hsv);
}


void ControlColourPicker::hueSliderValueChanged(Ref * sender, Control::EventType controlEvent)
{
    _hsv.h      = ((ControlHuePicker*)sender)->getHue();

    // Update the value
    RGBA rgb    = ControlUtils::RGBfromHSV(_hsv);
    // XXX fixed me if not correct
    Control::setColor(Color3B((GLubyte)(rgb.r * 255.0f), (GLubyte)(rgb.g * 255.0f), (GLubyte)(rgb.b * 255.0f)));
    
    // Send Control callback
    sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
    updateControlPicker();
}

void ControlColourPicker::colourSliderValueChanged(Ref * sender, Control::EventType controlEvent)
{
    _hsv.s=((ControlSaturationBrightnessPicker*)sender)->getSaturation();
    _hsv.v=((ControlSaturationBrightnessPicker*)sender)->getBrightness();


     // Update the value
    RGBA rgb    = ControlUtils::RGBfromHSV(_hsv);
    // XXX fixed me if not correct
    Control::setColor(Color3B((GLubyte)(rgb.r * 255.0f), (GLubyte)(rgb.g * 255.0f), (GLubyte)(rgb.b * 255.0f)));
    
    // Send Control callback
    sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
}

//ignore all touches, handled by children
bool ControlColourPicker::onTouchBegan(Touch* touch, Event* pEvent)
{
    return false;
}

NS_CC_EXT_END
