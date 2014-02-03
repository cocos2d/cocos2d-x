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

#include "CCMenuItem.h"
#include "CCLayer.h"
#include "CCVector.h"
#include "CCEventTouch.h"
#include "CCValue.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */



/** @brief A Menu
* 
* Features and Limitation:
*  - You can add MenuItem objects in runtime using addChild:
*  - But the only accepted children are MenuItem objects
*/
class CC_DLL Menu : public Layer
{
public:
    enum class State
    {
        WAITING,
        TRACKING_TOUCH,
    };
    
    /** creates an empty Menu */
    static Menu* create();

    /** creates a Menu with MenuItem objects */
    static Menu* create(MenuItem* item, ...) CC_REQUIRES_NULL_TERMINATION;

    /** creates a Menu with a Array of MenuItem objects */
    static Menu* createWithArray(const Vector<MenuItem*>& arrayOfItems);

    /** creates a Menu with it's item, then use addChild() to add 
      * other items. It is used for script, it can't init with undetermined
      * number of variables.
    */
    static Menu* createWithItem(MenuItem* item);
    
    /** creates a Menu with MenuItem objects */
    static Menu* createWithItems(MenuItem *firstItem, va_list args);

    /** align items vertically */
    void alignItemsVertically();
    /** align items vertically with padding
    @since v0.7.2
    */
    void alignItemsVerticallyWithPadding(float padding);

    /** align items horizontally */
    void alignItemsHorizontally();
    /** align items horizontally with padding
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

    /** align items in rows of columns */
    void alignItemsInColumns(int columns, ...) CC_REQUIRES_NULL_TERMINATION;
    void alignItemsInColumns(int columns, va_list args);
    void alignItemsInColumnsWithArray(const ValueVector& rows);

    /** align items in columns of rows */
    void alignItemsInRows(int rows, ...) CC_REQUIRES_NULL_TERMINATION;
    void alignItemsInRows(int rows, va_list args);
    void alignItemsInRowsWithArray(const ValueVector& columns);

    virtual bool isEnabled() const { return _enabled; }
    virtual void setEnabled(bool value) { _enabled = value; };

    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchCancelled(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    // overrides
    virtual void removeChild(Node* child, bool cleanup) override;
    
    virtual void addChild(Node * child) override;
    virtual void addChild(Node * child, int zOrder) override;
    virtual void addChild(Node * child, int zOrder, int tag) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void setOpacityModifyRGB(bool bValue) override {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) const override { return false;}

    virtual std::string getDescription() const override;

protected:
    /**
     * @js ctor
     */
    Menu() : _selectedItem(nullptr) {}
    virtual ~Menu();

    /** initializes an empty Menu */
    bool init();

    /** initializes a Menu with a NSArray of MenuItem objects */
    bool initWithArray(const Vector<MenuItem*>& arrayOfItems);

    /** whether or not the menu will receive events */
    bool _enabled;

    MenuItem* getItemForTouch(Touch * touch);
    State _state;
    MenuItem *_selectedItem;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Menu);
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif//__CCMENU_H_
