
#include "CCNodeGrid.h"
#include "CCGrid.h"

#include "CCGroupCommand.h"
#include "CCRenderer.h"
#include "CCCustomCommand.h"


NS_CC_BEGIN

NodeGrid* NodeGrid::create()
{
    NodeGrid * ret = new NodeGrid();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

NodeGrid::NodeGrid()
: _nodeGrid(nullptr)
, _gridTarget(nullptr)
{

}

void NodeGrid::setTarget(Node* target)
{
    CC_SAFE_RELEASE(_gridTarget);
    CC_SAFE_RETAIN(target);
    _gridTarget = target;
}

NodeGrid::~NodeGrid()
{
    CC_SAFE_RELEASE(_nodeGrid);
    CC_SAFE_RELEASE(_gridTarget);
}

bool NodeGrid::init()
{
    return Node::init();
}

void NodeGrid::onGridBeginDraw()
{
    if (_nodeGrid && _nodeGrid->isActive())
    {
        _nodeGrid->beforeDraw();
    }
}

void NodeGrid::onGridEndDraw()
{
    if(_nodeGrid && _nodeGrid->isActive())
    {
        _nodeGrid->afterDraw(this);
    }
}

void NodeGrid::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    
    Renderer* renderer = Director::getInstance()->getRenderer();

    GroupCommand* groupCommand = GroupCommand::getCommandPool().generateCommand();
    groupCommand->init(0,_vertexZ);
    renderer->addCommand(groupCommand);
    
    renderer->pushGroup(groupCommand->getRenderQueueID());

    kmGLPushMatrix();
    Director::Projection beforeProjectionType;
    if(_nodeGrid && _nodeGrid->isActive())
    {
        beforeProjectionType = Director::getInstance()->getProjection();
        _nodeGrid->set2DProjection();
    }
    
    kmGLGetMatrix(KM_GL_MODELVIEW, &_cachedMVmat);
    
    CustomCommand* gridBeginCmd = CustomCommand::getCommandPool().generateCommand();
    gridBeginCmd->init(0,_vertexZ);
    gridBeginCmd->func = CC_CALLBACK_0(NodeGrid::onGridBeginDraw, this);
    renderer->addCommand(gridBeginCmd);

    this->transform();
    
    if(_gridTarget)
    {
        _gridTarget->visit();
    }
    
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
        // self draw,currently we have nothing to draw on NodeGrid, so there is no need to add render command
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
    
    if(_nodeGrid && _nodeGrid->isActive())
    {
        // restore projection
        Director *director = Director::getInstance();
        director->setProjection(beforeProjectionType);
    }

    CustomCommand* gridEndCmd = CustomCommand::getCommandPool().generateCommand();
    gridEndCmd->init(0,_vertexZ);
    gridEndCmd->func = CC_CALLBACK_0(NodeGrid::onGridEndDraw, this);
    renderer->addCommand(gridEndCmd);

    renderer->popGroup();
 
    kmGLPopMatrix();
}

void NodeGrid::setGrid(GridBase *grid)
{
    CC_SAFE_RELEASE(_nodeGrid);
    CC_SAFE_RETAIN(grid);
    _nodeGrid = grid;
}

NS_CC_END
