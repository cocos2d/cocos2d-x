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

#include "CCNodeGrid.h"
#include "CCGrid.h"

#include "renderer/CCGroupCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"


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
: _gridTarget(nullptr)
, _nodeGrid(nullptr)
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

    _groupCommand.init(_globalZOrder);
    renderer->addCommand(&_groupCommand);
    renderer->pushGroup(_groupCommand.getRenderQueueID());

    kmGLPushMatrix();
    Director::Projection beforeProjectionType;
    if(_nodeGrid && _nodeGrid->isActive())
    {
        beforeProjectionType = Director::getInstance()->getProjection();
        _nodeGrid->set2DProjection();
    }

    _gridBeginCommand.init(_globalZOrder);
    _gridBeginCommand.func = CC_CALLBACK_0(NodeGrid::onGridBeginDraw, this);
    renderer->addCommand(&_gridBeginCommand);

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

            if ( node && node->getLocalZOrder() < 0 )
                node->visit();
            else
                break;
        }
        // self draw,currently we have nothing to draw on NodeGrid, so there is no need to add render command
        this->draw();

        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it) {
            (*it)->visit();
        }
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

    _gridEndCommand.init(_globalZOrder);
    _gridEndCommand.func = CC_CALLBACK_0(NodeGrid::onGridEndDraw, this);
    renderer->addCommand(&_gridEndCommand);

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
