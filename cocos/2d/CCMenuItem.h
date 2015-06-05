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
****************************************************************************/

#ifndef __CCMENU_ITEM_H__
#define __CCMENU_ITEM_H__

// C++ includes
#include <functional>

// cocos2d includes
#include "2d/CCNode.h"
#include "base/CCProtocols.h"

NS_CC_BEGIN

typedef std::function<void(Ref*)> ccMenuCallback;

class Label;
class LabelAtlas;
class Sprite;
class SpriteFrame;
#define kItemSize 32
    
/**
 * @addtogroup _2d
 * @{
 */

/** @class MenuItem
 * @brief @~english MenuItem base class.
 *  Subclass MenuItem (or any subclass) to create your custom MenuItem objects.
 *
 * @~chinese 菜单项基类。
 * 使用继承MenuItem的派生类创建自定义菜单项。
 */
class CC_DLL MenuItem : public Node
{
public:
    /** @~english Creates a MenuItem with no callback.
     * @~chinese 创建一个没有指定回调的菜单项。
     */
    static MenuItem* create();

    CC_DEPRECATED_ATTRIBUTE static MenuItem* create(Ref *rec, SEL_MenuHandler selector);

    /** @~english Creates a MenuItem with a callback.
     * @~chinese 创建一个指定回调的菜单项。
     */
    static MenuItem* create(const ccMenuCallback& callback);

    /** @~english Returns the outside box.
     * @~chinese 返回菜单项的外框。
     */
    Rect rect() const;

    /** @~english Activate the item.
     * @~chinese 激活菜单项。
     */
    virtual void activate();

    /** @~english The item was selected (not activated), similar to "mouse-over".
     * @~chinese 设定菜单项为选中状态 (没有激活), 类似鼠标悬停。
     */
    virtual void selected();

    /** @~english The item was unselected.
     * @~chinese 取消选中状态。
     */
    virtual void unselected();

    /** @~english Returns whether or not the item is enabled.
     * @~chinese 返回菜单项是否被启用（响应点击）。
     */
    virtual bool isEnabled() const;

    /** @~english Enables or disables the item.
     * @~chinese 启用或禁用菜单项。
     */
    virtual void setEnabled(bool value);

    /** @~english Returns whether or not the item is selected.
     * @~chinese 返回菜单项是否被选中。
     */
    virtual bool isSelected() const;

    /** @~english Set the callback to the menu item.
     * In js,can contain two params,the second param is jsptr.
     * @~chinese 设置菜单项回调。
     * 在js里，可以包含两个参数，第二个参数是jsptr。
     * @lua NA
     */
    void setCallback(const ccMenuCallback& callback);
    
    CC_DEPRECATED_ATTRIBUTE void setTarget(Ref *rec, SEL_MenuHandler selector);

    virtual void onExit() override;
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItem()
    : _selected(false)
    , _enabled(false)
	, _callback(nullptr)
    {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItem();
    
    /** 
     * @~english Initializes this MenuItem with a callback.
     * @~chinese 使用指定回调初始化该菜单项。
     * @lua NA
     */
    bool initWithCallback(const ccMenuCallback& callback);
    
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref *rec, SEL_MenuHandler selector);

protected:
    bool            _selected;
    bool            _enabled;
    ccMenuCallback _callback;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItem);
};

/** @class MenuItemLabel
 * @brief @~english An base class for "label" MenuItemLabel items.
 * Any Node that supports the LabelProtocol protocol can be added.
 * Supported nodes:
 * - LabelAtlas
 * - Label
 * @~chinese 一个"label"形式的标签菜单项基类。
 * 支持任何实现LabelProtocol接口的节点:
 * - LabelAtlas
 * - Label
 */
class CC_DLL MenuItemLabel : public MenuItem
{
public:
    CC_DEPRECATED_ATTRIBUTE static MenuItemLabel * create(Node*label, Ref* target, SEL_MenuHandler selector);

    /**
     * @~english Creates a MenuItemLabel with a Label and a callback.
     * @~chinese 使用给定的标签及回调创建一个标签菜单项。
     */
    static MenuItemLabel * create(Node*label, const ccMenuCallback& callback);

    /**
     * @~english Creates a MenuItemLabel with a Label without callback.
     * @~chinese 使用给定的标签创建一个没有设定回调的标签菜单项。
     */
    static MenuItemLabel* create(Node *label);

    /**
     * @~english Sets a new string to the inner label.
     * @~chinese 为内置的标签设置新的字符串。
     */
    void setString(const std::string& label);

    /**
     * @~english Gets the color that will be used to disable the item.
     * @~chinese 获取菜单项禁用状态下的颜色。
     */
    inline const Color3B& getDisabledColor() const { return _disabledColor; };

    /**
     * @~english Sets the color that will be used to disable the item.
     * @~chinese 设置菜单项禁用状态下的颜色。
     */
    inline void setDisabledColor(const Color3B& color) { _disabledColor = color; };
    
    /**
     * @~english Gets the label that is rendered.
     * @~chinese 获取菜单项中被用于显示文本的标签节点。
     */
    inline Node* getLabel() const { return _label; };
    
    /**
     * @~english Sets the label that is rendered.
     * @~chinese 给菜单项指定一个用于显示文本的标签节点。
     */
    void setLabel(Node* node);
    
    // Overrides
    virtual void activate() override;
    virtual void selected() override;
    virtual void unselected() override;
    virtual void setEnabled(bool enabled) override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemLabel()
    : _originalScale(0.0)
    , _label(nullptr)
    {}

    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemLabel();
    
    /** @~english Initializes a MenuItemLabel with a Label, target and selector.
     * @~chinese 初始化一个MenuItemLabel标签,目标和选择器。
     */
    bool initWithLabel(Node* label, const ccMenuCallback& callback);
    
    CC_DEPRECATED_ATTRIBUTE bool initWithLabel(Node* label, Ref* target, SEL_MenuHandler selector);
    
protected:
    Color3B    _colorBackup;
    float      _originalScale;

    Color3B _disabledColor;
    Node* _label;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemLabel);
};


/** @class MenuItemAtlasFont
 * @brief @~english Helper class that creates a MenuItemLabel class with a LabelAtlas.
 * @~chinese 一个基于给定的字符集配置创建菜单项的基类。
 */
class CC_DLL MenuItemAtlasFont : public MenuItemLabel
{
public:
    /**
     * @~english Creates a menu item from a string and atlas configuration.
     * @~chinese 使用给定的字符串及字符集配置创建菜单项。
     */
    static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap);

    CC_DEPRECATED_ATTRIBUTE static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector);

    /**
     * @~english Creates a menu item from a string, atlas configuration and callback.
     * @~chinese 使用给定的字符串、字符集配置及回调创建菜单项。
     */
    static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemAtlasFont(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemAtlasFont(){}
    
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector);
    
    bool initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemAtlasFont);
};


/** @class MenuItemFont
 * @brief @~english A MenuItemFont.
 * Helper class that creates a MenuItemLabel class with a Label.
 * @~chinese MenuItemFont A。
 * 一个创建MenuItemLabel菜单项的助手类。
 */
class CC_DLL MenuItemFont : public MenuItemLabel
{
public:
    /** @~english Creates a menu item from a string without callback. 
     * @~chinese 基于给定的字符串创建一个没有回调的菜单项。
     */
    static MenuItemFont * create(const std::string& value = "");

    CC_DEPRECATED_ATTRIBUTE static MenuItemFont * create(const std::string& value, Ref* target, SEL_MenuHandler selector);

    /** @~english Creates a menu item from a string with a callback. 
     * @~chinese 基于给定的字符串及回调创建菜单项。
     */
    static MenuItemFont * create(const std::string& value, const ccMenuCallback& callback);

    /** @~english Set default font size.  @~chinese 设置默认字体大小。*/
    static void setFontSize(int size);

    /** @~english Get default font size.  @~chinese 获取默认字体大小。*/
    static int getFontSize();

    CC_DEPRECATED_ATTRIBUTE static int fontSize() { return MenuItemFont::getFontSize(); };

    /** @~english Set the default font name.  @~chinese 设置默认字体名。*/
    static void setFontName(const std::string& name);

    /** @~english Get the default font name.  @~chinese 获取默认字体名。*/
    static const std::string& getFontName();

    CC_DEPRECATED_ATTRIBUTE static const std::string& fontName() { return MenuItemFont::getFontName(); };

    /** @~english Set the font size.
     * c++ can not overload static and non-static member functions with the same parameter types.
     * so change the name to setFontSizeObj.
     * @~chinese 设置字体大小。
     * c++不能重载相同参数类型的静态及非静态成员函数。
     * 所以改名setFontSizeObj。
     * @js setFontSize
     * @js NA
     */
    void setFontSizeObj(int size);
    
    /** @~english Get the font size .
     * @~chinese 获取字体大小。
     * @js getFontSize
     * @js NA
     */
    int getFontSizeObj() const;

    CC_DEPRECATED_ATTRIBUTE int fontSizeObj() const { return getFontSizeObj(); };
    
    /**@~english
     * Set the font name .
     * c++ can not overload static and non-static member functions with the same parameter types.
     * so change the name to setFontNameObj.
     * @~chinese 
     * 设置字体的名字。
     * c++不能重载相同参数类型的静态及非静态成员函数。
     * 所以改名setFontNameObj。
     * @js setFontName
     * @js NA
     */
    void setFontNameObj(const std::string& name);

    /** @~english Returns the name of the font.
     * @~chinese 返回字体的名称。
     * @js getFontNameObj
     * @js NA
     */
    const std::string& getFontNameObj() const;

    CC_DEPRECATED_ATTRIBUTE const std::string& fontNameObj() const { return getFontNameObj(); }
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemFont();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemFont();
    
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const std::string& value, Ref* target, SEL_MenuHandler selector);
    
    bool initWithString(const std::string& value, const ccMenuCallback& callback);
    
protected:
    int _fontSize;
    std::string _fontName;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemFont);
};


/** @class MenuItemSprite
 * @brief @~english MenuItemSprite accepts Node<RGBAProtocol> objects as displayed items.
 * Displayed item has 3 different states:
 * - normal
 * - selected
 * - disabled
 * 
 * @~chinese MenuItemSprite接受实现了Node<RGBAProtocol>接口的任何节点对象作为显示项。
 * 显示项有3个不同的状态:
 * - 正常
 * - 选中
 * - 不可用
 * 
 @since v0.8.0
 */
class CC_DLL MenuItemSprite : public MenuItem
{
public:
    /** @~english Creates a menu item with a normal, selected and disabled node. @~chinese 基于给定的不同状态下的Node对象创建菜单项。*/
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite = nullptr);
    
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Ref* target, SEL_MenuHandler selector);
    
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector);

    /** @~english Creates a menu item with a normal and selected node with a callback.  @~chinese 基于给定的不同状态下的Node对象及回调创建菜单项。*/
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback);

    /** @~english Creates a menu item with a normal,selected and disabled node with callback. @~chinese 基于给定的不同状态下的Node对象及回调创建菜单项 */
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);

    /** @~english Gets the node used when the item is not selected.  @~chinese 获取正常状态下使用的节点。*/
    inline Node* getNormalImage() const { return _normalImage; };
    
    /** @~english Sets the node used when the item is not selected.  @~chinese 设置用于正常状态下的节点。*/
    void setNormalImage(Node* image);
    
    /** @~english Gets the node used when the item is selected.  @~chinese 获取选中状态下使用的节点。*/
    inline Node* getSelectedImage() const { return _selectedImage; };
    
    /** @~english Sets the node used when the item is selected.  @~chinese 设置用于选中状态下的节点。*/
    void setSelectedImage(Node* image);
    
    /** @~english Gets the node used when the item is disabled.  @~chinese 获取不可用状态下使用的节点。*/
    inline Node* getDisabledImage() const { return _disabledImage; };
    
    /** @~english Sets the node used when the item is disabled.  @~chinese 设置用于不可用状态下的节点。*/
    void setDisabledImage(Node* image);
    
    
    virtual void selected() override;

    virtual void unselected() override;

    virtual void setEnabled(bool bEnabled) override;
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemSprite()
    :_normalImage(nullptr)
    ,_selectedImage(nullptr)
    ,_disabledImage(nullptr)
    {}
    
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector);

    bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);
    
protected:
    virtual void updateImagesVisibility();

    Node* _normalImage;
    Node* _selectedImage;
    Node* _disabledImage;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemSprite);
};


/** @class MenuItemImage
 * @brief @~english MenuItemImage accepts images as displayed items.
 * Displayed items has 3 different states:
 * - normal
 * - selected
 * - disabled
 * 
 * For best results try that all images are of the same size.
 * @~chinese 图片菜单项，接受图像资源作为显示项。
 * 显示项有3个不同的状态:
 * - 正常
 * - 选中
 * - 不可用
 * 
 * 为了获取最佳效果，所有图片资源的大小应该保持一致。
 */
class CC_DLL MenuItemImage : public MenuItemSprite
{
public:
    /** @~english Creates an MenuItemImage.  @~chinese 创建一个空的图片菜单项。*/
    static MenuItemImage* create();

    /** @~english Creates a menu item with a normal and selected image. @~chinese 基于给定的正常及选中状态的图片资源创建菜单项。*/
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage);
    /** @~english Creates a menu item with a normal,selected  and disabled image. @~chinese 基于给定的正常、选中及不可用状态的图片资源创建菜单项。*/
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage);

    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, Ref* target, SEL_MenuHandler selector);

    /** @~english Creates a menu item with a normal and selected image with a callback. @~chinese 基于给定的正常及选中状态的图片资源及回调创建菜单项。*/
    static MenuItemImage* create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);

    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    
    /** @~english Creates a menu item with a normal,selected  and disabled image with a callable object.  @~chinese 基于给定的不同状态下的图片资源及回调创建菜单项。*/
    static MenuItemImage* create(const std::string&normalImage, const std::string&selectedImage, const std::string&disabledImage, const ccMenuCallback& callback);

    /** @~english Sets the sprite frame for the normal image.  @~chinese 设置一个SpriteFrame对象给正常状态下所使用的图片。*/
    void setNormalSpriteFrame(SpriteFrame* frame);
    /** @~english Sets the sprite frame for the selected image.  @~chinese 设置一个SpriteFrame对象给选中状态下所使用的图片。*/
    void setSelectedSpriteFrame(SpriteFrame* frame);
    /** @~english Sets the sprite frame for the disabled image.  @~chinese 设置一个SpriteFrame对象给不可用状态下所使用的图片。*/
    void setDisabledSpriteFrame(SpriteFrame* frame);
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemImage(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemImage(){}
    
    bool init();
    
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    
    bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemImage);
};


/** @class MenuItemToggle
 * @brief @~english A MenuItemToggle.
 * A simple container class that "toggles" it's inner items.
 * The inner items can be any MenuItem.
 * @~chinese 菜单项触发器。
 * 一个实现切换内部菜单项的简单容器类。
 * 内部项可以是任何MenuItem对象。
 */
class CC_DLL MenuItemToggle : public MenuItem
{
public:
    
    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle * createWithTarget(Ref* target, SEL_MenuHandler selector, const Vector<MenuItem*>& menuItems);

    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle* createWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, ...)CC_REQUIRES_NULL_TERMINATION;
    
    /**
     *@brief @~english Creates a menu item toggle from a Vector of MenuItem with a callback.
     * @~chinese 基于给定的回调及菜单项数组创建菜单项触发器。
     */
    static MenuItemToggle * createWithCallback(const ccMenuCallback& callback, const Vector<MenuItem*>& menuItems);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported.
    typedef MenuItem* M;
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, m7, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return createWithCallbackVA(callback, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for lists longer than 10 items, use createWithArray or variadicCreate with NULL as the last argument.
    static MenuItemToggle* createWithCallbackVA(const ccMenuCallback& callback, M item, ...);
#else
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
#endif
    /** @~english Creates a menu item toggle with no callback. @~chinese 创建一个没有回调的菜单项触发器。*/
    static MenuItemToggle* create();
    
    /** @~english Creates a menu item toggle with a item.  @~chinese 基于一个给定的菜单项创建菜单项触发器。*/
    static MenuItemToggle* create(MenuItem *item);
    
    /** @~english Add more menu item.  @~chinese 添加菜单项。*/
    void addSubItem(MenuItem *item);
    
    /** @~english Return the selected item.  @~chinese 返回选中的菜单项。*/
    MenuItem* getSelectedItem();
    
    CC_DEPRECATED_ATTRIBUTE MenuItem* selectedItem() { return getSelectedItem(); }

    /** @~english Gets the index of the selected item.  @~chinese 获取被选中的菜单项索引。*/
    inline unsigned int getSelectedIndex() const { return _selectedIndex; };
    
    /** @~english Sets the index of the selected item.  @~chinese 设置被选中的菜单项索引。*/
    void setSelectedIndex(unsigned int index);
    
    /** @~english Gets the array that contains the subitems.
     *You can add/remove items in runtime, and you can replace the array with a new one.
     * @~chinese 获取触发器包含的菜单项。
     * 您可以在运行时添加或者删除菜单项，或者替换整个菜单项数组。
     * @since v0.7.2
     * @js NA
     * @lua NA
     */
    inline const Vector<MenuItem*>& getSubItems() const { return _subItems; };
    inline Vector<MenuItem*>& getSubItems() { return _subItems; };

    /** @~english Sets the array that contains the subitems.  @~chinese 设定触发器包含的菜单项。*/
    inline void setSubItems(const Vector<MenuItem*>& items) {
        _subItems = items;
    }
    
    // Overrides
    virtual void activate() override;
    virtual void selected() override;
    virtual void unselected() override;
    virtual void setEnabled(bool var) override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItemToggle()
    : _selectedIndex(0)
    {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItemToggle();
    
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, va_list args);

    bool initWithCallback(const ccMenuCallback& callback, MenuItem* item, va_list args);

    bool initWithItem(MenuItem *item);

protected:

    unsigned int _selectedIndex;
    
    Vector<MenuItem*> _subItems;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemToggle);

};


// end of 2d group
/// @}

NS_CC_END

#endif //__CCMENU_ITEM_H__
