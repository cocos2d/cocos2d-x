/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#include "editor-support/cocostudio/CCBatchNode.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "editor-support/cocostudio/CCSkin.h"

#include "renderer/CCRenderer.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCGLProgramState.h"
#include "base/CCDirector.h"

using namespace cocos2d;

namespace cocostudio {

BatchNode *BatchNode::create()
{
    BatchNode *batchNode = new (std::nothrow) BatchNode();
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
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    return ret;
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
            _groupCommand = new (std::nothrow) GroupCommand();
        }
    }
}

void BatchNode::addChild(cocos2d::Node *child, int zOrder, const std::string &name)
{
    Node::addChild(child, zOrder, name);
    Armature *armature = dynamic_cast<Armature *>(child);
    if (armature != nullptr)
    {
        armature->setBatchNode(this);
        if (_groupCommand == nullptr)
        {
            _groupCommand = new (std::nothrow) GroupCommand();
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

void BatchNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }

    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    if (isVisitableByVisitingCamera())
    {
        // IMPORTANT:
        // To ease the migration to v3.0, we still support the Mat4 stack,
        // but it is deprecated and your code should not rely on it
        Director* director = Director::getInstance();
        director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
        
        sortAllChildren();
        draw(renderer, _modelViewTransform, flags);
        
        // FIX ME: Why need to set _orderOfArrival to 0??
        // Please refer to https://github.com/cocos2d/cocos2d-x/pull/6920
        // setOrderOfArrival(0);
        
        director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    }
}

void BatchNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
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
        
            armature->visit(renderer, transform, flags);
        }
        else
        {
            renderer->popGroup();
            pushed = false;
            
            ((Node *)object)->visit(renderer, transform, flags);
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
