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
#ifndef __CCBITMAP_FONT_ATLAS_H__
#define __CCBITMAP_FONT_ATLAS_H__

#include "2d/CCLabel.h"
#if CC_LABELBMFONT_DEBUG_DRAW
#include "renderer/CCCustomCommand.h"
#endif

NS_CC_BEGIN

/** @brief LabelBMFont 是 SpriteBatchNode的子类.

特性:
- 对待那个字符都想对待 Sprite 一样，这意味着每一个子符都可以：
- rotated（旋转）
- scaled（）（缩放）
- translated（转换）
- tinted（色彩）
- 更改不透明度
- 它可以作为一个菜单项的一部分。
- 可以用来锚点对齐“标签”
- 支持AngelCode文本格式

限制:
- 所有字符的内部都使用锚点（0.5F，0.5F），但是不建议去改变它
 因为它可能会影响渲染
 
 LabelBMFont 实现了 LabelProtocol, 像一个 Label 、 LabelAtlas.
 LabelBMFont 是一个灵活的 Label, 他有 LabelAtlas 的速度， Sprite 的所有特性.
 如果有疑问，可以使用 LabelBMFont 代替 LabelAtlas / Label.

支持的编辑器:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

@since v0.8
*/

class CC_DLL CC_DEPRECATED_ATTRIBUTE LabelBMFont : public Node, public LabelProtocol, public BlendProtocol
{
public:
    /**
     * @js ctor
     */
    LabelBMFont();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelBMFont();

    /** 使用string和FNT文创建件并初始化bitmap(位图)字体集 */
    static LabelBMFont * create(const std::string& str, const std::string& fntFile, float width = 0, TextHAlignment alignment = TextHAlignment::LEFT,const Vec2& imageOffset = Vec2::ZERO);

    /**创建一个label.
     */
    static LabelBMFont * create();

    /** 使用string和FNT文初始化bitmap(位图)字体集 */
    bool initWithString(const std::string& str, const std::string& fntFile, float width = 0, TextHAlignment alignment = TextHAlignment::LEFT,const Vec2& imageOffset = Vec2::ZERO);

    // super method
    virtual void setString(const std::string& newString) override;

    virtual const std::string& getString() const override;

    virtual void setAlignment(TextHAlignment alignment);
    virtual void setWidth(float width);
    virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
    
    // RGBAProtocol 
    virtual bool isOpacityModifyRGB() const;
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);

    void setFntFile(const std::string& fntFile, const Vec2& imageOffset = Vec2::ZERO);
    const std::string& getFntFile() const;

    virtual void setBlendFunc(const BlendFunc &blendFunc) override;

    virtual const BlendFunc &getBlendFunc() const override;

    virtual Sprite * getLetter(int ID);
    virtual Node * getChildByTag(int tag) override;

    virtual void setColor(const Color3B& color) override;

    virtual const Size& getContentSize() const override;
    virtual Rect getBoundingBox() const override;

    virtual std::string getDescription() const override;
#if CC_LABELBMFONT_DEBUG_DRAW
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
#endif

private:
#if CC_LABELBMFONT_DEBUG_DRAW
    CustomCommand   _customDebugDrawCommand;
    void drawDebugData(const Mat4& transform, bool transformUpdated);
#endif
    
    // name of fntFile
    std::string _fntFile;

    Label*      _label;

};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCBITMAP_FONT_ATLAS_H__
