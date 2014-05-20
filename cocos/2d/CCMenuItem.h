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
#include "2d/CCProtocols.h"

NS_CC_BEGIN

typedef std::function<void(Ref*)> ccMenuCallback;

class Label;
class LabelAtlas;
class Sprite;
class SpriteFrame;
#define kItemSize 32
    
/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */

/** @brief MenuItem基类
 *
 *  子类菜单项（或任意一个子类）来创建自定义MenuItem对象.
 */
class CC_DLL MenuItem : public Node
{
public:
    /** 创建一个没有 target/selector 的菜单项 */
    static MenuItem* create();
    /** 创建一个指定 target/selector 的菜单项 */
    CC_DEPRECATED_ATTRIBUTE static MenuItem* create(Ref *rec, SEL_MenuHandler selector);
    /** 创建一个指定 target/selector 的菜单项 */
    static MenuItem* create(const ccMenuCallback& callback);

    /** 返回边框盒子 */
    Rect rect() const;
    /** 激活该项 */
    virtual void activate();
    /** 该项已经被选择了 (没有激活), 类似 "mouse-over" */
    virtual void selected();
    /** 该项没有被选中 */
    virtual void unselected();
    /** 返回该项是否被启用 */
    virtual bool isEnabled() const;
    /** 启用或禁用该项 */
    virtual void setEnabled(bool value);
    /** 返回该项是否被选中 */
    virtual bool isSelected() const;

    /** 设置菜单项的回调
    * @code
    * 在 js 里面，可以包含两个参数，第二个参数是 jsptr
    * @endcode
    * @lua NA
    */
    void setCallback(const ccMenuCallback& callback);
    /** 设置菜单项的 target/selector
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE void setTarget(Ref *rec, SEL_MenuHandler selector);


    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    MenuItem()
    : _selected(false)
    , _enabled(false)
	, _callback(nullptr)
    , _target(nullptr)
    {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~MenuItem();
    
    /** 指定 target/selector 初始化一个菜单项
     * @js NA
     * @lua NA
     */
    bool initWithCallback(const ccMenuCallback& callback);
    /** 指定 target/selector 初始化一个菜单项
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref *rec, SEL_MenuHandler selector);

protected:
    bool            _selected;
    bool            _enabled;
	// callback
	ccMenuCallback _callback;
	// If using the old API, the _target needs to be retained / released
	Ref		*_target;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItem);
};

/** @brief 一个"label"形式的标签菜单项项目的抽象类
 任何支持LabelProtocol协议的节点都可以添加进来.
 支持的节点:
 - BitmapFontAtlas
 - LabelAtlas
 - LabelTTF
 - Label
 */
class CC_DLL MenuItemLabel : public MenuItem
{
public:
    /** 使用指定标签, target和selector创建一个标签菜单项 */
    CC_DEPRECATED_ATTRIBUTE static MenuItemLabel * create(Node*label, Ref* target, SEL_MenuHandler selector);

	/** 使用指定标签和回调创建一个标签菜单项 */
    static MenuItemLabel * create(Node*label, const ccMenuCallback& callback);

    /** 使用指定标签创建一个标签菜单项. Target 和 selector可能为nil */
    static MenuItemLabel* create(Node *label);

    /** 为内置的标签设置新的string值 */
    void setString(const std::string& label);

    /** 获取用于该项禁用的颜色 */
    inline const Color3B& getDisabledColor() const { return _disabledColor; };

    /** 设置用于该项禁用的颜色 */
    inline void setDisabledColor(const Color3B& color) { _disabledColor = color; };
    
    /** 获取标签菜单项呈现的label. */
    inline Node* getLabel() const { return _label; };
    
    /** 设置标签菜单项呈现的label. */
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
    
	/** 使用指定标签, target和selector初始化一个标签菜单项 */
    bool initWithLabel(Node* label, const ccMenuCallback& callback);
    
    /** 使用指定标签, target和selector初始化一个标签菜单项 */
    CC_DEPRECATED_ATTRIBUTE bool initWithLabel(Node* label, Ref* target, SEL_MenuHandler selector);
    
protected:
    Color3B    _colorBackup;
    float      _originalScale;

    /** 用于该项被禁用显示的颜色 */
    Color3B _disabledColor;
    /** 呈现的标签Label. 它可以是实现LabelProtocol协议的任何节点(Node) */
    Node* _label;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemLabel);
};


/** @brief A MenuItemAtlasFont
 助手类，创建一个带LabelAtlas的标签菜单项(MenuItemLabel)
 */
class CC_DLL MenuItemAtlasFont : public MenuItemLabel
{
public:
    /** 通过使用一个 string 、 atlas 、 target/selector 创建一个菜单项 */
    static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap);
    /** 通过使用一个 string 、 atlas 创建一个菜单项. 在 MenuItemToggle 里面使用. */
    CC_DEPRECATED_ATTRIBUTE static MenuItemAtlasFont* create(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector);
    /** 通过使用一个 string 、 atlas 创建一个菜单项. 在 MenuItemToggle 里面使用. */
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
    
    /** 通过使用一个string 、 atlas 、 target/selector 初始化一个菜单项 */
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, Ref* target, SEL_MenuHandler selector);
    
    /** 通过使用一个string 、 atlas 、 target/selector 初始化一个菜单项 */
    bool initWithString(const std::string& value, const std::string& charMapFile, int itemWidth, int itemHeight, char startCharMap, const ccMenuCallback& callback);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemAtlasFont);
};


/** @brief A MenuItemFont
 助手类，创建一个带Label的标签菜单项
 */
class CC_DLL MenuItemFont : public MenuItemLabel
{
public:
    /** 不使用 target/selector 值使用一个 string 创建一个菜单项. 在 MenuItemToggle 里面使用 */
    static MenuItemFont * create(const std::string& value = "");
    /** 使用一个string 和 target/selector 创建一个菜单项 */
    CC_DEPRECATED_ATTRIBUTE static MenuItemFont * create(const std::string& value, Ref* target, SEL_MenuHandler selector);
    /** 使用一个string 和 target/selector 创建一个菜单项 */
    static MenuItemFont * create(const std::string& value, const ccMenuCallback& callback);

    /** 设置默认字体大小 */
    static void setFontSize(int size);
    /** 获取默认字体大小 */
    static int getFontSize();
    CC_DEPRECATED_ATTRIBUTE static int fontSize() { return MenuItemFont::getFontSize(); };
    /** 设置默认字体名称 */
    static void setFontName(const std::string& name);
    /** 获取默认字体名称 */
    static const std::string& getFontName();
    CC_DEPRECATED_ATTRIBUTE static const std::string& fontName() { return MenuItemFont::getFontName(); };

    /** 设置字体大小
     * c++ 不能重载具有相同参数类型的static和non-static成员方法
     * 所以名称修改为 setFontSizeObj
     * @js setFontSize
     */
    void setFontSizeObj(int size);
    
    /** 获取字体大小
     * @js getFontSize
     */
    int getFontSizeObj() const;
    CC_DEPRECATED_ATTRIBUTE int fontSizeObj() const { return getFontSizeObj(); };
    
    /** 设置字体名称
     * c++ 不能重载具有相同参数类型的static和non-static成员方法
     * 所以名称修改为 setFontNameObj
     * @js setFontName
     */
    void setFontNameObj(const std::string& name);

    /** 返回字体的名称
     * @js getFontNameObj
     */
    const std::string& getFontNameObj() const;

    /** 已弃用,使用 getFontNameObj() 替代 */
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
    
    /** 使用一个string和一个target/selector初始化一个菜单项 */
    CC_DEPRECATED_ATTRIBUTE bool initWithString(const std::string& value, Ref* target, SEL_MenuHandler selector);
    
    /** 使用一个string和一个target/selector初始化一个菜单项 */
    bool initWithString(const std::string& value, const ccMenuCallback& callback);
    
protected:
    int _fontSize;
    std::string _fontName;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemFont);
};


/** @brief MenuItemSprite 接受像Node<RGBAProtocol> 对象的items.
 图像有3种不同的状态:
 - unselected image
 - selected image
 - disabled image
 
 @since v0.8.0
 */
class CC_DLL MenuItemSprite : public MenuItem
{
public:
    /** 创建一个带normal, selected 和 disabled状态图像的菜单项 */
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite = nullptr);
    /** 创建一个带normal和selected状态图像和target/selector的菜单项 */
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Ref* target, SEL_MenuHandler selector);
    /** 创建一个带normal、selected和disabled状态图像和target/selector的菜单项 */
    CC_DEPRECATED_ATTRIBUTE static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector);
    /** 创建一个带normal、selected 状态图像和回调对象的菜单项 */
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, const ccMenuCallback& callback);
    /** 创建一个带normal、selected和disabled状态图像和回调对象的菜单项 */
    static MenuItemSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);

    /** 获取该项没有选中时的图像 */
    inline Node* getNormalImage() const { return _normalImage; };
    
    /** 设置该项没有选中时的图像 */
    void setNormalImage(Node* image);
    
    /** 获取该项被选中时的图像 */
    inline Node* getSelectedImage() const { return _selectedImage; };
    
    /** 设置该项被选中时的图像 */
    void setSelectedImage(Node* image);
    
    /** 获取该项被禁用时的图像 */
    inline Node* getDisabledImage() const { return _disabledImage; };
    
    /** 设置该项被禁用时的图像 */
    void setDisabledImage(Node* image);
    
    /**
     @since v0.99.5
     */
    virtual void selected();
    virtual void unselected();
    virtual void setEnabled(bool bEnabled);
    
CC_CONSTRUCTOR_ACCESS:
    MenuItemSprite()
    :_normalImage(nullptr)
    ,_selectedImage(nullptr)
    ,_disabledImage(nullptr)
    {}
    
    /** 初始化一个带normal、selected 和 disabled状态图像和target/selector的菜单项 */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Ref* target, SEL_MenuHandler selector);
    
    /** 初始化一个带normal、selected 和 disabled状态图像和target/selector的菜单项 */
    bool initWithNormalSprite(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, const ccMenuCallback& callback);
    
protected:
    virtual void updateImagesVisibility();

    /** 该项没有选中时所使用的图像 */
    Node* _normalImage;
    /** 该项被选中时所使用的图像 */
    Node* _selectedImage;
    /** 该项被禁用时所使用的图像 */
    Node* _disabledImage;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemSprite);
};


/** @brief MenuItemImage接受图像作为 items.
 图像有3种不同的状态:
 - unselected image
 - selected image
 - disabled image
 
 为了获得最佳效果，尝试所有的图片都是相同的大小
 */
class CC_DLL MenuItemImage : public MenuItemSprite
{
public:
    /** 创建一个MenuItemImage. */
    static MenuItemImage* create();
    /** 使用normal 和 selected 状态图创建一个菜单项 */
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage);
    /** 使用normal,selected和 disabled状态图像创建一个菜单项 */
    static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage);
    /** 使用normal、selected状态图像和target/selector创建一个菜单项 */
    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, Ref* target, SEL_MenuHandler selector);
    /** 使用normal、selected状态图像和回调对象创建一个菜单项 */
    static MenuItemImage* create(const std::string&normalImage, const std::string&selectedImage, const ccMenuCallback& callback);

    /** 使用normal、selected、disabled状态图像和target/selector创建一个菜单项 */
    CC_DEPRECATED_ATTRIBUTE static MenuItemImage* create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    /** 使用normal、selected、disabled状态图像和回调对象创建一个菜单项 */
    static MenuItemImage* create(const std::string&normalImage, const std::string&selectedImage, const std::string&disabledImage, const ccMenuCallback& callback);

    /** 设置精灵正常时候的图片 */
    void setNormalSpriteFrame(SpriteFrame* frame);
    /** 设置精灵选中时候的图片 */
    void setSelectedSpriteFrame(SpriteFrame* frame);
    /** 设置精灵禁用时候的图片 */
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
    
    /** 使用normal、selected、disabled状态图像和target/selector初始化一个菜单项 */
    CC_DEPRECATED_ATTRIBUTE bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, Ref* target, SEL_MenuHandler selector);
    
    /** 使用normal、selected、disabled状态图像和回调对象初始化一个菜单项 */
    bool initWithNormalImage(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback);

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemImage);
};


/** @brief A MenuItemToggle
 一个简单的容器类切换"toggles"它的内部是菜单项,
 内部的 Items 可以是任何类型的 MenuItem
 */
class CC_DLL MenuItemToggle : public MenuItem
{
public:
    /** 使用一个 菜单项Vector集合和target、selector创建一个菜单项
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle * createWithTarget(Ref* target, SEL_MenuHandler selector, const Vector<MenuItem*>& menuItems);
    /** 使用一个 菜单项列表和target、selector创建一个菜单项
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static MenuItemToggle* createWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, ...)CC_REQUIRES_NULL_TERMINATION;
    
    /** 使用一个 菜单项Vector集合和回调对象创建一个菜单项 */
    static MenuItemToggle * createWithCallback(const ccMenuCallback& callback, const Vector<MenuItem*>& menuItems);
    /** 使用一个 菜单项列表和回调对象创建一个菜单项 */
    static MenuItemToggle* createWithCallback(const ccMenuCallback& callback, MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
    /** 创建一个没有target/selector和items的菜单项 */
    static MenuItemToggle* create();
    /** 使用指定菜单项创建一个菜单项 */
    static MenuItemToggle* create(MenuItem *item);
    /** 添加多个菜单项 */
    void addSubItem(MenuItem *item);
    
    /** return 返回选中的菜单项 */
    MenuItem* getSelectedItem();
    /** @deprecated 已弃用，使用 getSelectedItem() 替代 */
    CC_DEPRECATED_ATTRIBUTE MenuItem* selectedItem() { return getSelectedItem(); }

    /** Gets 选中项的index */
    inline unsigned int getSelectedIndex() const { return _selectedIndex; };
    
    /** Sets 设置选中项的index */
    void setSelectedIndex(unsigned int index);
    
    /** Gets 容器中的子菜单项集合.
     你可以在运行时 add/remove 菜单项, 你也可以用新的菜单项集合替换该菜单项集合.
     @since v0.7.2
     * @js NA
     * @lua NA
     */
    inline const Vector<MenuItem*>& getSubItems() const { return _subItems; };
    inline Vector<MenuItem*>& getSubItems() { return _subItems; };

    /** Sets the array that contains the subitems. */
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
    
    /** 使用菜单项列表和target、selector初始化一个菜单项
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE bool initWithTarget(Ref* target, SEL_MenuHandler selector, MenuItem* item, va_list args);
    
    /** 使用菜单项列表和回调对象初始化一个菜单项 */
    bool initWithCallback(const ccMenuCallback& callback, MenuItem* item, va_list args);
    
    /** 使用指定的菜单项初始化一个菜单项 */
    bool initWithItem(MenuItem *item);

protected:
    /** returns 选中项的index */
    unsigned int _selectedIndex;
    /** 容器中的子菜单项集合.你可以在运行时 add/remove 菜单项, 你也可以用新的菜单项集合替换该菜单项集合.
     @since v0.7.2
     */
    Vector<MenuItem*> _subItems;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MenuItemToggle);

};


// end of GUI group
/// @}
/// @}

NS_CC_END

#endif //__CCMENU_ITEM_H__
