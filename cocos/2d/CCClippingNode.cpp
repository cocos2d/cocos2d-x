/*
 * Copyright (c) 2012      Pierre-David Bélanger
 * Copyright (c) 2012      cocos2d-x.org
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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
#include "renderer/CCRenderer.h"
#include "renderer/ccShaders.h"
#include "renderer/backend/ProgramState.h"
#include "base/CCDirector.h"
#include "base/CCStencilStateManager.h"

NS_CC_BEGIN

ClippingNode::ClippingNode()
: _stencil(nullptr)
, _stencilStateManager(new StencilStateManager())
{
}

ClippingNode::~ClippingNode()
{
    if (_stencil)
    {
        _stencil->stopAllActions();
        _stencil->release();
    }
    CC_SAFE_DELETE(_stencilStateManager);
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
    setStencil(stencil);
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
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnterTransitionDidFinish))
            return;
    }
#endif
    
    Node::onEnterTransitionDidFinish();
    
    if (_stencil != nullptr)
    {
        _stencil->onEnterTransitionDidFinish();
    }
}

void ClippingNode::onExitTransitionDidStart()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnExitTransitionDidStart))
            return;
    }
#endif
    
    if (_stencil != nullptr)
    {
        _stencil->onExitTransitionDidStart();
    }
   
    Node::onExitTransitionDidStart();
}

void ClippingNode::onExit()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnExit))
            return;
    }
#endif
    
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
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    //Add group command
        
    _groupCommandStencil.init(_globalZOrder);
    renderer->addCommand(&_groupCommandStencil);

    renderer->pushGroup(_groupCommandStencil.getRenderQueueID());

    // _beforeVisitCmd.init(_globalZOrder);
    // _beforeVisitCmd.func = CC_CALLBACK_0(StencilStateManager::onBeforeVisit, _stencilStateManager);
    // renderer->addCommand(&_beforeVisitCmd);
    _stencilStateManager->onBeforeVisit(_globalZOrder);
    
    auto alphaThreshold = this->getAlphaThreshold();
    if (alphaThreshold < 1)
    {
        auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_TEXTURE_COLOR_ALPHA_TEST);
        auto programState = new (std::nothrow) backend::ProgramState(program);
        auto alphaLocation = programState->getUniformLocation("u_alpha_value");
        programState->setUniform(alphaLocation, &alphaThreshold, sizeof(alphaThreshold));
        setProgramStateRecursively(_stencil, programState);

        CC_SAFE_RELEASE_NULL(programState);
    }
    _stencil->visit(renderer, _modelViewTransform, flags);

    _afterDrawStencilCmd.init(_globalZOrder);
    _afterDrawStencilCmd.func = CC_CALLBACK_0(StencilStateManager::onAfterDrawStencil, _stencilStateManager);
    renderer->addCommand(&_afterDrawStencilCmd);

    int i = 0;
    bool visibleByCamera = isVisitableByVisitingCamera();
    

    // `_groupCommandChildren` is used as a barrier
    // to ensure commands above be executed before children nodes
    _groupCommandChildren.init(_globalZOrder);
    renderer->addCommand(&_groupCommandChildren);

    renderer->pushGroup(_groupCommandChildren.getRenderQueueID());

    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for(auto size = _children.size(); i < size; ++i)
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

        for(auto it=_children.cbegin()+i, itCend = _children.cend(); it != itCend; ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
    }
    else if (visibleByCamera)
    {
        this->draw(renderer, _modelViewTransform, flags);
    }


    renderer->popGroup();

    _afterVisitCmd.init(_globalZOrder);
    _afterVisitCmd.func = CC_CALLBACK_0(StencilStateManager::onAfterVisit, _stencilStateManager);
    renderer->addCommand(&_afterVisitCmd);

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
    //early out if the stencil is already set
    if (_stencil == stencil)
        return;
    
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        if (_stencil)
            sEngine->releaseScriptObject(this, _stencil);
        if (stencil)
            sEngine->retainScriptObject(this, stencil);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    
    //cleanup current stencil
    if(_stencil != nullptr && _stencil->isRunning())
    {
        _stencil->onExitTransitionDidStart();
        _stencil->onExit();
    }
    CC_SAFE_RELEASE_NULL(_stencil);
    
    //initialise new stencil
    _stencil = stencil;
    CC_SAFE_RETAIN(_stencil);
    if(_stencil != nullptr && this->isRunning())
    {
        _stencil->onEnter();
        if(this->_isTransitionFinished)
        {
            _stencil->onEnterTransitionDidFinish();
        }
    }

    if (_stencil != nullptr)
    {
        _originalStencilProgramState[_stencil] = _stencil->getProgramState();
        auto& children = _stencil->getChildren();
        for (const auto &child : children) {
            _originalStencilProgramState[child] = child->getProgramState();
        }
    }
}

bool ClippingNode::hasContent() const
{
    return _children.size() > 0;
}

float ClippingNode::getAlphaThreshold() const
{
    return _stencilStateManager->getAlphaThreshold();
}

void ClippingNode::setAlphaThreshold(float alphaThreshold)
{
    if (alphaThreshold == 1 && alphaThreshold != _stencilStateManager->getAlphaThreshold())
    {
        // should reset program used by _stencil
        if (_stencil)
            restoreAllProgramStates();
    }
    _stencilStateManager->setAlphaThreshold(alphaThreshold);
}

bool ClippingNode::isInverted() const
{
    return _stencilStateManager->isInverted();
}

void ClippingNode::setInverted(bool inverted)
{
    _stencilStateManager->setInverted(inverted);
}

void ClippingNode::setProgramStateRecursively(Node* node, backend::ProgramState* programState)
{
    _originalStencilProgramState[node] = node->getProgramState();
    node->setProgramState(programState);

    auto& children = node->getChildren();
    for (const auto &child : children) {
        setProgramStateRecursively(child, programState);
    }
}

void ClippingNode::restoreAllProgramStates()
{
    for (auto item : _originalStencilProgramState)
    {
        auto node = item.first;
        auto programState = item.second;
        node->setProgramState(programState);
    }
}


NS_CC_END
