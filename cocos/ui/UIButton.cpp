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

#include "ui/UIButton.h"
#include "ui/UIScale9Sprite.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "2d/CCActionInterval.h"
#include "platform/CCFileUtils.h"
#include "ui/UIHelper.h"
#include <algorithm>
#include "editor-support/cocostudio/CocosStudioExtension.h"

NS_CC_BEGIN

namespace ui {

static const int NORMAL_RENDERER_Z = (-2);
static const int PRESSED_RENDERER_Z = (-2);
static const int DISABLED_RENDERER_Z = (-2);
static const int TITLE_RENDERER_Z = (-1);
static const float ZOOM_ACTION_TIME_STEP = 0.05f;

IMPLEMENT_CLASS_GUI_INFO(Button)

Button::Button():
_buttonNormalRenderer(nullptr),
_buttonClickedRenderer(nullptr),
_buttonDisabledRenderer(nullptr),
_titleRenderer(nullptr),
_zoomScale(0.1f),
_normalFileName(""),
_clickedFileName(""),
_disabledFileName(""),
_normalTexType(TextureResType::LOCAL),
_pressedTexType(TextureResType::LOCAL),
_disabledTexType(TextureResType::LOCAL),
_fontName(""),
_prevIgnoreSize(true),
_scale9Enabled(false),
_pressedActionEnabled(false),
_capInsetsNormal(Rect::ZERO),
_capInsetsPressed(Rect::ZERO),
_capInsetsDisabled(Rect::ZERO),
_normalTextureSize(_contentSize),
_pressedTextureSize(_contentSize),
_disabledTextureSize(_contentSize),
_normalTextureLoaded(false),
_pressedTextureLoaded(false),
_disabledTextureLoaded(false),
_normalTextureAdaptDirty(true),
_pressedTextureAdaptDirty(true),
_disabledTextureAdaptDirty(true),
_fontSize(10),
_type(FontType::SYSTEM)
{
    setTouchEnabled(true);
}

Button::~Button()
{
}

Button* Button::create()
{
    Button* widget = new (std::nothrow) Button();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

Button* Button::create(const std::string &normalImage,
                       const std::string& selectedImage ,
                       const std::string& disableImage,
                       TextureResType texType)
{
    Button *btn = new (std::nothrow) Button;
    if (btn && btn->init(normalImage,selectedImage,disableImage,texType))
    {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

bool Button::init(const std::string &normalImage,
                  const std::string& selectedImage ,
                  const std::string& disableImage,
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

        this->loadTextures(normalImage, selectedImage, disableImage,texType);
    } while (0);
    return ret;
}

bool Button::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

void Button::initRenderer()
{
    _buttonNormalRenderer = Scale9Sprite::create();
    _buttonClickedRenderer = Scale9Sprite::create();
    _buttonDisabledRenderer = Scale9Sprite::create();
    _buttonClickedRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
    _buttonNormalRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
    _buttonDisabledRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);

    addProtectedChild(_buttonNormalRenderer, NORMAL_RENDERER_Z, -1);
    addProtectedChild(_buttonClickedRenderer, PRESSED_RENDERER_Z, -1);
    addProtectedChild(_buttonDisabledRenderer, DISABLED_RENDERER_Z, -1);
}

void Button::createTitleRenderer()
{
    _titleRenderer = Label::create();
    _titleRenderer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addProtectedChild(_titleRenderer, TITLE_RENDERER_Z, -1);
}

void Button::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }

    _scale9Enabled = able;

    if (_scale9Enabled) {
        _buttonNormalRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
        _buttonClickedRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
        _buttonDisabledRenderer->setRenderingType(Scale9Sprite::RenderingType::SLICE);
    }else{
        _buttonNormalRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
        _buttonClickedRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
        _buttonDisabledRenderer->setRenderingType(Scale9Sprite::RenderingType::SIMPLE);
    }
    

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

    setCapInsetsNormalRenderer(_capInsetsNormal);
    setCapInsetsPressedRenderer(_capInsetsPressed);
    setCapInsetsDisabledRenderer(_capInsetsDisabled);

    _brightStyle = BrightStyle::NONE;
    setBright(_bright);

    _normalTextureAdaptDirty = true;
    _pressedTextureAdaptDirty = true;
    _disabledTextureAdaptDirty = true;
}

bool Button::isScale9Enabled()const
{
    return _scale9Enabled;
}

void Button::ignoreContentAdaptWithSize(bool ignore)
{
    if (_unifySize)
    {
        this->updateContentSize();
        return;
    }

    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void Button::loadTextures(const std::string& normal,
                          const std::string& selected,
                          const std::string& disabled,
                          TextureResType texType)
{
    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
}

void Button::loadTextureNormal(const std::string& normal,TextureResType texType)
{
    _normalFileName = normal;
    _normalTexType = texType;
    bool textureLoaded = true;
    if (normal.empty())
    {
        _buttonNormalRenderer->resetRender();
        textureLoaded = false;
    }
    else
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _buttonNormalRenderer->initWithFile(normal);
            break;
        case TextureResType::PLIST:
            _buttonNormalRenderer->initWithSpriteFrameName(normal);
            break;
        default:
            break;
        }
    }
    //FIXME: https://github.com/cocos2d/cocos2d-x/issues/12249
    if (!_ignoreSize && _customSize.equals(Size::ZERO)) {
        _customSize = _buttonNormalRenderer->getContentSize();
    }
    this->setupNormalTexture(textureLoaded);
}

void Button::setupNormalTexture(bool textureLoaded)
{
    _normalTextureSize = _buttonNormalRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    if (_unifySize )
    {
        if (!_scale9Enabled)
        {
            updateContentSizeWithTextureSize(this->getNormalSize());
        }
    }
    else
    {
        updateContentSizeWithTextureSize(_normalTextureSize);
    }
    _normalTextureLoaded = textureLoaded;
    _normalTextureAdaptDirty = true;
}

void Button::loadTextureNormal(SpriteFrame* normalSpriteFrame)
{
    _buttonNormalRenderer->initWithSpriteFrame(normalSpriteFrame);
    this->setupNormalTexture(nullptr != normalSpriteFrame);
}

void Button::loadTexturePressed(const std::string& selected,TextureResType texType)
{
    _clickedFileName = selected;
    _pressedTexType = texType;
    bool textureLoade = true;
    if (selected.empty())
    {
        _buttonClickedRenderer->resetRender();
        textureLoade = false;
    }
    else
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _buttonClickedRenderer->initWithFile(selected);
            break;
        case TextureResType::PLIST:
            _buttonClickedRenderer->initWithSpriteFrameName(selected);
            break;
        default:
            break;
        }
    }
    this->setupPressedTexture(textureLoade);
}

void Button::setupPressedTexture(bool textureLoaded)
{
    _pressedTextureSize = _buttonClickedRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    _pressedTextureLoaded = textureLoaded;
    _pressedTextureAdaptDirty = true;
}

void Button::loadTexturePressed(SpriteFrame* pressedSpriteFrame)
{
    _buttonClickedRenderer->initWithSpriteFrame(pressedSpriteFrame);
    this->setupPressedTexture(nullptr != pressedSpriteFrame);
}

void Button::loadTextureDisabled(const std::string& disabled,TextureResType texType)
{
    _disabledFileName = disabled;
    _disabledTexType = texType;
    bool textureLoaded = true;
    if (disabled.empty())
    {
        _buttonDisabledRenderer->resetRender();
        textureLoaded = false;
    }
    else
    {
        switch (texType)
        {
        case TextureResType::LOCAL:
            _buttonDisabledRenderer->initWithFile(disabled);
            break;
        case TextureResType::PLIST:
            _buttonDisabledRenderer->initWithSpriteFrameName(disabled);
            break;
        default:
            break;
        }
    }
    this->setupDisabledTexture(textureLoaded);
}

void Button::setupDisabledTexture(bool textureLoaded)
{
    _disabledTextureSize = _buttonDisabledRenderer->getContentSize();

    this->updateChildrenDisplayedRGBA();

    _disabledTextureLoaded = textureLoaded;
    _disabledTextureAdaptDirty = true;
}

void Button::loadTextureDisabled(SpriteFrame* disabledSpriteFrame)
{
    _buttonDisabledRenderer->initWithSpriteFrame(disabledSpriteFrame);
    this->setupDisabledTexture(nullptr != disabledSpriteFrame);
}

void Button::setCapInsets(const Rect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
}


void Button::setCapInsetsNormalRenderer(const Rect &capInsets)
{
    _capInsetsNormal = Helper::restrictCapInsetRect(capInsets, this->_normalTextureSize);

    //for performance issue
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonNormalRenderer->setCapInsets(_capInsetsNormal);
}

void Button::setCapInsetsPressedRenderer(const Rect &capInsets)
{
    _capInsetsPressed = Helper::restrictCapInsetRect(capInsets, this->_pressedTextureSize);

    //for performance issue
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonClickedRenderer->setCapInsets(_capInsetsPressed);
}

void Button::setCapInsetsDisabledRenderer(const Rect &capInsets)
{
    _capInsetsDisabled = Helper::restrictCapInsetRect(capInsets, this->_disabledTextureSize);

    //for performance issue
    if (!_scale9Enabled)
    {
        return;
    }
    _buttonDisabledRenderer->setCapInsets(_capInsetsDisabled);
}

const Rect& Button::getCapInsetsNormalRenderer()const
{
    return _capInsetsNormal;
}

const Rect& Button::getCapInsetsPressedRenderer()const
{
    return _capInsetsPressed;
}

const Rect& Button::getCapInsetsDisabledRenderer()const
{
    return _capInsetsDisabled;
}

void Button::onPressStateChangedToNormal()
{
    _buttonNormalRenderer->setVisible(true);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisabledRenderer->setVisible(false);
    _buttonNormalRenderer->setState(Scale9Sprite::State::NORMAL);

    if (_pressedTextureLoaded)
    {
        if (_pressedActionEnabled)
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonClickedRenderer->stopAllActions();

//            Action *zoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, _normalTextureScaleXInSize, _normalTextureScaleYInSize);
            //fixme: the zoomAction will run in the next frame which will cause the _buttonNormalRenderer to a wrong scale
            _buttonNormalRenderer->setScale(1.0);
            _buttonClickedRenderer->setScale(1.0);

            if(nullptr != _titleRenderer)
            {
                _titleRenderer->stopAllActions();
                if (_unifySize)
                {
                    Action *zoomTitleAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, 1.0f, 1.0f);
                    _titleRenderer->runAction(zoomTitleAction);
                }
                else
                {
                    _titleRenderer->setScaleX(1.0f);
                    _titleRenderer->setScaleY(1.0f);
                }
            }
        }
    }
    else
    {
        _buttonNormalRenderer->stopAllActions();
        _buttonNormalRenderer->setScale(1.0);

        if(nullptr != _titleRenderer)
        {
            _titleRenderer->stopAllActions();
            _titleRenderer->setScaleX(1.0f);
            _titleRenderer->setScaleY(1.0f);
        }

    }
}

void Button::onPressStateChangedToPressed()
{
    _buttonNormalRenderer->setState(Scale9Sprite::State::NORMAL);

    if (_pressedTextureLoaded)
    {
        _buttonNormalRenderer->setVisible(false);
        _buttonClickedRenderer->setVisible(true);
        _buttonDisabledRenderer->setVisible(false);

        if (_pressedActionEnabled)
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonClickedRenderer->stopAllActions();

            Action *zoomAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP,
                                                 1.0 + _zoomScale,
                                                 1.0 + _zoomScale);
            _buttonClickedRenderer->runAction(zoomAction);

            _buttonNormalRenderer->setScale(1.0 + _zoomScale,
                                            1.0 + _zoomScale);

            if(nullptr != _titleRenderer)
            {
                _titleRenderer->stopAllActions();
                Action *zoomTitleAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP,
                                                          1.0f + _zoomScale, 1.0f + _zoomScale);
                _titleRenderer->runAction(zoomTitleAction);
            }
        }
    }
    else
    {
        _buttonNormalRenderer->setVisible(true);
        _buttonClickedRenderer->setVisible(true);
        _buttonDisabledRenderer->setVisible(false);

        _buttonNormalRenderer->stopAllActions();
        _buttonNormalRenderer->setScale(1.0 +_zoomScale, 1.0 + _zoomScale);

        if(nullptr != _titleRenderer)
        {
            _titleRenderer->stopAllActions();
            _titleRenderer->setScaleX(1.0f + _zoomScale);
            _titleRenderer->setScaleY(1.0f + _zoomScale);
        }
    }
}

void Button::onPressStateChangedToDisabled()
{
    //if disable resource is null
    if (!_disabledTextureLoaded)
    {
        if (_normalTextureLoaded)
        {
            _buttonNormalRenderer->setState(Scale9Sprite::State::GRAY);
        }
    }
    else
    {
        _buttonNormalRenderer->setVisible(false);
        _buttonDisabledRenderer->setVisible(true);
    }

    _buttonClickedRenderer->setVisible(false);
    _buttonNormalRenderer->setScale(1.0);
    _buttonClickedRenderer->setScale(1.0);
}

void Button::updateTitleLocation()
{
    _titleRenderer->setPosition(_contentSize.width * 0.5f, _contentSize.height * 0.5f);
}

void Button::updateContentSize()
{
    if (_unifySize)
    {
        if (_scale9Enabled)
        {
            ProtectedNode::setContentSize(_customSize);
        }
        else
        {
            Size s = getNormalSize();
            ProtectedNode::setContentSize(s);
        }
        onSizeChanged();
        return;
    }

    if (_ignoreSize)
    {
        this->setContentSize(getVirtualRendererSize());
    }
}

void Button::onSizeChanged()
{
    Widget::onSizeChanged();
    if(nullptr != _titleRenderer)
    {
        updateTitleLocation();
    }
    _normalTextureAdaptDirty = true;
    _pressedTextureAdaptDirty = true;
    _disabledTextureAdaptDirty = true;
}

void Button::adaptRenderers()
{
    if (_normalTextureAdaptDirty)
    {
        normalTextureScaleChangedWithSize();
        _normalTextureAdaptDirty = false;
    }

    if (_pressedTextureAdaptDirty)
    {
        pressedTextureScaleChangedWithSize();
        _pressedTextureAdaptDirty = false;
    }

    if (_disabledTextureAdaptDirty)
    {
        disabledTextureScaleChangedWithSize();
        _disabledTextureAdaptDirty = false;
    }
}

Size Button::getVirtualRendererSize() const
{
    if (_unifySize)
    {
        return this->getNormalSize();
    }

    if (nullptr != _titleRenderer)
    {
        Size titleSize = _titleRenderer->getContentSize();
        if (!_normalTextureLoaded && _titleRenderer->getString().size() > 0)
        {
            return titleSize;
        }
    }
    return _normalTextureSize;
}

Node* Button::getVirtualRenderer()
{
    if (_bright)
    {
        switch (_brightStyle)
        {
            case BrightStyle::NORMAL:
                return _buttonNormalRenderer;
            case BrightStyle::HIGHLIGHT:
                return _buttonClickedRenderer;
            default:
                return nullptr;
        }
    }
    else
    {
        return _buttonDisabledRenderer;
    }
}

void Button::normalTextureScaleChangedWithSize()
{
    _buttonNormalRenderer->setPreferredSize(_contentSize);

    _buttonNormalRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void Button::pressedTextureScaleChangedWithSize()
{
    _buttonClickedRenderer->setPreferredSize(_contentSize);

    _buttonClickedRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void Button::disabledTextureScaleChangedWithSize()
{
    _buttonDisabledRenderer->setPreferredSize(_contentSize);
    
    _buttonDisabledRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void Button::setPressedActionEnabled(bool enabled)
{
    _pressedActionEnabled = enabled;
}

void Button::setTitleAlignment(TextHAlignment hAlignment)
{
    if (nullptr == _titleRenderer)
    {
        this->createTitleRenderer();
    }
    _titleRenderer->setAlignment(hAlignment);
}

void Button::setTitleAlignment(TextHAlignment hAlignment, TextVAlignment vAlignment)
{
    if (nullptr == _titleRenderer)
    {
        this->createTitleRenderer();
    }
    _titleRenderer->setAlignment(hAlignment, vAlignment);
}

void Button::setTitleText(const std::string& text)
{
    if (text == getTitleText())
    {
        return;
    }
    if(nullptr == _titleRenderer)
    {
        this->createTitleRenderer();
    }
    _titleRenderer->setString(text);
    this->setTitleFontSize(_fontSize);
    updateContentSize();
    updateTitleLocation();
}

std::string Button::getTitleText() const
{
    if(nullptr == _titleRenderer)
    {
        return "";
    }
    return _titleRenderer->getString();
}

void Button::setTitleColor(const Color3B& color)
{
    if(nullptr == _titleRenderer)
    {
        this->createTitleRenderer();
    }
    _titleRenderer->setTextColor(Color4B(color));
}

Color3B Button::getTitleColor() const
{
    if(nullptr == _titleRenderer)
    {
        return Color3B::WHITE;
    }
    return Color3B(_titleRenderer->getTextColor());
}

void Button::setTitleFontSize(float size)
{
    if (nullptr == _titleRenderer)
    {
        this->createTitleRenderer();
    }

    _fontSize = size;
    if (_type == FontType::SYSTEM)
    {
        _titleRenderer->setSystemFontSize(_fontSize);
    }
    else if (_type == FontType::TTF)
    {
        TTFConfig config = _titleRenderer->getTTFConfig();
        config.fontSize = _fontSize;
        _titleRenderer->setTTFConfig(config);
    }
    //we can't change font size of BMFont.
    if(FontType::BMFONT != _type)
    {
        updateContentSize();
    }
}

float Button::getTitleFontSize() const
{
    return _fontSize;
}

void Button::setZoomScale(float scale)
{
    _zoomScale = scale;
}

float Button::getZoomScale()const
{
    return _zoomScale;
}

void Button::setTitleFontName(const std::string& fontName)
{
    if(nullptr == _titleRenderer)
    {
        this->createTitleRenderer();
    }
    if(FileUtils::getInstance()->isFileExist(fontName))
    {
        std::string lowerCasedFontName = fontName;
        std::transform(lowerCasedFontName.begin(), lowerCasedFontName.end(), lowerCasedFontName.begin(), ::tolower);
        if (lowerCasedFontName.find(".fnt") != std::string::npos)
        {
            _titleRenderer->setBMFontFilePath(fontName);
            _type = FontType::BMFONT;
        }
        else
        {
            TTFConfig config = _titleRenderer->getTTFConfig();
            config.fontFilePath = fontName;
            config.fontSize = _fontSize;
            _titleRenderer->setTTFConfig(config);
            _type = FontType::TTF;
        }
    }
    else
    {
        _titleRenderer->setSystemFontName(fontName);
        if (_type == FontType::TTF)
        {
            _titleRenderer->requestSystemFontRefresh();
        }
        _titleRenderer->setSystemFontSize(_fontSize);
        _type = FontType::SYSTEM;
    }
    _fontName = fontName;
    this->updateContentSize();
}

Label* Button::getTitleRenderer()const
{
    return _titleRenderer;
}

std::string Button::getTitleFontName() const
{
    if (nullptr != _titleRenderer)
    {
        if (this->_type == FontType::SYSTEM)
        {
            return _titleRenderer->getSystemFontName();
        }
        else if (this->_type == FontType::TTF)
        {
            return  _titleRenderer->getTTFConfig().fontFilePath;
        }
        else
        {
            return _titleRenderer->getBMFontFilePath();
        }
    }
    else
    {
        return _fontName;
    }
}

std::string Button::getDescription() const
{
    return "Button";
}

Widget* Button::createCloneInstance()
{
    return Button::create();
}

void Button::copySpecialProperties(Widget *widget)
{
    Button* button = dynamic_cast<Button*>(widget);
    if (button)
    {
        _prevIgnoreSize = button->_prevIgnoreSize;
        setScale9Enabled(button->_scale9Enabled);
        auto normalSprite = button->_buttonNormalRenderer->getSprite();
        if (nullptr != normalSprite)
        {
            loadTextureNormal(normalSprite->getSpriteFrame());
        }
        auto clickedSprite = button->_buttonClickedRenderer->getSprite();
        if (nullptr != clickedSprite)
        {
            loadTexturePressed(clickedSprite->getSpriteFrame());
        }
        auto disabledSprite = button->_buttonDisabledRenderer->getSprite();
        if (nullptr != disabledSprite)
        {
            loadTextureDisabled(disabledSprite->getSpriteFrame());
        }
        setCapInsetsNormalRenderer(button->_capInsetsNormal);
        setCapInsetsPressedRenderer(button->_capInsetsPressed);
        setCapInsetsDisabledRenderer(button->_capInsetsDisabled);
        if(nullptr != button->getTitleRenderer())
        {
            setTitleText(button->getTitleText());
            setTitleFontName(button->getTitleFontName());
            setTitleFontSize(button->getTitleFontSize());
            setTitleColor(button->getTitleColor());
        }
        setPressedActionEnabled(button->_pressedActionEnabled);
        setZoomScale(button->_zoomScale);
    }

}
Size Button::getNormalSize() const
{
    Size titleSize;
    if (_titleRenderer != nullptr)
    {
        titleSize = _titleRenderer->getContentSize();
    }
    Size imageSize;
    if (_buttonNormalRenderer != nullptr)
    {
        imageSize = _buttonNormalRenderer->getContentSize();
    }
    float width = titleSize.width > imageSize.width ? titleSize.width : imageSize.width;
    float height = titleSize.height > imageSize.height ? titleSize.height : imageSize.height;

    return Size(width,height);
}

Size Button::getNormalTextureSize() const
{
    return _normalTextureSize;
}

void Button::resetNormalRender()
{
    _normalFileName = "";
    _normalTexType = TextureResType::LOCAL;

    _normalTextureSize = Size(0, 0);

    _normalTextureLoaded = false;
    _normalTextureAdaptDirty = false;

    _buttonNormalRenderer->resetRender();
}
void Button::resetPressedRender()
{
    _clickedFileName = "";
    _pressedTexType = TextureResType::LOCAL;

    _pressedTextureSize = Size(0, 0);

    _pressedTextureLoaded = false;
    _pressedTextureAdaptDirty = false;

    _buttonClickedRenderer->resetRender();
}

void Button::resetDisabledRender()
{
    _disabledFileName = "";
    _disabledTexType = TextureResType::LOCAL;

    _disabledTextureSize = Size(0, 0);

    _disabledTextureLoaded = false;
    _disabledTextureAdaptDirty = false;

    _buttonDisabledRenderer->resetRender();
}

ResourceData Button::getNormalFile()
{
    ResourceData rData;
    rData.type = (int)_normalTexType;
    rData.file = _normalFileName;
    return rData;
}
ResourceData Button::getPressedFile()
{
    ResourceData rData;
    rData.type = (int)_pressedTexType;
    rData.file = _clickedFileName;
    return rData;
}
ResourceData Button::getDisabledFile()
{
    ResourceData rData;
    rData.type = (int)_disabledTexType;
    rData.file = _disabledFileName;
    return rData;
}

}

NS_CC_END
