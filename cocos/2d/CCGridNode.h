#ifndef __MISCNODE_CCGRID_NODE_H__
#define __MISCNODE_CCGRID_NODE_H__

#include "CCNode.h"

NS_CC_BEGIN

class GridBase;

class GridNode : public Node
{
public:
    static GridNode* create();

    GridBase* getNodeGrid() { return _nodeGrid; }
    /**
    * @js NA
    */
    const GridBase* getNodeGrid() const { return _nodeGrid; }

    /**
     * Changes a grid object that is used when applying effects
     *
     * @param grid  A Grid object that is used when applying effects
     */
    void setNodeGrid(GridBase *grid);

    virtual bool init();
    virtual void visit();
protected:
    GridNode();
    virtual ~GridNode();

protected:
    GridBase* _nodeGrid;
};
NS_CC_END

#endif