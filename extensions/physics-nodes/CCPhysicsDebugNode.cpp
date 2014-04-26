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
#include "chipmunk.h"
#endif

#include "2d/ccTypes.h"
#include "base/CCGeometry.h"


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>

NS_CC_EXT_BEGIN

#if CC_ENABLE_CHIPMUNK_INTEGRATION
/*
 IMPORTANT - READ ME!
 
 This file sets pokes around in the private API a lot to provide efficient
 debug rendering given nothing more than reference to a Chipmunk space.
 It is not recommended to write rendering code like this in your own games
 as the private API may change with little or no warning.
 */

static Color4F ColorForBody(cpBody *body)
{
	if (cpBodyIsRogue(body) || cpBodyIsSleeping(body))
    {
		return Color4F(0.5f, 0.5f, 0.5f ,0.5f);
	}
    else if (body->CP_PRIVATE(node).idleTime > body->CP_PRIVATE(space)->sleepTimeThreshold)
    {
		return Color4F(0.33f, 0.33f, 0.33f, 0.5f);
	}
    else
    {
		return Color4F(1.0f, 0.0f, 0.0f, 0.5f);
	}
}

static Vector2 cpVert2Point(const cpVect &vert)
{
    return Vector2(vert.x, vert.y);
}

static Vector2* cpVertArray2ccpArrayN(const cpVect* cpVertArray, unsigned int count)
{
    if (count == 0) return NULL;
    Vector2* pPoints = new Vector2[count];
    
    for (unsigned int i = 0; i < count; ++i)
    {
        pPoints[i].x = cpVertArray[i].x;
        pPoints[i].y = cpVertArray[i].y;
    }
    return pPoints;
}

static void DrawShape(cpShape *shape, DrawNode *renderer)
{
	cpBody *body = shape->body;
	Color4F color = ColorForBody(body);
    
	switch (shape->CP_PRIVATE(klass)->type)
    {
		case CP_CIRCLE_SHAPE:
        {
            cpCircleShape *circle = (cpCircleShape *)shape;
            cpVect center = circle->tc;
            cpFloat radius = circle->r;
            renderer->drawDot(cpVert2Point(center), cpfmax(radius, 1.0), color);
            renderer->drawSegment(cpVert2Point(center), cpVert2Point(cpvadd(center, cpvmult(body->rot, radius))), 1.0, color);
        }
             break;
		case CP_SEGMENT_SHAPE:
        {
            cpSegmentShape *seg = (cpSegmentShape *)shape;
            renderer->drawSegment(cpVert2Point(seg->ta), cpVert2Point(seg->tb), cpfmax(seg->r, 2.0), color);
        }
            break;
		case CP_POLY_SHAPE:
        {
            cpPolyShape *poly = (cpPolyShape *)shape;
            Color4F line = color;
            line.a = cpflerp(color.a, 1.0, 0.5);
            Vector2* pPoints = cpVertArray2ccpArrayN(poly->tVerts, poly->numVerts);
            renderer->drawPolygon(pPoints, poly->numVerts, color, 1.0, line);
            CC_SAFE_DELETE_ARRAY(pPoints);
        }
            break;
		default:
			cpAssertHard(false, "Bad assertion in DrawShape()");
	}
}

static Color4F CONSTRAINT_COLOR(0, 1, 0, 0.5);

static void DrawConstraint(cpConstraint *constraint, DrawNode *renderer)
{
	cpBody *body_a = constraint->a;
	cpBody *body_b = constraint->b;
    
	const cpConstraintClass *klass = constraint->CP_PRIVATE(klass);
	if (klass == cpPinJointGetClass())
    {
		cpPinJoint *joint = (cpPinJoint *)constraint;
		
		cpVect a = cpBodyLocal2World(body_a, joint->anchr1);
		cpVect b = cpBodyLocal2World(body_b, joint->anchr2);
		
        renderer->drawDot(cpVert2Point(a), 3.0, CONSTRAINT_COLOR);
        renderer->drawDot(cpVert2Point(b), 3.0, CONSTRAINT_COLOR);
        renderer->drawSegment(cpVert2Point(a), cpVert2Point(b), 1.0, CONSTRAINT_COLOR);
	}
    else if (klass == cpSlideJointGetClass())
    {
		cpSlideJoint *joint = (cpSlideJoint *)constraint;
        
		cpVect a = cpBodyLocal2World(body_a, joint->anchr1);
		cpVect b = cpBodyLocal2World(body_b, joint->anchr2);
        
        renderer->drawDot(cpVert2Point(a), 3.0, CONSTRAINT_COLOR);
        renderer->drawDot(cpVert2Point(b), 3.0, CONSTRAINT_COLOR);
        renderer->drawSegment(cpVert2Point(a), cpVert2Point(b), 1.0, CONSTRAINT_COLOR);
	}
    else if (klass == cpPivotJointGetClass())
    {
		cpPivotJoint *joint = (cpPivotJoint *)constraint;
        
		cpVect a = cpBodyLocal2World(body_a, joint->anchr1);
		cpVect b = cpBodyLocal2World(body_b, joint->anchr2);
        
        renderer->drawDot(cpVert2Point(a), 3.0, CONSTRAINT_COLOR);
        renderer->drawDot(cpVert2Point(b), 3.0, CONSTRAINT_COLOR);
	}
    else if (klass == cpGrooveJointGetClass())
    {
		cpGrooveJoint *joint = (cpGrooveJoint *)constraint;
        
		cpVect a = cpBodyLocal2World(body_a, joint->grv_a);
		cpVect b = cpBodyLocal2World(body_a, joint->grv_b);
		cpVect c = cpBodyLocal2World(body_b, joint->anchr2);
        
        renderer->drawDot(cpVert2Point(c), 3.0, CONSTRAINT_COLOR);
        renderer->drawSegment(cpVert2Point(a), cpVert2Point(b), 1.0, CONSTRAINT_COLOR);
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
#endif // #if CC_ENABLE_CHIPMUNK_INTEGRATION

// implementation of PhysicsDebugNode

void PhysicsDebugNode::draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
{
    if (! _spacePtr)
    {
        return;
    }
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    // clear the shapes information before draw current shapes.
    DrawNode::clear();

    cpSpaceEachShape(_spacePtr, (cpSpaceShapeIteratorFunc)DrawShape, this);
	cpSpaceEachConstraint(_spacePtr, (cpSpaceConstraintIteratorFunc)DrawConstraint, this);
    
    DrawNode::draw(renderer, transform, transformUpdated);
#endif
}

PhysicsDebugNode::PhysicsDebugNode()
: _spacePtr(nullptr)
{}

PhysicsDebugNode* PhysicsDebugNode::create(cpSpace *space)
{
    PhysicsDebugNode *node = new PhysicsDebugNode();
    if (node)
    {
        node->init();
#if CC_ENABLE_CHIPMUNK_INTEGRATION
        node->_spacePtr = space;
#else
        CCASSERT(false, "CC_ENABLE_CHIPMUNK_INTEGRATION was not enabled!");
#endif
        node->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(node);
    }
    
    return node;
}

PhysicsDebugNode::~PhysicsDebugNode()
{
}

cpSpace* PhysicsDebugNode::getSpace() const
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    return _spacePtr;
#else
    CCASSERT(false, "Can't call chipmunk methods when Chipmunk is disabled");
    return nullptr;
#endif
}

void PhysicsDebugNode::setSpace(cpSpace *space)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    _spacePtr = space;
#else
    CCASSERT(false, "Can't call chipmunk methods when Chipmunk is disabled");
#endif
}

NS_CC_EXT_END
