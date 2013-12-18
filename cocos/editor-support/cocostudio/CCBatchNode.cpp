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

#include "cocostudio/CCBatchNode.h"
#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCSkin.h"
#include "CCRenderer.h"
#include "CCGroupCommand.h"

using namespace cocos2d;

namespace cocostudio {

BatchNode *BatchNode::create()
{
    BatchNode *batchNode = new BatchNode();
    if (batchNode && batchNode->init())
    {
        batchNode->autorelease();
        return batchNode;
    }
    CC_SAFE_DELETE(batchNode);
    return nullptr;
}

BatchNode::BatchNode()
{
}

BatchNode::~BatchNode()
{
}

bool BatchNode::init()
{
    bool ret = Node::init();
    setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    return ret;
}

void BatchNode::addChild(Node *pChild)
{
    Node::addChild(pChild);
}

void BatchNode::addChild(Node *child, int zOrder)
{
    Node::addChild(child, zOrder);
}

void BatchNode::addChild(Node *child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
    Armature *armature = dynamic_cast<Armature *>(child);
    if (armature != nullptr)
    {
        armature->setBatchNode(this);
    }
}

void BatchNode::removeChild(Node* child, bool cleanup)
{
    Armature *armature = dynamic_cast<Armature *>(child);
    if (armature != nullptr)
    {
        armature->setBatchNode(nullptr);
    }

    Node::removeChild(child, cleanup);
}

void BatchNode::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    kmGLPushMatrix();

    if (_grid && _grid->isActive())
    {
        _grid->beforeDraw();
    }

    transform();
    sortAllChildren();
    draw();

    // reset for next frame
    _orderOfArrival = 0;

    if (_grid && _grid->isActive())
    {
        _grid->afterDraw(this);
    }

    kmGLPopMatrix();
}

void BatchNode::draw()
{
    if (_children.empty())
    {
        return;
    }

    CC_NODE_DRAW_SETUP();
    
    generateGroupCommand();

    for(auto object : _children)
    {
        Armature *armature = dynamic_cast<Armature *>(object);
        if (armature)
        {
            if (_popGroupCommand)
            {
                generateGroupCommand();
            }
        
            armature->visit();
        }
        else
        {
            Director::getInstance()->getRenderer()->popGroup();
            _popGroupCommand = true;
            
            ((Node *)object)->visit();
        }
    }
}

void BatchNode::generateGroupCommand()
{
    Renderer* renderer = Director::getInstance()->getRenderer();
    GroupCommand* groupCommand = GroupCommand::getCommandPool().generateCommand();
    groupCommand->init(0,_vertexZ);
    renderer->addCommand(groupCommand);

    renderer->pushGroup(groupCommand->getRenderQueueID());
    
    _popGroupCommand = false;
}

}
