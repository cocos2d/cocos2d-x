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

#include "ui/UIScrollBar.h"
#include "ui/UIScale9Sprite.h"
#include "ui/UIHelper.h"
#include "2d/CCSprite.h"
#include "2d/CCCamera.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerMouse.h"
#include "base/CCEventDispatcher.h"

NS_CC_BEGIN

namespace ui {
    
static const int BASEBAR_RENDERER_Z = (-2);
static const int SLIDBALL_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(ScrollBar)
    
ScrollBar::ScrollBar():
_barRenderer(nullptr),
_barTextureSize(Size::ZERO),
_slidBallNormalRenderer(nullptr),
_slidBallPressedRenderer(nullptr),
_slidBallDisabledRenderer(nullptr),
_slidBallMouseOverRenderer(nullptr),
_slidBallRenderer(nullptr),
_barLength(0.f),
_percent(0.f),
_scale9Enabled(false),
_prevIgnoreSize(true),
_zoomScale(0.1f),
_sliderBallNormalTextureScaleX(1.0),
_sliderBallNormalTextureScaleY(1.0),
_isSliderBallPressedTextureLoaded(false),
_isSliderBallDisabledTexturedLoaded(false),
_isSliderBallMouseOverTexturedLoaded(false),
_capInsetsBarRenderer(Rect::ZERO),
_sliderEventListener(nullptr),
_sliderEventSelector(nullptr),
_eventCallback(nullptr),
_barTexType(TextureResType::LOCAL),
_ballNTexType(TextureResType::LOCAL),
_ballPTexType(TextureResType::LOCAL),
_ballDTexType(TextureResType::LOCAL),
_ballMTexType(TextureResType::LOCAL),
_barRendererAdaptDirty(true),
_textureFile(""),
_slidBallNormalTextureFile(""),
_slidBallPressedTextureFile(""),
_slidBallDisabledTextureFile(""),
_slidBallMouseOverTextureFile(""),
_imageScale(1.0f)
{
    setTouchEnabled(true);
}

ScrollBar::~ScrollBar()
{
    _sliderEventListener = nullptr;
    _sliderEventSelector = nullptr;
    
    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(_mouseListener);
    _mouseListener = nullptr;
    
    if (_dataScrollView)
    {
        _dataScrollView->removeScrollBarEventListener(this);
        _dataScrollView = nullptr;
    }
}

ScrollBar* ScrollBar::create()
{
    ScrollBar* widget = new (std::nothrow) ScrollBar();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
ScrollBar* ScrollBar::create(const std::string& barTextureName,
                      const std::string& normalBallTextureName,
                      TextureResType resType)
{
    ScrollBar* widget = new (std::nothrow) ScrollBar();
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

bool ScrollBar::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

void ScrollBar::initRenderer()
{
    _barRenderer = Scale9Sprite::create();
    _barRenderer->setScale9Enabled(false);
    addProtectedChild(_barRenderer, BASEBAR_RENDERER_Z, -1);
    
    _slidBallNormalRenderer = Scale9Sprite::create();
    _slidBallPressedRenderer = Scale9Sprite::create();
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer = Scale9Sprite::create();
    _slidBallDisabledRenderer->setVisible(false);
    _slidBallMouseOverRenderer = Scale9Sprite::create();
    _slidBallMouseOverRenderer->setVisible(false);
    
    _slidBallRenderer = Node::create();
    _slidBallRenderer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    _slidBallRenderer->addChild(_slidBallNormalRenderer);
    _slidBallRenderer->addChild(_slidBallPressedRenderer);
    _slidBallRenderer->addChild(_slidBallDisabledRenderer);
    _slidBallRenderer->addChild(_slidBallMouseOverRenderer);
    _slidBallRenderer->setCascadeColorEnabled(true);
    _slidBallRenderer->setCascadeOpacityEnabled(true);
    
    addProtectedChild(_slidBallRenderer, SLIDBALL_RENDERER_Z, -1);
}

void ScrollBar::visit(cocos2d::Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    Widget::visit(renderer, parentTransform, parentFlags);
    
    if (_doLayoutDirty)
    {
        doLayout();
    }
}

void ScrollBar::loadBarTexture(const std::string& fileName, TextureResType texType)
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
            _barRenderer->initWithFile(fileName);
            break;
        case TextureResType::PLIST:
            _barRenderer->initWithSpriteFrameName(fileName);
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
void ScrollBar::loadBarTexture(SpriteFrame* spriteframe)
{
    _barRenderer->initWithSpriteFrame(spriteframe);
    this->setupBarTexture();
}

void ScrollBar::setupBarTexture()
{
    this->updateChildrenDisplayedRGBA();
    _barRendererAdaptDirty = true;
    updateContentSizeWithTextureSize(_barRenderer->getContentSize());
    _barTextureSize = _barRenderer->getContentSize();
}

void ScrollBar::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    
    _scale9Enabled = able;
    _barRenderer->setScale9Enabled(_scale9Enabled);
    
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
    _barRendererAdaptDirty = true;
}
    
bool ScrollBar::isScale9Enabled()const
{
    return _scale9Enabled;
}

void ScrollBar::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void ScrollBar::setCapInsets(const Rect &capInsets)
{
    setCapInsetsBarRenderer(capInsets);
}

void ScrollBar::setCapInsetsBarRenderer(const Rect &capInsets)
{
    _capInsetsBarRenderer = ui::Helper::restrictCapInsetRect(capInsets, _barRenderer->getSprite()->getTexture()->getContentSize());
    if (!_scale9Enabled)
    {
        return;
    }
    _barRenderer->setCapInsets(_capInsetsBarRenderer);
}
    
const Rect& ScrollBar::getCapInsetsBarRenderer()const
{
    return _capInsetsBarRenderer;
}
    
void ScrollBar::setCapInsetsForBallRendereds(const Rect &capInsets)
{
    _ballsCapInsets = capInsets;
    
    _slidBallNormalRenderer->setCapInsets(capInsets);
    _slidBallPressedRenderer->setCapInsets(capInsets);
    _slidBallDisabledRenderer->setCapInsets(capInsets);
    _slidBallMouseOverRenderer->setCapInsets(capInsets);
}
    
const Rect& ScrollBar::getCapInsetsForBallRenerers() const
{
    return _ballsCapInsets;
}

void ScrollBar::loadSlidBallTextures(const std::string& normal,
                                      const std::string& pressed,
                                      const std::string& disabled,
                                      const std::string& mouseOver,
                                      TextureResType texType)
{
    loadSlidBallTextureNormal(normal, texType);
    loadSlidBallTexturePressed(pressed,texType);
    loadSlidBallTextureDisabled(disabled,texType);
    loadSlidBallTextureMouseOver(mouseOver,texType);
}

void ScrollBar::loadSlidBallTextureNormal(const std::string& normal,TextureResType texType)
{
    _slidBallNormalTextureFile = normal;
    _ballNTexType = texType;
    if (normal.empty())
    {
        _slidBallNormalRenderer->resetRender();
    }
    else
    {
        switch (_ballNTexType)
        {
        case TextureResType::LOCAL:
            _slidBallNormalRenderer->initWithFile(normal);
            break;
        case TextureResType::PLIST:
            _slidBallNormalRenderer->initWithSpriteFrameName(normal);
            break;
        default:
            break;
        }
    }
    
    this->updateChildrenDisplayedRGBA();
}
void ScrollBar::loadSlidBallTextureNormal(SpriteFrame* spriteframe)
{
    _slidBallNormalRenderer->setSpriteFrame(spriteframe);
    this->updateChildrenDisplayedRGBA();
}

void ScrollBar::loadSlidBallTexturePressed(const std::string& pressed,TextureResType texType)
{
    _slidBallPressedTextureFile = pressed;
    _isSliderBallPressedTextureLoaded = !pressed.empty();
    _ballPTexType = texType;
    if (pressed.empty())
    {
        _slidBallPressedRenderer->resetRender();
    }
    else
    {
        switch (_ballPTexType)
        {
        case TextureResType::LOCAL:
            _slidBallPressedRenderer->initWithFile(pressed);
            break;
        case TextureResType::PLIST:
            _slidBallPressedRenderer->initWithSpriteFrameName(pressed);
            break;
        default:
            break;
        }
    }
    this->updateChildrenDisplayedRGBA();
}


void ScrollBar::loadSlidBallTexturePressed(SpriteFrame* spriteframe)
{
    _slidBallPressedRenderer->setSpriteFrame(spriteframe);
    this->updateChildrenDisplayedRGBA();
}

void ScrollBar::loadSlidBallTextureDisabled(const std::string& disabled,TextureResType texType)
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
            _slidBallDisabledRenderer->initWithFile(disabled);
            break;
        case TextureResType::PLIST:
            _slidBallDisabledRenderer->initWithSpriteFrameName(disabled);
            break;
        default:
            break;
        }
    }
    this->updateChildrenDisplayedRGBA();
}

void ScrollBar::loadSlidBallTextureDisabled(SpriteFrame* spriteframe)
{
    _slidBallDisabledRenderer->setSpriteFrame(spriteframe);
    this->updateChildrenDisplayedRGBA();
}
    
void ScrollBar::loadSlidBallTextureMouseOver(const std::string& mouseOver,TextureResType texType)
{
    _slidBallMouseOverTextureFile = mouseOver;
    _isSliderBallMouseOverTexturedLoaded = !mouseOver.empty();
    _ballMTexType = texType;
    if (mouseOver.empty())
    {
        _slidBallMouseOverRenderer->resetRender();
    }
    else
    {
        switch (_ballMTexType)
        {
            case TextureResType::LOCAL:
                _slidBallMouseOverRenderer->initWithFile(mouseOver);
                break;
            case TextureResType::PLIST:
                _slidBallMouseOverRenderer->initWithSpriteFrameName(mouseOver);
                break;
            default:
                break;
        }
    }
    this->updateChildrenDisplayedRGBA();
}

void ScrollBar::loadSlidBallTextureMouseOver(SpriteFrame* spriteframe)
{
    _slidBallMouseOverRenderer->setSpriteFrame(spriteframe);
    this->updateChildrenDisplayedRGBA();
}
    
void ScrollBar::setImageScale(float scale)
{
    if(_imageScale != scale)
    {
        _imageScale = scale;
        _barRendererAdaptDirty = true;
    }
}

float ScrollBar::getImageScale() const
{
    return _imageScale;
}
    
void ScrollBar::setBarType(const BarType barType)
{
    _barType = barType;
    _doLayoutDirty = true;
}
    
bool ScrollBar::hitTest(const cocos2d::Vec2 &pt, const Camera *camera, Vec3 *p) const
{
    Rect rect;
    rect.size = _slidBallNormalRenderer->getContentSize();
    auto w2l = _slidBallNormalRenderer->getWorldToNodeTransform();

    Rect sliderBarRect;
    sliderBarRect.size = this->_barRenderer->getContentSize();
    auto barW2l = this->_barRenderer->getWorldToNodeTransform();
    return isScreenPointInRect(pt, camera, w2l, rect, p) || isScreenPointInRect(pt, camera, barW2l, sliderBarRect, p);
}

bool ScrollBar::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    bool pass = Widget::onTouchBegan(touch, unusedEvent);
    if (_hitted)
    {
        bool isBallTouched = false;
        Vec3 p;
        Rect sliderBarRect;
        sliderBarRect.size = _slidBallNormalRenderer->getContentSize();
        auto barW2l = _slidBallNormalRenderer->getWorldToNodeTransform();
        if (isScreenPointInRect(_touchBeganPosition, _hittedByCamera, barW2l, sliderBarRect, &p)) {
            isBallTouched = true;
        }
        
        Widget::hitTest(_touchBeganPosition, _hittedByCamera, &p);
        
        _posDiff = {0.f, 0.f};
        if (isBallTouched) {
            
            if (BarType::kHorizontal == _barType) {
                _posDiff = {p.x - _slidBallRenderer->getPosition().x, 0.f};
            }
            else{
                _posDiff = {0.f, p.y - _slidBallRenderer->getPosition().y};
            }
        }
        
        setBallPosition(Vec2{p.x, p.y} - _posDiff);
        
        percentChangedEvent(EventType::ON_SLIDEBALL_DOWN);
    }
    return pass;
}

void ScrollBar::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    _touchMovePosition = touch->getLocation();
    
    Vec3 p;
    Widget::hitTest(_touchMovePosition, _hittedByCamera, &p);
    setBallPosition(Vec2{p.x, p.y} - _posDiff);
    
    percentChangedEvent(EventType::ON_PERCENTAGE_CHANGED);
}

void ScrollBar::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    Widget::onTouchEnded(touch, unusedEvent);
    percentChangedEvent(EventType::ON_PERCENTAGE_CHANGED);
    percentChangedEvent(EventType::ON_SLIDEBALL_UP);
}

void ScrollBar::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    Widget::onTouchCancelled(touch, unusedEvent);
    percentChangedEvent(EventType::ON_SLIDEBALL_CANCEL);
}

void ScrollBar::addEventListenerSlider(Ref *target, SEL_ScrollBarPercentChangedEvent selector)
{
    _sliderEventListener = target;
    _sliderEventSelector = selector;
}
    
void ScrollBar::addEventListener(const ccSliderCallback& callback)
{
    _eventCallback = callback;
}

float ScrollBar::getPercent()const
{
    if (BarType::kVertical == _barType)
    {
        return 100.0f - _percent;
    }
    return _percent;
}

void ScrollBar::onSizeChanged()
{
    Widget::onSizeChanged();
    _barRendererAdaptDirty = true;
}
    
void ScrollBar::adaptRenderers()
{
    if (_barRendererAdaptDirty)
    {
        barRendererScaleChangedWithSize();
        _barRendererAdaptDirty = false;
    }
}

Size ScrollBar::getVirtualRendererSize() const
{
    return _barRenderer->getContentSize();
}

Node* ScrollBar::getVirtualRenderer()
{
    return _barRenderer;
}

void ScrollBar::barRendererScaleChangedWithSize()
{
    _doLayoutDirty = true;
    _doCalcBackgroundSize = true;
}
    
void ScrollBar::setScrollView(cocos2d::ui::ScrollView *scrollView)
{
    if (!scrollView)
    {
        if (_dataScrollView)
        {
            _dataScrollView->removeScrollBarEventListener(this);
            _dataScrollView = nullptr;
        }
    }
    else
    {
        if (_dataScrollView != scrollView)
        {
            _dataScrollView = scrollView;
            _dataScrollView->addScrollBarEventListener(this, [this](cocos2d::ui::ScrollBar *scrollBar, cocos2d::Ref* target, cocos2d::ui::ScrollView::EventType type)
            {
                if (scrollBar == this)
                {
                    updateBarPosition();
                }
            });

            _mouseListener = cocos2d::EventListenerMouse::create();
            _mouseListener->onMouseScroll = [this](cocos2d::Event *e)
            {
                cocos2d::EventMouse *mouseEvent = dynamic_cast<cocos2d::EventMouse *>(e);
                if (mouseEvent)
                {
                    this->updateByWheelMouse(mouseEvent->getScrollX(), -mouseEvent->getScrollY());
                }
            };
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_mouseListener, this);
        }
        
        if (_barType == BarType::kVertical)
        {
            setWindowSize({_dataScrollView->getContentSize().width, _dataScrollView->getContentSize().height});
            setSizeOfContent({_dataScrollView->getInnerContainer()->getContentSize().width, _dataScrollView->getInnerContainer()->getContentSize().height});
        }
        else
        {
            setWindowSize({_dataScrollView->getContentSize().height, _dataScrollView->getContentSize().width});
            setSizeOfContent({_dataScrollView->getInnerContainer()->getContentSize().height, _dataScrollView->getInnerContainer()->getContentSize().width});
        }
        
        updateBarPosition(true);
    }
}
    
void ScrollBar::updateBarPosition(bool isSetPercent)
{
    if (!_slidBallPressedRenderer->isVisible())
    {
        if (BarType::kVertical == _barType)
        {
            float minY = _dataScrollView->getContentSize().height - _dataScrollView->getInnerContainerSize().height;
            float h = -minY;
            if (h > 0)
            {
                float percent = (h - (_dataScrollView->getInnerContainerPosition().y - minY)) * 100.0f / h;
                
                if (isSetPercent)
                {
                    setPercent(percent);
                }
                else
                {
                    updatePercent(percent);
                }
            }
        }
        else
        {
            float minX = _dataScrollView->getContentSize().width - _dataScrollView->getInnerContainerSize().width;
            float w = -minX;
            if (w > 0)
            {
                float percent = (w - (_dataScrollView->getInnerContainerPosition().x - minX)) * 100.0f / w;
                
                if (isSetPercent)
                {
                    setPercent(percent);
                }
                else
                {
                    updatePercent(percent);
                }
            }
        }

    }
}
    
void ScrollBar::setPercent(float percent)
{
    if (BarType::kVertical == _barType)
    {
        percent = 100.f - percent;
    }
    
    updatePercent(percent);
}

void ScrollBar::updatePercent(float percent)
{
    _percent = std::min(std::max(percent, 0.f), 100.f);
    
    Vec2 sliderPos;
    const float barLen = (_barType == BarType::kHorizontal) ? _contentSize.width : _contentSize.height;
    auto ballRenderer = _slidBallNormalRenderer;
    const float minPosX = ballRenderer->getContentSize().width * ballRenderer->getAnchorPoint().x * ballRenderer->getScaleX();
    const float maxPosX = barLen - ballRenderer->getContentSize().width * (1 - ballRenderer->getAnchorPoint().x) * ballRenderer->getScaleX();
    
    if (_barType == BarType::kHorizontal)
    {
        sliderPos.x = std::min(std::max(barLen * _percent / 100.f, minPosX), maxPosX);
        sliderPos.y = _contentSize.height/2.f-ballRenderer->getContentSize().height*(0.5f + ballRenderer->getAnchorPoint().y) + ballRenderer->getContentSize().height;
    }
    else
    {
        sliderPos.y = std::min(std::max(barLen * _percent / 100.f, minPosX), maxPosX);
        sliderPos.x = _contentSize.width/2.f-ballRenderer->getContentSize().width*(0.5f + ballRenderer->getAnchorPoint().x) + ballRenderer->getContentSize().width;
    }
    
    _slidBallRenderer->setPosition(sliderPos);
    
}

void ScrollBar::setBallPosition(const cocos2d::Vec2 & pos)
{
    auto posToSet       = pos;
    const float barLen  = (BarType::kHorizontal == _barType) ? _contentSize.width : _contentSize.height;
    auto ballRenderer   = _slidBallNormalRenderer;
    const float minPosX = ballRenderer->getContentSize().width * ballRenderer->getAnchorPoint().x * ballRenderer->getScaleX();
    const float maxPosX = barLen - ballRenderer->getContentSize().width * (1 - ballRenderer->getAnchorPoint().x) * ballRenderer->getScaleX();
    
    if (BarType::kHorizontal == _barType)
    {
        posToSet.x = std::min(std::max(pos.x, minPosX), maxPosX);
        posToSet.y = _slidBallRenderer->getPosition().y;
    }
    else
    {
        posToSet.y = std::min(std::max(pos.y, minPosX), maxPosX);
        posToSet.x = _slidBallRenderer->getPosition().x;
    }
    
    _slidBallRenderer->setPosition(posToSet);
    _percent = calcPercentByBallPos(pos);
}

void ScrollBar::percentChangedEvent(EventType event)
{
    this->retain();
    if (_sliderEventListener && _sliderEventSelector)
    {
        (_sliderEventListener->*_sliderEventSelector)(this,SCOLBAR_PERCENTCHANGED);
    }
    if (_eventCallback)
    {
        _eventCallback(this,event);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(EventType::ON_PERCENTAGE_CHANGED));
    }
    
    if (_dataScrollView && _slidBallPressedRenderer->isVisible())
    {
        if (_barType == BarType::kVertical)
        {
            _dataScrollView->jumpToPercentVertical(100.0f - getPercent());
        }
        else
        {
            _dataScrollView->jumpToPercentHorizontal(getPercent());
        }
    }
    
    this->release();
}
    
void ScrollBar::updateByWheelMouse(float scrollX, float scrollY)
{
    if (!isVisible())
        return ;
    
    const cocos2d::Size& bbox = _dataScrollView->getContentSize();
    if (_barType == BarType::kVertical && fabs(scrollY) > MATH_EPSILON)
    {
        bool canScrolling = bbox.height < _dataScrollView->getInnerContainerSize().height;
        
        if (canScrolling)
        {
            bool isGreatZero = (scrollY > 0.0f);
            float addPercent = (isGreatZero ? ceilf(scrollY) : floorf(scrollY));
            float newPrecent = _percent + addPercent;
            
            if (0 <= newPrecent && newPrecent <= 100.0f)
            {
                updatePercent(newPrecent);
                _dataScrollView->jumpToPercentVertical(getPercent());
            }
            else
            {
                if (newPrecent < 0)
                {
                    updatePercent(0);
                    _dataScrollView->jumpToPercentVertical(getPercent());
                }
                else if (newPrecent > 100)
                {
                    updatePercent(100);
                    _dataScrollView->jumpToPercentVertical(getPercent());
                }
            }
        }
    }
    else if (_barType == BarType::kHorizontal && fabs(scrollX) > MATH_EPSILON)
    {
        bool canScrolling = bbox.width < _dataScrollView->getInnerContainerSize().width;
        
        if (canScrolling)
        {
            bool isGreatZero = (scrollX > 0.0f);
            float addPercent = (isGreatZero ? ceilf(scrollX) : floorf(scrollX));
            float newPrecent = _percent + addPercent;
            
            if (0 <= newPrecent && newPrecent <= 100.0f)
            {
                updatePercent(newPrecent);
                _dataScrollView->jumpToPercentHorizontal(getPercent());
            }
            else
            {
                if (newPrecent < 0)
                {
                    updatePercent(0);
                    _dataScrollView->jumpToPercentHorizontal(getPercent());
                }
                else if (newPrecent > 100)
                {
                    updatePercent(100);
                    _dataScrollView->jumpToPercentHorizontal(getPercent());
                }
            }
        }

    }
}

void ScrollBar::onPressStateChangedToNormal()
{
    _slidBallNormalRenderer->setVisible(true);
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer->setVisible(false);
    _slidBallMouseOverRenderer->setVisible(false);
    
    if (_slidBallNormalRenderer && _slidBallNormalRenderer->getSprite()) {
        _slidBallNormalRenderer->setGLProgramState(this->getNormalGLProgramState(_slidBallNormalRenderer->getSprite()->getTexture()));
    }
    _slidBallRenderer->setScale(1.0);
}

void ScrollBar::onPressStateChangedToPressed()
{
    _slidBallNormalRenderer->setGLProgramState(this->getNormalGLProgramState(_slidBallNormalRenderer->getSprite()->getTexture()));

    _slidBallRenderer->setScale(1.0 + _zoomScale);
    
    if (_isSliderBallPressedTextureLoaded)
    {
        _slidBallNormalRenderer->setVisible(false);
        _slidBallPressedRenderer->setVisible(true);
        _slidBallDisabledRenderer->setVisible(false);
    }
    _slidBallMouseOverRenderer->setVisible(false);
}

void ScrollBar::onPressStateChangedToDisabled()
{
    if (!_isSliderBallDisabledTexturedLoaded)
    {
        _slidBallNormalRenderer->setGLProgramState(this->getGrayGLProgramState(_slidBallNormalRenderer->getSprite()->getTexture()));
        _slidBallNormalRenderer->setVisible(true);
    }
    else
    {
        _slidBallNormalRenderer->setVisible(false);
        _slidBallDisabledRenderer->setVisible(true);
    }
    
    _slidBallRenderer->setScale(1.0);
    
    _slidBallPressedRenderer->setVisible(false);
    _slidBallMouseOverRenderer->setVisible(false);
}
    
void ScrollBar::onPressStateChangedToMouseOver()
{
    if (!_isSliderBallMouseOverTexturedLoaded)
    {
        _slidBallNormalRenderer->setVisible(true);
    }
    else
    {
        _slidBallNormalRenderer->setVisible(false);
        _slidBallMouseOverRenderer->setVisible(true);
    }
    
    _slidBallRenderer->setScale(1.0);
    
    _slidBallPressedRenderer->setVisible(false);
    _slidBallDisabledRenderer->setVisible(false);
}
    
    
void ScrollBar::setZoomScale(float scale)
{
    _zoomScale = scale;
}

float ScrollBar::getZoomScale()const
{
    return _zoomScale;
}

std::string ScrollBar::getDescription() const
{
    return "ScrollBar";
}

Widget* ScrollBar::createCloneInstance()
{
    return ScrollBar::create();
}

void ScrollBar::copySpecialProperties(Widget *widget)
{
    ScrollBar* slider = dynamic_cast<ScrollBar*>(widget);
    if (slider)
    {
        _prevIgnoreSize = slider->_prevIgnoreSize;
        setScale9Enabled(slider->_scale9Enabled);
        auto barSprite = slider->_barRenderer->getSprite();
        if (nullptr != barSprite)
        {
            loadBarTexture(barSprite->getSpriteFrame());
        }

        loadSlidBallTextureNormal(slider->_slidBallNormalRenderer->getSprite()->getSpriteFrame());
        loadSlidBallTexturePressed(slider->_slidBallPressedRenderer->getSprite()->getSpriteFrame());
        loadSlidBallTextureDisabled(slider->_slidBallDisabledRenderer->getSprite()->getSpriteFrame());
        loadSlidBallTextureMouseOver(slider->_slidBallMouseOverRenderer->getSprite()->getSpriteFrame());
        setPercent(slider->getPercent());
        _isSliderBallPressedTextureLoaded = slider->_isSliderBallPressedTextureLoaded;
        _isSliderBallDisabledTexturedLoaded = slider->_isSliderBallDisabledTexturedLoaded;
        _isSliderBallMouseOverTexturedLoaded = slider->_isSliderBallMouseOverTexturedLoaded;
        _sliderEventListener = slider->_sliderEventListener;
        _sliderEventSelector = slider->_sliderEventSelector;
        _eventCallback = slider->_eventCallback;
        _ccEventCallback = slider->_ccEventCallback;
    }
}

ResourceData ScrollBar::getBackFile()
{
    ResourceData rData;
    rData.type = (int)_barTexType;
    rData.file = _textureFile;
    return rData;
}

ResourceData ScrollBar::getBallNormalFile()
{
    ResourceData rData;
    rData.type = (int)_ballNTexType;
    rData.file = _slidBallNormalTextureFile;
    return rData;
}
ResourceData ScrollBar::getBallPressedFile()
{
    ResourceData rData;
    rData.type = (int)_ballPTexType;
    rData.file = _slidBallPressedTextureFile;
    return rData;
}
ResourceData ScrollBar::getBallDisabledFile()
{
    ResourceData rData;
    rData.type = (int)_ballDTexType;
    rData.file = _slidBallDisabledTextureFile;
    return rData;
}
ResourceData ScrollBar::getBallMouseOverFile()
{
    ResourceData rData;
    rData.type = (int)_ballMTexType;
    rData.file = _slidBallMouseOverTextureFile;
    return rData;
}

Node *ScrollBar::getSlidBarNode() const
{
    return _slidBallRenderer;
}
    
void ScrollBar::setWindowSize(const cocos2d::Size & winSize)
{
    _windowSize = winSize;
}
    
void ScrollBar::setSizeOfContent(const cocos2d::Size & sizeOfContent)
{
    _sizeOfContent = sizeOfContent;
    
    float contentLen = 0;
    float winLen = 0;
    float barLen = 0;
    
    switch (_barType) {
        case BarType::kHorizontal:
        {
            contentLen = std::max(sizeOfContent.width, _windowSize.width);
            winLen = _windowSize.width;
            barLen = _contentSize.width;
            
            float sliderDesiredLen = winLen*barLen/contentLen;
            
            setContentSizeForBar(sliderDesiredLen, getContentSize().height);
            
            break;
        }
        case BarType::kVertical:
        {
            contentLen = std::max(sizeOfContent.height, _windowSize.height);
            winLen = _windowSize.height;
            barLen = _contentSize.height;
            
            float sliderDesiredLen = winLen*barLen/contentLen;
            
            setContentSizeForBar(getContentSize().width, sliderDesiredLen);
            
            break;
        }
            
        default:
            break;
    }
}
    
void ScrollBar::setContentSizeForBar(float w, float h)
{
    _sizeForBar = Size(w, h);
    _doLayoutDirty = true;
    _doCalcBarSize = true;
}

float ScrollBar::calcPercentByBallPos(const cocos2d::Vec2 & pos) const
{
    auto ballRenderer   = _slidBallNormalRenderer;
    const float barLen  = (BarType::kHorizontal == _barType) ? _contentSize.width : _contentSize.height;
    const float minVal  = ballRenderer->getContentSize().width * ballRenderer->getAnchorPoint().x * ballRenderer->getScaleX();
    const float maxVal  = barLen - ballRenderer->getContentSize().width * (1 - ballRenderer->getAnchorPoint().x) * ballRenderer->getScaleX();
    float posVal        = (BarType::kHorizontal == _barType) ? pos.x : pos.y;
    posVal              = std::min(std::max(posVal, minVal), maxVal);
    float percent       = (maxVal - minVal != 0) ? (posVal-minVal) / (maxVal - minVal) * 100.f : 0.0f;
        
    return percent;
}
    
void ScrollBar::doLayout()
{
    if (_barType == BarType::kVertical)
    {
        _slidBallRenderer->setRotation(90.0f);
        _barRenderer->setRotation(90.0f);
    }

    if (_doCalcBarSize)
    {
        _doCalcBarSize = false;
        recalcSizeScrollBar();
    }
    
    if (_doCalcBackgroundSize)
    {
        _doCalcBackgroundSize = false;
        recalcSizeBarBackground();
    }
    
    _doLayoutDirty = false;
}
    
void ScrollBar::recalcSizeScrollBar()
{
    Size horizontalSize = Size(_sizeForBar.width / _imageScale, _sizeForBar.height / _imageScale);
    
    if (getBarType() == ScrollBar::BarType::kVertical)
    {
        Size verticalSize = Size(horizontalSize.height, horizontalSize.width);
        
        if (verticalSize.width < _barTextureSize.width)
            verticalSize.width = _barTextureSize.width;
        
        if (_slidBallNormalRenderer) {
            _slidBallNormalRenderer->setContentSize(verticalSize);
            _slidBallNormalRenderer->setScale(_imageScale);
        }
        
        if (_slidBallPressedRenderer) {
            _slidBallPressedRenderer->setContentSize(verticalSize);
            _slidBallPressedRenderer->setScale(_imageScale);
        }
        
        if (_slidBallDisabledRenderer) {
            _slidBallDisabledRenderer->setContentSize(verticalSize);
            _slidBallDisabledRenderer->setScale(_imageScale);
        }
        
        if (_slidBallMouseOverRenderer) {
            _slidBallMouseOverRenderer->setContentSize(verticalSize);
            _slidBallMouseOverRenderer->setScale(_imageScale);
        }
    }
    else
    {
        if (horizontalSize.width < _barTextureSize.width)
            horizontalSize.width = _barTextureSize.width;
        
        if (_slidBallNormalRenderer) {
            _slidBallNormalRenderer->setContentSize(horizontalSize);
            _slidBallNormalRenderer->setScale(_imageScale);
        }
        
        if (_slidBallPressedRenderer) {
            _slidBallPressedRenderer->setContentSize(horizontalSize);
            _slidBallPressedRenderer->setScale(_imageScale);
        }
        
        if (_slidBallDisabledRenderer) {
            _slidBallDisabledRenderer->setContentSize(horizontalSize);
            _slidBallDisabledRenderer->setScale(_imageScale);
        }
        
        if (_slidBallMouseOverRenderer) {
            _slidBallMouseOverRenderer->setContentSize(horizontalSize);
            _slidBallMouseOverRenderer->setScale(_imageScale);
        }
    }
}
    
void ScrollBar::recalcSizeBarBackground()
{
    if (_barType == BarType::kHorizontal)
    {
        _barLength = _contentSize.width;
        
        if (_unifySize)
        {
            _barRenderer->setPreferredSize(_contentSize);
        }
        else if (_ignoreSize)
        {
            _barRenderer->setScale(1.0f);
        }
        else
        {
            if (_scale9Enabled)
            {
                _barRenderer->setPreferredSize(_contentSize / _imageScale);
                _barRenderer->setScale(_imageScale);
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
    }
    else
    {
        _barLength = _contentSize.height;
        
        if (_unifySize)
        {
            _barRenderer->setPreferredSize(Size(_contentSize.height, _contentSize.width));
        }
        else if (_ignoreSize)
        {
            
            _barRenderer->setScale(1.0f);
        }
        else
        {
            if (_scale9Enabled)
            {
                _barRenderer->setPreferredSize(Size(_contentSize.height / _imageScale, _contentSize.width / _imageScale));
                _barRenderer->setScale(_imageScale);
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
                    _barRenderer->setScaleX(bscaleY);
                    _barRenderer->setScaleY(bscaleX);
                }
            }
        }
    }
    
    _barRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
    setPercent(_percent);
}
    
}

NS_CC_END
