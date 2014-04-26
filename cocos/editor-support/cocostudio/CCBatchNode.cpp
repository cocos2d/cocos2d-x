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

#include "cocostudio/CCBatchNode.h"
#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCSkin.h"

#include "2d/renderer/CCRenderer.h"
#include "2d/renderer/CCGroupCommand.h"
#include "CCShaderCache.h"
#include "2d/CCDirector.h"

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
: _groupCommand(nullptr)
{
}

BatchNode::~BatchNode()
{
    CC_SAFE_DELETE(_groupCommand);
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
        if (_groupCommand == nullptr)
        {
            _groupCommand = new GroupCommand();
        }
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

void BatchNode::visit(Renderer *renderer, const Matrix &parentTransform, bool parentTransformUpdated)
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }

    bool dirty = parentTransformUpdated || _transformUpdated;
    if(dirty)
        _modelViewTransform = transform(parentTransform);
    _transformUpdated = false;

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Matrix stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    sortAllChildren();
    draw(renderer, _modelViewTransform, dirty);

    // reset for next frame
    _orderOfArrival = 0;

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void BatchNode::draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
{
    if (_children.empty())
    {
        return;
    }

//    CC_NODE_DRAW_SETUP();

    bool pushed = false;
    for(auto object : _children)
    {
        Armature *armature = dynamic_cast<Armature *>(object);
        if (armature)
        {
            if (!pushed)
            {
                generateGroupCommand();
                pushed = true;
            }
        
            armature->visit(renderer, transform, transformUpdated);
        }
        else
        {
            renderer->popGroup();
            pushed = false;
            
            ((Node *)object)->visit(renderer, transform, transformUpdated);
        }
    }
}

void BatchNode::generateGroupCommand()
{
    Renderer* renderer = Director::getInstance()->getRenderer();
    _groupCommand->init(_globalZOrder);
    renderer->addCommand(_groupCommand);

    renderer->pushGroup(_groupCommand->getRenderQueueID());
}

}
