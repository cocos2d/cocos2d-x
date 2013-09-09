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

#include "CCBatchNode.h"
#include "../utils/CCArmatureDefine.h"
#include "../CCArmature.h"

namespace cocos2d { namespace extension { namespace armature {

BatchNode *BatchNode::create()
{
    BatchNode *batchNode = new BatchNode();
    if (batchNode && batchNode->init())
    {
        batchNode->autorelease();
        return batchNode;
    }
    CC_SAFE_DELETE(batchNode);
    return NULL;
}

BatchNode::BatchNode()
    : _atlas(NULL)
{
}

bool BatchNode::init()
{
    bool ret = Node::init();
    setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
    return ret;
}

void BatchNode::addChild(Node *child, int zOrder, int tag)
{
    Node::addChild(child, zOrder, tag);
    Armature *armature = dynamic_cast<Armature *>(child);
    if (armature != NULL)
    {
        armature->setBatchNode(this);
    }
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
    CC_NODE_DRAW_SETUP();
    Object *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        Armature *armature = dynamic_cast<Armature *>(object);
        if (armature)
        {
            armature->visit();
            _atlas = armature->getTextureAtlas();
        }
        else
        {
            static_cast<Node*>(object)->visit();
        }
    }

    if (_atlas)
    {
        _atlas->drawQuads();
        _atlas->removeAllQuads();
    }
}

}}} // namespace cocos2d { namespace extension { namespace armature {
