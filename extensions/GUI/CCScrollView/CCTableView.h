/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2010 Sangwoo Im

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

#ifndef __CCTABLEVIEW_H__
#define __CCTABLEVIEW_H__

#include "CCScrollView.h"
#include "CCTableViewCell.h"

#include <set>
#include <vector>

NS_CC_EXT_BEGIN

class TableView;

/**
 * 本版本中此委托只处理单点触摸事件
 */
class TableViewDelegate : public ScrollViewDelegate
{
public:
    /**
     * 单元格被点击时响应此委托
     *
     * @param table 包含所给单元格的TableView
     * @param cell  被点击的单元格
     * @js NA
     * @lua NA
     */
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) = 0;

    /**
     * 单元格被按下时响应此委托
     *
     * @param table 包含所给单元格的TableView
     * @param cell  被按下的单元格
     * @js NA
     * @lua NA
     */
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell){};

    /**
     * 单元格被释放时响应此委托（译者注：可能为按下后松手，或者按下后拖动超过阈值）
     *
     * @param table 包含所给单元格的TableView
     * @param cell  被释放的单元格
     * @js NA
     * @lua NA
     */
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell){};

    /**
     * 单元格即将被回收时响应此委托
     * 本委托调用结束后，此单元格会立即从场景移除回收等待重用。
     *
     * @param table 包含所给单元格的TableView
     * @param cell  被回收的单元格
     * @js NA
     * @lua NA
     */
    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell){};

};


/**
 * 用于管理表格后端数据的数据源
 */
class TableViewDataSource
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TableViewDataSource() {}

    /**
     * 获取指定索引对应单元格的尺寸
     *
     * @param idx 需要查询尺寸的单元格索引
     * @return 对应单元格的尺寸
     */
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx) {
        return cellSizeForTable(table);
    };
    /**
     * 获取指定表格的单元格尺寸
     *
     * @param table 存放本数据源数据的TableView
     * @return 单元格尺寸
     */
    virtual Size cellSizeForTable(TableView *table) {
        return Size::ZERO;
    };
    /**
     * 获取指定索引对应的单元格实例
     *
     * @param idx 需要获取的单元格的索引
     * @return 指定索引对应的单元格
     */
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) = 0;
    /**
     * 返回指定TableView中单元格的个数
     *
     * @return 单元格个数
     */
    virtual ssize_t numberOfCellsInTableView(TableView *table) = 0;

};


/**
 * Cocos2d-x中的TableView支持
 *
 * 这是一个类UITableView元件的最小实现，为Cocos2d-x带来表格的基本支持
 */
class TableView : public ScrollView, public ScrollViewDelegate
{
public:
    
    enum class VerticalFillOrder
    {
        TOP_DOWN,
        BOTTOM_UP
    };
    
    /** TableView的空构造函数 */
    static TableView* create();
    
    /**
     * 创建一个被初始化的TableView
     *
     * @param dataSource 数据源
     * @param size 表格可见尺寸
     * @return 表格
     * @code
     * 此函数被js或lua绑定后，输入参数发生改变
     * in js:var create(var jsObject,var size)
     * in lua:local create(var size)
     * in lua:
     * @endcode
     */
    static TableView* create(TableViewDataSource* dataSource, Size size);
    /**
     * 创建一个被初始化的TableView
     *
     * @param dataSource 数据源
     * @param size 表格可见尺寸
     * @param container 单元格的父对象容器
     * @return 表格
     * @code
     * 此函数被js或lua绑定后，输入参数发生改变
     * in js:var create(var jsObject,var size,var container)
     * in lua:local create(var size, var container)
     * in lua:
     * @endcode
     */
    static TableView* create(TableViewDataSource* dataSource, Size size, Node *container);
    /**
     * @js ctor
     */
    TableView();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TableView();

    bool initWithViewSize(Size size, Node* container = NULL);

    /**
     * data source
     * @js NA
     * @lua NA
     */
    TableViewDataSource* getDataSource() { return _dataSource; }
    /**
     * 此函数被js或lua绑定后，输入参数发生改变
     * in js:var setDataSource(var jsSource)
     * in lua:local setDataSource()
     * @endcode
     */
    void setDataSource(TableViewDataSource* source) { _dataSource = source; }
    /**
     * delegate
     * @js NA
     * @lua NA
     */
    TableViewDelegate* getDelegate() { return _tableViewDelegate; }
    /**
     * @code
     * 此函数被js或lua绑定后，输入参数发生改变
     * in js:var setDelegate(var jsDelegate)
     * in lua:local setDelegate()
     * @endcode
     */
    void setDelegate(TableViewDelegate* pDelegate) { _tableViewDelegate = pDelegate; }

    /**
     * 设置单元格在表格中的填充顺序
     */
    void setVerticalFillOrder(VerticalFillOrder order);
    VerticalFillOrder getVerticalFillOrder();

    /**
     * 更新索引对应单元格的内容
     *
     * @param idx 用于指定单元格的索引
     */
    void updateCellAtIndex(ssize_t idx);
    /**
     * 在指定索引插入新单元格
     *
     * @param idx 用于指定插入位置的索引
     */
    void insertCellAtIndex(ssize_t idx);
    /**
     * 移除指定索引的单元格
     *
     * @param idx 用于指定单元格的索引
     */
    void removeCellAtIndex(ssize_t idx);
    /**
     * 从数据源重新载入数据，整个表格会被刷新
     */
    void reloadData();
    /**
     * 从回收队列获取一个可用的空闲单元格，如果没有可用单元格则返回空指针
     *
     * @return 空闲单元格
     */
    TableViewCell *dequeueCell();

    /**
     * 获取索引对应的单元格。如果当前索引对应单元格不存在则返回空指针。
     *
     * @param idx 索引
     * @return 对应单元格
     */
    TableViewCell *cellAtIndex(ssize_t idx);

    // Overrides
    virtual void scrollViewDidScroll(ScrollView* view) override;
    virtual void scrollViewDidZoom(ScrollView* view)  override {}
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent) override;

protected:
    long __indexFromOffset(Vec2 offset);
    long _indexFromOffset(Vec2 offset);
    Vec2 __offsetFromIndex(ssize_t index);
    Vec2 _offsetFromIndex(ssize_t index);

    void _moveCellOutOfSight(TableViewCell *cell);
    void _setIndexForCell(ssize_t index, TableViewCell *cell);
    void _addCellIfNecessary(TableViewCell * cell);

    void _updateCellPositions();


    TableViewCell *_touchedCell;
    /**
     * 单元格垂直方向的填充顺序
     */
    VerticalFillOrder _vordering;

    /**
     * 用于查询已用单元格的索引集合
     */
    std::set<ssize_t>* _indices;

    /**
     * 用于存放所有单元格位置的数组容器
     */
    std::vector<float> _vCellsPositions;
    //NSMutableIndexSet *indices_;
    /**
     * 当前正在使用的单元格
     */
    Vector<TableViewCell*> _cellsUsed;
    /**
     * 空闲单元格
     */
    Vector<TableViewCell*> _cellsFreed;
    /**
     * 数据源对象的弱引用
     */
    TableViewDataSource* _dataSource;
    /**
     * 委托对象的弱引用
     */
    TableViewDelegate* _tableViewDelegate;

    Direction _oldDirection;

    bool _isUsedCellsDirty;

public:
    void _updateContentSize();

};


NS_CC_EXT_END

#endif /* __CCTABLEVIEW_H__ */
