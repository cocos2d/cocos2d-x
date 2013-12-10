
#include "CCGridNode.h"
#include "CCGrid.h"

#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

GridNode* GridNode::create()
{
    GridNode * pRet = new GridNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

GridNode::GridNode()
:Node()
,_nodeGrid(nullptr)
{

}

GridNode::~GridNode()
{
    CC_SAFE_RELEASE(_nodeGrid);
}

bool GridNode::init()
{
    return Node::init();
}

void GridNode::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    
    kmGLPushMatrix();

     if (_nodeGrid && _nodeGrid->isActive())
     {
         _nodeGrid->beforeDraw();
     }

    this->transform();
    int i = 0;

    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for( ; i < _children.size(); i++ )
        {
            auto node = _children.at(i);

            if ( node && node->getZOrder() < 0 )
                node->visit();
            else
                break;
        }
        // self draw
        this->draw();

        // Uses std::for_each to improve performance.
        std::for_each(_children.cbegin()+i, _children.cend(), [](Node* node){
            node->visit();
        });
    }
    else
    {
        this->draw();
    }

    // reset for next frame
    _orderOfArrival = 0;

     if (_nodeGrid && _nodeGrid->isActive())
     {
         _nodeGrid->afterDraw(this);
    }
 
    kmGLPopMatrix();
}


NS_CC_END
