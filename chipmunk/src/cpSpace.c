/* Copyright (c) 2007 Scott Lembcke
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
 
#include <stdlib.h>
//#include <stdio.h>
#include <string.h>
#include <math.h>

#include "chipmunk_private.h"

cpTimestamp cp_contact_persistence = 3;

#pragma mark Contact Set Helpers

// Equal function for contactSet.
static cpBool
contactSetEql(cpShape **shapes, cpArbiter *arb)
{
	cpShape *a = shapes[0];
	cpShape *b = shapes[1];
	
	return ((a == arb->a && b == arb->b) || (b == arb->a && a == arb->b));
}

// Transformation function for contactSet.
static void *
contactSetTrans(cpShape **shapes, cpSpace *space)
{
	if(space->pooledArbiters->num == 0){
		// arbiter pool is exhausted, make more
		int count = CP_BUFFER_BYTES/sizeof(cpArbiter);
		cpAssert(count, "Buffer size too small.");
		
		cpArbiter *buffer = (cpArbiter *)cpcalloc(1, CP_BUFFER_BYTES);
		cpArrayPush(space->allocatedBuffers, buffer);
		
		for(int i=0; i<count; i++) cpArrayPush(space->pooledArbiters, buffer + i);
	}
	
	return cpArbiterInit((cpArbiter *) cpArrayPop(space->pooledArbiters), shapes[0], shapes[1]);
}

#pragma mark Collision Pair Function Helpers

// Equals function for collFuncSet.
static cpBool
collFuncSetEql(cpCollisionHandler *check, cpCollisionHandler *pair)
{
	return ((check->a == pair->a && check->b == pair->b) || (check->b == pair->a && check->a == pair->b));
}

// Transformation function for collFuncSet.
static void *
collFuncSetTrans(cpCollisionHandler *handler, void *unused)
{
	cpCollisionHandler *copy = (cpCollisionHandler *)cpcalloc(1, sizeof(cpCollisionHandler));
	(*copy) = (*handler);
	
	return copy;
}

#pragma mark Misc Helper Funcs

// Default collision functions.
static cpBool alwaysCollide(cpArbiter *arb, cpSpace *space, void *data){return 1;}
static void nothing(cpArbiter *arb, cpSpace *space, void *data){}

// BBfunc callback for the spatial hash.
static cpBB shapeBBFunc(cpShape *shape){return shape->bb;}

// Iterator functions for destructors.
static void             freeWrap(void         *ptr, void *unused){            cpfree(ptr);}
static void        shapeFreeWrap(cpShape      *ptr, void *unused){     cpShapeFree(ptr);}
static void         bodyFreeWrap(cpBody       *ptr, void *unused){      cpBodyFree(ptr);}
static void   constraintFreeWrap(cpConstraint *ptr, void *unused){cpConstraintFree(ptr);}

#pragma mark Memory Management Functions

cpSpace *
cpSpaceAlloc(void)
{
	return (cpSpace *)cpcalloc(1, sizeof(cpSpace));
}

#define DEFAULT_DIM_SIZE 100.0f
#define DEFAULT_COUNT 1000
#define DEFAULT_ITERATIONS 10
#define DEFAULT_ELASTIC_ITERATIONS 0

cpCollisionHandler cpSpaceDefaultHandler = {0, 0, alwaysCollide, alwaysCollide, nothing, nothing, NULL};

cpSpace*
cpSpaceInit(cpSpace *space)
{
	space->iterations = DEFAULT_ITERATIONS;
	space->elasticIterations = DEFAULT_ELASTIC_ITERATIONS;
//	space->sleepTicks = 300;
	
	space->gravity = cpvzero;
	space->damping = 1.0f;
	
	space->locked = 0;
	space->stamp = 0;

	space->staticShapes = cpSpaceHashNew(DEFAULT_DIM_SIZE, DEFAULT_COUNT, (cpSpaceHashBBFunc)shapeBBFunc);
	space->activeShapes = cpSpaceHashNew(DEFAULT_DIM_SIZE, DEFAULT_COUNT, (cpSpaceHashBBFunc)shapeBBFunc);
	
	space->allocatedBuffers = cpArrayNew(0);
	
	space->bodies = cpArrayNew(0);
	space->sleepingComponents = cpArrayNew(0);
	space->rousedBodies = cpArrayNew(0);
	
	space->sleepTimeThreshold = INFINITY;
	space->idleSpeedThreshold = 0.0f;
	
	space->arbiters = cpArrayNew(0);
	space->pooledArbiters = cpArrayNew(0);
	
	space->contactBuffersHead = NULL;
	space->contactSet = cpHashSetNew(0, (cpHashSetEqlFunc)contactSetEql, (cpHashSetTransFunc)contactSetTrans);
	
	space->constraints = cpArrayNew(0);
	
	space->defaultHandler = cpSpaceDefaultHandler;
	space->collFuncSet = cpHashSetNew(0, (cpHashSetEqlFunc)collFuncSetEql, (cpHashSetTransFunc)collFuncSetTrans);
	space->collFuncSet->default_value = &cpSpaceDefaultHandler;
	
	space->postStepCallbacks = NULL;
	
	cpBodyInitStatic(&space->staticBody);
	
	return space;
}

cpSpace*
cpSpaceNew(void)
{
	return cpSpaceInit(cpSpaceAlloc());
}

void
cpSpaceDestroy(cpSpace *space)
{
	cpSpaceHashFree(space->staticShapes);
	cpSpaceHashFree(space->activeShapes);
	
	cpArrayFree(space->bodies);
	cpArrayFree(space->sleepingComponents);
	cpArrayFree(space->rousedBodies);
	
	cpArrayFree(space->constraints);
	
	cpHashSetFree(space->contactSet);
	
	cpArrayFree(space->arbiters);
	cpArrayFree(space->pooledArbiters);
	
	if(space->allocatedBuffers) cpArrayEach(space->allocatedBuffers, freeWrap, NULL);
	cpArrayFree(space->allocatedBuffers);
	
	if(space->postStepCallbacks) cpHashSetEach(space->postStepCallbacks, freeWrap, NULL);
	cpHashSetFree(space->postStepCallbacks);
	
	if(space->collFuncSet) cpHashSetEach(space->collFuncSet, freeWrap, NULL);
	cpHashSetFree(space->collFuncSet);
}

void
cpSpaceFree(cpSpace *space)
{
	if(space){
		cpSpaceDestroy(space);
		cpfree(space);
	}
}

void
cpSpaceFreeChildren(cpSpace *space)
{
	cpArray *components = space->sleepingComponents;
	while(components->num) cpBodyActivate((cpBody *)components->arr[0]);
	
	cpSpaceHashEach(space->staticShapes, (cpSpaceHashIterator)&shapeFreeWrap, NULL);
	cpSpaceHashEach(space->activeShapes, (cpSpaceHashIterator)&shapeFreeWrap, NULL);
	cpArrayEach(space->bodies,           (cpArrayIter)&bodyFreeWrap,          NULL);
	cpArrayEach(space->constraints,      (cpArrayIter)&constraintFreeWrap,    NULL);
}

#define cpAssertSpaceUnlocked(space) \
	cpAssert(!space->locked, \
		"This addition/removal cannot be done safely during a call to cpSpaceStep() or during a query. " \
		"Put these calls into a post-step callback." \
	);

#pragma mark Collision Handler Function Management

void
cpSpaceAddCollisionHandler(
	cpSpace *space,
	cpCollisionType a, cpCollisionType b,
	cpCollisionBeginFunc begin,
	cpCollisionPreSolveFunc preSolve,
	cpCollisionPostSolveFunc postSolve,
	cpCollisionSeparateFunc separate,
	void *data
){
	cpAssertSpaceUnlocked(space);
	
	// Remove any old function so the new one will get added.
	cpSpaceRemoveCollisionHandler(space, a, b);
	
	cpCollisionHandler handler = {
		a, b,
		begin ? begin : alwaysCollide,
		preSolve ? preSolve : alwaysCollide,
		postSolve ? postSolve : nothing,
		separate ? separate : nothing,
		data
	};
	
	cpHashSetInsert(space->collFuncSet, CP_HASH_PAIR(a, b), &handler, NULL);
}

void
cpSpaceRemoveCollisionHandler(cpSpace *space, cpCollisionType a, cpCollisionType b)
{
	cpAssertSpaceUnlocked(space);
	
	struct{cpCollisionType a, b;} ids = {a, b};
	cpCollisionHandler *old_handler = (cpCollisionHandler *) cpHashSetRemove(space->collFuncSet, CP_HASH_PAIR(a, b), &ids);
	cpfree(old_handler);
}

void
cpSpaceSetDefaultCollisionHandler(
	cpSpace *space,
	cpCollisionBeginFunc begin,
	cpCollisionPreSolveFunc preSolve,
	cpCollisionPostSolveFunc postSolve,
	cpCollisionSeparateFunc separate,
	void *data
){
	cpAssertSpaceUnlocked(space);
	
	cpCollisionHandler handler = {
		0, 0,
		begin ? begin : alwaysCollide,
		preSolve ? preSolve : alwaysCollide,
		postSolve ? postSolve : nothing,
		separate ? separate : nothing,
		data
	};
	
	space->defaultHandler = handler;
	space->collFuncSet->default_value = &space->defaultHandler;
}

#pragma mark Body, Shape, and Joint Management
static void
cpBodyAddShape(cpBody *body, cpShape *shape)
{
	shape->next = shape->body->shapesList;
	shape->body->shapesList = shape;
}

static void
cpBodyRemoveShape(cpBody *body, cpShape *shape)
{
	cpShape **prev_ptr = &body->shapesList;
	cpShape *node = body->shapesList;
	
	while(node && node != shape){
		prev_ptr = &node->next;
		node = node->next;
	}
	
	cpAssert(node, "Attempted to remove a shape from a body it was never attached to.");
	(*prev_ptr) = node->next;
}

cpShape *
cpSpaceAddShape(cpSpace *space, cpShape *shape)
{
	cpBody *body = shape->body;
	if(!body || cpBodyIsStatic(body)) return cpSpaceAddStaticShape(space, shape);
	
	cpAssert(!cpHashSetFind(space->activeShapes->handleSet, shape->hashid, shape),
		"Cannot add the same shape more than once.");
	cpAssertSpaceUnlocked(space);
	
	cpBodyActivate(body);
	cpBodyAddShape(body, shape);
	
	cpShapeCacheBB(shape);
	cpSpaceHashInsert(space->activeShapes, shape, shape->hashid, shape->bb);
		
	return shape;
}

cpShape *
cpSpaceAddStaticShape(cpSpace *space, cpShape *shape)
{
	cpAssert(!cpHashSetFind(space->staticShapes->handleSet, shape->hashid, shape),
		"Cannot add the same static shape more than once.");
	cpAssertSpaceUnlocked(space);
	
	if(!shape->body) shape->body = &space->staticBody;
	
	cpShapeCacheBB(shape);
	cpSpaceActivateShapesTouchingShape(space, shape);
	cpSpaceHashInsert(space->staticShapes, shape, shape->hashid, shape->bb);
	
	return shape;
}

cpBody *
cpSpaceAddBody(cpSpace *space, cpBody *body)
{
	cpAssertWarn(!cpBodyIsStatic(body), "Static bodies cannot be added to a space as they are not meant to be simulated.");
	cpAssert(!body->space, "Cannot add a body to a more than one space or to the same space twice.");
//	cpAssertSpaceUnlocked(space); This should be safe as long as it's not from an integration callback
	
	cpArrayPush(space->bodies, body);
	body->space = space;
	
	return body;
}

cpConstraint *
cpSpaceAddConstraint(cpSpace *space, cpConstraint *constraint)
{
	cpAssert(!cpArrayContains(space->constraints, constraint), "Cannot add the same constraint more than once.");
//	cpAssertSpaceUnlocked(space); This should be safe as long as its not from a constraint callback.
	
	if(!constraint->a) constraint->a = &space->staticBody;
	if(!constraint->b) constraint->b = &space->staticBody;
	
	cpBodyActivate(constraint->a);
	cpBodyActivate(constraint->b);
	cpArrayPush(space->constraints, constraint);
	
	return constraint;
}

typedef struct removalContext {
	cpSpace *space;
	cpShape *shape;
} removalContext;

// Hashset filter func to throw away old arbiters.
static cpBool
contactSetFilterRemovedShape(cpArbiter *arb, removalContext *context)
{
	if(context->shape == arb->a || context->shape == arb->b){
		if(arb->state != cpArbiterStateCached){
			arb->handler->separate(arb, context->space, arb->handler->data);
		}
		
		cpArrayPush(context->space->pooledArbiters, arb);
		return cpFalse;
	}
	
	return cpTrue;
}

void
cpSpaceRemoveShape(cpSpace *space, cpShape *shape)
{
	cpBody *body = shape->body;
	if(cpBodyIsStatic(body)){
		cpSpaceRemoveStaticShape(space, shape);
		return;
	}

	cpBodyActivate(body);
	
	cpAssertSpaceUnlocked(space);
	cpAssertWarn(cpHashSetFind(space->activeShapes->handleSet, shape->hashid, shape),
		"Cannot remove a shape that was not added to the space. (Removed twice maybe?)");
	
	cpBodyRemoveShape(body, shape);
	
	removalContext context = {space, shape};
	cpHashSetFilter(space->contactSet, (cpHashSetFilterFunc)contactSetFilterRemovedShape, &context);
	cpSpaceHashRemove(space->activeShapes, shape, shape->hashid);
}

void
cpSpaceRemoveStaticShape(cpSpace *space, cpShape *shape)
{
	cpAssertWarn(cpHashSetFind(space->staticShapes->handleSet, shape->hashid, shape),
		"Cannot remove a static or sleeping shape that was not added to the space. (Removed twice maybe?)");
	cpAssertSpaceUnlocked(space);
	
	removalContext context = {space, shape};
	cpHashSetFilter(space->contactSet, (cpHashSetFilterFunc)contactSetFilterRemovedShape, &context);
	cpSpaceHashRemove(space->staticShapes, shape, shape->hashid);
	
	cpSpaceActivateShapesTouchingShape(space, shape);
}

void
cpSpaceRemoveBody(cpSpace *space, cpBody *body)
{
	cpAssertWarn(body->space == space,
		"Cannot remove a body that was not added to the space. (Removed twice maybe?)");
	cpAssertSpaceUnlocked(space);
	
	cpBodyActivate(body);
	cpArrayDeleteObj(space->bodies, body);
	body->space = NULL;
}

void
cpSpaceRemoveConstraint(cpSpace *space, cpConstraint *constraint)
{
	cpAssertWarn(cpArrayContains(space->constraints, constraint),
		"Cannot remove a constraint that was not added to the space. (Removed twice maybe?)");
//	cpAssertSpaceUnlocked(space); Should be safe as long as its not from a constraint callback.
	
	cpBodyActivate(constraint->a);
	cpBodyActivate(constraint->b);
	cpArrayDeleteObj(space->constraints, constraint);
}

#pragma mark Spatial Hash Management

static void updateBBCache(cpShape *shape, void *unused){cpShapeCacheBB(shape);}

void
cpSpaceResizeStaticHash(cpSpace *space, cpFloat dim, int count)
{
	cpSpaceHashResize(space->staticShapes, dim, count);
	cpSpaceHashRehash(space->staticShapes);
}

void
cpSpaceResizeActiveHash(cpSpace *space, cpFloat dim, int count)
{
	cpSpaceHashResize(space->activeShapes, dim, count);
}

void 
cpSpaceRehashStatic(cpSpace *space)
{
	cpSpaceHashEach(space->staticShapes, (cpSpaceHashIterator)&updateBBCache, NULL);
	cpSpaceHashRehash(space->staticShapes);
}

void
cpSpaceRehashShape(cpSpace *space, cpShape *shape)
{
	cpShapeCacheBB(shape);
	
	// attempt to rehash the shape in both hashes
	cpSpaceHashRehashObject(space->activeShapes, shape, shape->hashid);
	cpSpaceHashRehashObject(space->staticShapes, shape, shape->hashid);
}

void
cpSpaceEachBody(cpSpace *space, cpSpaceBodyIterator func, void *data)
{
	cpSpaceLock(space); {
		cpArray *bodies = space->bodies;
		
		for(int i=0; i<bodies->num; i++){
			func((cpBody *)bodies->arr[i], data);
		}
		
		cpArray *components = space->sleepingComponents;
		for(int i=0; i<components->num; i++){
			cpBody *root = (cpBody *)components->arr[i];
			cpBody *body = root, *next;
			do {
				next = body->node.next;
				func(body, data);
			} while((body = next) != root);
		}
	} cpSpaceUnlock(space);
}


