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
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

class Label;

namespace ui {
    
/**
 * @class TextBMFont
 * @brief @~english A widget for displaying BMFont label.
 * @~chinese 用以显示位图字体的空间
 */    
class CC_GUI_DLL TextBMFont : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * @~english Default constructor
     * @~chinese 默认构造函数
     * @js ctor
     * @lua new
     */
    TextBMFont();
    
    /**
     * @~english Default destructor
     * @~chinese 默认析构函数
     * @js NA
     * @lua NA
     */
    virtual ~TextBMFont();
    
    /**
     * @~english Create TextBMFont object.
     * @~chinese 创建TextBMFont对象
     * @return @~english The TextBMFont Object.
     * @~chinese 被创建的TextBMFont对象
     */
    static TextBMFont* create();
    
    /**
    * @~english Create TextBMFont object byspecified text and bitmap font name
    * @~chinese 通过指定的文本，以及位图字体的路径，创建TextBMFont对象
    * @param text @~english The text string
    * @~chinese 文本的字符串形式
    * @param filename @~english The BitMap font file path
    * @~chinese 位图字体的文件路径
    * @return @~english The TextBMFont Object.
    * @~chinese 被创建的TextBMFont对象
    */
    static TextBMFont* create(const std::string& text, const std::string& filename);
    
    /**
     * @~english Set BitMap font file
     * @~chinese 设置位图字体文件
     * @param fileName @~english BitMap font file name
     * @~chinese 位图字体文件名路径
     */
    void setFntFile(const std::string& fileName);
    
    /**
     * @~english Set string value for TextBMFont
     * @~chinese 设置TextBMFont显示的字符串
     * @param string @~english The String value.
     * @~chinese 字符串
     */
    CC_DEPRECATED_ATTRIBUTE void setText(const std::string& value){this->setString(value);}

    /**
    * @~english Set string value for TextBMFont
    * @~chinese 设置TextBMFont显示的字符串
    * @param string @~english The String value.
    * @~chinese 字符串
    */
    void setString(const std::string& value);
    
    /**
     * @~english Get string value for TextBMFont.
     * @~chinese 获取TextBMFont当前显示的字符串
     * @return @~english The string value.
     * @~chinese 字符串
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue()const{return this->getString();}

    /**
    * @~english Get string value for TextBMFont.
    * @~chinese 获取TextBMFont当前显示的字符串
    * @return @~english The string value.
    * @~chinese 字符串
    */
    const std::string& getString()const;
    
    /**
     * @~english Gets the string length of the label.
     * @~chinese 获取字符串长度
     * @note @~english This length will be larger than the raw string length,
     * if you want to get the raw string length, you should call this->getString().size() instead
     * @~chinese 该长度会比原始字符串长度要大，若需要原始字符串长度，请调用this->getString().size()
     * @return  @~english The string length.
     * @~chinese 字符串长度
     */
    ssize_t getStringLength()const;

    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
   
    void labelBMFontScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    Label* _labelBMFontRenderer;
    bool _fntFileHasInit;
    std::string _fntFileName;
    std::string _stringValue;
    bool _labelBMFontRendererAdaptDirty;
};
    
}
NS_CC_END
// end of ui group
/// @}

#endif /* defined(__LabelBMFont__) */
