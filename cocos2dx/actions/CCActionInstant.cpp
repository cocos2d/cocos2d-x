/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
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
#include "CCNode.h"
#include "CCSprite.h"

namespace cocos2d {
//
// InstantAction
//
CCActionInstant::CCActionInstant() {
}

CCObject * CCActionInstant::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	CCActionInstant *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (CCActionInstant*) (pZone->m_pCopyObject);
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

void CCActionInstant::step(ccTime dt) {
	CC_UNUSED_PARAM(dt);
	update(1);
}

void CCActionInstant::update(ccTime time) {
	CC_UNUSED_PARAM(time);
	// ignore
}

CCFiniteTimeAction * CCActionInstant::reverse() {
	return (CCFiniteTimeAction*) (copy()->autorelease());
}

//
// Show
//
CCShow* CCShow::action() {
	CCShow* pRet = new CCShow();

	if (pRet) {
		pRet->autorelease();
	}

	return pRet;
}

void CCShow::startWithTarget(CCNode *pTarget) {
	CCActionInstant::startWithTarget(pTarget);
	pTarget->setIsVisible(true);
}

CCFiniteTimeAction* CCShow::reverse() {
	return (CCFiniteTimeAction*) (CCHide::action());
}

CCObject* CCShow::copyWithZone(CCZone *pZone) {

	CCZone *pNewZone = NULL;
	CCShow *pRet = NULL;
	if (pZone && pZone->m_pCopyObject) {
		pRet = (CCShow*) (pZone->m_pCopyObject);
	} else {
		pRet = new CCShow();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//
// Hide
//
CCHide * CCHide::action() {
	CCHide *pRet = new CCHide();

	if (pRet) {
		pRet->autorelease();
	}

	return pRet;
}

void CCHide::startWithTarget(CCNode *pTarget) {
	CCActionInstant::startWithTarget(pTarget);
	pTarget->setIsVisible(false);
}

CCFiniteTimeAction *CCHide::reverse() {
	return (CCFiniteTimeAction*) (CCShow::action());
}

CCObject* CCHide::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	CCHide *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (CCHide*) (pZone->m_pCopyObject);
	} else {
		pRet = new CCHide();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//
// ToggleVisibility
//
CCToggleVisibility * CCToggleVisibility::action() {
	CCToggleVisibility *pRet = new CCToggleVisibility();

	if (pRet) {
		pRet->autorelease();
	}

	return pRet;
}

void CCToggleVisibility::startWithTarget(CCNode *pTarget) {
	CCActionInstant::startWithTarget(pTarget);
	pTarget->setIsVisible(!pTarget->getIsVisible());
}

//
// FlipX
//
CCFlipX *CCFlipX::actionWithFlipX(bool x) {
	CCFlipX *pRet = new CCFlipX();

	if (pRet && pRet->initWithFlipX(x)) {
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet)
	return NULL;
}

bool CCFlipX::initWithFlipX(bool x) {
	m_bFlipX = x;
	return true;
}

void CCFlipX::startWithTarget(CCNode *pTarget) {
	CCActionInstant::startWithTarget(pTarget);
	((CCSprite*) (pTarget))->setFlipX(m_bFlipX);
}

CCFiniteTimeAction* CCFlipX::reverse() {
	return CCFlipX::actionWithFlipX(!m_bFlipX);
}

CCObject * CCFlipX::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	CCFlipX *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (CCFlipX*) (pZone->m_pCopyObject);
	} else {
		pRet = new CCFlipX();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->initWithFlipX(m_bFlipX);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//
// FlipY
//
CCFlipY * CCFlipY::actionWithFlipY(bool y) {
	CCFlipY *pRet = new CCFlipY();

	if (pRet && pRet->initWithFlipY(y)) {
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCFlipY::initWithFlipY(bool y) {
	m_bFlipY = y;
	return true;
}

void CCFlipY::startWithTarget(CCNode *pTarget) {
	CCActionInstant::startWithTarget(pTarget);
	((CCSprite*) (pTarget))->setFlipY(m_bFlipY);
}

CCFiniteTimeAction* CCFlipY::reverse() {
	return CCFlipY::actionWithFlipY(!m_bFlipY);
}

CCObject* CCFlipY::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	CCFlipY *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (CCFlipY*) (pZone->m_pCopyObject);
	} else {
		pRet = new CCFlipY();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->initWithFlipY(m_bFlipY);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//
// Place
//
CCPlace* CCPlace::actionWithPosition(const CCPoint& pos) {
	CCPlace *pRet = new CCPlace();

	if (pRet && pRet->initWithPosition(pos)) {
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCPlace::initWithPosition(const CCPoint& pos) {
	m_tPosition = pos;
	return true;
}

CCObject * CCPlace::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	CCPlace *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (CCPlace*) (pZone->m_pCopyObject);
	} else {
		pRet = new CCPlace();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->initWithPosition(m_tPosition);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCPlace::startWithTarget(CCNode *pTarget) {
	CCActionInstant::startWithTarget(pTarget);
	m_pTarget->setPosition(m_tPosition);
}

//
// CallFunc
//

CCCallFunc * CCCallFunc::actionWithTarget(CCObject* pSelectorTarget,
		SEL_CallFunc selector) {
	CCCallFunc *pRet = new CCCallFunc();

	if (pRet && pRet->initWithTarget(pSelectorTarget)) {
		pRet->m_pCallFunc = selector;
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCCallFunc::initWithTarget(CCObject* pSelectorTarget) {
	if (pSelectorTarget) 
	{
		pSelectorTarget->retain();
	}

	if (m_pSelectorTarget) 
	{
		m_pSelectorTarget->release();
	}

	m_pSelectorTarget = pSelectorTarget;
	return true;
}

CCObject * CCCallFunc::copyWithZone(CCZone *pZone) {
	CCZone* pNewZone = NULL;
	CCCallFunc* pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		//in case of being called at sub class
		pRet = (CCCallFunc*) (pZone->m_pCopyObject);
	} else {
		pRet = new CCCallFunc();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->initWithTarget(m_pSelectorTarget);
	pRet->m_pCallFunc = m_pCallFunc;
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCCallFunc::startWithTarget(CCNode *pTarget) {
	CCActionInstant::startWithTarget(pTarget);
	this->execute();
}

void CCCallFunc::execute() {
	if (m_pCallFunc) {
		(m_pSelectorTarget->*m_pCallFunc)();
	}
}

//
// CallFuncN
//
void CCCallFuncN::execute() {
	if (m_pCallFuncN) {
		(m_pSelectorTarget->*m_pCallFuncN)(m_pTarget);
	}
}

CCCallFuncN * CCCallFuncN::actionWithTarget(CCObject* pSelectorTarget,
		SEL_CallFuncN selector) {
	CCCallFuncN *pRet = new CCCallFuncN();

	if (pRet && pRet->initWithTarget(pSelectorTarget, selector)) {
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCCallFuncN::initWithTarget(CCObject* pSelectorTarget,
		SEL_CallFuncN selector) {
	if (CCCallFunc::initWithTarget(pSelectorTarget)) {
		m_pCallFuncN = selector;
		return true;
	}

	return false;
}

CCObject * CCCallFuncN::copyWithZone(CCZone* zone) {
	CCZone* pNewZone = NULL;
	CCCallFuncN* pRet = NULL;

	if (zone && zone->m_pCopyObject) {
		//in case of being called at sub class
		pRet = (CCCallFuncN*) (zone->m_pCopyObject);
	} else {
		pRet = new CCCallFuncN();
		zone = pNewZone = new CCZone(pRet);
	}

	CCCallFunc::copyWithZone(zone);
	pRet->initWithTarget(m_pSelectorTarget, m_pCallFuncN);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

//
// CallFuncND
//
CCCallFuncND * CCCallFuncND::actionWithTarget(CCObject* pSelectorTarget,
		SEL_CallFuncND selector, void* d) {
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
		m_pData = d;
		m_pCallFuncND = selector;
		return true;
	}

	return false;
}

CCObject * CCCallFuncND::copyWithZone(CCZone* zone) {
	CCZone* pNewZone = NULL;
	CCCallFuncND* pRet = NULL;

	if (zone && zone->m_pCopyObject) {
		//in case of being called at sub class
		pRet = (CCCallFuncND*) (zone->m_pCopyObject);
	} else {
		pRet = new CCCallFuncND();
		zone = pNewZone = new CCZone(pRet);
	}

	CCCallFunc::copyWithZone(zone);
	pRet->initWithTarget(m_pSelectorTarget, m_pCallFuncND, m_pData);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void CCCallFuncND::execute() {
	if (m_pCallFuncND) {
		(m_pSelectorTarget->*m_pCallFuncND)(m_pTarget, m_pData);
	}
}

//
// CCCallFuncO
//
CCCallFuncO::CCCallFuncO() :
		m_pObject(NULL) {
}

CCCallFuncO::~CCCallFuncO() {
	CC_SAFE_RELEASE(m_pObject);
}

void CCCallFuncO::execute() {
	if (m_pCallFuncO) {
		(m_pSelectorTarget->*m_pCallFuncO)(m_pObject);
	}
}

CCCallFuncO * CCCallFuncO::actionWithTarget(CCObject* pSelectorTarget,
		SEL_CallFuncO selector, CCObject* pObject) {
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
		m_pObject = pObject;
		CC_SAFE_RETAIN(m_pObject)

		m_pCallFuncO = selector;
		return true;
	}

	return false;
}

CCObject * CCCallFuncO::copyWithZone(CCZone* zone) {
	CCZone* pNewZone = NULL;
	CCCallFuncO* pRet = NULL;

	if (zone && zone->m_pCopyObject) {
		//in case of being called at sub class
		pRet = (CCCallFuncO*) (zone->m_pCopyObject);
	} else {
		pRet = new CCCallFuncO();
		zone = pNewZone = new CCZone(pRet);
	}

	CCCallFunc::copyWithZone(zone);
	pRet->initWithTarget(m_pSelectorTarget, m_pCallFuncO, m_pObject);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}
}
