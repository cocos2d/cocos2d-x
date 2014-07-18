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

__ControlColourPicker::__ControlColourPicker()
: _colourPicker(nullptr)
, _huePicker(nullptr)
, _background(nullptr)
{

}

__ControlColourPicker::~__ControlColourPicker()
{
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_huePicker);
    CC_SAFE_RELEASE(_colourPicker);
}

bool __ControlColourPicker::init()
{
    if (__Control::init())
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
        _background=__ControlUtils::addSpriteToTargetWithPosAndAnchor("menuColourPanelBackground.png", spriteSheet, Vec2::ZERO, Vec2(0.5f, 0.5f));
        if(!_background) return false;
        CC_SAFE_RETAIN(_background);
        
        Vec2 backgroundPointZero = _background->getPosition() - Vec2(_background->getContentSize().width / 2, _background->getContentSize().height / 2);
        
        // Setup panels
        float hueShift                = 8;
        float colourShift             = 28;
        
        _huePicker = new __ControlHuePicker();
        _huePicker->initWithTargetAndPos(spriteSheet, Vec2(backgroundPointZero.x + hueShift, backgroundPointZero.y + hueShift));
        _colourPicker = new __ControlSaturationBrightnessPicker();
        _colourPicker->initWithTargetAndPos(spriteSheet, Vec2(backgroundPointZero.x + colourShift, backgroundPointZero.y + colourShift));
        
        // Setup events
        _huePicker->addTargetWithActionForControlEvents(this, cccontrol_selector(__ControlColourPicker::hueSliderValueChanged), __Control::EventType::VALUE_CHANGED);
        _colourPicker->addTargetWithActionForControlEvents(this, cccontrol_selector(__ControlColourPicker::colourSliderValueChanged), __Control::EventType::VALUE_CHANGED);
       
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

__ControlColourPicker* __ControlColourPicker::create()
{
    __ControlColourPicker *pRet = new __ControlColourPicker();
    pRet->init();
    pRet->autorelease();
    return pRet;
}


void __ControlColourPicker::setColor(const Color3B& color)
{
    // XXX fixed me if not correct
    __Control::setColor(color);
    
    RGBA rgba;
    rgba.r      = color.r / 255.0f;
    rgba.g      = color.g / 255.0f;
    rgba.b      = color.b / 255.0f;
    rgba.a      = 1.0f;
    
    _hsv=__ControlUtils::HSVfromRGB(rgba);
    updateHueAndControlPicker();
}

void __ControlColourPicker::setEnabled(bool enabled)
{
    __Control::setEnabled(enabled);
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
void __ControlColourPicker::updateControlPicker()
{
    _huePicker->setHue(_hsv.h);
    _colourPicker->updateWithHSV(_hsv);
}

void __ControlColourPicker::updateHueAndControlPicker()
{
    _huePicker->setHue(_hsv.h);
    _colourPicker->updateWithHSV(_hsv);
    _colourPicker->updateDraggerWithHSV(_hsv);
}


void __ControlColourPicker::hueSliderValueChanged(Ref * sender, __Control::EventType controlEvent)
{
    _hsv.h      = ((__ControlHuePicker*)sender)->getHue();

    // Update the value
    RGBA rgb    = __ControlUtils::RGBfromHSV(_hsv);
    // XXX fixed me if not correct
    __Control::setColor(Color3B((GLubyte)(rgb.r * 255.0f), (GLubyte)(rgb.g * 255.0f), (GLubyte)(rgb.b * 255.0f)));
    
    // Send Control callback
    sendActionsForControlEvents(__Control::EventType::VALUE_CHANGED);
    updateControlPicker();
}

void __ControlColourPicker::colourSliderValueChanged(Ref * sender, __Control::EventType controlEvent)
{
    _hsv.s=((__ControlSaturationBrightnessPicker*)sender)->getSaturation();
    _hsv.v=((__ControlSaturationBrightnessPicker*)sender)->getBrightness();


     // Update the value
    RGBA rgb    = __ControlUtils::RGBfromHSV(_hsv);
    // XXX fixed me if not correct
    __Control::setColor(Color3B((GLubyte)(rgb.r * 255.0f), (GLubyte)(rgb.g * 255.0f), (GLubyte)(rgb.b * 255.0f)));
    
    // Send Control callback
    sendActionsForControlEvents(__Control::EventType::VALUE_CHANGED);
}

//ignore all touches, handled by children
bool __ControlColourPicker::onTouchBegan(Touch* touch, Event* pEvent)
{
    return false;
}

NS_CC_EXT_END
