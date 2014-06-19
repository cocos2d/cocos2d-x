/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2009      Valentin Milea
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

#include "CCProtectedNode.h"

#include "base/CCDirector.h"

#if CC_USE_PHYSICS
#include "physics/CCPhysicsBody.h"
#endif
#include "2d/CCScene.h"

NS_CC_BEGIN

ProtectedNode::ProtectedNode() : _reorderProtectedChildDirty(false)
{
}

ProtectedNode::~ProtectedNode()
{
    
    CCLOGINFO( "deallocing ProtectedNode: %p - tag: %i", this, _tag );
}

ProtectedNode * ProtectedNode::create(void)
{
	ProtectedNode * ret = new ProtectedNode();
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

void ProtectedNode::cleanup()
{
    Node::cleanup();
    // timers
    for( const auto &child: _protectedChildren)
        child->cleanup();
}

void ProtectedNode::addProtectedChild(cocos2d::Node *child)
{
    addProtectedChild(child, child->getLocalZOrder(), child->getTag());
}

void ProtectedNode::addProtectedChild(cocos2d::Node *child, int localZOrder)
{
    addProtectedChild(child, localZOrder, child->getTag());
}

/* "add" logic MUST only be on this method
 * If a class want's to extend the 'addChild' behavior it only needs
 * to override this method
 */
void ProtectedNode::addProtectedChild(Node *child, int zOrder, int tag)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    CCASSERT( child->getParent() == nullptr, "child already added. It can't be added again");
    
    if (_protectedChildren.empty())
    {
        _protectedChildren.reserve(4);
    }
    
    this->insertProtectedChild(child, zOrder);
    
    child->setTag(tag);
    
    child->setParent(this);
    child->setOrderOfArrival(s_globalOrderOfArrival++);
    
#if CC_USE_PHYSICS
    // Recursive add children with which have physics body.
    for (Node* node = this; node != nullptr; node = node->getParent())
    {
        Scene* scene = dynamic_cast<Scene*>(node);
        if (scene != nullptr && scene->getPhysicsWorld() != nullptr)
        {
            scene->addChildToPhysicsWorld(child);
            break;
        }
    }
#endif
    
    if( _running )
    {
        child->onEnter();
        // prevent onEnterTransitionDidFinish to be called twice when a node is added in onEnter
        if (_isTransitionFinished) {
            child->onEnterTransitionDidFinish();
        }
    }
    
    if (_cascadeColorEnabled)
    {
        updateCascadeColor();
    }
    
    if (_cascadeOpacityEnabled)
    {
        updateCascadeOpacity();
    }
}

Node* ProtectedNode::getProtectedChildByTag(int tag)
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");
    
    for (auto& child : _protectedChildren)
    {
        if(child && child->getTag() == tag)
            return child;
    }
    return nullptr;
}

/* "remove" logic MUST only be on this method
 * If a class want's to extend the 'removeChild' behavior it only needs
 * to override this method
 */
void ProtectedNode::removeProtectedChild(cocos2d::Node *child, bool cleanup)
{
    // explicit nil handling
    if (_protectedChildren.empty())
    {
        return;
    }
    
    ssize_t index = _protectedChildren.getIndex(child);
    if( index != CC_INVALID_INDEX )
    {
        
        // IMPORTANT:
        //  -1st do onExit
        //  -2nd cleanup
        if (_running)
        {
            child->onExitTransitionDidStart();
            child->onExit();
        }
        
#if CC_USE_PHYSICS
        if (child->getPhysicsBody() != nullptr)
        {
            child->getPhysicsBody()->removeFromWorld();
        }
        
#endif
        // If you don't do cleanup, the child's actions will not get removed and the
        // its scheduledSelectors_ dict will not get released!
        if (cleanup)
        {
            child->cleanup();
        }
        
        // set parent nil at the end
        child->setParent(nullptr);
        
        _protectedChildren.erase(index);
    }
}

void ProtectedNode::removeAllProtectedChildren()
{
    removeAllProtectedChildrenWithCleanup(true);
}

void ProtectedNode::removeAllProtectedChildrenWithCleanup(bool cleanup)
{
    // not using detachChild improves speed here
    for (auto& child : _protectedChildren)
    {
        // IMPORTANT:
        //  -1st do onExit
        //  -2nd cleanup
        if(_running)
        {
            child->onExitTransitionDidStart();
            child->onExit();
        }
        
#if CC_USE_PHYSICS
        if (child->getPhysicsBody() != nullptr)
        {
            child->getPhysicsBody()->removeFromWorld();
        }
#endif
        
        if (cleanup)
        {
            child->cleanup();
        }
        // set parent nil at the end
        child->setParent(nullptr);
    }
    
    _protectedChildren.clear();
}

void ProtectedNode::removeProtectedChildByTag(int tag, bool cleanup)
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");
    
    Node *child = this->getProtectedChildByTag(tag);
    
    if (child == nullptr)
    {
        CCLOG("cocos2d: removeChildByTag(tag = %d): child not found!", tag);
    }
    else
    {
        this->removeProtectedChild(child, cleanup);
    }
}

// helper used by reorderChild & add
void ProtectedNode::insertProtectedChild(cocos2d::Node *child, int z)
{
    _reorderProtectedChildDirty = true;
    _protectedChildren.pushBack(child);
    child->_setLocalZOrder(z);
}

void ProtectedNode::sortAllProtectedChildren()
{
    if( _reorderProtectedChildDirty ) {
        std::sort( std::begin(_protectedChildren), std::end(_protectedChildren), nodeComparisonLess );
        _reorderProtectedChildDirty = false;
    }
}

void ProtectedNode::reorderProtectedChild(cocos2d::Node *child, int localZOrder)
{
    CCASSERT( child != nullptr, "Child must be non-nil");
    _reorderProtectedChildDirty = true;
    child->setOrderOfArrival(s_globalOrderOfArrival++);
    child->_setLocalZOrder(localZOrder);
}

void ProtectedNode::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    
    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    int i = 0;      // used by _children
    int j = 0;      // used by _protectedChildren
    
    sortAllChildren();
    sortAllProtectedChildren();
    
    //
    // draw children and protectedChildren zOrder < 0
    //
    for( ; i < _children.size(); i++ )
    {
        auto node = _children.at(i);
        
        if ( node && node->getLocalZOrder() < 0 )
            node->visit(renderer, _modelViewTransform, flags);
        else
            break;
    }
    
    for( ; j < _protectedChildren.size(); j++ )
    {
        auto node = _protectedChildren.at(j);
        
        if ( node && node->getLocalZOrder() < 0 )
            node->visit(renderer, _modelViewTransform, flags);
        else
            break;
    }
    
    //
    // draw self
    //
    this->draw(renderer, _modelViewTransform, flags);
    
    //
    // draw children and protectedChildren zOrder >= 0
    //
    for(auto it=_protectedChildren.cbegin()+j; it != _protectedChildren.cend(); ++it)
        (*it)->visit(renderer, _modelViewTransform, flags);
    
    for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
        (*it)->visit(renderer, _modelViewTransform, flags);
    
    // reset for next frame
    _orderOfArrival = 0;
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void ProtectedNode::onEnter()
{
    Node::onEnter();
    for( const auto &child: _protectedChildren)
        child->onEnter();
}

void ProtectedNode::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
    for( const auto &child: _protectedChildren)
        child->onEnterTransitionDidFinish();
}

void ProtectedNode::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
    for( const auto &child: _protectedChildren)
        child->onExitTransitionDidStart();
}

void ProtectedNode::onExit()
{
    Node::onExit();
    for( const auto &child: _protectedChildren)
        child->onExit();
}

void ProtectedNode::updateDisplayedOpacity(GLubyte parentOpacity)
{
	_displayedOpacity = _realOpacity * parentOpacity/255.0;
    updateColor();
    
    if (_cascadeOpacityEnabled)
    {
        for(auto child : _children){
            child->updateDisplayedOpacity(_displayedOpacity);
        }
        for(auto child : _protectedChildren){
            child->updateDisplayedOpacity(_displayedOpacity);
        }
    }
}

void ProtectedNode::updateDisplayedColor(const Color3B& parentColor)
{
	_displayedColor.r = _realColor.r * parentColor.r/255.0;
	_displayedColor.g = _realColor.g * parentColor.g/255.0;
	_displayedColor.b = _realColor.b * parentColor.b/255.0;
    updateColor();
    
    if (_cascadeColorEnabled)
    {
        for(const auto &child : _children){
            child->updateDisplayedColor(_displayedColor);
        }
        for(const auto &child : _protectedChildren){
            child->updateDisplayedColor(_displayedColor);
        }
    }
}

void ProtectedNode::disableCascadeColor()
{
    for(auto child : _children){
        child->updateDisplayedColor(Color3B::WHITE);
    }
    for(auto child : _protectedChildren){
        child->updateDisplayedColor(Color3B::WHITE);
    }
}

NS_CC_END