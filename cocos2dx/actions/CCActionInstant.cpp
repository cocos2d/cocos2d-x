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

CCActionInstant * CCActionInstant::clone() const
{
	auto a = new CCActionInstant(*this);
	a->autorelease();
	return a;
}

CCObject * CCActionInstant::copyWithZone(CCZone *pZone) {

    CCZone *pNewZone = NULL;
    CCActionInstant *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (CCActionInstant*) (pZone->_copyObject);
    } else {
        pRet = new CCActionInstant();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCFiniteTimeAction::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

bool CCActionInstant::isDone() {
    return true;
}

void CCActionInstant::step(float dt) {
    CC_UNUSED_PARAM(dt);
    update(1);
}

void CCActionInstant::update(float time) {
    CC_UNUSED_PARAM(time);
    // nothing
}

CCFiniteTimeAction * CCActionInstant::reverse() {
    return (CCFiniteTimeAction*) (copy()->autorelease());
}

//
// Show
//

CCShow* CCShow::create() 
{
    CCShow* pRet = new CCShow();

    if (pRet) {
        pRet->autorelease();
    }

    return pRet;
}

void CCShow::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setVisible(true);
}

CCFiniteTimeAction* CCShow::reverse() {
    return (CCFiniteTimeAction*) (CCHide::create());
}

CCShow * CCShow::clone() const
{
	auto a = new CCShow(*this);
	a->autorelease();
	return a;
}

CCObject* CCShow::copyWithZone(CCZone *pZone) {

    CCZone *pNewZone = NULL;
    CCShow *pRet = NULL;
    if (pZone && pZone->_copyObject) {
        pRet = (CCShow*) (pZone->_copyObject);
    } else {
        pRet = new CCShow();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// Hide
//
CCHide * CCHide::create() 
{
    CCHide *pRet = new CCHide();

    if (pRet) {
        pRet->autorelease();
    }

    return pRet;
}

void CCHide::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setVisible(false);
}

CCFiniteTimeAction *CCHide::reverse() {
    return (CCFiniteTimeAction*) (CCShow::create());
}

CCHide * CCHide::clone() const
{
	auto a = new CCHide(*this);
	a->autorelease();
	return a;
}

CCObject* CCHide::copyWithZone(CCZone *pZone) {
    CCZone *pNewZone = NULL;
    CCHide *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (CCHide*) (pZone->_copyObject);
    } else {
        pRet = new CCHide();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// ToggleVisibility
//
CCToggleVisibility * CCToggleVisibility::create()
{
    CCToggleVisibility *pRet = new CCToggleVisibility();

    if (pRet)
    {
        pRet->autorelease();
    }

    return pRet;
}

void CCToggleVisibility::update(float time) 
{
    CC_UNUSED_PARAM(time);
    _target->setVisible(!_target->isVisible());
}

CCToggleVisibility * CCToggleVisibility::clone() const
{
	auto a = new CCToggleVisibility(*this);
	a->autorelease();
	return a;
}

CCObject* CCToggleVisibility::copyWithZone(CCZone *pZone)
{
    CCZone *pNewZone = NULL;
    CCToggleVisibility *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (CCToggleVisibility*) (pZone->_copyObject);
    } else {
        pRet = new CCToggleVisibility();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// Remove Self
//
CCRemoveSelf * CCRemoveSelf::create(bool isNeedCleanUp /*= true*/) 
{
	CCRemoveSelf *pRet = new CCRemoveSelf();

	if (pRet && pRet->init(isNeedCleanUp)) {
		pRet->autorelease();
	}

	return pRet;
}

bool CCRemoveSelf::init(bool isNeedCleanUp) {
	_isNeedCleanUp = isNeedCleanUp;
	return true;
}

void CCRemoveSelf::update(float time) {
	CC_UNUSED_PARAM(time);
	_target->removeFromParentAndCleanup(_isNeedCleanUp);
}

CCFiniteTimeAction *CCRemoveSelf::reverse() {
	return (CCFiniteTimeAction*) (CCRemoveSelf::create(_isNeedCleanUp));
}

CCRemoveSelf * CCRemoveSelf::clone() const
{
	auto a = new CCRemoveSelf(*this);
	a->init(_isNeedCleanUp);
	a->autorelease();
	return a;
}

CCObject* CCRemoveSelf::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	CCRemoveSelf *pRet = NULL;

	if (pZone && pZone->_copyObject) {
		pRet = (CCRemoveSelf*) (pZone->_copyObject);
	} else {
		pRet = new CCRemoveSelf();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->init(_isNeedCleanUp);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//
// FlipX
//

CCFlipX *CCFlipX::create(bool x)
{
    CCFlipX *pRet = new CCFlipX();

    if (pRet && pRet->initWithFlipX(x)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCFlipX::initWithFlipX(bool x) {
    _flipX = x;
    return true;
}

void CCFlipX::update(float time) {
    CC_UNUSED_PARAM(time);
    ((CCSprite*) (_target))->setFlipX(_flipX);
}

CCFiniteTimeAction* CCFlipX::reverse() {
    return CCFlipX::create(!_flipX);
}

CCFlipX * CCFlipX::clone() const
{
	auto a = new CCFlipX(*this);
	a->initWithFlipX(_flipX);
	a->autorelease();
	return a;
}

CCObject * CCFlipX::copyWithZone(CCZone *pZone) {
    CCZone *pNewZone = NULL;
    CCFlipX *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (CCFlipX*) (pZone->_copyObject);
    } else {
        pRet = new CCFlipX();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInstant::copyWithZone(pZone);
    pRet->initWithFlipX(_flipX);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// FlipY
//

CCFlipY * CCFlipY::create(bool y)
{
    CCFlipY *pRet = new CCFlipY();

    if (pRet && pRet->initWithFlipY(y)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCFlipY::initWithFlipY(bool y) {
    _flipY = y;
    return true;
}

void CCFlipY::update(float time) {
    CC_UNUSED_PARAM(time);
    ((CCSprite*) (_target))->setFlipY(_flipY);
}

CCFiniteTimeAction* CCFlipY::reverse() {
    return CCFlipY::create(!_flipY);
}

CCFlipY * CCFlipY::clone() const
{
	auto a = new CCFlipY(*this);
	a->initWithFlipY(_flipY);
	a->autorelease();
	return a;
}

CCObject* CCFlipY::copyWithZone(CCZone *pZone) {
    CCZone *pNewZone = NULL;
    CCFlipY *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (CCFlipY*) (pZone->_copyObject);
    } else {
        pRet = new CCFlipY();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInstant::copyWithZone(pZone);
    pRet->initWithFlipY(_flipY);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// Place
//

CCPlace* CCPlace::create(const CCPoint& pos)
{
    CCPlace *pRet = new CCPlace();

    if (pRet && pRet->initWithPosition(pos)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCPlace::initWithPosition(const CCPoint& pos) {
    _position = pos;
    return true;
}

CCPlace * CCPlace::clone() const
{
	auto a = new CCPlace(*this);
	a->initWithPosition(_position);
	a->autorelease();
	return a;
}

CCObject * CCPlace::copyWithZone(CCZone *pZone) {
    CCZone *pNewZone = NULL;
    CCPlace *pRet = NULL;

    if (pZone && pZone->_copyObject) {
        pRet = (CCPlace*) (pZone->_copyObject);
    } else {
        pRet = new CCPlace();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInstant::copyWithZone(pZone);
    pRet->initWithPosition(_position);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCPlace::update(float time) {
    CC_UNUSED_PARAM(time);
    _target->setPosition(_position);
}

//
// CallFunc
//

CCCallFunc * CCCallFunc::create(const std::function<void()> &func)
{
    CCCallFunc *pRet = new CCCallFunc();

    if (pRet && pRet->initWithFunction(func) ) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCCallFunc * CCCallFunc::create(CCObject* pSelectorTarget, SEL_CallFunc selector) 
{
    CCCallFunc *pRet = new CCCallFunc();

    if (pRet && pRet->initWithTarget(pSelectorTarget)) {
        pRet->_callFunc = selector;
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCCallFunc * CCCallFunc::create(int nHandler)
{
	CCCallFunc *pRet = new CCCallFunc();

	if (pRet) {
		pRet->_scriptHandler = nHandler;
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CCCallFunc::initWithFunction(const std::function<void()> &func)
{
	_function = func;
    return true;
}

bool CCCallFunc::initWithTarget(CCObject* pSelectorTarget) {
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

CCCallFunc::~CCCallFunc(void)
{
    if (_scriptHandler)
    {
        cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_scriptHandler);
    }
    CC_SAFE_RELEASE(_selectorTarget);
}

CCCallFunc * CCCallFunc::clone() const
{
	auto a = new CCCallFunc(*this);
	if( _selectorTarget) {
		a->initWithTarget(_selectorTarget);
		a->_callFunc = _callFunc;
	}
	else if( _function )
		a->initWithFunction(_function);

	a->autorelease();
	return a;
}

CCObject * CCCallFunc::copyWithZone(CCZone *pZone) {
    CCZone* pNewZone = NULL;
    CCCallFunc* pRet = NULL;

    if (pZone && pZone->_copyObject) {
        //in case of being called at sub class
        pRet = (CCCallFunc*) (pZone->_copyObject);
    } else {
        pRet = new CCCallFunc();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInstant::copyWithZone(pZone);
	if( _selectorTarget) {
		pRet->initWithTarget(_selectorTarget);
		pRet->_callFunc = _callFunc;
	}
	else if( _function )
		pRet->initWithFunction(_function);

    if (_scriptHandler > 0 ) {
        pRet->_scriptHandler = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->reallocateScriptHandler(_scriptHandler);
    }
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCCallFunc::update(float time) {
    CC_UNUSED_PARAM(time);
    this->execute();
}

void CCCallFunc::execute() {
    if (_callFunc) {
        (_selectorTarget->*_callFunc)();
    } else if( _function )
		_function();
	if (_scriptHandler) {
		CCScriptEngineManager::sharedManager()->getScriptEngine()->executeCallFuncActionEvent(this);
	}
}

//
// CallFuncN
//
void CCCallFuncN::execute() {
    if (_callFuncN) {
        (_selectorTarget->*_callFuncN)(_target);
    }
	if (_scriptHandler) {
		CCScriptEngineManager::sharedManager()->getScriptEngine()->executeCallFuncActionEvent(this, _target);
	}
}

CCCallFuncN * CCCallFuncN::create(CCObject* pSelectorTarget, SEL_CallFuncN selector)
{
    CCCallFuncN *pRet = new CCCallFuncN();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCCallFuncN * CCCallFuncN::create(int nHandler)
{
	CCCallFuncN *pRet = new CCCallFuncN();

	if (pRet) {
		pRet->_scriptHandler = nHandler;
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CCCallFuncN::initWithTarget(CCObject* pSelectorTarget,
        SEL_CallFuncN selector) {
    if (CCCallFunc::initWithTarget(pSelectorTarget)) {
        _callFuncN = selector;
        return true;
    }

    return false;
}

CCCallFuncN * CCCallFuncN::clone() const
{
	auto a = new CCCallFuncN(*this);
	a->initWithTarget(_selectorTarget, _callFuncN);
	a->autorelease();
	return a;
}

CCObject * CCCallFuncN::copyWithZone(CCZone* zone) {
    CCZone* pNewZone = NULL;
    CCCallFuncN* pRet = NULL;

    if (zone && zone->_copyObject) {
        //in case of being called at sub class
        pRet = (CCCallFuncN*) (zone->_copyObject);
    } else {
        pRet = new CCCallFuncN();
        zone = pNewZone = new CCZone(pRet);
    }

    CCCallFunc::copyWithZone(zone);
    pRet->initWithTarget(_selectorTarget, _callFuncN);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

//
// CallFuncND
//

CCCallFuncND * CCCallFuncND::create(CCObject* pSelectorTarget, SEL_CallFuncND selector, void* d)
{
    CCCallFuncND* pRet = new CCCallFuncND();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector, d)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCCallFuncND::initWithTarget(CCObject* pSelectorTarget,
        SEL_CallFuncND selector, void* d) {
    if (CCCallFunc::initWithTarget(pSelectorTarget)) {
        _data = d;
        _callFuncND = selector;
        return true;
    }

    return false;
}

CCCallFuncND * CCCallFuncND::clone() const
{
	auto a = new CCCallFuncND(*this);
	a->initWithTarget(_selectorTarget, _callFuncND, _data);
	a->autorelease();
	return a;
}

CCObject * CCCallFuncND::copyWithZone(CCZone* zone) {
    CCZone* pNewZone = NULL;
    CCCallFuncND* pRet = NULL;

    if (zone && zone->_copyObject) {
        //in case of being called at sub class
        pRet = (CCCallFuncND*) (zone->_copyObject);
    } else {
        pRet = new CCCallFuncND();
        zone = pNewZone = new CCZone(pRet);
    }

    CCCallFunc::copyWithZone(zone);
    pRet->initWithTarget(_selectorTarget, _callFuncND, _data);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCCallFuncND::execute() {
    if (_callFuncND) {
        (_selectorTarget->*_callFuncND)(_target, _data);
    }
}

//
// CCCallFuncO
//
CCCallFuncO::CCCallFuncO() :
        _object(NULL) {
}

CCCallFuncO::~CCCallFuncO() {
    CC_SAFE_RELEASE(_object);
}

void CCCallFuncO::execute() {
    if (_callFuncO) {
        (_selectorTarget->*_callFuncO)(_object);
    }
}

CCCallFuncO * CCCallFuncO::create(CCObject* pSelectorTarget, SEL_CallFuncO selector, CCObject* pObject)
{
    CCCallFuncO *pRet = new CCCallFuncO();

    if (pRet && pRet->initWithTarget(pSelectorTarget, selector, pObject)) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCCallFuncO::initWithTarget(CCObject* pSelectorTarget,
        SEL_CallFuncO selector, CCObject* pObject) {
    if (CCCallFunc::initWithTarget(pSelectorTarget)) {
        _object = pObject;
        CC_SAFE_RETAIN(_object);

        _callFuncO = selector;
        return true;
    }

    return false;
}

CCCallFuncO * CCCallFuncO::clone() const
{
	auto a = new CCCallFuncO(*this);
	a->initWithTarget(_selectorTarget, _callFuncO, _object);
	a->autorelease();
	return a;
}

CCObject * CCCallFuncO::copyWithZone(CCZone* zone) {
    CCZone* pNewZone = NULL;
    CCCallFuncO* pRet = NULL;

    if (zone && zone->_copyObject) {
        //in case of being called at sub class
        pRet = (CCCallFuncO*) (zone->_copyObject);
    } else {
        pRet = new CCCallFuncO();
        zone = pNewZone = new CCZone(pRet);
    }

    CCCallFunc::copyWithZone(zone);
    pRet->initWithTarget(_selectorTarget, _callFuncO, _object);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

NS_CC_END
