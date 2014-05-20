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

#ifndef __UILABELBMFONT_H__
#define __UILABELBMFONT_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {
    
/**
*   @js NA
*   @lua NA
*/    
class TextBMFont : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * 默认构造函数
     */
    TextBMFont();
    
    /**
     * 默认析构函数
     */
    virtual ~TextBMFont();
    
    /**
     * 创建和初始化对象
     */
    static TextBMFont* create();
    
    static TextBMFont* create(const std::string& text, const std::string& filename);
    
    /** 根据初始字符串和FNT文件初始化一个位图字体图集 */
    void setFntFile(const std::string& fileName);
    
    /** 设置labelbmfont的字符串值*/
    CC_DEPRECATED_ATTRIBUTE void setText(const std::string& value){this->setString(value);}
    void setString(const std::string& value);
    
    /** 获得labelbmfont的字符串值*/
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue()const{return this->getString();}
    const std::string& getString()const;
    
    /**
     * 获得标签（label）的字符串长度
     * 注：获得的长度会比原始字符串的长度长，
     * 如果你想得到原始字符串的长度， 你应用调用this->getString().size()来获得
     *
     * @return 字符串长度
     */
    ssize_t getStringLength()const;

    virtual const Size& getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    /**
     * 返回控件（widget）的类名（class name）
     */
    virtual std::string getDescription() const override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    void labelBMFontScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    cocos2d::Label* _labelBMFontRenderer;
    bool _fntFileHasInit;
    std::string _fntFileName;
    std::string _stringValue;
    bool _labelBMFontRendererAdaptDirty;
};
    
}
NS_CC_END

#endif /* defined(__LabelBMFont__) */
