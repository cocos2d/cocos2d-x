#ifndef __MISCNODE_CCGRID_NODE_H__
#define __MISCNODE_CCGRID_NODE_H__

#include "CCNode.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

class GridBase;

class NodeGrid : public Node
{
public:
    static NodeGrid* create();

    GridBase* getGrid() { return _nodeGrid; }
    /**
    * @js NA
    */
    const GridBase* getGrid() const { return _nodeGrid; }

    /**
     * Changes a grid object that is used when applying effects
     *
     * @param grid  A Grid object that is used when applying effects
     */
    void setGrid(GridBase *grid);

    virtual bool init();
    virtual void visit();

    void setTarget(Node *target);
protected:
    NodeGrid();
    virtual ~NodeGrid();

    void onGridBeginDraw();
    void onGridEndDraw();

protected:
    kmMat4 _cachedMVmat;
    Node* _gridTarget;
    GridBase* _nodeGrid;
};
NS_CC_END

#endif