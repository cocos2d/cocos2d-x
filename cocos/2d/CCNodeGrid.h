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

#ifndef __MISCNODE_CCGRID_NODE_H__
#define __MISCNODE_CCGRID_NODE_H__

#include "2d/CCNode.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class GridBase;
/**
 *  @addtogroup _2d
 *  @{
 */

/** @class NodeGrid
 * @brief @~english Base class for Grid Node,the grid action's management class.
 * @~chinese 网格节点,网格动作的管理节点。网格节点的网格动作作用于所有子孙节点。
 */

class CC_DLL NodeGrid : public Node
{
public:
    /** @~english Create a grid node.
     *
     * @~chinese 创建一个网格节点。
     * 
     * @return @~english An autorelease Grid Node.
     * @~chinese 一个autorelease网格节点。
     */
    static NodeGrid* create();

    /** @~english Create a grid node with rect.
     *
     * @~chinese 用网格矩形创建一个网格节点。
     * 
     * @return @~english An autorelease Grid Node.
     * @~chinese 一个autorelease网格节点。
     */
    static NodeGrid* create(const Rect& rect);
    
    /** @~english Gets the grid action of NodeGrid.
     *
     * @~chinese 获取网格节点的网格动作。
     * 
     * @return @~english Return a GridBase.
     * @~chinese 返回网格动作GridBase。
     */
    GridBase* getGrid() { return _nodeGrid; }

    /**
     * @js NA
     */
    const GridBase* getGrid() const { return _nodeGrid; }

    /**@~english
     * Changes a grid object that is used when applying effects.
     *
     * @~chinese 
     * 设置网格节点的网格动作。
     * 
     * @param grid  @~english A Grid object that is used when applying effects.
     * @~chinese 一个网格动作对象。
     */
    void setGrid(GridBase *grid);
    
    /** @~english Set the Grid Target. 
     *
     * @~chinese 设置受网格动作作用的一个额外节点。
     * 
     * @param target @~english A Node is used to set the Grid Target.
     * @~chinese 目标节点。
     */
    void setTarget(Node *target);
    
    /**
     * @brief Set the effect grid rect.
     * @param gridRect The effect grid rect.
     */
    inline void setGridRect(const Rect& gridRect){_gridRect = gridRect;}
    /**
     * @brief Get the effect grid rect.
     * @return Return the effect grid rect.
     */
    inline const Rect& getGridRect() const { return _gridRect;}

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

CC_CONSTRUCTOR_ACCESS:
    NodeGrid();
    virtual ~NodeGrid();

protected:
    void onGridBeginDraw();
    void onGridEndDraw();

    Node* _gridTarget;
    GridBase* _nodeGrid;
    GroupCommand _groupCommand;
    CustomCommand _gridBeginCommand;
    CustomCommand _gridEndCommand;
    
    Rect _gridRect;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(NodeGrid);
};
/** @} */
NS_CC_END

#endif
