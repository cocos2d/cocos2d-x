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
#ifndef __CCLABELTTF_H__
#define __CCLABELTTF_H__

#include "2d/CCNode.h"

NS_CC_BEGIN

class Label;

/**
 * @addtogroup GUI
 * @{
 * @addtogroup label
 * @{
 */



/** @brief LabelTTF 是 TextureNode 的子类，它可以渲染 labels 的标签（label上面显示的文字)
 *
 * TextureNode 的所有功能在 LabelTTF 里面都是有效的
 *
 * LabelTTF 对象非常缓慢. 可以考虑使用 LabelAtlas 、 LabelBMFont 代替.
 *
 * 自定义的 ttf 文件 可以放在  assets/ 应用程序可以访问的存储器里面.
 * @code
 * LabelTTF *label1 = LabelTTF::create("alignment left", "A Damn Mess", fontSize, blockSize, 
 *                                          TextHAlignment::LEFT, TextVAlignment::CENTER);
 * LabelTTF *label2 = LabelTTF::create("alignment right", "/mnt/sdcard/Scissor Cuts.ttf", fontSize, blockSize,
 *                                          TextHAlignment::LEFT, TextVAlignment::CENTER);
 * @endcode
 *
 */
class CC_DLL CC_DEPRECATED_ATTRIBUTE LabelTTF : public Node, public LabelProtocol, public BlendProtocol
{
public:
    /**
     * @js ctor
     */
    LabelTTF();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~LabelTTF();

    /**  使用 字体名称, 对齐方式, 质量大小(以点为单位), fontSize（以点为单位）创建一个 LabelTTF creates a Label from a fontname, alignment, dimension in points and font size in points
     @since v2.0.1
     */
    static LabelTTF * create(const std::string& string, const std::string& fontName, float fontSize,
                             const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::CENTER,
                             TextVAlignment vAlignment = TextVAlignment::TOP);
    
    
    /** 使用 string、textDefinition 创建一个 LabelTTF */
    static LabelTTF * createWithFontDefinition(const std::string& string, FontDefinition &textDefinition);
    
    /** 使用 字体名称, 对齐方式, 质量大小(以点为单位), fontSize（以点为单位）初始化一个 LabelTTF */
    bool initWithString(const std::string& string, const std::string& fontName, float fontSize,
                        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT, 
                        TextVAlignment vAlignment = TextVAlignment::TOP);
    
    /** 使用 string、textDefinition 初始化一个 LabelTTF */
    bool initWithStringAndTextDefinition(const std::string& string, FontDefinition &textDefinition);
    
    /** 设置这个label使用的文本definition */
    void setTextDefinition(const FontDefinition& theDefinition);
    
    /** 获取这个label使用的文本definition */
    const FontDefinition& getTextDefinition() const;
    
    
    
    /** 启用/禁用 这个 label 的阴影 */
    void enableShadow(const Size &shadowOffset, float shadowOpacity, float shadowBlur, bool mustUpdateTexture = true);
    
    /** 禁用阴影渲染 */
    void disableShadow(bool mustUpdateTexture = true);
    
    /** 启用/禁用绘制轮廓 */
    void enableStroke(const Color3B &strokeColor, float strokeSize, bool mustUpdateTexture = true);
    
    /** 禁用绘制轮廓 */
    void disableStroke(bool mustUpdateTexture = true);
    
    /** 设置文本着色 */
    void setFontFillColor(const Color3B &tintColor, bool mustUpdateTexture = true);

    /** 创建一个label.
     */
    static LabelTTF * create();


    /**修改要渲染的字符串
     * @warning 改变字符串是昂贵的像创建一个LabelTTF一样. 为了获得更好的性能建议使用LabelAtlas
     */
    virtual void setString(const std::string &label) override;
    virtual const std::string& getString(void) const override ;
    
    TextHAlignment getHorizontalAlignment() const;
    void setHorizontalAlignment(TextHAlignment alignment);
    
    TextVAlignment getVerticalAlignment() const;
    void setVerticalAlignment(TextVAlignment verticalAlignment);
    
    const Size& getDimensions() const;
    void setDimensions(const Size &dim);
    
    float getFontSize() const;
    void setFontSize(float fontSize);
    
    const std::string& getFontName() const;
    void setFontName(const std::string& fontName);

    virtual void setBlendFunc(const BlendFunc &blendFunc) override;

    virtual const BlendFunc &getBlendFunc() const override;

    virtual void setFlippedX(bool flippedX);
    virtual void setFlippedY(bool flippedY);

    virtual Rect getBoundingBox() const override;

    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const override;
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, bool parentTransformUpdated) override;
    virtual const Size& getContentSize() const override;
protected:
    Label*    _renderLabel;
    bool _contentDirty;
};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCLABEL_H__

