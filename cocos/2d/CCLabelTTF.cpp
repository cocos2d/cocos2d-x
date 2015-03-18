/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "2d/CCLabelTTF.h"
#include "2d/CCLabel.h"
#include "base/ccUTF8.h"

NS_CC_BEGIN

__LabelTTF::__LabelTTF()
{
    _renderLabel = Label::create();
    _renderLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(_renderLabel);
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    _contentDirty = false;
    _cascadeColorEnabled = true;
    _cascadeOpacityEnabled = true;
}

__LabelTTF::~__LabelTTF()
{
}

__LabelTTF * __LabelTTF::create()
{
    __LabelTTF * ret = new (std::nothrow) __LabelTTF();
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

__LabelTTF* __LabelTTF::create(const std::string& string, const std::string& fontName, float fontSize,
                               const Size &dimensions, TextHAlignment hAlignment, 
                               TextVAlignment vAlignment)
{
    __LabelTTF *ret = new (std::nothrow) __LabelTTF();
    if(ret && ret->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

__LabelTTF * __LabelTTF::createWithFontDefinition(const std::string& string, FontDefinition &textDefinition)
{
    __LabelTTF *ret = new (std::nothrow) __LabelTTF();
    if(ret && ret->initWithStringAndTextDefinition(string, textDefinition))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool __LabelTTF::initWithString(const std::string& string, const std::string& fontName, float fontSize,
                                const cocos2d::Size &dimensions, TextHAlignment hAlignment,
                                TextVAlignment vAlignment)
{
    _renderLabel->setString(string);
    _renderLabel->setSystemFontSize(fontSize);
    _renderLabel->setDimensions(dimensions.width,dimensions.height);
    _renderLabel->setAlignment(hAlignment,vAlignment);
    _renderLabel->setSystemFontName(fontName);
    _contentDirty = true;

    return true;
}

bool __LabelTTF::initWithStringAndTextDefinition(const std::string& string, FontDefinition &textDefinition)
{
    _renderLabel->setFontDefinition(textDefinition);
    _renderLabel->setString(string);
    _contentDirty = true;
    
    return true;
}

void __LabelTTF::setString(const std::string &string)
{
    _renderLabel->setString(string);
    _contentDirty = true;
}

const std::string& __LabelTTF::getString() const
{
    return _renderLabel->getString();
}

std::string __LabelTTF::getDescription() const
{
    return StringUtils::format("<__LabelTTF | FontName = %s, FontSize = %f, Label = '%s'>", _renderLabel->getSystemFontName().c_str(), _renderLabel->getSystemFontSize(), _renderLabel->getString().c_str());
}

TextHAlignment __LabelTTF::getHorizontalAlignment() const
{
    return _renderLabel->getHorizontalAlignment();
}

void __LabelTTF::setHorizontalAlignment(TextHAlignment alignment)
{
    _renderLabel->setHorizontalAlignment(alignment);
    _contentDirty = true;
}

TextVAlignment __LabelTTF::getVerticalAlignment() const
{
    return _renderLabel->getVerticalAlignment();
}

void __LabelTTF::setVerticalAlignment(TextVAlignment verticalAlignment)
{
    _renderLabel->setVerticalAlignment(verticalAlignment);
    _contentDirty = true;
}

const Size& __LabelTTF::getDimensions() const
{
    return _renderLabel->getDimensions();
}

void __LabelTTF::setDimensions(const Size &dim)
{
    _renderLabel->setDimensions(dim.width,dim.height);
    _contentDirty = true;
}

float __LabelTTF::getFontSize() const
{
    return _renderLabel->getSystemFontSize();
}

void __LabelTTF::setFontSize(float fontSize)
{
    _renderLabel->setSystemFontSize(fontSize);
    _contentDirty = true;
}

const std::string& __LabelTTF::getFontName() const
{
    return _renderLabel->getSystemFontName();
}

void __LabelTTF::setFontName(const std::string& fontName)
{
    _renderLabel->setSystemFontName(fontName);
    _contentDirty = true;
}

void __LabelTTF::enableShadow(const Size &shadowOffset, float shadowOpacity, float shadowBlur, bool updateTexture)
{
    Color4B temp(Color3B::BLACK);
    temp.a = 255 * shadowOpacity;
    _renderLabel->enableShadow(temp,shadowOffset,shadowBlur);
    _contentDirty = true;
}

void __LabelTTF::disableShadow(bool updateTexture)
{
    _renderLabel->disableEffect();
    _contentDirty = true;
}

void __LabelTTF::enableStroke(const Color3B &strokeColor, float strokeSize, bool updateTexture)
{
    _renderLabel->enableOutline(Color4B(strokeColor),strokeSize);
    _contentDirty = true;
}

void __LabelTTF::disableStroke(bool updateTexture)
{
    _renderLabel->disableEffect();
    _contentDirty = true;
}

void __LabelTTF::setFontFillColor(const Color3B &tintColor, bool updateTexture)
{
    _renderLabel->setTextColor(Color4B(tintColor));
}

void __LabelTTF::setTextDefinition(const FontDefinition& theDefinition)
{
    _renderLabel->setFontDefinition(theDefinition);
    _contentDirty = true;
}

const FontDefinition& __LabelTTF::getTextDefinition() const
{
    return _renderLabel->_fontDefinition;
}

void __LabelTTF::setBlendFunc(const BlendFunc &blendFunc)
{
    _renderLabel->setBlendFunc(blendFunc);
}

const BlendFunc &__LabelTTF::getBlendFunc() const
{
    return _renderLabel->getBlendFunc();
}

void __LabelTTF::setFlippedX(bool flippedX)
{
    if (flippedX)
    {
        _renderLabel->setScaleX(-1.0f);
    } 
    else
    {
        _renderLabel->setScaleX(1.0f);
    }
}

void __LabelTTF::setFlippedY(bool flippedY)
{
    if (flippedY)
    {
        _renderLabel->setScaleY(-1.0f);
    } 
    else
    {
        _renderLabel->setScaleY(1.0f);
    }
}

void __LabelTTF::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (_contentDirty)
    {
        this->setContentSize(_renderLabel->getContentSize());
        _contentDirty = false;
    }
    Node::visit(renderer,parentTransform, parentFlags);
}

const Size& __LabelTTF::getContentSize() const
{
    const_cast<__LabelTTF*>(this)->setContentSize(_renderLabel->getContentSize());
    return _contentSize;
}

Rect __LabelTTF::getBoundingBox() const
{
    const_cast<__LabelTTF*>(this)->setContentSize(_renderLabel->getContentSize());
    return Node::getBoundingBox();
}

NS_CC_END
