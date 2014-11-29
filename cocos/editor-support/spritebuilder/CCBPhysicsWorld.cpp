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

#include "CCBPhysicsWorld.h"
#include "CCPhysicsWorldInfo_chipmunk.h"
#include "CCPhysicsShapeInfo_chipmunk.h"
#include "CCBPhysicsBody.h"
#include "CCPhysicsHelper_chipmunk.h"
#include "CCPhysicsJointInfo_chipmunk.h"
#include "CCBReader.h"

using namespace cocos2d;
namespace spritebuilder {
    

    CCBPhysicsWorld* CCBPhysicsWorld::construct(cocos2d::PhysicsNode& scene)
    {
        CCBPhysicsWorld * world = new CCBPhysicsWorld();
        if(world && world->init(scene))
        {
            return world;
        }
    
        CC_SAFE_DELETE(world);
        return nullptr;
    }
    void CCBPhysicsWorld::update(float delta)
    {
        if (_delayDirty)
        {
            // the updateJoints must run before the updateBodies.
            updateJoints();
            updateBodies();
            _delayDirty = !(_delayAddBodies.size() == 0 && _delayRemoveBodies.size() == 0 && _delayAddJoints.size() == 0 && _delayRemoveJoints.size() == 0);
        }
        
        _updateTime += delta;
        if (++_updateRateCount >= _updateRate)
        {
            _info->step(_updateTime * _speed);
            for (auto& body : _bodies)
            {
                ((CCBPhysicsBody*)body)->update(_updateTime * _speed);
            }
            _updateRateCount = 0;
            _updateTime = 0.0f;
        }
        
        if (_debugDrawMask != DEBUGDRAW_NONE)
        {
            debugDraw();
        }
    }
    void CCBPhysicsWorld::debugDraw() {
        if (_debugDraw == nullptr)
        {
            _debugDraw = new CCBPhysicsDebugDraw(*this);
        }
        PhysicsWorld::debugDraw();
    }
    
    
    //Nguyen Thai Duong: Cheater classes
    
    class CCBPhysicsShape : public PhysicsShape {
    protected:
        inline PhysicsShapeInfo* getShapeInfor() {return _info;};
        friend class CCBPhysicsDebugDraw;
    };
    
    class CCBPhysicsJoint : public PhysicsJoint {
    protected:
        inline PhysicsJointInfo* getJointInfor() {return _info;};
        friend class CCBPhysicsDebugDraw;
    };
    
   
    CCBPhysicsDebugDraw::CCBPhysicsDebugDraw(CCBPhysicsWorld& world): PhysicsDebugDraw(world)
    {
    }
    
    void CCBPhysicsDebugDraw::drawShape(PhysicsShape& shape)
    {
        const Color4F fillColor(1.0f, 0.0f, 0.0f, 0.3f);
        const Color4F outlineColor(1.0f, 0.0f, 0.0f, 1.0f);
        float ptmRatio = CCBReader::getPTMRatio();
        
        for (auto it = ((CCBPhysicsShape*)&shape)->getShapeInfor()->getShapes().begin(); it != ((CCBPhysicsShape*)&shape)->getShapeInfor()->getShapes().end(); ++it)
        {
            cpShape *subShape = *it;
            
            switch ((*it)->klass_private->type)
            {
                case CP_CIRCLE_SHAPE:
                {
                    float radius = PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(subShape)) * ptmRatio;
                    Point centre = PhysicsHelper::cpv2point(cpBodyGetPos(cpShapeGetBody(subShape)))
                    + PhysicsHelper::cpv2point(cpCircleShapeGetOffset(subShape));
                    
                    centre = centre * ptmRatio;
                    
                    static const int CIRCLE_SEG_NUM = 12;
                    Point seg[CIRCLE_SEG_NUM] = {};
                    
                    for (int i = 0; i < CIRCLE_SEG_NUM; ++i)
                    {
                        float angle = (float)i * M_PI / (float)CIRCLE_SEG_NUM * 2.0f;
                        Point d(radius * cosf(angle), radius * sinf(angle));
                        seg[i] = centre + d;
                    }
                    _drawNode->drawPolygon(seg, CIRCLE_SEG_NUM, fillColor, 1, outlineColor);
                    break;
                }
                case CP_SEGMENT_SHAPE:
                {
                    cpSegmentShape *seg = (cpSegmentShape *)subShape;
                    seg->ta.x *= ptmRatio;
                    seg->ta.y *= ptmRatio;
                    
                    seg->tb.x *= ptmRatio;
                    seg->tb.y *= ptmRatio;

                    _drawNode->drawSegment(PhysicsHelper::cpv2point(seg->ta),
                                           PhysicsHelper::cpv2point(seg->tb),
                                           PhysicsHelper::cpfloat2float(seg->r==0 ? 1 : seg->r), outlineColor);
                    break;
                }
                case CP_POLY_SHAPE:
                {
                    cpPolyShape* poly = (cpPolyShape*)subShape;
                    int num = poly->numVerts;
                    Point* seg = new Point[num];
                   
                    PhysicsHelper::cpvs2points(poly->tVerts, seg, num);
                    
                    for (int i = 0; i < num; i++) {
                        seg[i] = seg[i] * ptmRatio;
                    }

                    _drawNode->drawPolygon(seg, num, fillColor, 1.0f, outlineColor);
                    
                    delete[] seg;
                    break;
                }
                default:
                    break;
            }
        }
    }
    
    void CCBPhysicsDebugDraw::drawJoint(PhysicsJoint& joint)
    {
        
        const Color4F lineColor(0.0f, 0.0f, 1.0f, 1.0f);
        const Color4F jointPointColor(0.0f, 1.0f, 0.0f, 1.0f);
        
        for (auto it = ((CCBPhysicsJoint*)&joint)->getJointInfor()->getJoints().begin(); it != ((CCBPhysicsJoint*)&joint)->getJointInfor()->getJoints().end(); ++it)
        {
            cpConstraint *constraint = *it;
            
            
            cpBody *body_a = constraint->a;
            cpBody *body_b = constraint->b;
            
            const cpConstraintClass *klass = constraint->klass_private;
            if(klass == cpPinJointGetClass())
            {
                cpPinJoint *subJoint = (cpPinJoint *)constraint;
                
                cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
                cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
                
                a.x *= CCBReader::getPTMRatio();
                a.y *= CCBReader::getPTMRatio();
                b.x *= CCBReader::getPTMRatio();
                b.y *= CCBReader::getPTMRatio();
                
                _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, lineColor);
                _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, jointPointColor);
                _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, jointPointColor);
            }
            else if(klass == cpSlideJointGetClass())
            {
                cpSlideJoint *subJoint = (cpSlideJoint *)constraint;
                
                cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
                
                cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
                
                a.x *= CCBReader::getPTMRatio();
                a.y *= CCBReader::getPTMRatio();
                b.x *= CCBReader::getPTMRatio();
                b.y *= CCBReader::getPTMRatio();
                
                _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, lineColor);
                _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, jointPointColor);
                _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, jointPointColor);
            }
            else if(klass == cpPivotJointGetClass())
            {
                cpPivotJoint *subJoint = (cpPivotJoint *)constraint;
                
                cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
                cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
                
                
                a.x *= CCBReader::getPTMRatio();
                a.y *= CCBReader::getPTMRatio();
                b.x *= CCBReader::getPTMRatio();
                b.y *= CCBReader::getPTMRatio();
                
                _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, jointPointColor);
                _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, jointPointColor);
            }
            else if(klass == cpGrooveJointGetClass())
            {
                cpGrooveJoint *subJoint = (cpGrooveJoint *)constraint;
                
                cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->grv_a, body_a->rot));
                cpVect b = cpvadd(body_a->p, cpvrotate(subJoint->grv_b, body_a->rot));
                cpVect c = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
                
                a.x *= CCBReader::getPTMRatio();
                a.y *= CCBReader::getPTMRatio();
                b.x *= CCBReader::getPTMRatio();
                b.y *= CCBReader::getPTMRatio();
                c.x *= CCBReader::getPTMRatio();
                c.y *= CCBReader::getPTMRatio();
                
                _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, lineColor);
                _drawNode->drawDot(PhysicsHelper::cpv2point(c), 2, jointPointColor);
            }
            else if(klass == cpDampedSpringGetClass())
            {
                cpDampedSpring *subJoint = (cpDampedSpring *)constraint;
                
                cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
                cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
                
                a.x *= CCBReader::getPTMRatio();
                a.y *= CCBReader::getPTMRatio();
                b.x *= CCBReader::getPTMRatio();
                b.y *= CCBReader::getPTMRatio();
                
                _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, lineColor);
                _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, jointPointColor);
                _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, jointPointColor);
            }
            
        }
    }
    
    void CCBPhysicsDebugDraw::drawContact()
    {
        
    }

   
}