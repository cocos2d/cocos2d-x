/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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



/** @brief A Menu for touch handling.
* 
* Features and Limitation:
*  - You can add MenuItem objects in runtime using addChild.
*  - But the only accepted children are MenuItem objects.
*/
class CC_DLL Menu : public Layer
{
public:
    /**
     * Menu state, it's used internally.
     */
    enum class State
    {
        WAITING,
        TRACKING_TOUCH,
    };
    
    /**
     *@brief Creates an empty Menu.
     */
    static Menu* create();
    
    /** Creates a Menu with MenuItem objects. */
    static Menu* create(MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;

    /** 
     * Creates a Menu with a Array of MenuItem objects.
     * @js NA
     */
    static Menu* createWithArray(const Vector<MenuItem*>& arrayOfItems);

    /**
     * Creates a Menu with it's item, then use addChild() to add 
     * other items. It is used for script, it can't be initialized with undetermined
     * number of variables.
     * @js NA
     */
    static Menu* createWithItem(MenuItem* item);
    
    /** Creates a Menu with MenuItem objects.
     * @js NA
     */
    static Menu* createWithItems(MenuItem *firstItem, va_list args);

    /** Align items vertically. */
    void alignItemsVertically();

    /** Align items vertically with padding.
    @since v0.7.2
    */
    void alignItemsVerticallyWithPadding(float padding);

    /** Align items horizontally. */
    void alignItemsHorizontally();
    
    /** Align items horizontally with padding.
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

    /** Align items in rows of columns. */
    void alignItemsInColumns(int columns, ...) CC_REQUIRES_NULL_TERMINATION;
    
    /** Align items in rows of columns. */
    void alignItemsInColumns(int columns, va_list args);
    
    /** Align items in array of columns.
     * @js NA
     */
    void alignItemsInColumnsWithArray(const ValueVector& rows);

    /** Align items in columns of rows. */
    void alignItemsInRows(int rows, ...) CC_REQUIRES_NULL_TERMINATION;
    
    /** Align items in columns of rows. */
    void alignItemsInRows(int rows, va_list args);
    
    /** Align items in array of rows.
     * @js NA
     */
    void alignItemsInRowsWithArray(const ValueVector& columns);

    /**
     * Determines if the menu is enabled.
     * @see `setEnabled(bool)`.
     * @return whether the menu is enabled or not.
     */
    virtual bool isEnabled() const { return _enabled; }

    /**
     * Set whether the menu is enabled. If set to false, interacting with the menu
     * will have no effect.
     * The default value is true, a menu is enabled by default.
     * @param value true if menu is to be enabled, false if menu is to be disabled.
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
    virtual void setOpacityModifyRGB(bool value) override;
    virtual bool isOpacityModifyRGB() const override;

    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    Menu() : _selectedItem(nullptr), _selectedWithCamera(nullptr) {}
    virtual ~Menu();

    /** initializes an empty Menu */
    bool init() override;

    /** initializes a Menu with a NSArray of MenuItem objects */
    bool initWithArray(const Vector<MenuItem*>& arrayOfItems);

protected:



    /** whether or not the menu will receive events */
    bool _enabled;

    virtual MenuItem* getItemForTouch(Touch * touch, const Camera *camera);
    State _state;
    MenuItem *_selectedItem;
    const Camera *_selectedWithCamera;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Menu);
};

// end of _2d group
/// @}

NS_CC_END

#endif//__CCMENU_H_
