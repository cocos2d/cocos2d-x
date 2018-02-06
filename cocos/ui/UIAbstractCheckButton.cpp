/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "ui/UIAbstractCheckButton.h"
#include "2d/CCSprite.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

NS_CC_BEGIN

namespace ui {

static const int BACKGROUNDBOX_RENDERER_Z = (-1);
static const int BACKGROUNDSELECTEDBOX_RENDERER_Z = (-1);
static const int FRONTCROSS_RENDERER_Z = (-1);
static const int BACKGROUNDBOXDISABLED_RENDERER_Z = (-1);
static const int FRONTCROSSDISABLED_RENDERER_Z = (-1);

AbstractCheckButton::AbstractCheckButton():
_backGroundBoxRenderer(nullptr),
_backGroundSelectedBoxRenderer(nullptr),
_frontCrossRenderer(nullptr),
_backGroundBoxDisabledRenderer(nullptr),
_frontCrossDisabledRenderer(nullptr),
_isSelected(true),
_isBackgroundSelectedTextureLoaded(false),
_isBackgroundDisabledTextureLoaded(false),
_isFrontCrossDisabledTextureLoaded(false),
_backGroundTexType(TextureResType::LOCAL),
_backGroundSelectedTexType(TextureResType::LOCAL),
_frontCrossTexType(TextureResType::LOCAL),
_backGroundDisabledTexType(TextureResType::LOCAL),
_frontCrossDisabledTexType(TextureResType::LOCAL),
_zoomScale(0.1f),
_backgroundTextureScaleX(1.0),
_backgroundTextureScaleY(1.0),
_backGroundFileName(""),
_backGroundSelectedFileName(""),
_frontCrossFileName(""),
_backGroundDisabledFileName(""),
_frontCrossDisabledFileName(""),
_backGroundBoxRendererAdaptDirty(true),
_backGroundSelectedBoxRendererAdaptDirty(true),
_frontCrossRendererAdaptDirty(true),
_backGroundBoxDisabledRendererAdaptDirty(true),
_frontCrossDisabledRendererAdaptDirty(true)
{
    setTouchEnabled(true);
}

AbstractCheckButton::~AbstractCheckButton()
{
}

bool AbstractCheckButton::init(const std::string& backGround,
                    const std::string& backGroundSelected,
                    const std::string& cross,
                    const std::string& backGroundDisabled,
                    const std::string& frontCrossDisabled,
                    TextureResType texType)
{
    bool ret = true;
    do
    {
        if (!Widget::init())
        {
            ret = false;
            break;
        }
        
        setSelected(false);
        loadTextures(backGround, backGroundSelected, cross, backGroundDisabled, frontCrossDisabled, texType);
    } while (0);
    return ret;
}

bool AbstractCheckButton::init()
{
    if (Widget::init())
    {
        setSelected(false);
        return true;
    }
    return false;
}

void AbstractCheckButton::initRenderer()
{
    _backGroundBoxRenderer = Sprite::create();
    _backGroundSelectedBoxRenderer = Sprite::create();
    _frontCrossRenderer = Sprite::create();
    _backGroundBoxDisabledRenderer = Sprite::create();
    _frontCrossDisabledRenderer = Sprite::create();
    
    addProtectedChild(_backGroundBoxRenderer, BACKGROUNDBOX_RENDERER_Z, -1);
    addProtectedChild(_backGroundSelectedBoxRenderer, BACKGROUNDSELECTEDBOX_RENDERER_Z, -1);
    addProtectedChild(_frontCrossRenderer, FRONTCROSS_RENDERER_Z, -1);
    addProtectedChild(_backGroundBoxDisabledRenderer, BACKGROUNDBOXDISABLED_RENDERER_Z, -1);
    addProtectedChild(_frontCrossDisabledRenderer, FRONTCROSSDISABLED_RENDERER_Z, -1);
}

void AbstractCheckButton::loadTextures(const std::string& backGround,
                            const std::string& backGroundSelected,
                            const std::string& cross,
                            const std::string& backGroundDisabled,
                            const std::string& frontCrossDisabled,
                            TextureResType texType)
{
    loadTextureBackGround(backGround,texType);
    loadTextureBackGroundSelected(backGroundSelected,texType);
    loadTextureFrontCross(cross,texType);
    loadTextureBackGroundDisabled(backGroundDisabled,texType);
    loadTextureFrontCrossDisabled(frontCrossDisabled,texType);
}

void AbstractCheckButton::loadTextureBackGround(const std::string& backGround,TextureResType texType)
{
    _backGroundFileName = backGround;

    _backGroundTexType = texType;
    switch (_backGroundTexType)
    {
        case TextureResType::LOCAL:
            _backGroundBoxRenderer->setTexture(backGround);
            break;
        case TextureResType::PLIST:
            _backGroundBoxRenderer->setSpriteFrame(backGround);
            break;
        default:
            break;
    }
    
    this->setupBackgroundTexture();
}

void AbstractCheckButton::setupBackgroundTexture()
{
    
    this->updateChildrenDisplayedRGBA();
    
    updateContentSizeWithTextureSize(_backGroundBoxRenderer->getContentSize());
    _backGroundBoxRendererAdaptDirty = true;
}

void AbstractCheckButton::loadTextureBackGround(SpriteFrame* spriteFrame)
{
    _backGroundBoxRenderer->setSpriteFrame(spriteFrame);
    this->setupBackgroundTexture();
}

void AbstractCheckButton::loadTextureBackGroundSelected(const std::string& backGroundSelected,TextureResType texType)
{
    _backGroundSelectedFileName = backGroundSelected;
    _isBackgroundSelectedTextureLoaded = !backGroundSelected.empty();

    _backGroundSelectedTexType = texType;
    switch (_backGroundSelectedTexType)
    {
        case TextureResType::LOCAL:
            _backGroundSelectedBoxRenderer->setTexture(backGroundSelected);
            break;
        case TextureResType::PLIST:
            _backGroundSelectedBoxRenderer->setSpriteFrame(backGroundSelected);
            break;
        default:
            break;
    }
    this->setupBackgroundSelectedTexture();
}

void AbstractCheckButton::loadTextureBackGroundSelected(SpriteFrame* spriteframe)
{
    this->_backGroundSelectedBoxRenderer->setSpriteFrame(spriteframe);
    this->setupBackgroundSelectedTexture();
}

void AbstractCheckButton::setupBackgroundSelectedTexture()
{
    this->updateChildrenDisplayedRGBA();
    _backGroundSelectedBoxRendererAdaptDirty = true;
}

void AbstractCheckButton::loadTextureFrontCross(const std::string& cross,TextureResType texType)
{
    _frontCrossFileName = cross;

    _frontCrossTexType = texType;
    switch (_frontCrossTexType)
    {
        case TextureResType::LOCAL:
            _frontCrossRenderer->setTexture(cross);
            break;
        case TextureResType::PLIST:
            _frontCrossRenderer->setSpriteFrame(cross);
            break;
        default:
            break;
    }
    this->setupFrontCrossTexture();
}

void AbstractCheckButton::loadTextureFrontCross(SpriteFrame* spriteFrame)
{
    this->_frontCrossRenderer->setSpriteFrame(spriteFrame);
    this->setupFrontCrossTexture();
}

void AbstractCheckButton::setupFrontCrossTexture()
{
    this->updateChildrenDisplayedRGBA();
    _frontCrossRendererAdaptDirty = true;
}

void AbstractCheckButton::loadTextureBackGroundDisabled(const std::string& backGroundDisabled,TextureResType texType)
{
    _backGroundDisabledFileName = backGroundDisabled;
    _isBackgroundDisabledTextureLoaded = !backGroundDisabled.empty();

    _backGroundDisabledTexType = texType;
    switch (_backGroundDisabledTexType)
    {
        case TextureResType::LOCAL:
            _backGroundBoxDisabledRenderer->setTexture(backGroundDisabled);
            break;
        case TextureResType::PLIST:
            _backGroundBoxDisabledRenderer->setSpriteFrame(backGroundDisabled);
            break;
        default:
            break;
    }
    this->setupBackgroundDisable();
}

void AbstractCheckButton::loadTextureBackGroundDisabled(SpriteFrame* spriteframe)
{
    this->_backGroundBoxDisabledRenderer->setSpriteFrame(spriteframe);
    this->setupBackgroundDisable();
}

void AbstractCheckButton::setupBackgroundDisable()
{
    this->updateChildrenDisplayedRGBA();
    
    _backGroundBoxDisabledRendererAdaptDirty = true;
}

void AbstractCheckButton::loadTextureFrontCrossDisabled(const std::string& frontCrossDisabled,TextureResType texType)
{
    _frontCrossDisabledFileName = frontCrossDisabled;
    _isFrontCrossDisabledTextureLoaded = !frontCrossDisabled.empty();

    _frontCrossDisabledTexType = texType;
    switch (_frontCrossDisabledTexType)
    {
        case TextureResType::LOCAL:
            _frontCrossDisabledRenderer->setTexture(frontCrossDisabled);
            break;
        case TextureResType::PLIST:
            _frontCrossDisabledRenderer->setSpriteFrame(frontCrossDisabled);
            break;
        default:
            break;
    }
    this->setupFrontCrossDisableTexture();

}

void AbstractCheckButton::loadTextureFrontCrossDisabled(SpriteFrame* spriteframe)
{
    this->_frontCrossDisabledRenderer->setSpriteFrame(spriteframe);
    this->setupFrontCrossDisableTexture();
}

void AbstractCheckButton::setupFrontCrossDisableTexture()
{
    this->updateChildrenDisplayedRGBA();
    _frontCrossDisabledRendererAdaptDirty = true;
}

void AbstractCheckButton::onPressStateChangedToNormal()
{
    _backGroundBoxRenderer->setVisible(true);
    _backGroundSelectedBoxRenderer->setVisible(false);
    _backGroundBoxDisabledRenderer->setVisible(false);
    _frontCrossDisabledRenderer->setVisible(false);
    
    _backGroundBoxRenderer->setGLProgramState(this->getNormalGLProgramState(_backGroundBoxRenderer->getTexture()));
    _frontCrossRenderer->setGLProgramState(this->getNormalGLProgramState(_frontCrossRenderer->getTexture()));
    
    
    _backGroundBoxRenderer->setScale(_backgroundTextureScaleX, _backgroundTextureScaleY);
    _frontCrossRenderer->setScale(_backgroundTextureScaleX, _backgroundTextureScaleY);
    
    
    if (_isSelected)
    {
        _frontCrossRenderer->setVisible(true);
        _frontCrossRendererAdaptDirty = true;
    }
}

void AbstractCheckButton::onPressStateChangedToPressed()
{
    _backGroundBoxRenderer->setGLProgramState(this->getNormalGLProgramState(_backGroundBoxRenderer->getTexture()));
    _frontCrossRenderer->setGLProgramState(this->getNormalGLProgramState(_frontCrossRenderer->getTexture()));
    
    if (!_isBackgroundSelectedTextureLoaded)
    {
        _backGroundBoxRenderer->setScale(_backgroundTextureScaleX + _zoomScale,
                                         _backgroundTextureScaleY + _zoomScale);
        _frontCrossRenderer->setScale(_backgroundTextureScaleX + _zoomScale,
                                      _backgroundTextureScaleY + _zoomScale);
    }
    else
    {
        _backGroundBoxRenderer->setVisible(false);
        _backGroundSelectedBoxRenderer->setVisible(true);
        _backGroundBoxDisabledRenderer->setVisible(false);
        _frontCrossDisabledRenderer->setVisible(false);
    }
}

void AbstractCheckButton::onPressStateChangedToDisabled()
{
    if (!_isBackgroundDisabledTextureLoaded
        || !_isFrontCrossDisabledTextureLoaded)
    {
        _backGroundBoxRenderer->setGLProgramState(this->getGrayGLProgramState(_backGroundBoxRenderer->getTexture()));
        _frontCrossRenderer->setGLProgramState(this->getGrayGLProgramState(_backGroundBoxRenderer->getTexture()));
    }
    else
    {
        _backGroundBoxRenderer->setVisible(false);
        _backGroundBoxDisabledRenderer->setVisible(true);
    }
    
    _backGroundSelectedBoxRenderer->setVisible(false);
    _frontCrossRenderer->setVisible(false);
    _backGroundBoxRenderer->setScale(_backgroundTextureScaleX, _backgroundTextureScaleY);
    _frontCrossRenderer->setScale(_backgroundTextureScaleX, _backgroundTextureScaleY);
    
    if (_isSelected)
    {
        _frontCrossDisabledRenderer->setVisible(true);
        _frontCrossDisabledRendererAdaptDirty = true;
    }
}

void AbstractCheckButton::setZoomScale(float scale)
{
    _zoomScale = scale;
}

float AbstractCheckButton::getZoomScale()const
{
    return _zoomScale;
}

void AbstractCheckButton::setSelected(bool selected)
{
    if (selected == _isSelected)
    {
        return;
    }
    _isSelected = selected;
    _frontCrossRenderer->setVisible(_isSelected);
}

bool AbstractCheckButton::isSelected()const
{
    return _isSelected;
}

void AbstractCheckButton::onSizeChanged()
{
    Widget::onSizeChanged();
    _backGroundBoxRendererAdaptDirty = true;
    _backGroundSelectedBoxRendererAdaptDirty = true;
    _frontCrossRendererAdaptDirty = true;
    _backGroundBoxDisabledRendererAdaptDirty = true;
    _frontCrossDisabledRendererAdaptDirty = true;
}

void AbstractCheckButton::adaptRenderers()
{
    if (_backGroundBoxRendererAdaptDirty)
    {
        backGroundTextureScaleChangedWithSize();
        _backGroundBoxRendererAdaptDirty = false;
    }
    if (_backGroundSelectedBoxRendererAdaptDirty)
    {
        backGroundSelectedTextureScaleChangedWithSize();
        _backGroundSelectedBoxRendererAdaptDirty = false;
    }
    if (_frontCrossRendererAdaptDirty)
    {
        frontCrossTextureScaleChangedWithSize();
        _frontCrossRendererAdaptDirty = false;
    }
    if (_backGroundBoxDisabledRendererAdaptDirty)
    {
        backGroundDisabledTextureScaleChangedWithSize();
        _backGroundBoxDisabledRendererAdaptDirty = false;
    }
    if (_frontCrossDisabledRendererAdaptDirty)
    {
        frontCrossDisabledTextureScaleChangedWithSize();
        _frontCrossDisabledRendererAdaptDirty = false;
    }
}

Size AbstractCheckButton::getVirtualRendererSize() const
{
    return _backGroundBoxRenderer->getContentSize();
}

Node* AbstractCheckButton::getVirtualRenderer()
{
    return _backGroundBoxRenderer;
}

void AbstractCheckButton::backGroundTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _backGroundBoxRenderer->setScale(1.0f);
        _backgroundTextureScaleX = _backgroundTextureScaleY = 1.0f;
    }
    else
    {
        Size textureSize = _backGroundBoxRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _backGroundBoxRenderer->setScale(1.0f);
            _backgroundTextureScaleX = _backgroundTextureScaleY = 1.0f;
            return;
        }
        float scaleX = _contentSize.width / textureSize.width;
        float scaleY = _contentSize.height / textureSize.height;
        _backgroundTextureScaleX = scaleX;
        _backgroundTextureScaleY = scaleY;
        _backGroundBoxRenderer->setScaleX(scaleX);
        _backGroundBoxRenderer->setScaleY(scaleY);
    }
    _backGroundBoxRenderer->setPosition(_contentSize.width / 2, _contentSize.height / 2);
}

void AbstractCheckButton::backGroundSelectedTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _backGroundSelectedBoxRenderer->setScale(1.0f);
    }
    else
    {
        Size textureSize = _backGroundSelectedBoxRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _backGroundSelectedBoxRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _contentSize.width / textureSize.width;
        float scaleY = _contentSize.height / textureSize.height;
        _backGroundSelectedBoxRenderer->setScaleX(scaleX);
        _backGroundSelectedBoxRenderer->setScaleY(scaleY);
    }
    _backGroundSelectedBoxRenderer->setPosition(_contentSize.width / 2, _contentSize.height / 2);
}

void AbstractCheckButton::frontCrossTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _frontCrossRenderer->setScale(1.0f);
    }
    else
    {
        Size textureSize = _frontCrossRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _frontCrossRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _contentSize.width / textureSize.width;
        float scaleY = _contentSize.height / textureSize.height;
        _frontCrossRenderer->setScaleX(scaleX);
        _frontCrossRenderer->setScaleY(scaleY);
    }
    _frontCrossRenderer->setPosition(_contentSize.width / 2, _contentSize.height / 2);
}

void AbstractCheckButton::backGroundDisabledTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _backGroundBoxDisabledRenderer->setScale(1.0f);
    }
    else
    {
        Size textureSize = _backGroundBoxDisabledRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _backGroundBoxDisabledRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _contentSize.width / textureSize.width;
        float scaleY = _contentSize.height / textureSize.height;
        _backGroundBoxDisabledRenderer->setScaleX(scaleX);
        _backGroundBoxDisabledRenderer->setScaleY(scaleY);
    }
    _backGroundBoxDisabledRenderer->setPosition(_contentSize.width / 2, _contentSize.height / 2);
}

void AbstractCheckButton::frontCrossDisabledTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _frontCrossDisabledRenderer->setScale(1.0f);
    }
    else
    {
        Size textureSize = _frontCrossDisabledRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _frontCrossDisabledRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _contentSize.width / textureSize.width;
        float scaleY = _contentSize.height / textureSize.height;
        _frontCrossDisabledRenderer->setScaleX(scaleX);
        _frontCrossDisabledRenderer->setScaleY(scaleY);
    }
    _frontCrossDisabledRenderer->setPosition(_contentSize.width / 2, _contentSize.height / 2);
}

void AbstractCheckButton::copySpecialProperties(Widget *widget)
{
    AbstractCheckButton* abstractCheckButton = dynamic_cast<AbstractCheckButton*>(widget);
    if (abstractCheckButton)
    {
        loadTextureBackGround(abstractCheckButton->_backGroundBoxRenderer->getSpriteFrame());
        loadTextureBackGroundSelected(abstractCheckButton->_backGroundSelectedBoxRenderer->getSpriteFrame());
        loadTextureFrontCross(abstractCheckButton->_frontCrossRenderer->getSpriteFrame());
        loadTextureBackGroundDisabled(abstractCheckButton->_backGroundBoxDisabledRenderer->getSpriteFrame());
        loadTextureFrontCrossDisabled(abstractCheckButton->_frontCrossDisabledRenderer->getSpriteFrame());
        setSelected(abstractCheckButton->_isSelected);
        _zoomScale = abstractCheckButton->_zoomScale;
        _backgroundTextureScaleX = abstractCheckButton->_backgroundTextureScaleX;
        _backgroundTextureScaleY = abstractCheckButton->_backgroundTextureScaleY;
        _isBackgroundSelectedTextureLoaded = abstractCheckButton->_isBackgroundSelectedTextureLoaded;
        _isBackgroundDisabledTextureLoaded = abstractCheckButton->_isBackgroundDisabledTextureLoaded;
        _isFrontCrossDisabledTextureLoaded = abstractCheckButton->_isFrontCrossDisabledTextureLoaded;
    }
}


ResourceData AbstractCheckButton::getBackNormalFile()
{
    ResourceData rData;
    rData.type = (int)_backGroundTexType;
    rData.file = _backGroundFileName;
    return rData;
}

ResourceData AbstractCheckButton::getBackPressedFile()
{
    ResourceData rData;
    rData.type = (int)_backGroundSelectedTexType;
    rData.file = _backGroundSelectedFileName;
    return rData;
}

ResourceData AbstractCheckButton::getBackDisabledFile()
{
    ResourceData rData;
    rData.type = (int)_backGroundDisabledTexType;
    rData.file = _backGroundDisabledFileName;
    return rData;
}

ResourceData AbstractCheckButton::getCrossNormalFile()
{
    ResourceData rData;
    rData.type = (int)_frontCrossTexType;
    rData.file = _frontCrossFileName;
    return rData;
}

ResourceData AbstractCheckButton::getCrossDisabledFile()
{
    ResourceData rData;
    rData.type = (int)_frontCrossDisabledTexType;
    rData.file = _frontCrossDisabledFileName;
    return rData;
}

}

NS_CC_END
