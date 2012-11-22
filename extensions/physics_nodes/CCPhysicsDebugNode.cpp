/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
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
#include "CCPhysicsDebugNode.h"

#if CC_ENABLE_CHIPMUNK_INTEGRATION

#include "ccTypes.h"
#include "cocoa/CCGeometry.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>

NS_CC_EXT_BEGIN

/*
 IMPORTANT - READ ME!
 
 This file sets pokes around in the private API a lot to provide efficient
 debug rendering given nothing more than reference to a Chipmunk space.
 It is not recommended to write rendering code like this in your own games
 as the private API may change with little or no warning.
 */

static ccColor4F ColorForBody(cpBody *body)
{
	if (cpBodyIsRogue(body) || cpBodyIsSleeping(body))
    {
		return ccc4f(0.5f, 0.5f, 0.5f ,0.5f);
	}
    else if (body->CP_PRIVATE(node).idleTime > body->CP_PRIVATE(space)->sleepTimeThreshold)
    {
		return ccc4f(0.33f, 0.33f, 0.33f, 0.5f);
	}
    else
    {
		return ccc4f(1.0f, 0.0f, 0.0f, 0.5f);
	}
}

static CCPoint cpVert2ccp(const cpVect &vert)
{
    return CCPointMake(vert.x, vert.y);
}

static CCPoint* cpVertArray2ccpArrayN(const cpVect* cpVertArray, unsigned int count)
{
    if (count == 0) return NULL;
    CCPoint* pPoints = new CCPoint[count];
    
    for (unsigned int i = 0; i < count; ++i)
    {
        pPoints[i].x = cpVertArray[i].x;
        pPoints[i].y = cpVertArray[i].y;
    }
    return pPoints;
}

static void DrawShape(cpShape *shape, CCDrawNode *renderer)
{
	cpBody *body = shape->body;
	ccColor4F color = ColorForBody(body);
    
	switch (shape->CP_PRIVATE(klass)->type)
    {
		case CP_CIRCLE_SHAPE:
        {
            cpCircleShape *circle = (cpCircleShape *)shape;
            cpVect center = circle->tc;
            cpFloat radius = circle->r;
            renderer->drawDot(cpVert2ccp(center), cpfmax(radius, 1.0), color);
            renderer->drawSegment(cpVert2ccp(center), cpVert2ccp(cpvadd(center, cpvmult(body->rot, radius))), 1.0, color);
        }
             break;
		case CP_SEGMENT_SHAPE:
        {
            cpSegmentShape *seg = (cpSegmentShape *)shape;
            renderer->drawSegment(cpVert2ccp(seg->ta), cpVert2ccp(seg->tb), cpfmax(seg->r, 2.0), color);
        }
            break;
		case CP_POLY_SHAPE:
        {
            cpPolyShape *poly = (cpPolyShape *)shape;
            ccColor4F line = color;
            line.a = cpflerp(color.a, 1.0, 0.5);
            CCPoint* pPoints = cpVertArray2ccpArrayN(poly->tVerts, poly->numVerts);
            renderer->drawPolygon(pPoints, poly->numVerts, color, 1.0, line);
            CC_SAFE_DELETE_ARRAY(pPoints);
        }
            break;
		default:
			cpAssertHard(false, "Bad assertion in DrawShape()");
	}
}

static ccColor4F CONSTRAINT_COLOR = {0, 1, 0, 0.5};

static void DrawConstraint(cpConstraint *constraint, CCDrawNode *renderer)
{
	cpBody *body_a = constraint->a;
	cpBody *body_b = constraint->b;
    
	const cpConstraintClass *klass = constraint->CP_PRIVATE(klass);
	if (klass == cpPinJointGetClass())
    {
		cpPinJoint *joint = (cpPinJoint *)constraint;
		
		cpVect a = cpBodyLocal2World(body_a, joint->anchr1);
		cpVect b = cpBodyLocal2World(body_b, joint->anchr2);
		
        renderer->drawDot(cpVert2ccp(a), 3.0, CONSTRAINT_COLOR);
        renderer->drawDot(cpVert2ccp(b), 3.0, CONSTRAINT_COLOR);
        renderer->drawSegment(cpVert2ccp(a), cpVert2ccp(b), 1.0, CONSTRAINT_COLOR);
	}
    else if (klass == cpSlideJointGetClass())
    {
		cpSlideJoint *joint = (cpSlideJoint *)constraint;
        
		cpVect a = cpBodyLocal2World(body_a, joint->anchr1);
		cpVect b = cpBodyLocal2World(body_b, joint->anchr2);
        
        renderer->drawDot(cpVert2ccp(a), 3.0, CONSTRAINT_COLOR);
        renderer->drawDot(cpVert2ccp(b), 3.0, CONSTRAINT_COLOR);
        renderer->drawSegment(cpVert2ccp(a), cpVert2ccp(b), 1.0, CONSTRAINT_COLOR);
	}
    else if (klass == cpPivotJointGetClass())
    {
		cpPivotJoint *joint = (cpPivotJoint *)constraint;
        
		cpVect a = cpBodyLocal2World(body_a, joint->anchr1);
		cpVect b = cpBodyLocal2World(body_b, joint->anchr2);
        
        renderer->drawDot(cpVert2ccp(a), 3.0, CONSTRAINT_COLOR);
        renderer->drawDot(cpVert2ccp(b), 3.0, CONSTRAINT_COLOR);
	}
    else if (klass == cpGrooveJointGetClass())
    {
		cpGrooveJoint *joint = (cpGrooveJoint *)constraint;
        
		cpVect a = cpBodyLocal2World(body_a, joint->grv_a);
		cpVect b = cpBodyLocal2World(body_a, joint->grv_b);
		cpVect c = cpBodyLocal2World(body_b, joint->anchr2);
        
        renderer->drawDot(cpVert2ccp(c), 3.0, CONSTRAINT_COLOR);
        renderer->drawSegment(cpVert2ccp(a), cpVert2ccp(b), 1.0, CONSTRAINT_COLOR);
	}
    else if (klass == cpDampedSpringGetClass())
    {
		// TODO
	}
    else
    {
        //		printf("Cannot draw constraint\n");
	}
}

// implementation of CCPhysicsDebugNode

void CCPhysicsDebugNode::draw()
{
    if (! m_pSpacePtr)
    {
        return;
    }
    
    cpSpaceEachShape(m_pSpacePtr, (cpSpaceShapeIteratorFunc)DrawShape, this);
	cpSpaceEachConstraint(m_pSpacePtr, (cpSpaceConstraintIteratorFunc)DrawConstraint, this);
    
    CCDrawNode::draw();
    CCDrawNode::clear();
}

CCPhysicsDebugNode::CCPhysicsDebugNode()
: m_pSpacePtr(NULL)
{}

CCPhysicsDebugNode* CCPhysicsDebugNode::create(cpSpace *space)
{
    CCPhysicsDebugNode *node = new CCPhysicsDebugNode();
    if (node)
    {
        node->init();
        
        node->m_pSpacePtr = space;
        
        node->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(node);
    }
    
    return node;
}

CCPhysicsDebugNode::~CCPhysicsDebugNode()
{
}

cpSpace* CCPhysicsDebugNode::getSpace() const
{
    return m_pSpacePtr;
}

void CCPhysicsDebugNode::setSpace(cpSpace *space)
{
    m_pSpacePtr = space;
}

NS_CC_EXT_END

#endif // CC_ENABLE_CHIPMUNK_INTEGRATION
