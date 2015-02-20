
/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

Use any of these editors to generate BMFonts:
  http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
  http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
  http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
  http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/

#ifndef __CCBITMAP_FONT_ATLAS_H__
#define __CCBITMAP_FONT_ATLAS_H__

#include "2d/CCLabel.h"
#include "2d/CCSprite.h"

#if CC_LABELBMFONT_DEBUG_DRAW
#    include "renderer/CCCustomCommand.h"
#    include "2d/CCDrawNode.h"
#endif

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */

class CC_DEPRECATED_ATTRIBUTE LabelBMFont
    : public Label
{
public:
    
    static LabelBMFont* create()
    {
        auto ret = new (std::nothrow) LabelBMFont;
        if (ret)
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    static LabelBMFont* create(const std::string& str, const std::string& fntFile, float width = 0, TextHAlignment alignment = TextHAlignment::LEFT, const Vec2& imageOffset = Vec2::ZERO)
    {
        auto ret = new (std::nothrow) LabelBMFont;
        if (ret)
        {
            if (ret->setBMFontFilePath(fntFile, imageOffset))
            {
                ret->setMaxLineWidth(width);
                ret->setAlignment(alignment);
                ret->setString(str);
                
                ret->autorelease();
                return ret;
            }
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    void setOpacityModifyRGB(bool var)
    {
        Label::setOpacityModifyRGB(var);
        for(const auto &child : _children)
            child->setOpacityModifyRGB(var);
    }
    
    void setWidth(float width)
    {
        setMaxLineWidth(width);
    }
    
    void setFntFile(const std::string& fntFile, const Vec2& imageOffset = Vec2::ZERO)
    {
        setBMFontFilePath(fntFile, imageOffset);
    }
    
    std::string getDescription() const
    {
        return StringUtils::format("<LabelBMFont | Tag = %d, Label = '%s'>", getTag(), getString().c_str());
    }
    
    Node* getChildByTag(int tag) const
    {
        return const_cast<LabelBMFont*>(this)->getLetter(tag);
    }
    
#if CC_LABELBMFONT_DEBUG_DRAW
    void draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
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
    
protected:
    DrawNode _debugDrawNode;
#endif
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCBITMAP_FONT_ATLAS_H__
