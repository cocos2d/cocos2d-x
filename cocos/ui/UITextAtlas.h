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

#ifndef __UILABELATLAS_H__
#define __UILABELATLAS_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN

/**
 * @addtogroup ui
 * @{
 */

class Label;

namespace ui {
    
/**
 * @class TextAtlas
 * @brief @~english UI TextAtlas widget.
 * @~chinses 使用字符映射表来获取字体的文本控件
 */
class CC_GUI_DLL TextAtlas : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * @~english Default constructor.
     * @~chinese 默认构造函数
     * @lua new
     */
    TextAtlas();
    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构函数
     * @lua NA
     */
    virtual ~TextAtlas();
    
    /**
     * @~english Create a TextAtlas object.
     * @~chinese 创建一个TextAtlas对象
     * @return @~english An autoreleased TextAtlas object.
     * @~chinese 被创建的TextAtlas对象
     */
    static TextAtlas* create();
    
    /**
     * @~english Create a LabelAtlas from a char map file.
     * @~chinese 通过给定的字符映射表文件，创建一个TexAtlas对象
     * @param stringValue @~english A given string needs to be displayed.
     * @~chinese 待显示的字符串
     * @param charMapFile @~english A given char map file name.
     * @~chinese 字符映射表的文件名
     * @param itemWidth @~english The element width.
     * @~chinese 字符宽度
     * @param itemHeight @~english The element height.
     * @~chinese 字符高度
     * @param startCharMap @~english The starting char of the atlas.
     * @~chinese 字符映射表的起始字符
     * @return @~english An autoreleased TextAtlas object.
     * @~chinese 被创建的TextAtlas对象
     */
    static TextAtlas* create(const std::string& stringValue,
                             const std::string& charMapFile,
                             int itemWidth,
                             int itemHeight,
                             const std::string& startCharMap);
    
    /** @~english Initializes the LabelAtlas with a string, a char map file(the atlas), the width and height of each element and the starting char of the atlas.
     * @~chinese 通过给定字符串，字符映射表，字符映射表中每个字符的高度和宽度以及字符映射表的起始字符来初始化对象
     * @param stringValue @~english A given string needs to be displayed.
     * @~chinese 指定的字符串
     * @param charMapFile @~english A given char map file name.
     * @~chinese 字符映射表
     * @param itemWidth @~english The element width.
     * @~chinese 字符宽度
     * @param itemHeight @~english The element height.
     * @~chinese 字符高度
     * @param startCharMap @~english The starting char of the atlas.
     * @~chinese 字符映射表的起始字符
     */
    
    void setProperty(const std::string& stringValue,
                     const std::string& charMapFile,
                     int itemWidth,
                     int itemHeight,
                     const std::string& startCharMap);
    
    /**
     * @~english Set string value for labelatlas.
     * @~chinese 设置待显示的字符串
     * @param value @~english A given string needs to be displayed.
     * @~chinese 待显示的字符串
     */
    CC_DEPRECATED_ATTRIBUTE void setStringValue(const std::string& value){this->setString(value);}

    /**
     * @~english Set string value for labelatlas.
     * @~chinese 设置待显示的字符串
     * @param value A given string needs to be displayed.
     * @~chinese 待显示的字符串
     */
    void setString(const std::string& value);
    
    /**
     * @~english Get string value for labelatlas.
     * @~chinese 获取当前显示显示的字符串
     * @return @~english The string value of TextAtlas.
     * @~chinese 当前显示的字符串
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getStringValue() const{return this->getString();}

    /**
    * @~english Get string value for labelatlas.
    * @~chinese 获取当前显示显示的字符串
    * @return The string value of TextAtlas.
    * @~chinese 当前显示的字符串
    */
    const std::string& getString() const;
    
    /**
     * @~english Gets the string length of the label.
     * @~chinese 获取字符串的长度
     * @note @~english This length will be larger than the raw string length,
     * if you want to get the raw string length, you should call this->getString().size() instead
     * @~chinese 该长度会比原始字符串长度要大，如果你要获取原始字符串长度，请使用this->getString().size() 代替
     * @return  @~english The string length.
     * @~chinese 长度
     */
    ssize_t getStringLength()const;
    
    //override "getVirtualRendererSize" method of widget.
    virtual Size getVirtualRendererSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
    /**
     * @js NA
     */
    virtual void adaptRenderers() override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
  
    void labelAtlasScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    Label* _labelAtlasRenderer;
    std::string _stringValue;
    std::string _charMapFileName;
    int _itemWidth;
    int _itemHeight;
    std::string _startCharMap;
    bool _labelAtlasRendererAdaptDirty;
};

}

// end of ui group
/// @}

NS_CC_END

#endif /* defined(__CocoGUI__LabelAtlas__) */
