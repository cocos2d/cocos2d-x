/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011 Zynga Inc.
 
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

#include "CCActionInstant.h"
#include "base_nodes/CCNode.h"
#include "sprite_nodes/CCSprite.h"
#include "script_support/CCScriptSupport.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN
//
// InstantAction
//
bool ActionInstant::isDone() {
    return true;
}

void ActionInstant::step(float dt) {
    CC_UNUSED_PARAM(dt);
    update(1);
}

void ActionInstant::update(float time) {
    CC_UNUSED_PARAM(time);
    // nothing
}

//
// Show
//

Show* Show::create() 
{
    Show* pRet = new Show();

    if (pRet) {
        pRet->autorelease();
    }

    return pRet;
}

void Show::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setVisible(true);
}

ActionInstant* Show::reverse() const
{
    return Hide::create();
}

Show * Show::clone() const
{
	// no copy constructor
	auto a = new Show();
	a->autorelease();
	return a;
}

Object* Show::copyWithZone(Zone *pZone) {

    Zone *pNewZone = NULL;
    Show *pRet = NULL;
    if (pZone && pZone->_copyObject) {
        pRet = (Show*) (pZone->_copyObject);
    } else {
        pRet = new Show();
        pZone = pNewZone = new Zone(pRet);
    }

    ActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// Hide
//
Hide * Hide::create() 
{
    Hide *pRet = new Hide();

    if (pRet) {
        pRet->autorelease();
    }

    return pRet;
}

void Hide::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setVisible(false);
}

ActionInstant *Hide::reverse() const
{
    return Show::create();
}

Hide * Hide::clone() const
{
	// no copy constructor
	auto a = new Hide();
	a->autorelease();
	return a;
}

Object* Hide::copyWithZone(Zone *pZone) {
    Zone *pNewZone = NULL;
    Hide *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (Hide*) (pZone->_copyObject);
    } else {
        pRet = new Hide();
        pZone = pNewZone = new Zone(pRet);
    }

    ActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// ToggleVisibility
//
ToggleVisibility * ToggleVisibility::create()
{
    ToggleVisibility *pRet = new ToggleVisibility();

    if (pRet)
    {
        pRet->autorelease();
    }

    return pRet;
}

void ToggleVisibility::update(float time) 
{
    CC_UNUSED_PARAM(time);
    _target->setVisible(!_target->isVisible());
}

ToggleVisibility * ToggleVisibility::reverse() const
{
	return ToggleVisibility::create();
}

ToggleVisibility * ToggleVisibility::clone() const
{
	// no copy constructor
	auto a = new ToggleVisibility();
	a->autorelease();
	return a;
}

Object* ToggleVisibility::copyWithZone(Zone *pZone)
{
    Zone *pNewZone = NULL;
    ToggleVisibility *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (ToggleVisibility*) (pZone->_copyObject);
    } else {
        pRet = new ToggleVisibility();
        pZone = pNewZone = new Zone(pRet);
    }

    ActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// Remove Self
//
RemoveSelf * RemoveSelf::create(bool isNeedCleanUp /*= true*/) 
{
	RemoveSelf *pRet = new RemoveSelf();

	if (pRet && pRet->init(isNeedCleanUp)) {
		pRet->autorelease();
	}

	return pRet;
}

bool RemoveSelf::init(bool isNeedCleanUp) {
	_isNeedCleanUp = isNeedCleanUp;
	return true;
}

void RemoveSelf::update(float time) {
	CC_UNUSED_PARAM(time);
	_target->removeFromParentAndCleanup(_isNeedCleanUp);
}

RemoveSelf *RemoveSelf::reverse() const
{
	return RemoveSelf::create(_isNeedCleanUp);
}

RemoveSelf * RemoveSelf::clone() const
{
	// no copy constructor
	auto a = new RemoveSelf();
	a->init(_isNeedCleanUp);
	a->autorelease();
	return a;
}

Object* RemoveSelf::copyWithZone(Zone *pZone) {
	Zone *pNewZone = NULL;
	RemoveSelf *pRet = NULL;

	if (pZone && pZone->_copyObject) {
		pRet = (RemoveSelf*) (pZone->_copyObject);
	} else {
		pRet = new RemoveSelf();
		pZone = pNewZone = new Zone(pRet);
	}

	ActionInstant::copyWithZone(pZone);
	pRet->init(_isNeedCleanUp);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//
// FlipX
//

FlipX *FlipX::create(bool x)
{
    FlipX *pRet = new FlipX();

    if (pRet && pRet->initWithFlipX(x)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool FlipX::initWithFlipX(bool x) {
    _flipX = x;
    return true;
}

void FlipX::update(float time) {
    CC_UNUSED_PARAM(time);
    ((Sprite*) (_target))->setFlipX(_flipX);
}

FlipX* FlipX::reverse() const
{
    return FlipX::create(!_flipX);
}

FlipX * FlipX::clone() const
{
	// no copy constructor
	auto a = new FlipX();
	a->initWithFlipX(_flipX);
	a->autorelease();
	return a;
}

Object * FlipX::copyWithZone(Zone *pZone) {
    Zone *pNewZone = NULL;
    FlipX *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (FlipX*) (pZone->_copyObject);
    } else {
        pRet = new FlipX();
        pZone = pNewZone = new Zone(pRet);
    }

    ActionInstant::copyWithZone(pZone);
    pRet->initWithFlipX(_flipX);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// FlipY
//

FlipY * FlipY::create(bool y)
{
    FlipY *pRet = new FlipY();

    if (pRet && pRet->initWithFlipY(y)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool FlipY::initWithFlipY(bool y) {
    _flipY = y;
    return true;
}

void FlipY::update(float time) {
    CC_UNUSED_PARAM(time);
    ((Sprite*) (_target))->setFlipY(_flipY);
}

FlipY* FlipY::reverse() const
{
    return FlipY::create(!_flipY);
}

FlipY * FlipY::clone() const
{
	// no copy constructor
	auto a = new FlipY();
	a->initWithFlipY(_flipY);
	a->autorelease();
	return a;
}

Object* FlipY::copyWithZone(Zone *pZone) {
    Zone *pNewZone = NULL;
    FlipY *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (FlipY*) (pZone->_copyObject);
    } else {
        pRet = new FlipY();
        pZone = pNewZone = new Zone(pRet);
    }

    ActionInstant::copyWithZone(pZone);
    pRet->initWithFlipY(_flipY);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// Place
//

Place* Place::create(const Point& pos)
{
    Place *pRet = new Place();

    if (pRet && pRet->initWithPosition(pos)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool Place::initWithPosition(const Point& pos) {
    _position = pos;
    return true;
}

Place * Place::clone() const
{
	// no copy constructor
	auto a = new Place();
	a->initWithPosition(_position);
	a->autorelease();
	return a;
}

Place * Place::reverse() const
{
	// no reverse, just clone
	return this->clone();
}

Object * Place::copyWithZone(Zone *pZone) {
    Zone *pNewZone = NULL;
    Place *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (Place*) (pZone->_copyObject);
    } else {
        pRet = new Place();
        pZone = pNewZone = new Zone(pRet);
    }

    ActionInstant::copyWithZone(pZone);
    pRet->initWithPosition(_position);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void Place::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setPosition(_position);
}

//
// CallFunc
//

CallFunc * CallFunc::create(const std::function<void()> &func)
{
    CallFunc *pRet = new CallFunc();

    if (pRet && pRet->initWithFunction(func) ) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CallFunc * CallFunc::create(Object* pSelectorTarget, SEL_CallFunc selector) 
{
    CallFunc *pRet = new CallFunc();

    if (pRet && pRet->initWithTarget(pSelectorTarget)) {
        pRet->_callFunc = selector;
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CallFunc * CallFunc::create(int nHandler)
{
	CallFunc *pRet = new CallFunc();

	if (pRet) {
		pRet->_scriptHandler = nHandler;
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CallFunc::initWithFunction(const std::function<void()> &func)
{
	_function = func;
    return true;
}

bool CallFunc::initWithTarget(Object* pSelectorTarget) {
    if (pSelectorTarget) 
    {
        pSelectorTarget->retain();
    }

    if (_selectorTarget) 
    {
        _selectorTarget->release();
    }

    _selectorTarget = pSelectorTarget;
    return true;
}

CallFunc::~CallFunc(void)
{
    if (_scriptHandler)
    {
        cocos2d::ScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_scriptHandler);
    }
    CC_SAFE_RELEASE(_selectorTarget);
}

CallFunc * CallFunc::clone() const
{
	// no copy constructor
	auto a = new CallFunc();
	if( _selectorTarget) {
		a->initWithTarget(_selectorTarget);
		a->_callFunc = _callFunc;
	}
	else if( _function )
		a->initWithFunction(_function);

	a->autorelease();
	return a;
}

CallFunc * CallFunc::reverse() const
{
	// no reverse here, just return a clone
	return this->clone();
}


Object * CallFunc::copyWithZone(Zone *pZone) {
    Zone* pNewZone = NULL;
    CallFunc* pRet = NULL;

    if (pZone && pZone->_copyObject) {
        //in case of being called at sub class
        pRet = (CallFunc*) (pZone->_copyObject);
    } else {
        pRet = new CallFunc();
        pZone = pNewZone = new Zone(pRet);
    }

    ActionInstant::copyWithZone(pZone);
	if( _selectorTarget) {
		pRet->initWithTarget(_selectorTarget);
		pRet->_callFunc = _callFunc;
	}
	else if( _function )
		pRet->initWithFunction(_function);

    if (_scriptHandler > 0 ) {
        pRet->_scriptHandler = cocos2d::ScriptEngineManager::sharedManager()->getScriptEngine()->reallocateScriptHandler(_scriptHandler);
    }
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CallFunc::update(float time) {
    CC_UNUSED_PARAM(time);
    this->execute();
}

void CallFunc::execute() {
    if (_callFunc) {
        (_selectorTarget->*_callFunc)();
    } else if( _function )
		_function();
	if (_scriptHandler) {
		ScriptEngineManager::sharedManager()->getScriptEngine()->executeCallFuncActionEvent(this);
	}
}

//
// CallFuncN
//
void CallFuncN::execute() {
    if (_callFuncN) {
        (_selectorTarget->*_callFuncN)(_target);
    }
	if (_scriptHandler) {
		ScriptEngineManager::sharedManager()->getScriptEngine()->executeCallFuncActionEvent(this, _target);
	}
}

CallFuncN * CallFuncN::create(Object* pSelectorTarget, SEL_CallFuncN selector)
{
    CallFuncN *pRet = new CallFuncN();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CallFuncN * CallFuncN::create(int nHandler)
{
	CallFuncN *pRet = new CallFuncN();

	if (pRet) {
		pRet->_scriptHandler = nHandler;
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CallFuncN::initWithTarget(Object* pSelectorTarget,
        SEL_CallFuncN selector) {
    if (CallFunc::initWithTarget(pSelectorTarget)) {
        _callFuncN = selector;
        return true;
    }

    return false;
}

CallFuncN * CallFuncN::clone() const
{
	// no copy constructor
	auto a = new CallFuncN();
	a->initWithTarget(_selectorTarget, _callFuncN);
	a->autorelease();
	return a;
}

Object * CallFuncN::copyWithZone(Zone* zone) {
    Zone* pNewZone = NULL;
    CallFuncN* pRet = NULL;

    if (zone && zone->_copyObject) {
        //in case of being called at sub class
        pRet = (CallFuncN*) (zone->_copyObject);
    } else {
        pRet = new CallFuncN();
        zone = pNewZone = new Zone(pRet);
    }

    CallFunc::copyWithZone(zone);
    pRet->initWithTarget(_selectorTarget, _callFuncN);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// CallFuncND
//

CallFuncND * CallFuncND::create(Object* pSelectorTarget, SEL_CallFuncND selector, void* d)
{
    CallFuncND* pRet = new CallFuncND();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector, d)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CallFuncND::initWithTarget(Object* pSelectorTarget,
        SEL_CallFuncND selector, void* d) {
    if (CallFunc::initWithTarget(pSelectorTarget)) {
        _data = d;
        _callFuncND = selector;
        return true;
    }

    return false;
}

CallFuncND * CallFuncND::clone() const
{
	// no copy constructor
	auto a = new CallFuncND();
	a->initWithTarget(_selectorTarget, _callFuncND, _data);
	a->autorelease();
	return a;
}

Object * CallFuncND::copyWithZone(Zone* zone) {
    Zone* pNewZone = NULL;
    CallFuncND* pRet = NULL;

    if (zone && zone->_copyObject) {
        //in case of being called at sub class
        pRet = (CallFuncND*) (zone->_copyObject);
    } else {
        pRet = new CallFuncND();
        zone = pNewZone = new Zone(pRet);
    }

    CallFunc::copyWithZone(zone);
    pRet->initWithTarget(_selectorTarget, _callFuncND, _data);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CallFuncND::execute() {
    if (_callFuncND) {
        (_selectorTarget->*_callFuncND)(_target, _data);
    }
}

//
// CallFuncO
//
CallFuncO::CallFuncO() :
        _object(NULL) {
}

CallFuncO::~CallFuncO() {
    CC_SAFE_RELEASE(_object);
}

void CallFuncO::execute() {
    if (_callFuncO) {
        (_selectorTarget->*_callFuncO)(_object);
    }
}

CallFuncO * CallFuncO::create(Object* pSelectorTarget, SEL_CallFuncO selector, Object* pObject)
{
    CallFuncO *pRet = new CallFuncO();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector, pObject)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CallFuncO::initWithTarget(Object* pSelectorTarget,
        SEL_CallFuncO selector, Object* pObject) {
    if (CallFunc::initWithTarget(pSelectorTarget)) {
        _object = pObject;
        CC_SAFE_RETAIN(_object);

        _callFuncO = selector;
        return true;
    }

    return false;
}

CallFuncO * CallFuncO::clone() const
{
	// no copy constructor	
	auto a = new CallFuncO();
	a->initWithTarget(_selectorTarget, _callFuncO, _object);
	a->autorelease();
	return a;
}

Object * CallFuncO::copyWithZone(Zone* zone) {
    Zone* pNewZone = NULL;
    CallFuncO* pRet = NULL;

    if (zone && zone->_copyObject) {
        //in case of being called at sub class
        pRet = (CallFuncO*) (zone->_copyObject);
    } else {
        pRet = new CallFuncO();
        zone = pNewZone = new Zone(pRet);
    }

    CallFunc::copyWithZone(zone);
    pRet->initWithTarget(_selectorTarget, _callFuncO, _object);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

NS_CC_END
