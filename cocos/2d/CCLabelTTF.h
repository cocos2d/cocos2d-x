
/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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

#ifndef __CCLABELTTF_H__
#define __CCLABELTTF_H__

#include "2d/CCNode.h"
#include "2d/CCLabel.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */

class CC_DEPRECATED_ATTRIBUTE LabelTTF
    : public Label
{
public:
    
    static LabelTTF* create()
    {
        LabelTTF* ret = new (std::nothrow) LabelTTF;
        if (ret)
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    static LabelTTF* create(const std::string& string, const std::string& fontName, float fontSize, const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::CENTER, TextVAlignment vAlignment = TextVAlignment::TOP)
    {
        LabelTTF* ret = new (std::nothrow) LabelTTF;
        if(ret)
        {
            ret->setString(string);
            ret->setSystemFontSize(fontSize);
            ret->setDimensions(dimensions.width, dimensions.height);
            ret->setAlignment(hAlignment, vAlignment);
            ret->setSystemFontName(fontName);

            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    static LabelTTF* createWithFontDefinition(const std::string& string, FontDefinition &textDefinition)
    {
        LabelTTF* ret = new (std::nothrow) LabelTTF;
        if (ret)
        {
            ret->setFontDefinition(textDefinition);
            ret->setString(string);

            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    std::string getDescription() const
    {
        return StringUtils::format("<LabelTTF | FontName = %s, FontSize = %f, Label = '%s'>", getSystemFontName().c_str(), getSystemFontSize(), getString().c_str());
    }

    float getFontSize() const
    {
        return getSystemFontSize();
    }
    
    void setFontSize(float fontSize)
    {
        setSystemFontSize(fontSize);
    }
    
    const std::string& getFontName() const
    {
        return getSystemFontName();
    }
    
    void setFontName(const std::string& fontName)
    {
        setSystemFontName(fontName);
    }
    
    void enableShadow(const Size& shadowOffset, float shadowOpacity, float shadowBlur, bool mustUpdateTexture = true)
    {
        Label::enableShadow(Color4B(0, 0, 0, 255 * shadowOpacity), shadowOffset, shadowBlur);
    }
    
    void disableShadow(bool updateTexture = true)
    {
        disableEffect();
    }
    
    void enableStroke(const Color3B &strokeColor, float strokeSize, bool updateTexture = true)
    {
        enableOutline(Color4B(strokeColor), strokeSize);
    }
    
    void disableStroke(bool updateTexture)
    {
        disableEffect();
    }
    
    void setFontFillColor(const Color3B &tintColor, bool updateTexture = true)
    {
        setTextColor(Color4B(tintColor));
    }
    
    void setTextDefinition(const FontDefinition& theDefinition)
    {
        setFontDefinition(theDefinition);
    }
    
    const FontDefinition& getTextDefinition() const
    {
        return getFontDefinition();
    }

    void setFlippedX(bool flippedX)
    {
        setScaleX(flippedX ? -1.f : 1.f);
    }
    
    void setFlippedY(bool flippedY)
    {
        setScaleY(flippedY ? -1.f : 1.f);
    }
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABELTTF_H__

