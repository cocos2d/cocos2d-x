/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

Use any of these editors to generate BMFonts:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#include "2d/CCLabelBMFont.h"
#include "base/ccUTF8.h"
#include "2d/CCSprite.h"

#if CC_LABELBMFONT_DEBUG_DRAW
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"
#endif

using namespace std;

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

NS_CC_BEGIN

LabelBMFont * LabelBMFont::create()
{
    LabelBMFont * pRet = new (std::nothrow) LabelBMFont();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

//LabelBMFont - Creation & Init
LabelBMFont *LabelBMFont::create(const std::string& str, const std::string& fntFile, float width /* = 0 */, TextHAlignment alignment /* = TextHAlignment::LEFT */,const Vec2& imageOffset /* = Vec2::ZERO */)
{
    LabelBMFont *ret = new (std::nothrow) LabelBMFont();
    if(ret && ret->initWithString(str, fntFile, width, alignment,imageOffset))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LabelBMFont::initWithString(const std::string& str, const std::string& fntFile, float width /* = 0 */, TextHAlignment alignment /* = TextHAlignment::LEFT */,const Vec2& imageOffset /* = Vec2::ZERO */)
{
    if (_label->setBMFontFilePath(fntFile,imageOffset))
    {
        _fntFile = fntFile;
        _label->setMaxLineWidth(width);
        _label->setAlignment(alignment);
        _label->setString(str);
        this->setContentSize(_label->getContentSize());
        return true;
    }

    return false;
}

LabelBMFont::LabelBMFont()
{
    _label = Label::create();
    _label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(_label);
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _cascadeOpacityEnabled = true;
    
#if CC_LABELBMFONT_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif
}

LabelBMFont::~LabelBMFont()
{

}

//LabelBMFont - LabelProtocol protocol
void LabelBMFont::setString(const std::string &newString)
{
    _label->setString(newString);
    this->setContentSize(_label->getContentSize());
}

const std::string& LabelBMFont::getString() const
{
    return _label->getString();
}

/** Override synthesized setOpacity to recurse items */

void LabelBMFont::setOpacityModifyRGB(bool var)
{
    _label->setOpacityModifyRGB(var);
    for(const auto &child : _children) {
        child->setOpacityModifyRGB(var);
    }
}
bool LabelBMFont::isOpacityModifyRGB() const
{
    return _label->isOpacityModifyRGB();
}

// LabelBMFont - Alignment
void LabelBMFont::setAlignment(TextHAlignment alignment)
{
    _label->setAlignment(alignment);
    this->setContentSize(_label->getContentSize());
}

void LabelBMFont::setWidth(float width)
{
    _label->setMaxLineWidth(width);
    this->setContentSize(_label->getContentSize());
}

void LabelBMFont::setLineBreakWithoutSpace( bool breakWithoutSpace )
{
    _label->setLineBreakWithoutSpace(breakWithoutSpace);
    this->setContentSize(_label->getContentSize());
}

// LabelBMFont - FntFile
void LabelBMFont::setFntFile(const std::string& fntFile, const Vec2& imageOffset /* = Vec2::ZERO */)
{
    if (_fntFile.compare(fntFile) != 0)
    {
        _fntFile = fntFile;
        _label->setBMFontFilePath(fntFile,imageOffset);
    }
}

const std::string& LabelBMFont::getFntFile() const
{
    return _fntFile;
}

std::string LabelBMFont::getDescription() const
{
    return StringUtils::format("<LabelBMFont | Tag = %d, Label = '%s'>", _tag, _label->getString().c_str());
}

void LabelBMFont::setBlendFunc(const BlendFunc &blendFunc)
{
    _label->setBlendFunc(blendFunc);
}

const BlendFunc &LabelBMFont::getBlendFunc() const
{
    return _label->getBlendFunc();
}

Node* LabelBMFont::getChildByTag(int tag) const
{
    return _label->getLetter(tag);
}

Sprite* LabelBMFont::getLetter(int ID)
{
    return _label->getLetter(ID);
}

void LabelBMFont::setColor(const Color3B& color)
{
    _label->setColor(color);
}

const Size& LabelBMFont::getContentSize() const
{
    const_cast<LabelBMFont*>(this)->setContentSize(_label->getContentSize());
    return _contentSize;
}

Rect LabelBMFont::getBoundingBox() const
{
    return Node::getBoundingBox();
}
#if CC_LABELBMFONT_DEBUG_DRAW
void LabelBMFont::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Node::draw(renderer, transform, _transformUpdated);

    _debugDrawNode->clear();
    auto size = getContentSize();
    Vec2 vertices[4]=
    {
        Vec2::ZERO,
        Vec2(size.width, 0),
        Vec2(size.width, size.height),
        Vec2(0, size.height)
    };
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
}
#endif

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif

NS_CC_END
