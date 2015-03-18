/*
 * Copyright (c) 2012      Pierre-David Bélanger
 * Copyright (c) 2012      cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * cocos2d-x: http://www.cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "2d/CCClippingNode.h"
#include "2d/CCDrawingPrimitives.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"


NS_CC_BEGIN

ClippingNode::ClippingNode()
: _stencil(nullptr)
, _alphaThreshold(0.0f)
, _inverted(false)
{}

ClippingNode::~ClippingNode()
{
    if (_stencil)
    {
        _stencil->stopAllActions();
        _stencil->release();
    }
}

ClippingNode* ClippingNode::create()
{
    ClippingNode *ret = new (std::nothrow) ClippingNode();
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

ClippingNode* ClippingNode::create(Node *pStencil)
{
    ClippingNode *ret = new (std::nothrow) ClippingNode();
    if (ret && ret->init(pStencil))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool ClippingNode::init()
{
    return init(nullptr);
}

bool ClippingNode::init(Node *stencil)
{
    CC_SAFE_RELEASE(_stencil);
    _stencil = stencil;
    CC_SAFE_RETAIN(_stencil);
    
    _alphaThreshold = 1;
    _inverted = false;
    
    return true;
}

void ClippingNode::onEnter()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
            return;
    }
#endif
    
    Node::onEnter();
    
    if (_stencil != nullptr)
    {
        _stencil->onEnter();
    }
    else
    {
        CCLOG("ClippingNode warning: _stencil is nil.");
    }
}

void ClippingNode::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    
    if (_stencil != nullptr)
    {
        _stencil->onEnterTransitionDidFinish();
    }
}

void ClippingNode::onExitTransitionDidStart()
{
    if (_stencil != nullptr)
    {
        _stencil->onExitTransitionDidStart();
    }
   
    Node::onExitTransitionDidStart();
}

void ClippingNode::onExit()
{
    if (_stencil != nullptr)
    {
        _stencil->onExit();
    }
    
    Node::onExit();
}

void ClippingNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    if (!_visible || !hasContent())
        return;
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    _groupCommand.init(_globalZOrder);
    renderer->addCommand(&_groupCommand);
    
    renderer->pushGroup(_groupCommand.getRenderQueueID());

    _beginStencilCommand.init(_globalZOrder, _inverted, _alphaThreshold, _stencil);
    renderer->addCommand(&_beginStencilCommand);
    
    _stencil->visit(renderer, _modelViewTransform, flags);

    _afterStencilCommand.init(_globalZOrder, _alphaThreshold);
    renderer->addCommand(&_afterStencilCommand);

    int i = 0;
    bool visibleByCamera = isVisitableByVisitingCamera();
    
    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for( ; i < _children.size(); i++ )
        {
            auto node = _children.at(i);
            
            if ( node && node->getLocalZOrder() < 0 )
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }
        // self draw
        if (visibleByCamera)
            this->draw(renderer, _modelViewTransform, flags);
        
        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
    }
    else if (visibleByCamera)
    {
        this->draw(renderer, _modelViewTransform, flags);
    }

    _endStencilCommand.init(_globalZOrder);
    renderer->addCommand(&_endStencilCommand);

    renderer->popGroup();
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void ClippingNode::setCameraMask(unsigned short mask, bool applyChildren)
{
    Node::setCameraMask(mask, applyChildren);
    
    if (_stencil)
        _stencil->setCameraMask(mask, applyChildren);
}

Node* ClippingNode::getStencil() const
{
    return _stencil;
}

void ClippingNode::setStencil(Node *stencil)
{
    CC_SAFE_RETAIN(stencil);
    CC_SAFE_RELEASE(_stencil);
    _stencil = stencil;
}

bool ClippingNode::hasContent() const
{
    return _children.size() > 0;
}

GLfloat ClippingNode::getAlphaThreshold() const
{
    return _alphaThreshold;
}

void ClippingNode::setAlphaThreshold(GLfloat alphaThreshold)
{
    _alphaThreshold = alphaThreshold;
}

bool ClippingNode::isInverted() const
{
    return _inverted;
}

void ClippingNode::setInverted(bool inverted)
{
    _inverted = inverted;
}

NS_CC_END
