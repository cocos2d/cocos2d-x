/*
 *
 * Copyright (c) 2014 Nguyen Thai Duong
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
 */

#include "CCBPhysicsBody.h"
#include "CCBReader.h"
#include "chipmunk.h"
#include "CCPhysicsBodyInfo_chipmunk.h"

using namespace cocos2d;
namespace spritebuilder {
    


CCBPhysicsBody* CCBPhysicsBody::create() {
    CCBPhysicsBody* body = new CCBPhysicsBody();
    if (body && body->init())
    {
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;

}

Point CCBPhysicsBody::getPosition() const {
    Point position = PhysicsBody::getPosition();
    position = position * CCBReader::getPTMRatio();
    return position;
}

void CCBPhysicsBody::setPosition(Point position) {
    position = position / CCBReader::getPTMRatio();
    PhysicsBody::setPosition(position);
}
void CCBPhysicsBody::update(float delta) {

    if (_node != nullptr)
    {
        Node* parent = _node->getParent();
        Point position = parent != nullptr ? parent->convertToNodeSpace(getPosition()) : getPosition();
        
        _positionResetTag = true;
        _rotationResetTag = true;
        _node->setPosition(position);
        _node->setRotation(getRotation());
        _positionResetTag = false;
        _rotationResetTag = false;
        
        // damping compute
        if (_isDamping && _dynamic && !isResting())
        {
            _info->getBody()->v.x *= cpfclamp(1.0f - delta * _linearDamping, 0.0f, 1.0f);
            _info->getBody()->v.y *= cpfclamp(1.0f - delta * _linearDamping, 0.0f, 1.0f);
            _info->getBody()->w *= cpfclamp(1.0f - delta * _angularDamping, 0.0f, 1.0f);
        }
    }
    
}
}
