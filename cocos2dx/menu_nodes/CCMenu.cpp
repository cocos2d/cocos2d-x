/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#include "CCMenu.h"
#include "CCDirector.h"
#include "CCApplication.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCStdC.h"
#include "cocoa/CCInteger.h"

#include <vector>
#include <stdarg.h>

using namespace std;

NS_CC_BEGIN

static std::vector<unsigned int> ccarray_to_std_vector(Array* pArray)
{
    std::vector<unsigned int> ret;
    Object* pObj;
    CCARRAY_FOREACH(pArray, pObj)
    {
        Integer* pInteger = static_cast<Integer*>(pObj);
        ret.push_back((unsigned int)pInteger->getValue());
    }
    return ret;
}

enum 
{
    kDefaultPadding =  5,
};

//
//CCMenu
//

Menu* Menu::create()
{
    return Menu::create(NULL, NULL);
}

Menu * Menu::create(MenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    Menu *pRet = Menu::createWithItems(item, args);
    
    va_end(args);
    
    return pRet;
}

Menu* Menu::createWithArray(Array* pArrayOfItems)
{
    Menu *pRet = new Menu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

Menu* Menu::createWithItems(MenuItem* item, va_list args)
{
    Array* pArray = NULL;
    if( item )
    {
        pArray = Array::create(item, NULL);
        MenuItem *i = va_arg(args, MenuItem*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, MenuItem*);
        }
    }
    
    return Menu::createWithArray(pArray);
}

Menu* Menu::createWithItem(MenuItem* item)
{
    return Menu::create(item, NULL);
}

bool Menu::init()
{
    return initWithArray(NULL);
}

bool Menu::initWithArray(Array* pArrayOfItems)
{
    if (Layer::init())
    {
        setTouchPriority(Menu::HANDLER_PRIORITY);
        setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        setTouchEnabled(true);

        _enabled = true;
        // menu in the center of the screen
        Size s = Director::getInstance()->getWinSize();

        this->ignoreAnchorPointForPosition(true);
        setAnchorPoint(Point(0.5f, 0.5f));
        this->setContentSize(s);

        setPosition(Point(s.width/2, s.height/2));
        
        if (pArrayOfItems != NULL)
        {
            int z=0;
            Object* pObj = NULL;
            CCARRAY_FOREACH(pArrayOfItems, pObj)
            {
                MenuItem* item = static_cast<MenuItem*>(pObj);
                this->addChild(item, z);
                z++;
            }
        }
    
        //    [self alignItemsVertically];
        _selectedItem = NULL;
        _state = Menu::State::WAITING;
        
        // enable cascade color and opacity on menus
        setCascadeColorEnabled(true);
        setCascadeOpacityEnabled(true);
        
        return true;
    }
    return false;
}

/*
* override add:
*/
void Menu::addChild(Node * child)
{
    Layer::addChild(child);
}

void Menu::addChild(Node * child, int zOrder)
{
    Layer::addChild(child, zOrder);
}

void Menu::addChild(Node * child, int zOrder, int tag)
{
    CCASSERT( dynamic_cast<MenuItem*>(child) != NULL, "Menu only supports MenuItem objects as children");
    Layer::addChild(child, zOrder, tag);
}

void Menu::onExit()
{
    if (_state == Menu::State::TRACKING_TOUCH)
    {
        if (_selectedItem)
        {
            _selectedItem->unselected();
            _selectedItem = NULL;
        }
        
        _state = Menu::State::WAITING;
    }

    Layer::onExit();
}

void Menu::removeChild(Node* child, bool cleanup)
{
    MenuItem *pMenuItem = dynamic_cast<MenuItem*>(child);
    CCASSERT(pMenuItem != NULL, "Menu only supports MenuItem objects as children");
    
    if (_selectedItem == pMenuItem)
    {
        _selectedItem = NULL;
    }
    
    Node::removeChild(child, cleanup);
}

//Menu - Events

void Menu::setHandlerPriority(int newPriority)
{
    TouchDispatcher* pDispatcher = Director::getInstance()->getTouchDispatcher();
    pDispatcher->setPriority(newPriority, this);
}

void Menu::registerWithTouchDispatcher()
{
    Director* pDirector = Director::getInstance();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), true);
}

bool Menu::ccTouchBegan(Touch* touch, Event* event)
{
    CC_UNUSED_PARAM(event);
    if (_state != Menu::State::WAITING || ! _visible || !_enabled)
    {
        return false;
    }

    for (Node *c = this->_parent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }

    _selectedItem = this->itemForTouch(touch);
    if (_selectedItem)
    {
        _state = Menu::State::TRACKING_TOUCH;
        _selectedItem->selected();
        return true;
    }
    return false;
}

void Menu::ccTouchEnded(Touch *touch, Event* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    CCASSERT(_state == Menu::State::TRACKING_TOUCH, "[Menu ccTouchEnded] -- invalid state");
    if (_selectedItem)
    {
        _selectedItem->unselected();
        _selectedItem->activate();
    }
    _state = Menu::State::WAITING;
}

void Menu::ccTouchCancelled(Touch *touch, Event* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    CCASSERT(_state == Menu::State::TRACKING_TOUCH, "[Menu ccTouchCancelled] -- invalid state");
    if (_selectedItem)
    {
        _selectedItem->unselected();
    }
    _state = Menu::State::WAITING;
}

void Menu::ccTouchMoved(Touch* touch, Event* event)
{
    CC_UNUSED_PARAM(event);
    CCASSERT(_state == Menu::State::TRACKING_TOUCH, "[Menu ccTouchMoved] -- invalid state");
    MenuItem *currentItem = this->itemForTouch(touch);
    if (currentItem != _selectedItem) 
    {
        if (_selectedItem)
        {
            _selectedItem->unselected();
        }
        _selectedItem = currentItem;
        if (_selectedItem)
        {
            _selectedItem->selected();
        }
    }
}

//Menu - Alignment
void Menu::alignItemsVertically()
{
    this->alignItemsVerticallyWithPadding(kDefaultPadding);
}

void Menu::alignItemsVerticallyWithPadding(float padding)
{
    float height = -padding;
    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Node* child = dynamic_cast<Node*>(pObject);
            if (child)
            {
                height += child->getContentSize().height * child->getScaleY() + padding;
            }
        }
    }

    float y = height / 2.0f;
    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Node* child = dynamic_cast<Node*>(pObject);
            if (child)
            {
                child->setPosition(Point(0, y - child->getContentSize().height * child->getScaleY() / 2.0f));
                y -= child->getContentSize().height * child->getScaleY() + padding;
            }
        }
    }
}

void Menu::alignItemsHorizontally(void)
{
    this->alignItemsHorizontallyWithPadding(kDefaultPadding);
}

void Menu::alignItemsHorizontallyWithPadding(float padding)
{

    float width = -padding;
    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Node* child = dynamic_cast<Node*>(pObject);
            if (child)
            {
                width += child->getContentSize().width * child->getScaleX() + padding;
            }
        }
    }

    float x = -width / 2.0f;
    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Node* child = dynamic_cast<Node*>(pObject);
            if (child)
            {
                child->setPosition(Point(x + child->getContentSize().width * child->getScaleX() / 2.0f, 0));
                 x += child->getContentSize().width * child->getScaleX() + padding;
            }
        }
    }
}

void Menu::alignItemsInColumns(int columns, ...)
{
    va_list args;
    va_start(args, columns);

    this->alignItemsInColumns(columns, args);

    va_end(args);
}

void Menu::alignItemsInColumns(int columns, va_list args)
{
    CCASSERT(columns >= 0, "Columns must be >= 0");
    Array* rows = Array::create();
    while (columns)
    {
        rows->addObject(Integer::create(columns));
        columns = va_arg(args, int);
    }
    alignItemsInColumnsWithArray(rows);
}

void Menu::alignItemsInColumnsWithArray(Array* rowsArray)
{
    vector<unsigned int> rows = ccarray_to_std_vector(rowsArray);

    int height = -5;
    unsigned int row = 0;
    unsigned int rowHeight = 0;
    unsigned int columnsOccupied = 0;
    unsigned int rowColumns;

    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Node* child = dynamic_cast<Node*>(pObject);
            if (child)
            {
                CCASSERT(row < rows.size(), "");

                rowColumns = rows[row];
                // can not have zero columns on a row
                CCASSERT(rowColumns, "");

                float tmp = child->getContentSize().height;
                rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

                ++columnsOccupied;
                if (columnsOccupied >= rowColumns)
                {
                    height += rowHeight + 5;

                    columnsOccupied = 0;
                    rowHeight = 0;
                    ++row;
                }
            }
        }
    }    

    // check if too many rows/columns for available menu items
    CCASSERT(! columnsOccupied, "");

    Size winSize = Director::getInstance()->getWinSize();

    row = 0;
    rowHeight = 0;
    rowColumns = 0;
    float w = 0.0;
    float x = 0.0;
    float y = (float)(height / 2);

    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Node* child = dynamic_cast<Node*>(pObject);
            if (child)
            {
                if (rowColumns == 0)
                {
                    rowColumns = rows[row];
                    w = winSize.width / (1 + rowColumns);
                    x = w;
                }

                float tmp = child->getContentSize().height;
                rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

                child->setPosition(Point(x - winSize.width / 2,
                                       y - child->getContentSize().height / 2));

                x += w;
                ++columnsOccupied;

                if (columnsOccupied >= rowColumns)
                {
                    y -= rowHeight + 5;

                    columnsOccupied = 0;
                    rowColumns = 0;
                    rowHeight = 0;
                    ++row;
                }
            }
        }
    }    
}

void Menu::alignItemsInRows(int rows, ...)
{
    va_list args;
    va_start(args, rows);

    this->alignItemsInRows(rows, args);

    va_end(args);
}

void Menu::alignItemsInRows(int rows, va_list args)
{
    Array* pArray = Array::create();
    while (rows)
    {
        pArray->addObject(Integer::create(rows));
        rows = va_arg(args, int);
    }
    alignItemsInRowsWithArray(pArray);
}

void Menu::alignItemsInRowsWithArray(Array* columnArray)
{
    vector<unsigned int> columns = ccarray_to_std_vector(columnArray);

    vector<unsigned int> columnWidths;
    vector<unsigned int> columnHeights;

    int width = -10;
    int columnHeight = -5;
    unsigned int column = 0;
    unsigned int columnWidth = 0;
    unsigned int rowsOccupied = 0;
    unsigned int columnRows;

    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Node* child = dynamic_cast<Node*>(pObject);
            if (child)
            {
                // check if too many menu items for the amount of rows/columns
                CCASSERT(column < columns.size(), "");

                columnRows = columns[column];
                // can't have zero rows on a column
                CCASSERT(columnRows, "");

                // columnWidth = fmaxf(columnWidth, [item contentSize].width);
                float tmp = child->getContentSize().width;
                columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

                columnHeight += (int)(child->getContentSize().height + 5);
                ++rowsOccupied;

                if (rowsOccupied >= columnRows)
                {
                    columnWidths.push_back(columnWidth);
                    columnHeights.push_back(columnHeight);
                    width += columnWidth + 10;

                    rowsOccupied = 0;
                    columnWidth = 0;
                    columnHeight = -5;
                    ++column;
                }
            }
        }
    }

    // check if too many rows/columns for available menu items.
    CCASSERT(! rowsOccupied, "");

    Size winSize = Director::getInstance()->getWinSize();

    column = 0;
    columnWidth = 0;
    columnRows = 0;
    float x = (float)(-width / 2);
    float y = 0.0;

    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            Node* child = dynamic_cast<Node*>(pObject);
            if (child)
            {
                if (columnRows == 0)
                {
                    columnRows = columns[column];
                    y = (float) columnHeights[column];
                }

                // columnWidth = fmaxf(columnWidth, [item contentSize].width);
                float tmp = child->getContentSize().width;
                columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

                child->setPosition(Point(x + columnWidths[column] / 2,
                                       y - winSize.height / 2));

                y -= child->getContentSize().height + 10;
                ++rowsOccupied;

                if (rowsOccupied >= columnRows)
                {
                    x += columnWidth + 5;
                    rowsOccupied = 0;
                    columnRows = 0;
                    columnWidth = 0;
                    ++column;
                }
            }
        }
    }
}

MenuItem* Menu::itemForTouch(Touch *touch)
{
    Point touchLocation = touch->getLocation();

    if (_children && _children->count() > 0)
    {
        Object* pObject = NULL;
        CCARRAY_FOREACH(_children, pObject)
        {
            MenuItem* child = dynamic_cast<MenuItem*>(pObject);
            if (child && child->isVisible() && child->isEnabled())
            {
                Point local = child->convertToNodeSpace(touchLocation);
                Rect r = child->rect();
                r.origin = Point::ZERO;

                if (r.containsPoint(local))
                {
                    return child;
                }
            }
        }
    }

    return NULL;
}

NS_CC_END
