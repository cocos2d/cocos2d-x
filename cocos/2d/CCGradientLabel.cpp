//
//  CCGradientLabel.cpp
//
//  Created by vitaly on 29.12.16.
//
//

#include "2d/CCGradientLabel.h"

#include <algorithm>

#include "2d/CCFont.h"
#include "2d/CCFontAtlasCache.h"
#include "2d/CCFontAtlas.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteBatchNode.h"
#include "2d/CCDrawNode.h"
#include "2d/CCCamera.h"
#include "base/ccUTF8.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"
#include "base/CCDirector.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventCustom.h"
#include "2d/CCFontFNT.h"

NS_CC_BEGIN


GradientLabel* GradientLabel::create()
{
    auto ret = new (std::nothrow) GradientLabel;

    if (ret)
    {
        ret->autorelease();
    }

    return ret;
}

GradientLabel* GradientLabel::create(const std::string& text, const std::string& font, float fontSize, const Size& dimensions /* = Size::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    if (FileUtils::getInstance()->isFileExist(font))
    {
        return createWithTTF(text,font,fontSize,dimensions,hAlignment,vAlignment);
    } 
    else
    {
        return createWithSystemFont(text,font,fontSize,dimensions,hAlignment,vAlignment);
    }
}

GradientLabel* GradientLabel::createWithSystemFont(const std::string& text, const std::string& font, float fontSize, const Size& dimensions /* = Size::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    auto ret = new (std::nothrow) GradientLabel(hAlignment,vAlignment);

    if (ret)
    {
        ret->setSystemFontName(font);
        ret->setSystemFontSize(fontSize);
        ret->setDimensions(dimensions.width, dimensions.height);
        ret->setString(text);

        ret->autorelease();

        return ret;
    }

    return nullptr;
}

GradientLabel* GradientLabel::createWithTTF(const std::string& text, const std::string& fontFile, float fontSize, const Size& dimensions /* = Size::ZERO */, TextHAlignment hAlignment /* = TextHAlignment::LEFT */, TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    auto ret = new (std::nothrow) GradientLabel(hAlignment,vAlignment);

    if (ret && ret->initWithTTF(text, fontFile, fontSize, dimensions, hAlignment, vAlignment))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

GradientLabel* GradientLabel::createWithTTF(const TTFConfig& ttfConfig, const std::string& text, TextHAlignment hAlignment /* = TextHAlignment::CENTER */, int maxLineWidth /* = 0 */)
{
    auto ret = new (std::nothrow) GradientLabel(hAlignment);

    if (ret && ret->initWithTTF(ttfConfig, text, hAlignment, maxLineWidth))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

GradientLabel* GradientLabel::createWithBMFont(const std::string& bmfontFilePath, const std::string& text,const TextHAlignment& hAlignment /* = TextHAlignment::LEFT */, int maxLineWidth /* = 0 */, const Vec2& imageOffset /* = Vec2::ZERO */)
{
    auto ret = new (std::nothrow) GradientLabel(hAlignment);

    if (ret && ret->setBMFontFilePath(bmfontFilePath,imageOffset))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        ret->autorelease();

        return ret;
    }
    
    delete ret;
    return nullptr;
}

GradientLabel* GradientLabel::createWithCharMap(const std::string& plistFile)
{
    auto ret = new (std::nothrow) GradientLabel();

    if (ret && ret->setCharMap(plistFile))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

GradientLabel* GradientLabel::createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    auto ret = new (std::nothrow) GradientLabel();

    if (ret && ret->setCharMap(texture,itemWidth,itemHeight,startCharMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

GradientLabel* GradientLabel::createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    auto ret = new (std::nothrow) GradientLabel();

    if (ret && ret->setCharMap(charMapFile,itemWidth,itemHeight,startCharMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

GradientLabel::GradientLabel(TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
             TextVAlignment vAlignment /* = TextVAlignment::TOP */)
:cocos2d::Label(hAlignment, vAlignment)
{
}

GradientLabel::~GradientLabel()
{
}

void GradientLabel::reset()
{
    Label::reset();
    
}

void GradientLabel::updateContent()
{
    Label::updateContent();
    
    getGLProgram()->setUniformLocationWith2f(_textSize, _contentSize.width, _contentSize.height);
}

static Texture2D* _getTexture(GradientLabel* label)
{
    struct _FontAtlasPub : public FontAtlas
    {
        Texture2D* getTexture()
        {
            if (!_atlasTextures.empty())
                return _atlasTextures.begin()->second;
            return nullptr;
        }
    };
    
    auto fontAtlas = label->getFontAtlas();
    Texture2D* texture = nullptr;
    if (fontAtlas != nullptr)
        texture = ((_FontAtlasPub*)(fontAtlas))->getTexture();
    return texture;
}

void GradientLabel::updateShaderProgram()
{
    switch (_currLabelEffect)
    {
    case cocos2d::LabelEffect::NORMAL:
        if (_useDistanceField)
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL));
        else if (_useA8Shader)
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_LABEL_NORMAL));
        else if (_shadowEnabled)
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR, _getTexture(this)));
        else
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP, _getTexture(this)));

        break;
    case cocos2d::LabelEffect::OUTLINE: 
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_GRADIENT_LABEL_OUTLINE));
        _uniformEffectColor = glGetUniformLocation(getGLProgram()->getProgram(), "u_effectColor");
        break;
    case cocos2d::LabelEffect::GLOW:
        if (_useDistanceField)
        {
            setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_LABEL_DISTANCEFIELD_GLOW));
            _uniformEffectColor = glGetUniformLocation(getGLProgram()->getProgram(), "u_effectColor");
        }
        break;
    default:
        return;
    }
    
    _uniformTextColor = glGetUniformLocation(getGLProgram()->getProgram(), "u_textColor");
    
    _textSize = glGetUniformLocation(getGLProgram()->getProgram(), "textSize");
    _leftTopUniform = glGetUniformLocation(getGLProgram()->getProgram(), "leftTopColor");
    _rightTopUniform = glGetUniformLocation(getGLProgram()->getProgram(), "rightTopColor");
    _leftBottomUniform = glGetUniformLocation(getGLProgram()->getProgram(), "leftBottomColor");
    _rightBottomUniform = glGetUniformLocation(getGLProgram()->getProgram(), "rightBottomColor");
    
    updateUniformColors();
}

std::string GradientLabel::getDescription() const
{
    char tmp[50];
    sprintf(tmp, "<GradientLabel | Tag = %d, Label = >", _tag);
    std::string ret = tmp;
    ret += _utf8Text;

    return ret;
}

void GradientLabel::setGradientColor(const Color4B &leftTop, const Color4B &rightTop, const Color4B &leftBottom, const Color4B &rightBottom)
{
    _leftTopColor = leftTop;
    _rightTopColor = rightTop;
    _leftBottomColor = leftBottom;
    _rightBottomColor = rightBottom;
    updateUniformColors();
}

void GradientLabel::setHGradientColor(const Color4B &color1, const Color4B &color2)
{
    setGradientColor(color1, color2, color1, color2);
}

void GradientLabel::setVGradientColor(const Color4B &color1, const Color4B &color2)
{
    setGradientColor(color1, color2, color1, color2);
}

const Color4B &GradientLabel::getLeftTopColor() const
{
    return _leftTopColor;
}

const Color4B &GradientLabel::getRightTopColor() const
{
    return _rightTopColor;
}

const Color4B &GradientLabel::getLeftBottomColor() const
{
    return _leftBottomColor;
}

const Color4B &GradientLabel::getRightBottomTopColor() const
{
    return _rightBottomColor;
}

void GradientLabel::updateUniformColors()
{
    getGLProgram()->setUniformLocationWith2f(_textSize, _contentSize.width, _contentSize.height);
    getGLProgram()->setUniformLocationWith4f(_leftTopUniform, _leftTopColor.r / 255.0f, _leftTopColor.g / 255.0f, _leftTopColor.b / 255.0f, _leftTopColor.a / 255.0f);
    getGLProgram()->setUniformLocationWith4f(_rightTopUniform, _rightTopColor.r / 255.0f, _rightTopColor.g / 255.0f, _rightTopColor.b / 255.0f, _rightTopColor.a / 255.0f);
    getGLProgram()->setUniformLocationWith4f(_leftBottomUniform, _leftBottomColor.r / 255.0f, _leftBottomColor.g / 255.0f, _leftBottomColor.b / 255.0f, _leftBottomColor.a / 255.0f);
    getGLProgram()->setUniformLocationWith4f(_rightBottomUniform, _rightBottomColor.r / 255.0f, _rightBottomColor.g / 255.0f, _rightBottomColor.b / 255.0f, _rightBottomColor.a / 255.0f);
}

NS_CC_END
