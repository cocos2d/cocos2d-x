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

/**
 * @brief Base class for Grid Node.
 */

class CC_DLL NodeGrid : public Node
{
public:
    /** Create a Grid Node.
     *
     * @return An autorelease Grid Node.
     */
    static NodeGrid* create();
    
    static NodeGrid* create(const Rect& rect);
    
    /** Get a Grid Node. 
     *
     * @return Return a GridBase.
     */
    GridBase* getGrid() { return _nodeGrid; }
    /**
     * @js NA
     */
    const GridBase* getGrid() const { return _nodeGrid; }

    /**
     * Changes a grid object that is used when applying effects.
     *
     * @param grid  A Grid object that is used when applying effects.
     */
    void setGrid(GridBase *grid);
    
    /** Set the Grid Target. 
     *
     * @param target A Node is used to set the Grid Target.
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

    // overrides
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
