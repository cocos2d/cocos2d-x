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

#ifndef __LAYOUTPARMETER_H__
#define __LAYOUTPARMETER_H__

#include <string>
#include "base/CCRef.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {

/**
 * @brief @~english Margin of widget's in point. Margin value should be positive.
 * @~chinese 控件的边距。
 * @lua NA
 */
class CC_GUI_DLL Margin
{
public:

    /**
     * @~english
     * Left margin.
     * @~chinese 
     * 左边距
     */
    float left;

    /**
     * @~english
     * Top margin.
     * @~chinese 
     * 上边距
     */
    float top;

    /**
     * @~english
     * Right margin.
     * @~chinese 
     * 右边距
     */
    float right;

    /**
     * @~english
     * Bottom margin.
     * @~chinese 
     * 底部边距。
     */
    float bottom;
    
public:

    /**
     * @~english
     * Default constructor.
     * @~chinese 
     * 默认构造函数。
     */
    Margin();

    /**
     * @~english
     * Construct a Margin instance with left, top, right and bottom margins.
     * @~chinese 
     * 使用左,上,右,下边距构造一个Margin实例。
     *
     * @param l @~english Left margin in float.
     * @~chinese 左边距
     * @param t @~english Top margin in float.
     * @~chinese 上边距
     * @param r @~english Right margin in float.
     * @~chinese 右边距
     * @param b @~english Bottom margin in float.
     * @~chinese 下边距
     */
    Margin(float l, float t, float r, float b);

    /**
     * @~english
     * Copy constructor.
     * @~chinese 
     * 拷贝构造函数。
     */
    Margin(const Margin& other);

    /**
     * @~english
     * Copy assignment operator.
     * @~chinese 
     * 拷贝赋值运算符。
     */
    Margin& operator= (const Margin& other);

    /**
     * @~english
     * Change margin with left, top, right and bottom margin.
     * @~chinese 
     * 设置Margin实例内的左,上,右,下边距
     *
     * @param l @~english Left margin in float.
     * @~chinese 左边距
     *
     * @param t @~english Top margin in float.
     * @~chinese 上边距
     * @param r @~english Right margin in float.
     * @~chinese 右边距
     *
     * @param b @~english Bottom margin in float.
     * @~chinese 下边距
     */
    void setMargin(float l, float t, float r, float b);

    /**
     * @~english
     * Test equality of two margins.
     * @~chinese 
     * 测试两个边距是否相等
     *
     * @param target @~english A Margin instance.
     * @~chinese Margin实例。
     *
     * @return @~english True if two margins are equal, false otherwise.
     * @~chinese 如果两个Margin相等返回true，否则返回false
     */
    bool equals(const Margin& target) const;
    
    /**
     * @~english
     * A margin constant with all margins equal zero.
     * @~chinese 
     * 一个所有边距为0的Margin实例
     */
    static const Margin ZERO;

};


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef RELATIVE
#undef RELATIVE
#endif
#endif

/**
 * @brief @~english Base class for various LayoutParameter.
 * @~chinese LayoutParameter基类。
 */
class CC_GUI_DLL LayoutParameter : public Ref
{
public:

    /**
     * @~english
     * Layout parameter type.
     * There are mainly two types:
     * - Linear: Elements will be arranged by margin.
     * - Relative: Elements will be arranged by margin and relative widget name.
     * @~chinese 
     * 布局参数类型。
     * 主要有两种类型:
     *  - 线性:元素将根据边距布置。
     *  - 相对:元素将根据边距和相对控件的名字来布置
     */
    enum class Type
    {
        NONE = 0,
        LINEAR,
        RELATIVE
    };

    /**
     * @~english
     * Default constructor.
     *
     * @~chinese 
     * 默认构造函数。
     * 
     * @lua new
     */
    LayoutParameter() : _margin(Margin())
    {
        _layoutParameterType = Type::NONE;
    };
    
    /**
     * @~english
     * Default destructor.
     * @~chinese 
     * 默认的析构函数。
     * @lua NA
     */
    virtual ~LayoutParameter(){};
    
    /**
     * @~english
     * Create a empty LayoutParameter.
     * @~chinese 
     * 一个空的LayoutParameter
     * @return @~english A autorelease LayoutParameter instance.
     * @~chinese 一个autorelease LayoutParameter实例。
     */
    static LayoutParameter* create();
    
    /**
     * @~english
     * Set margin parameter for LayoutParameter.
     * 
     * @~chinese 
     * 设置LayoutParameter边距参数。
     * 
     * @see Margin
     * @param @~english margin
     * @~chinese 边距
     */
    void setMargin(const Margin& margin);
    
    /**
     * @~english
     * Gets margin parameter of LayoutParameter.
     *
     * @~chinese 
     * 获取LayoutParameter的边距参数。
     * 
     * @see Margin
     * @return @~english Margin of layout parameter.
     * @~chinese layout的边距参数
     */
    const Margin& getMargin() const;
    
    /**
     * @~english
     * Gets LayoutParameterType of LayoutParameter.
     *
     * @~chinese 
     * 获取LayoutParameter的LayoutParameterType
     * 
     * @see LayoutParameterType.
     * @return @~english LayoutParameterType
     * @~chinese layout参数类型
     */
    Type getLayoutType() const;
    
    /**
     * @~english
     * Create a copy of original LayoutParameter.
     * @~chinese 
     * 创建一个原始的LayoutParameter。
     *@return @~english A LayoutParameter pointer.
     * @~chinese LayoutParameter指针。
     */
    LayoutParameter* clone();

    /**
     * @~english
     * Create a cloned instance of LayoutParameter.
     * @~chinese 
     * 克隆一个LayoutParameter的实例。
     * @return @~english A LayoutParameter pointer.
     * @~chinese LayoutParameter指针。
     */
    virtual LayoutParameter* createCloneInstance();
    
    /**
     * @~english
     * Copy all the member field from argument LayoutParameter to self.
     * @~chinese 
     * 复制LayoutParameter的所有参数
     * @param model @~english A LayoutParameter instance.
     * @~chinese LayoutParameter实例。
     */
    virtual void copyProperties(LayoutParameter* model);

protected:
    Margin _margin;
    Type _layoutParameterType;
};
    
/**
 * @~english
 * Protocol for getting a LayoutParameter.
 * Every element want to have layout parameter should inherit from this class.
 * @~chinese 
 * 获取一个LayoutParameter的协议
 * 每一个带有布局参数的元素都应该继承自这个类。
 */
class CC_GUI_DLL LayoutParameterProtocol
{
public:

    /**
     * @~english
     * Default destructor.
     * @~chinese 
     * 默认的析构函数。
     */
    virtual ~LayoutParameterProtocol(){}

    /**
     * @return @~english A LayoutParameter and its descendant pointer.
     * @~chinese LayoutParameter及其子类的指针。
     */
    virtual LayoutParameter* getLayoutParameter() const= 0;
};

    
/**
 * @brief @~english Linear layout parameter.
 * It is used by linear layout manager for arranging elements linearly.
 * @~chinese 线性布局参数
 * 它是专门为线性排列元素用线性布局管理器
 */
class CC_GUI_DLL LinearLayoutParameter : public LayoutParameter
{
public:

    /**
     * @~english
     * Linear gravity.
     * @~chinese 
     * 线性引力
     */
    enum class LinearGravity
    {
        NONE,
        LEFT,
        TOP,
        RIGHT,
        BOTTOM,
        CENTER_VERTICAL,
        CENTER_HORIZONTAL
    };

    /**
     * @~english
     * Default constructor.
     *
     * @~chinese 
     * 默认构造函数。
     * 
     * @lua new
     */
    LinearLayoutParameter()
    : _linearGravity(LinearGravity::NONE)
    {
        _layoutParameterType = Type::LINEAR;
    };
    
    /**
     * @~english
     * Default destructor.
     *
     * @~chinese 
     * 默认的析构函数。
     * 
     * @lua NA
     */
    virtual ~LinearLayoutParameter(){};
    
    /**
     * @~english
     * Create a empty LinearLayoutParameter instance.
     * @~chinese 
     * 创建一个空的LinearLayoutParameter实例
     * @return @~english A initialized LayoutParameter which is marked as "autorelease".
     * @~chinese 初始化一个被标记为autorelease的LayoutParameter
     */
    static LinearLayoutParameter* create();
    
    /**
     * @~english
     * Sets LinearGravity parameter for LayoutParameter.
     *
     * @~chinese 
     * 设置LayoutParameter的LinearGravity参数。
     * 
     * @see LinearGravity
     * @param gravity @~english Gravity in LinearGravity.
     * @~chinese LinearGravity的引力
     */
    void setGravity(LinearGravity gravity);
    
    /**
     * @~english
     * Gets LinearGravity parameter for LayoutParameter.
     *
     * @~chinese 
     * 获取LayoutParameter的LinearGravity参数。
     * 
     * @see LinearGravity
     * @return @~english LinearGravity
     * @~chinese 线性引力
     */
    LinearGravity getGravity() const;

    //override functions.
    virtual LayoutParameter* createCloneInstance() override;
    virtual void copyProperties(LayoutParameter* model) override;
protected:
    LinearGravity _linearGravity;
    int i;
};
    
    

/**
 * @brief @~english Relative layout parameter.
 * It is mainly used by  `RelativeLayoutManager`.
 * @~chinese 相对布局参数
 * 它主要用于RelativeLayoutManager。
 */
class CC_GUI_DLL RelativeLayoutParameter : public LayoutParameter
{
public:

    /**
     * @~english
     * Relative Alignment type
     * @~chinese 
     * 相对对齐的类型
     */
    enum class RelativeAlign
    {
        NONE,
        PARENT_TOP_LEFT,
        PARENT_TOP_CENTER_HORIZONTAL,
        PARENT_TOP_RIGHT,
        PARENT_LEFT_CENTER_VERTICAL,
        
        CENTER_IN_PARENT,
        
        PARENT_RIGHT_CENTER_VERTICAL,
        PARENT_LEFT_BOTTOM,
        PARENT_BOTTOM_CENTER_HORIZONTAL,
        PARENT_RIGHT_BOTTOM,
        
        LOCATION_ABOVE_LEFTALIGN,
        LOCATION_ABOVE_CENTER,
        LOCATION_ABOVE_RIGHTALIGN,
        LOCATION_LEFT_OF_TOPALIGN,
        LOCATION_LEFT_OF_CENTER,
        LOCATION_LEFT_OF_BOTTOMALIGN,
        LOCATION_RIGHT_OF_TOPALIGN,
        LOCATION_RIGHT_OF_CENTER,
        LOCATION_RIGHT_OF_BOTTOMALIGN,
        LOCATION_BELOW_LEFTALIGN,
        LOCATION_BELOW_CENTER,
        LOCATION_BELOW_RIGHTALIGN
    };

    /**
     * @~english
     * Default constructor
     *
     * @~chinese 
     * 默认构造函数
     * 
     * @lua new
     */
    RelativeLayoutParameter()
    : _relativeAlign(RelativeAlign::NONE),
    _relativeWidgetName(""),
    _relativeLayoutName(""),
    _put(false)
    {
        _layoutParameterType = Type::RELATIVE;
    };
    
    /**
     * @~english
     * Default destructor
     *
     * @~chinese 
     * 默认的析构函数
     * 
     * @lua NA
     */
    virtual ~RelativeLayoutParameter(){};
    
    /**
     * @~english
     * Create a RelativeLayoutParameter instance.
     * @~chinese 
     * 创建一个RelativeLayoutParameter实例。
     * @return @~english A initialized LayoutParameter which is marked as "autorelease".
     * @~chinese 初始化一个标记为autorelease的LayoutParameter。
     */
    static RelativeLayoutParameter* create();
    
    /**
     * @~english
     * Sets RelativeAlign parameter for LayoutParameter.
     *
     * @~chinese 
     * 设置为LayoutParameter的RelativeAlign参数。
     * 
     * @see RelativeAlign
     * @param align @~english Relative align in  `RelativeAlign`.
     * @~chinese 相对对齐参数`RelativeAlign`。
     */
    void setAlign(RelativeAlign align);
    
    /**
     * @~english
     * Get RelativeAlign parameter for LayoutParameter.
     *
     * @~chinese 
     * 获得LayoutParameter的RelativeAlign参数。
     * 
     * @see RelativeAlign
     * @return @~english A RelativeAlign variable.
     * @~chinese 一个RelativeAlign变量。
     */
    RelativeAlign getAlign() const;
    
    /**
     * @~english
     * Set widget name your widget want to relative to.
     *
     * @~chinese 
     * 设置相对于控件的名称。
     * 
     * @param name @~english Relative widget name.
     * @~chinese 相对控件的名称。
     */
    void setRelativeToWidgetName(const std::string& name);
    
    /**
     * @~english
     * Get the relative widget name.
     * @~chinese 
     * 得到相对的控件的名称。
     * @return @~english name A relative widget name in string.
     * @~chinese 相对控件名称字符串
     */
    const std::string& getRelativeToWidgetName() const;
    
    /**
     * @~english
     * Set a name for LayoutParameter in Relative Layout.
     *
     * @~chinese 
     * 为LayoutParameter在相对布局里设置一个名字。
     * 
     * @param name @~english A string name.
     * @~chinese 一个名字字符串。
     */
    void setRelativeName(const std::string& name);
    
    /**
     * @~english
     * Get a name of LayoutParameter in Relative Layout.
     *
     * @~chinese 
     * 在相对布局中获取LayoutParameter的名字。
     * 
     * @return @~english name Relative name in string.
     * @~chinese 相对布局的的名字字符串。
     */
    const std::string& getRelativeName() const;
    
    //override functions.
    virtual LayoutParameter* createCloneInstance() override;
    virtual void copyProperties(LayoutParameter* model) override;
protected:
    RelativeAlign _relativeAlign;
    std::string _relativeWidgetName;
    std::string _relativeLayoutName;
    bool _put;
    friend class RelativeLayoutManager;
};

}
NS_CC_END
// end of ui group
/// @}

#endif /* defined(__LayoutParameter__) */
