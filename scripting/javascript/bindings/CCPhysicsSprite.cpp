/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "CCPhysicsSprite.h"
#include "ScriptingCore.h"
#include "cocosjs_manual_conversions.h"

using namespace cocos2d;

static CCPoint cpVect_to_ccPoint(cpVect p) {
    return CCPoint(p.x, p.y);
}

static cpVect ccPoint_to_cpVect(CCPoint point) {
    cpVect t;
    t.x = point.x;
    t.y = point.y;
    return t;
}

const cocos2d::CCPoint& CCPhysicsSprite::getPosition() {
    cpVect temp = cpBodyGetPos(_body);
	return cpVect_to_ccPoint(temp);
}

void CCPhysicsSprite::setPosition(const cocos2d::CCPoint &pos) {
    cpBodySetPos(_body, ccPoint_to_cpVect(getPosition()));
}


float CCPhysicsSprite::getRotation() {
    return (_ignoreBodyRotation ? m_fRotation : -CC_RADIANS_TO_DEGREES(cpBodyGetAngle(_body)));
}

void CCPhysicsSprite::setRotation(float rotation) {
	if(_ignoreBodyRotation){
		m_fRotation = rotation;
	} else {
		cpBodySetAngle(_body, -CC_DEGREES_TO_RADIANS(rotation));
        m_fRotation = -CC_DEGREES_TO_RADIANS(rotation);
	}
}

cocos2d::CCAffineTransform CCPhysicsSprite::nodeToParentTransform() {
    cpVect rot = (_ignoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(m_fRotation)) : _body->rot);
    float x = _body->p.x + rot.x*-m_tAnchorPointInPoints.x - rot.y*-m_tAnchorPointInPoints.y;
    float y = _body->p.y + rot.y*-m_tAnchorPointInPoints.x + rot.x*-m_tAnchorPointInPoints.y;
    
    if(m_bIgnoreAnchorPointForPosition){
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }
    
    return (m_tTransform = cocos2d::__CCAffineTransformMake(rot.x, rot.y, -rot.y, rot.x, x,	y));
}
