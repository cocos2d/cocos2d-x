/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __UIRICHTEXT_H__
#define __UIRICHTEXT_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {
    
/** @class RichElement
*@brief @~english Rich text element base class.
 It defines the basic common properties for all rich text element.
 
 @~chinese 富文本元素基类。
 它定义了所有的富文本元素的通用属性。
*/
class CC_GUI_DLL RichElement : public Ref
{
public:
    /**
     *@brief Rich element type.
     */
    enum class Type
    {
        TEXT,
        IMAGE,
        CUSTOM
    };
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RichElement(){};
    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichElement(){};

    
    /**
     * @~english Initialize a rich element with different arguments.
     * @~chinese 通过不同的参数初始化一个富文本元素。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in @see `Color3B`. @~chinese 颜色值。 
     * @param opacity @~english A opacity value in `GLubyte`. @~chinese 不透明度。
     * @return @~english True if initialize success, false otherwise. @~chinese True表明初始化成功，反之失败。
     */
    bool init(int tag, const Color3B& color, GLubyte opacity);
protected:
    Type _type;
    int _tag;
    Color3B _color;
    GLubyte _opacity;
    friend class RichText;
};
    
/** @class RichElementText
*@brief @~english Rich element for displaying text.

 @~chinese 用以显示文本的RichElementText。
*/
class CC_GUI_DLL RichElementText : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RichElementText(){_type = Type::TEXT;};

    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichElementText(){};
    
    /**
     * @~english Initialize a RichElementText with various arguments.
     * @~chinese 通过多个变量初始化一个RichElementText类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param text @~english Content string. @~chinese 文本内容。
     * @param fontName @~english Content font name. @~chinese 文本字体名称。
     * @param fontSize @~english Content font size. @~chinese 文本字体大小。
     * @return @~english True if initialize scucess, false otherwise. @~chinese True表明初始化成功，反之失败。
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);

    
    /**
     * @~english Create a RichElementText with various arguments.
     * @~chinese 通过多个变量创建一个RichElementText类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param text @~english Content string. @~chinese 文本内容。
     * @param fontName @~english Content font name. @~chinese 文本字体名称。
     * @param fontSize @~english Content font size. @~chinese 文本字体大小。
     * @return @~english RichElementText instance. @~chinese 富文本类实例。
     */
    static RichElementText* create(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);
protected:
    std::string _text;
    std::string _fontName;
    float _fontSize;
    friend class RichText;
    
};
    
/** @class RichElementImage
*@brief @~english Rich element for displaying images.

 @~chinese 用以显示图片的RichElementImage。
*/
class CC_GUI_DLL RichElementImage : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     *
     */
    RichElementImage(){_type = Type::IMAGE;};

    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichElementImage(){};

    
    /**
     * @~english Initialize a RichElementImage with various arguments.
     * @~chinese 通过多个变量初始化一个RichElementImage类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param filePath @~english A image file name. @~chinese 图片文件名。
     * @return @~english True if initialize success, false otherwise. @~chinese True表明初始化成功，反之失败。
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);

    
    /**
     * @~english Create a RichElementImage with various arguments.
     * @~chinese 通过多个变量创建一个RichElementImage类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param filePath @~english A image file name. @~chinese 图片文件名。
     * @return @~english A RichElementImage instance. @~chinese 一个RichElementImage实例。
     */
    static RichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);
protected:
    std::string _filePath;
    Rect _textureRect;
    int _textureType;
    friend class RichText;
};
    
/** @class RichElementCustomNode
*@brief @~english Rich element for displaying custom node type.

 @~chinese 用以显示自定义节点类型的RichElementCustomNode。
*/
class CC_GUI_DLL RichElementCustomNode : public RichElement
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RichElementCustomNode(){_type = Type::CUSTOM;};

    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};

    
    /**
     * @~english Initialize a RichElementCustomNode with various arguments.
     * @~chinese 通过多个变量初始化一个RichElementCustomNode类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param customNode @~english A custom node pointer. @~chinese 自定义节点指针。
     * @return @~english True if initialize success, false otherwise. @~chinese True表明初始化成功，反之失败。
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
    
    /**
     * @~english Create a RichElementCustomNode with various arguments.
     * @~chinese 通过多个变量创建一个RichElementCustomNode类。
     * @param tag @~english A integer tag value. @~chinese 标签值。
     * @param color @~english A color in Color3B. @~chinese 颜色值。
     * @param opacity @~english A opacity in GLubyte. @~chinese 不透明度。
     * @param customNode @~english A custom node pointer. @~chinese 自定义节点指针。
     * @return @~english A RichElementCustomNode instance. @~chinese True表明初始化成功，反之失败。
     */
    static RichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
protected:
    Node* _customNode;
    friend class RichText;
};
    
/**
*@brief @~english A container for displaying various RichElements.
 We could use it to display texts with images easily.

 @~chinese 一个显示多个RichElement的容器类。
 我们可以使用它很容易显示带图片的文本。
*/
class CC_GUI_DLL RichText : public Widget
{
public:
    
    /**
     * @~english Default constructor.
     * @~chinese 默认构造器
     * @js ctor
     * @lua new
     */
    RichText();
    
    /**
     * @~english Default destructor.
     * @~chinese 默认析构器
     * @js NA
     * @lua NA
     */
    virtual ~RichText();
    
    /**
     * @~english Create a empty RichText.
     * @~chinese 创建一个空的RichText。
     * @return @~english RichText instance. @~chinese RichText实例。
     */
    static RichText* create();
    
    /**
     * @~english Insert a RichElement at a given index.
     * @~chinese 在指定位置插入一个RichElement。
     * @param element @~english A RichElement type. @~chinese 一个RichElement类。
     * @param index @~english A given index. @~chinese 索引值。
     */
    void insertElement(RichElement* element, int index);
    
    /**
     * @~english Add a RichElement at the end of RichText.
     * @~chinese 在容器最后插入一个RichElement。
     * @param element @~english A RichElement instance. @~chinese 一个RichElement类。
     */
    void pushBackElement(RichElement* element);
    
    /**
     * @~english Remove a RichElement at a given index.
     * @~chinese 移除指定位置的RichElement。
     * @param index @~english A integer index value. @~chinese 索引值。
     */
    void removeElement(int index);
    
    /**
     * @~english Remove specific RichElement.
     * @~chinese 移除一个RichElement。
     * @param element @~english A RichElement type. @~chinese 一个RichElement类指针。
     */
    void removeElement(RichElement* element);
    
    /**
     * @~english Set vertical space between each RichElement.
     * @~chinese 设置每个RichElement的垂直间隔。
     * @param space @~english Point in float. @~chinese 垂直间隔值。
     */
    void setVerticalSpace(float space);
    
    /**
     * @~english Rearrange all RichElement in the RichText.
     * It's usually called internally.
     * @~chinese 重新排列所有的RichElement。
     * 常内部调用。
     */
    void formatText();

    //override functions.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void adaptRenderers() override;

    virtual void initRenderer() override;
    void pushToContainer(Node* renderer);
    void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B& color, GLubyte opacity);
    void handleImageRenderer(const std::string& fileParh, const Color3B& color, GLubyte opacity);
    void handleCustomRenderer(Node* renderer);
    void formarRenderers();
    void addNewLine();
protected:
    bool _formatTextDirty;
    Vector<RichElement*> _richElements;
    std::vector<Vector<Node*>*> _elementRenders;
    float _leftSpaceWidth;
    float _verticalSpace;
};
    
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UIRichText__) */
