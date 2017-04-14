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

#include "ui/UISlider.h"
#include "ui/UIScale9Sprite.h"
#include "ui/UIHelper.h"
#include "2d/CCSprite.h"
#include "2d/CCCamera.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

NS_CC_BEGIN

/* FIXME:
 Code could be simplified by using Sprite's setContentSize feature.
 Instead of scaling the sprite, set call setContentSize both in scale9 and non-scale9 modes
 */

namespace ui {
    
static const int BASEBAR_RENDERER_Z = (-2);
static const int PROGRESSBAR_RENDERER_Z = (-2);
static const int SLIDBALL_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(Slider)

Slider::Slider():
_barRenderer(nullptr),
_progressBarRenderer(nullptr),
_barTextureSize(Size::ZERO),
_originalBarRect(Rect::ZERO),
_progressBarTextureSize(Size::ZERO),
_originalProgressBarRect(Rect::ZERO),
_slidBallNormalRenderer(nullptr),
_slidBallPressedRenderer(nullptr),
_slidBallDisabledRenderer(nullptr),
_slidBallRenderer(nullptr),
_barLength(0.0),
_percent(0),
_maxPercent(100),
_scale9Enabled(false),
_prevIgnoreSize(true),
_zoomScale(0.1f),
_sliderBallNormalTextureScaleX(1.0),
_sliderBallNormalTextureScaleY(1.0),
_isSliderBallPressedTextureLoaded(false),
_isSliderBallDisabledTexturedLoaded(false),
_capInsetsBarRenderer(Rect::ZERO),
_capInsetsProgressBarRenderer(Rect::ZERO),
_sliderEventListener(nullptr),
_sliderEventSelector(nullptr),
_eventCallback(nullptr),
_barTexType(TextureResType::LOCAL),
_progressBarTexType(TextureResType::LOCAL),
_ballNTexType(TextureResType::LOCAL),
_ballPTexType(TextureResType::LOCAL),
_ballDTexType(TextureResType::LOCAL),
_barRendererAdaptDirty(true),
_progressBarRendererDirty(true),
_textureFile(""),
_progressBarTextureFile(""),
_slidBallNormalTextureFile(""),
_slidBallPressedTextureFile(""),
_slidBallDisabledTextureFile("")
{
    setTouchEnabled(true);
}

Slider::~Slider()
{
    _sliderEventListener = nullptr;
    _sliderEventSelector = nullptr;
}

Slider* Slider::create()
{
    Slider* widget = new (std::nothrow) Slider();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
Slider* Slider::create(const std::string& barTextureName,
                      const std::string& normalBallTextureName,
                      TextureResType resType)
{
    Slider* widget = new (std::nothrow) Slider();
    if (widget && widget->init())
    {
        widget->loadBarTexture(barTextureName, resType);
        widget->loadSlidBallTextureNormal(normalBallTextureName, resType);
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool Slider::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

void Slider::initRenderer()
{
    _barRenderer = Scale9Sprite::create();
    _progressBarRenderer = Scale9Sprite::create();
    _barRenderer->setScale9Enabled(false);
    _progressBarRenderer->setScale9Enabled(false);
    
    _progressBarRenderer->setAnchorPoint(Vec2(0.0f, 0.5f));
    
    addProtectedChild(_barRenderer, BASEBAR_RENDERER_Z, -1);
    addProtectedChild(_progressBarRenderer, PROGRESSBAR_RENDERER_Z, -1);
    
    _slidBallNormalRenderer = Sprite::create();
    _slidBallPressedRenderer = Sprite::create();
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer = Sprite::create();
    _slidBallDisabledRenderer->setVisible(false);
    
    _slidBallRenderer = Node::create();
    
    _slidBallRenderer->addChild(_slidBallNormalRenderer);
    _slidBallRenderer->addChild(_slidBallPressedRenderer);
    _slidBallRenderer->addChild(_slidBallDisabledRenderer);
    _slidBallRenderer->setCascadeColorEnabled(true);
    _slidBallRenderer->setCascadeOpacityEnabled(true);
    
    addProtectedChild(_slidBallRenderer, SLIDBALL_RENDERER_Z, -1);
}

void Slider::loadBarTexture(const std::string& fileName, TextureResType texType)
{
    _textureFile = fileName;
    _barTexType = texType;
    if (fileName.empty())
    {
        _barRenderer->resetRender();
    }
    else
    {
        switch (_barTexType)
        {
        case TextureResType::LOCAL:
            _barRenderer->setTexture(fileName);
            break;
        case TextureResType::PLIST:
            _barRenderer->setSpriteFrame(fileName);
            break;
        default:
            break;
        }
    }
    //FIXME: https://github.com/cocos2d/cocos2d-x/issues/12249
    if (!_ignoreSize && _customSize.equals(Size::ZERO)) {
        _customSize = _barRenderer->getContentSize();
    }
    this->setupBarTexture();
}
void Slider::loadBarTexture(SpriteFrame* spriteframe)
{
    _barRenderer->setSpriteFrame(spriteframe);
    this->setupBarTexture();
}

void Slider::setupBarTexture()
{
    this->updateChildrenDisplayedRGBA();
    _barRendererAdaptDirty = true;
    _progressBarRendererDirty = true;
    updateContentSizeWithTextureSize(_barRenderer->getContentSize());
    _barTextureSize = _barRenderer->getContentSize();
    _originalBarRect = _barRenderer->getTextureRect();
}

void Slider::loadProgressBarTexture(const std::string& fileName, TextureResType texType)
{
    _progressBarTextureFile = fileName;
    _progressBarTexType = texType;
    if (fileName.empty())
    {
        _progressBarRenderer->resetRender();
    }
    else
    {
        switch (_progressBarTexType)
        {
        case TextureResType::LOCAL:
            _progressBarRenderer->setTexture(fileName);
            break;
        case TextureResType::PLIST:
            _progressBarRenderer->setSpriteFrame(fileName);
            break;
        default:
            break;
        }
    }
    this->setupProgressBarTexture();
}

void Slider::loadProgressBarTexture(SpriteFrame* spriteframe)
{
    _progressBarRenderer->setSpriteFrame(spriteframe);
    this->setupProgressBarTexture();
}

void Slider::setupProgressBarTexture()
{
    this->updateChildrenDisplayedRGBA();
    _progressBarRenderer->setAnchorPoint(Vec2(0.0f, 0.5f));
    _progressBarTextureSize = _progressBarRenderer->getContentSize();
    _originalProgressBarRect = _progressBarRenderer->getTextureRect();
    _progressBarRendererDirty = true;
}

void Slider::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    _scale9Enabled = able;
    _barRenderer->setScale9Enabled(_scale9Enabled);
    _progressBarRenderer->setScale9Enabled(_scale9Enabled);
    
    if (_scale9Enabled)
    {
        bool ignoreBefore = _ignoreSize;
        ignoreContentAdaptWithSize(false);
        _prevIgnoreSize = ignoreBefore;
    }
    else
    {
        ignoreContentAdaptWithSize(_prevIgnoreSize);
    }
    setCapInsetsBarRenderer(_capInsetsBarRenderer);
    setCapInsetProgressBarRenderer(_capInsetsProgressBarRenderer);
    _barRendererAdaptDirty = true;
    _progressBarRendererDirty = true;
}
    
bool Slider::isScale9Enabled()const
{
    return _scale9Enabled;
}

void Slider::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void Slider::setCapInsets(const Rect &capInsets)
{
    setCapInsetsBarRenderer(capInsets);
    setCapInsetProgressBarRenderer(capInsets);
}

void Slider::setCapInsetsBarRenderer(const Rect &capInsets)
{
    _capInsetsBarRenderer = ui::Helper::restrictCapInsetRect(capInsets, _barRenderer->getContentSize());
    if (!_scale9Enabled)
    {
        return;
    }

    // textureRect should be restored in order to calculate the scale9 correctly
    // https://github.com/cocos2d/cocos2d-x/issues/16928
    _barRenderer->setTextureRect(_originalBarRect, _barRenderer->isTextureRectRotated(), _barTextureSize);

    _barRenderer->setCapInsets(_capInsetsBarRenderer);
}
    
const Rect& Slider::getCapInsetsBarRenderer()const
{
    return _capInsetsBarRenderer;
}

void Slider::setCapInsetProgressBarRenderer(const Rect &capInsets)
{
    _capInsetsProgressBarRenderer = ui::Helper::restrictCapInsetRect(capInsets, _progressBarRenderer->getContentSize());

    if (!_scale9Enabled)
    {
        return;
    }
    // textureRect should be restored in order to calculate the scale9 correctly
    // https://github.com/cocos2d/cocos2d-x/issues/16928
    _progressBarRenderer->setTextureRect(_originalProgressBarRect, _progressBarRenderer->isTextureRectRotated(), _progressBarTextureSize);

    _progressBarRenderer->setCapInsets(_capInsetsProgressBarRenderer);
}
    
const Rect& Slider::getCapInsetsProgressBarRenderer()const
{
    return _capInsetsProgressBarRenderer;
}

void Slider::loadSlidBallTextures(const std::string& normal,
                                      const std::string& pressed,
                                      const std::string& disabled,
                                      TextureResType texType)
{
    loadSlidBallTextureNormal(normal, texType);
    loadSlidBallTexturePressed(pressed,texType);
    loadSlidBallTextureDisabled(disabled,texType);
}

void Slider::loadSlidBallTextureNormal(const std::string& normal,TextureResType texType)
{
    _slidBallNormalTextureFile = normal;
    _ballNTexType = texType;
    if (normal.empty())
    {
        _slidBallNormalRenderer->init();
    }
    else
    {
        switch (_ballNTexType)
        {
        case TextureResType::LOCAL:
            _slidBallNormalRenderer->setTexture(normal);
            break;
        case TextureResType::PLIST:
            _slidBallNormalRenderer->setSpriteFrame(normal);
            break;
        default:
            break;
        }
    }
    this->updateChildrenDisplayedRGBA();
}
void Slider::loadSlidBallTextureNormal(SpriteFrame* spriteframe)
{
    _slidBallNormalRenderer->setSpriteFrame(spriteframe);
    this->updateChildrenDisplayedRGBA();
}

void Slider::loadSlidBallTexturePressed(const std::string& pressed,TextureResType texType)
{
    _slidBallPressedTextureFile = pressed;
    _isSliderBallPressedTextureLoaded = !pressed.empty();
    _ballPTexType = texType;
    if (pressed.empty())
    {
        _slidBallPressedRenderer->init();
    }
    else
    {
        switch (_ballPTexType)
        {
        case TextureResType::LOCAL:
            _slidBallPressedRenderer->setTexture(pressed);
            break;
        case TextureResType::PLIST:
            _slidBallPressedRenderer->setSpriteFrame(pressed);
            break;
        default:
            break;
        }
    }
    this->updateChildrenDisplayedRGBA();
}


void Slider::loadSlidBallTexturePressed(SpriteFrame* spriteframe)
{
    _slidBallPressedRenderer->setSpriteFrame(spriteframe);
    this->updateChildrenDisplayedRGBA();
}

void Slider::loadSlidBallTextureDisabled(const std::string& disabled,TextureResType texType)
{
    _slidBallDisabledTextureFile = disabled;
    _isSliderBallDisabledTexturedLoaded = !disabled.empty();
    _ballDTexType = texType;
    if (disabled.empty())
    {
        _slidBallDisabledRenderer->init();
    }
    else
    {
        switch (_ballDTexType)
        {
        case TextureResType::LOCAL:
            _slidBallDisabledRenderer->setTexture(disabled);
            break;
        case TextureResType::PLIST:
            _slidBallDisabledRenderer->setSpriteFrame(disabled);
            break;
        default:
            break;
        }
    }
    this->updateChildrenDisplayedRGBA();
}

void Slider::loadSlidBallTextureDisabled(SpriteFrame* spriteframe)
{
    _slidBallDisabledRenderer->setSpriteFrame(spriteframe);
    this->updateChildrenDisplayedRGBA();
}

void Slider::setMaxPercent(int percent)
{
    _maxPercent = percent;
}

int Slider::getMaxPercent()const
{
    return _maxPercent;
}

void Slider::setPercent(int percent)
{
    if (percent > _maxPercent)
    {
        percent = _maxPercent;
    }
    if (percent < 0)
    {
        percent = 0;
    }
    _percent = percent;
    float res = 1.0 * percent / _maxPercent;
    float dis = _barLength * res;
    _slidBallRenderer->setPosition(dis, _contentSize.height / 2.0f);
    if (_scale9Enabled)
    {
        _progressBarRenderer->setPreferredSize(Size(dis,_contentSize.height));
    }
    else
    {
        Rect rect = _progressBarRenderer->getTextureRect();
        rect.size.width = _progressBarTextureSize.width * res;
        _progressBarRenderer->setTextureRect(rect, _progressBarRenderer->isTextureRectRotated(), rect.size);
    }
}
    
bool Slider::hitTest(const cocos2d::Vec2 &pt, const Camera *camera, Vec3* /*p*/) const
{
    Rect rect;
    rect.size = _slidBallNormalRenderer->getContentSize();
    auto w2l = _slidBallNormalRenderer->getWorldToNodeTransform();

    Rect sliderBarRect;
    sliderBarRect.size = this->_barRenderer->getContentSize();
    auto barW2l = this->_barRenderer->getWorldToNodeTransform();
    return isScreenPointInRect(pt, camera, w2l, rect, nullptr) || isScreenPointInRect(pt, camera, barW2l, sliderBarRect, nullptr);
}

bool Slider::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    bool pass = Widget::onTouchBegan(touch, unusedEvent);
    if (_hitted)
    {
        setPercent(getPercentWithBallPos(_touchBeganPosition));
        percentChangedEvent(EventType::ON_SLIDEBALL_DOWN);
    }
    return pass;
}

void Slider::onTouchMoved(Touch *touch, Event* /*unusedEvent*/)
{
    _touchMovePosition = touch->getLocation();
    setPercent(getPercentWithBallPos(_touchMovePosition));
    percentChangedEvent(EventType::ON_PERCENTAGE_CHANGED);
}

void Slider::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    Widget::onTouchEnded(touch, unusedEvent);
    percentChangedEvent(EventType::ON_PERCENTAGE_CHANGED);
    percentChangedEvent(EventType::ON_SLIDEBALL_UP);
}

void Slider::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    Widget::onTouchCancelled(touch, unusedEvent);
    percentChangedEvent(EventType::ON_SLIDEBALL_CANCEL);
}

float Slider::getPercentWithBallPos(const Vec2 &pt) const
{
    Vec3 p;
    Widget::hitTest(pt, _hittedByCamera, &p);
    return ((p.x/_barLength) * static_cast<float>(_maxPercent));
}

void Slider::addEventListenerSlider(Ref *target, SEL_SlidPercentChangedEvent selector)
{
    _sliderEventListener = target;
    _sliderEventSelector = selector;
}
    
void Slider::addEventListener(const ccSliderCallback& callback)
{
    _eventCallback = callback;
}

void Slider::percentChangedEvent(EventType event)
{
    this->retain();
    if (_sliderEventListener && _sliderEventSelector)
    {
        (_sliderEventListener->*_sliderEventSelector)(this,SLIDER_PERCENTCHANGED);
    }
    if (_eventCallback)
    {
        _eventCallback(this,event);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(EventType::ON_PERCENTAGE_CHANGED));
    }
    this->release();
}

int Slider::getPercent()const
{
    return _percent;
}

void Slider::onSizeChanged()
{
    Widget::onSizeChanged();
    _barRendererAdaptDirty = true;
    _progressBarRendererDirty = true;
}
    
void Slider::adaptRenderers()
{
    if (_barRendererAdaptDirty)
    {
        barRendererScaleChangedWithSize();
        _barRendererAdaptDirty = false;
    }
    if (_progressBarRendererDirty)
    {
        progressBarRendererScaleChangedWithSize();
        _progressBarRendererDirty = false;
    }
}

Size Slider::getVirtualRendererSize() const
{
    return _barRenderer->getContentSize();
}

Node* Slider::getVirtualRenderer()
{
    return _barRenderer;
}

void Slider::barRendererScaleChangedWithSize()
{
    if (_unifySize)
    {
        _barLength = _contentSize.width;
        _barRenderer->setPreferredSize(_contentSize);
    }
    else if (_ignoreSize)
    {
        
        _barRenderer->setScale(1.0f);
        _barLength = _contentSize.width;
    }
    else
    {
        _barLength = _contentSize.width;
        if (_scale9Enabled)
        {
            _barRenderer->setPreferredSize(_contentSize);
            _barRenderer->setScale(1.0f);
        }
        else
        {
            Size btextureSize = _barTextureSize;
            if (btextureSize.width <= 0.0f || btextureSize.height <= 0.0f)
            {
                _barRenderer->setScale(1.0f);
            }
            else
            {
                float bscaleX = _contentSize.width / btextureSize.width;
                float bscaleY = _contentSize.height / btextureSize.height;
                _barRenderer->setScaleX(bscaleX);
                _barRenderer->setScaleY(bscaleY);
            }
        }
    }
    _barRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
    setPercent(_percent);
}

void Slider::progressBarRendererScaleChangedWithSize()
{
    if (_unifySize)
    {
        _progressBarRenderer->setPreferredSize(_contentSize);
    }
    else if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            Size ptextureSize = _progressBarTextureSize;
            float pscaleX = _contentSize.width / ptextureSize.width;
            float pscaleY = _contentSize.height / ptextureSize.height;
            _progressBarRenderer->setScaleX(pscaleX);
            _progressBarRenderer->setScaleY(pscaleY);
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            _progressBarRenderer->setPreferredSize(_contentSize);
            _progressBarRenderer->setScale(1.0);
        }
        else
        {
            Size ptextureSize = _progressBarTextureSize;
            if (ptextureSize.width <= 0.0f || ptextureSize.height <= 0.0f)
            {
                _progressBarRenderer->setScale(1.0f);
                return;
            }
            float pscaleX = _contentSize.width / ptextureSize.width;
            float pscaleY = _contentSize.height / ptextureSize.height;
            _progressBarRenderer->setScaleX(pscaleX);
            _progressBarRenderer->setScaleY(pscaleY);
        }
    }
    _progressBarRenderer->setPosition(0.0f, _contentSize.height / 2.0f);
    setPercent(_percent);
}

void Slider::onPressStateChangedToNormal()
{
    _slidBallNormalRenderer->setVisible(true);
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer->setVisible(false);
    
    _slidBallNormalRenderer->setGLProgramState(this->getNormalGLProgramState(_slidBallNormalRenderer->getTexture()));
    _slidBallNormalRenderer->setScale(_sliderBallNormalTextureScaleX, _sliderBallNormalTextureScaleY);
}

void Slider::onPressStateChangedToPressed()
{
    _slidBallNormalRenderer->setGLProgramState(this->getNormalGLProgramState(_slidBallNormalRenderer->getTexture()));

    
    if (!_isSliderBallPressedTextureLoaded)
    {
        _slidBallNormalRenderer->setScale(_sliderBallNormalTextureScaleX + _zoomScale,
                                          _sliderBallNormalTextureScaleY + _zoomScale);
    }
    else
    {
        _slidBallNormalRenderer->setVisible(false);
        _slidBallPressedRenderer->setVisible(true);
        _slidBallDisabledRenderer->setVisible(false);
    }
}

void Slider::onPressStateChangedToDisabled()
{
    if (!_isSliderBallDisabledTexturedLoaded)
    {
        _slidBallNormalRenderer->setGLProgramState(this->getGrayGLProgramState(_slidBallNormalRenderer->getTexture()));
        _slidBallNormalRenderer->setVisible(true);
    }
    else
    {
        _slidBallNormalRenderer->setVisible(false);
        _slidBallDisabledRenderer->setVisible(true);
    }
    
    _slidBallNormalRenderer->setScale(_sliderBallNormalTextureScaleX, _sliderBallNormalTextureScaleY);
    
    _slidBallPressedRenderer->setVisible(false);
}
    
    
void Slider::setZoomScale(float scale)
{
    _zoomScale = scale;
}

float Slider::getZoomScale()const
{
    return _zoomScale;
}


std::string Slider::getDescription() const
{
    return "Slider";
}

Widget* Slider::createCloneInstance()
{
    return Slider::create();
}

void Slider::copySpecialProperties(Widget *widget)
{
    Slider* slider = dynamic_cast<Slider*>(widget);
    if (slider)
    {
        _prevIgnoreSize = slider->_prevIgnoreSize;
        setScale9Enabled(slider->_scale9Enabled);

        // clone the inner sprite: https://github.com/cocos2d/cocos2d-x/issues/16928
        slider->_barRenderer->copyTo(_barRenderer);
        setupBarTexture();
        slider->_progressBarRenderer->copyTo(_progressBarRenderer);
        setupProgressBarTexture();

        loadSlidBallTextureNormal(slider->_slidBallNormalRenderer->getSpriteFrame());
        loadSlidBallTexturePressed(slider->_slidBallPressedRenderer->getSpriteFrame());
        loadSlidBallTextureDisabled(slider->_slidBallDisabledRenderer->getSpriteFrame());
        setPercent(slider->getPercent());
        setMaxPercent(slider->getMaxPercent());
        _isSliderBallPressedTextureLoaded = slider->_isSliderBallPressedTextureLoaded;
        _isSliderBallDisabledTexturedLoaded = slider->_isSliderBallDisabledTexturedLoaded;
        _sliderEventListener = slider->_sliderEventListener;
        _sliderEventSelector = slider->_sliderEventSelector;
        _eventCallback = slider->_eventCallback;
        _ccEventCallback = slider->_ccEventCallback;
    }
}

Sprite* Slider::getSlidBallNormalRenderer() const {
    return _slidBallNormalRenderer;
}

Sprite* Slider::getSlidBallPressedRenderer() const {
    return _slidBallPressedRenderer;
}

Sprite* Slider::getSlidBallDisabledRenderer() const {
    return _slidBallDisabledRenderer;
}

Node* Slider::getSlidBallRenderer() const {
    return _slidBallRenderer;
}

ResourceData Slider::getBackFile()
{
    ResourceData rData;
    rData.type = (int)_barTexType;
    rData.file = _textureFile;
    return rData;
}
ResourceData Slider::getProgressBarFile()
{
    ResourceData rData;
    rData.type = (int)_progressBarTexType;
    rData.file = _progressBarTextureFile;
    return rData;
}
ResourceData Slider::getBallNormalFile()
{
    ResourceData rData;
    rData.type = (int)_ballNTexType;
    rData.file = _slidBallNormalTextureFile;
    return rData;
}
ResourceData Slider::getBallPressedFile()
{
    ResourceData rData;
    rData.type = (int)_ballPTexType;
    rData.file = _slidBallPressedTextureFile;
    return rData;
}
ResourceData Slider::getBallDisabledFile()
{
    ResourceData rData;
    rData.type = (int)_ballDTexType;
    rData.file = _slidBallDisabledTextureFile;
    return rData;
}

}

NS_CC_END
