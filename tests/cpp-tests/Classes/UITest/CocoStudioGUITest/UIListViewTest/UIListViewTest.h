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

#ifndef __TestCpp__UIListViewTest__
#define __TestCpp__UIListViewTest__

#include "../UIScene.h"
#include "ui/UIScrollView.h"

DEFINE_TEST_SUITE(UIListViewTests);

class UIListViewTest_Vertical : public UIScene
{
public:
    CREATE_FUNC(UIListViewTest_Vertical);

    UIListViewTest_Vertical();
    ~UIListViewTest_Vertical();

    virtual bool init() override;
    void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(cocos2d::Ref* sender, cocos2d::ui::ScrollView::EventType type);
    virtual void update(float dt) override;
    
protected:
    float getItemPositionYInView(cocos2d::ui::Widget* item) const;
    void updateItem(int itemID, int templateID);
    
    cocos2d::ui::Text* _displayValueLabel;
    //how many items we actually spawn, these items will be reused.
    int _spawnCount;
    // how many items we need for the ListView. Usually this is a big number.
    int _totalCount;
    //when item is away from bufferSzone, we relocate it.
    float _bufferZone;
    float _itemTemplateHeight;
    float _updateInterval;
    float _updateTimer;
    float _lastContentPosY;
    float _reuseItemOffset;
    cocos2d::ui::ListView* _listView;
    std::vector<std::string> _array;
    cocos2d::ui::Text* _indexLabels[3];
};

class UIListViewTest_Horizontal : public UIScene
{
public:
    CREATE_FUNC(UIListViewTest_Horizontal);

    UIListViewTest_Horizontal();
    ~UIListViewTest_Horizontal();

    virtual bool init() override;
    void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
    virtual void update(float dt) override;
protected:
    float getItemPositionXInView(cocos2d::ui::Widget* item) const;
    void updateItem(int itemID, int templateID);
    
    cocos2d::ui::Text* _displayValueLabel;
    //how many items we actually spawn, these items will be reused.
    int _spawnCount;
    // how many items we need for the ListView. Usually this is a big number.
    int _totalCount;
    //when item is away from bufferSzone, we relocate it.
    float _bufferZone;
    float _itemTemplateWidth;
    float _updateInterval;
    float _updateTimer;
    float _lastContentPosX;
    float _reuseItemOffset;
    cocos2d::ui::ListView* _listView;
    
    std::vector<std::string> _array;
};

class Issue12692 : public UIScene
{
public:
    CREATE_FUNC(Issue12692);
    
    virtual bool init() override;
};

class Issue8316 : public UIScene
{
public:
    CREATE_FUNC(Issue8316);
    
    virtual bool init() override;
};


// Test for scroll to item
class UIListViewTest_ScrollToItem : public UIScene
{
protected:
    virtual bool init() override;
    virtual cocos2d::ui::ScrollView::Direction getListViewDirection() const = 0;
    
    cocos2d::ui::ListView* _listView;
    cocos2d::ui::Text* _titleLabel;
    int _nextIndex;
};

class UIListViewTest_ScrollToItemVertical : public UIListViewTest_ScrollToItem
{
public:
    CREATE_FUNC(UIListViewTest_ScrollToItemVertical);
    virtual cocos2d::ui::ScrollView::Direction getListViewDirection() const
    {
        return cocos2d::ui::ScrollView::Direction::VERTICAL;
    }
};

class UIListViewTest_ScrollToItemHorizontal : public UIListViewTest_ScrollToItem
{
public:
    CREATE_FUNC(UIListViewTest_ScrollToItemHorizontal);
    virtual cocos2d::ui::ScrollView::Direction getListViewDirection() const
    {
        return cocos2d::ui::ScrollView::Direction::HORIZONTAL;
    }
};


// Test for magnetic scroll
class UIListViewTest_Magnetic : public UIScene
{
protected:
    virtual bool init() override;
    virtual cocos2d::ui::ScrollView::Direction getListViewDirection() const = 0;
    
    cocos2d::ui::ListView* _listView;
    cocos2d::ui::Text* _titleLabel;
    cocos2d::ui::Text* _indexLabels[5];
    
};

class UIListViewTest_MagneticVertical : public UIListViewTest_Magnetic
{
public:
    CREATE_FUNC(UIListViewTest_MagneticVertical);
    virtual cocos2d::ui::ScrollView::Direction getListViewDirection() const
    {
        return cocos2d::ui::ScrollView::Direction::VERTICAL;
    }
};

class UIListViewTest_MagneticHorizontal : public UIListViewTest_Magnetic
{
public:
    CREATE_FUNC(UIListViewTest_MagneticHorizontal);
    virtual cocos2d::ui::ScrollView::Direction getListViewDirection() const
    {
        return cocos2d::ui::ScrollView::Direction::HORIZONTAL;
    }
};

#endif /* defined(__TestCpp__UIListViewTest__) */
