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

NS_CC_EXT_BEGIN

CCBatchNode *CCBatchNode::create()
{
    CCBatchNode *batchNode = new CCBatchNode();
    if (batchNode && batchNode->init())
    {
        batchNode->autorelease();
        return batchNode;
    }
    CC_SAFE_DELETE(batchNode);
    return NULL;
}

CCBatchNode::CCBatchNode()
    : _atlas(NULL)
{
}

bool CCBatchNode::init()
{
    bool ret = CCNode::init();
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    return ret;
}

void CCBatchNode::addChild(CCNode *child, int zOrder, int tag)
{
    CCNode::addChild(child, zOrder, tag);
    CCArmature *armature = dynamic_cast<CCArmature *>(child);
    if (armature != NULL)
    {
        armature->setBatchNode(this);
    }
}

void CCBatchNode::visit()
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

void CCBatchNode::draw()
{
    CC_NODE_DRAW_SETUP();
    CCObject *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        CCArmature *armature = dynamic_cast<CCArmature *>(object);
        if (armature)
        {
            armature->visit();
            _atlas = armature->getTextureAtlas();
        }
        else
        {
            ((CCNode *)object)->visit();
        }
    }

    if (_atlas)
    {
        _atlas->drawQuads();
        _atlas->removeAllQuads();
    }
}

NS_CC_EXT_END
