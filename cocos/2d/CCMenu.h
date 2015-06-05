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
#ifndef __CCMENU_H_
#define __CCMENU_H_

#include "2d/CCMenuItem.h"
#include "2d/CCLayer.h"
#include "base/CCValue.h"

NS_CC_BEGIN
class Touch;

/**
 * @addtogroup _2d
 * @{
 */



/** @class Menu
 * @brief @~english A Menu for touch handling.
 * 
 * Features and Limitation:
 *  - You can add MenuItem objects in runtime using addChild.
 *  - But the only accepted children are MenuItem objects.
 *
 * @~chinese 处理触摸事件的菜单。
 * 
 * 特性和限制:
 * - 在运行时你可以通过addChild函数添加菜单项。
 * - 只接受菜单项（MenuItem）及其派生类对象作为孩子节点。
*/
class CC_DLL Menu : public Layer
{
public:
    /**@~english
     * Menu state, it's used internally.
     * @~chinese 
     * 菜单的状态,内部使用。
     */
    enum class State
    {
        WAITING,
        TRACKING_TOUCH,
    };
    
    /**
     *@brief @~english Creates an empty Menu.
     * @~chinese 创建一个空的菜单。
     */
    static Menu* create();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // VS2013 does not support nullptr in variable args lists and variadic templates are also not supported.
    typedef MenuItem* M;
    static Menu* create(M m1, std::nullptr_t listEnd) { return variadicCreate(m1, NULL); }
    static Menu* create(M m1, M m2, std::nullptr_t listEnd) { return variadicCreate(m1, m2, NULL); }
    static Menu* create(M m1, M m2, M m3, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, NULL); }
    static Menu* create(M m1, M m2, M m3, M m4, M m5, M m6, M m7, M m8, M m9, M m10, std::nullptr_t listEnd) { return variadicCreate(m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,  NULL); }

    // On WP8 for lists longer than 10 items, use createWithArray or variadicCreate with NULL as the last argument.
    static Menu* variadicCreate(MenuItem* item, ...);
#else
    /** @~english Creates a Menu with MenuItem objects.  
     * @~chinese 通过给定的一个或多个菜单项对象创建菜单。
     */
    static Menu* create(MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;
#endif

    /** @~english
     * Creates a Menu with a Array of MenuItem objects.
     * @~chinese 
     * 通过给定的一组菜单项对象创建菜单。
     * @js NA
     */
    static Menu* createWithArray(const Vector<MenuItem*>& arrayOfItems);

    /**@~english
     * Creates a Menu with it's item, then use addChild() to add other items.
     * @~chinese 
     * 通过给定的一个菜单项对象创建菜单，之后可通过addChild函数添加其他菜单项。
     * @js NA
     */
    static Menu* createWithItem(MenuItem* item);
    
    /** @~english Creates a Menu with MenuItem objects.
     * @~chinese 通过给定的一个或多个菜单项对象创建菜单。
     * @js NA
     */
    static Menu* createWithItems(MenuItem *firstItem, va_list args);

    /** @~english Align items vertically. 
     * @~chinese 以默认间距垂直排列菜单项。
     */
    void alignItemsVertically();

    /** @~english Align items vertically with padding.
     * @~chinese 以指定间距垂直排列菜单项。
     * @since v0.7.2
     */
    void alignItemsVerticallyWithPadding(float padding);

    /** @~english Align items horizontally.
     * @~chinese 以默认间距水平排列菜单项。
     */
    void alignItemsHorizontally();
    
    /** @~english Align items horizontally with padding.
     * @~chinese 以指定间距水平排列菜单项。
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

    /** @~english Align items in rows of columns.
     * @~chinese 将菜单项按照列分组排列，参数为每列所包含的菜单项数。
     */
    void alignItemsInColumns(int columns, ...) CC_REQUIRES_NULL_TERMINATION;
    
    /** @~english Align items in rows of columns.
     * @~chinese 将菜单项按照列分组排列，参数为每列所包含的菜单项数。
     */
    void alignItemsInColumns(int columns, va_list args);
    
    /** @~english Align items in rows of columns.
     * @~chinese 将菜单项按照列分组排列，参数为每列所包含的菜单项数。
     * @js NA
     */
    void alignItemsInColumnsWithArray(const ValueVector& rows);

    /** @~english Align items in columns of rows.
     * @~chinese 将菜单项按照行分组排列，参数为每行所包含的菜单项数。
     */
    void alignItemsInRows(int rows, ...) CC_REQUIRES_NULL_TERMINATION;
    
    /** @~english Align items in columns of rows.
     * @~chinese 将菜单项按照行分组排列，参数为每行所包含的菜单项数。
     */
    void alignItemsInRows(int rows, va_list args);
    
    /** @~english Align items in columns of rows.
     * @~chinese 将菜单项按照行分组排列，参数为每行所包含的菜单项数。
     * @js NA
     */
    void alignItemsInRowsWithArray(const ValueVector& columns);

    /**@~english
     * Determines if the menu is enable.
     * @~chinese 
     * 验证菜单是否可点击。
     * @see `setEnabled(bool)`.
     * @return @~english whether the menu is enabled or not.
     * @~chinese 是可点击返回true，否则返回false。
     */
    virtual bool isEnabled() const { return _enabled; }

    /**@~english
     * Set whether the menu is enable.
     * The default value is true, a menu is default to enable.
     * @~chinese 
     * 设置菜单是否可点击。
     * 默认为true,可点击。
     * @param value @~english true if menu is enable, false if menu is disable.
     * @~chinese true 菜单响应点击，false 菜单不响应点击。
     */
    virtual void setEnabled(bool value) { _enabled = value; };

    virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;
    virtual void onTouchCancelled(Touch* touch, Event* event) override;
    virtual void onTouchMoved(Touch* touch, Event* event) override;
    
    // overrides
    virtual void removeChild(Node* child, bool cleanup) override;
    
    virtual void addChild(Node * child) override;
    virtual void addChild(Node * child, int zOrder) override;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    virtual void addChild(Node * child, int zOrder, const std::string &name) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void setOpacityModifyRGB(bool bValue) override {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) const override { return false;}

    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    Menu() : _selectedItem(nullptr) {}
    virtual ~Menu();

    bool init() override;

    bool initWithArray(const Vector<MenuItem*>& arrayOfItems);

protected:

    bool _enabled;

    MenuItem* getItemForTouch(Touch * touch);
    State _state;
    MenuItem *_selectedItem;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Menu);
};

// end of _2d group
/// @}

NS_CC_END

#endif//__CCMENU_H_
