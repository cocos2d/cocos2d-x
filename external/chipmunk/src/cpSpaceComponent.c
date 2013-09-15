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
 
#include <string.h>

#include "chipmunk_private.h"

//MARK: Sleeping Functions

void
cpSpaceActivateBody(cpSpace *space, cpBody *body)
{
	cpAssertHard(!cpBodyIsRogue(body), "Internal error: Attempting to activate a rogue body.");
		
	if(space->locked){
		// cpSpaceActivateBody() is called again once the space is unlocked
		if(!cpArrayContains(space->rousedBodies, body)) cpArrayPush(space->rousedBodies, body);
	} else {
		cpAssertSoft(body->node.root == NULL && body->node.next == NULL, "Internal error: Activating body non-NULL node pointers.");
		cpArrayPush(space->bodies, body);

		CP_BODY_FOREACH_SHAPE(body, shape){
			cpSpatialIndexRemove(space->staticShapes, shape, shape->hashid);
			cpSpatialIndexInsert(space->activeShapes, shape, shape->hashid);
		}
		
		CP_BODY_FOREACH_ARBITER(body, arb){
			cpBody *bodyA = arb->body_a;
			
			// Arbiters are shared between two bodies that are always woken up together.
			// You only want to restore the arbiter once, so bodyA is arbitrarily chosen to own the arbiter.
			// The edge case is when static bodies are involved as the static bodies never actually sleep.
			// If the static body is bodyB then all is good. If the static body is bodyA, that can easily be checked.
			if(body == bodyA || cpBodyIsStatic(bodyA)){
				int numContacts = arb->numContacts;
				cpContact *contacts = arb->contacts;
				
				// Restore contact values back to the space's contact buffer memory
				arb->contacts = cpContactBufferGetArray(space);
				memcpy(arb->contacts, contacts, numContacts*sizeof(cpContact));
				cpSpacePushContacts(space, numContacts);
				
				// Reinsert the arbiter into the arbiter cache
				cpShape *a = arb->a, *b = arb->b;
				cpShape *shape_pair[] = {a, b};
				cpHashValue arbHashID = CP_HASH_PAIR((cpHashValue)a, (cpHashValue)b);
				cpHashSetInsert(space->cachedArbiters, arbHashID, shape_pair, arb, NULL);
				
				// Update the arbiter's state
				arb->stamp = space->stamp;
				arb->handler = cpSpaceLookupHandler(space, a->collision_type, b->collision_type);
				cpArrayPush(space->arbiters, arb);
				
				cpfree(contacts);
			}
		}
		
		CP_BODY_FOREACH_CONSTRAINT(body, constraint){
			cpBody *bodyA = constraint->a;
			if(body == bodyA || cpBodyIsStatic(bodyA)) cpArrayPush(space->constraints, constraint);
		}
	}
}

static void
cpSpaceDeactivateBody(cpSpace *space, cpBody *body)
{
	cpAssertHard(!cpBodyIsRogue(body), "Internal error: Attempting to deactivate a rouge body.");
	
	cpArrayDeleteObj(space->bodies, body);
	
	CP_BODY_FOREACH_SHAPE(body, shape){
		cpSpatialIndexRemove(space->activeShapes, shape, shape->hashid);
		cpSpatialIndexInsert(space->staticShapes, shape, shape->hashid);
	}
	
	CP_BODY_FOREACH_ARBITER(body, arb){
		cpBody *bodyA = arb->body_a;
		if(body == bodyA || cpBodyIsStatic(bodyA)){
			cpSpaceUncacheArbiter(space, arb);
			
			// Save contact values to a new block of memory so they won't time out
			size_t bytes = arb->numContacts*sizeof(cpContact);
			cpContact *contacts = (cpContact *)cpcalloc(1, bytes);
			memcpy(contacts, arb->contacts, bytes);
			arb->contacts = contacts;
		}
	}
		
	CP_BODY_FOREACH_CONSTRAINT(body, constraint){
		cpBody *bodyA = constraint->a;
		if(body == bodyA || cpBodyIsStatic(bodyA)) cpArrayDeleteObj(space->constraints, constraint);
	}
}

static inline cpBody *
ComponentRoot(cpBody *body)
{
	return (body ? body->node.root : NULL);
}

static inline void
ComponentActivate(cpBody *root)
{
	if(!root || !cpBodyIsSleeping(root)) return;
	cpAssertHard(!cpBodyIsRogue(root), "Internal Error: ComponentActivate() called on a rogue body.");
	
	cpSpace *space = root->space;
	cpBody *body = root;
	while(body){
		cpBody *next = body->node.next;
		
		body->node.idleTime = 0.0f;
		body->node.root = NULL;
		body->node.next = NULL;
		cpSpaceActivateBody(space, body);
		
		body = next;
	}
	
	cpArrayDeleteObj(space->sleepingComponents, root);
}

void
cpBodyActivate(cpBody *body)
{
	if(!cpBodyIsRogue(body)){
		body->node.idleTime = 0.0f;
		ComponentActivate(ComponentRoot(body));
	}
	
	CP_BODY_FOREACH_ARBITER(body, arb){
		// Reset the idle timer of things the body is touching as well.
		// That way things don't get left hanging in the air.
		cpBody *other = (arb->body_a == body ? arb->body_b : arb->body_a);
		if(!cpBodyIsStatic(other)) other->node.idleTime = 0.0f;
	}
}

void
cpBodyActivateStatic(cpBody *body, cpShape *filter)
{
	cpAssertHard(cpBodyIsStatic(body), "cpBodyActivateStatic() called on a non-static body.");
	
	CP_BODY_FOREACH_ARBITER(body, arb){
		if(!filter || filter == arb->a || filter == arb->b){
			cpBodyActivate(arb->body_a == body ? arb->body_b : arb->body_a);
		}
	}
	
	// TODO should also activate joints?
}

static inline void
cpBodyPushArbiter(cpBody *body, cpArbiter *arb)
{
	cpAssertSoft(cpArbiterThreadForBody(arb, body)->next == NULL, "Internal Error: Dangling contact graph pointers detected. (A)");
	cpAssertSoft(cpArbiterThreadForBody(arb, body)->prev == NULL, "Internal Error: Dangling contact graph pointers detected. (B)");
	
	cpArbiter *next = body->arbiterList;
	cpAssertSoft(next == NULL || cpArbiterThreadForBody(next, body)->prev == NULL, "Internal Error: Dangling contact graph pointers detected. (C)");
	cpArbiterThreadForBody(arb, body)->next = next;
	
	if(next) cpArbiterThreadForBody(next, body)->prev = arb;
	body->arbiterList = arb;
}

static inline void
ComponentAdd(cpBody *root, cpBody *body){
	body->node.root = root;

	if(body != root){
		body->node.next = root->node.next;
		root->node.next = body;
	}
}

static inline void
FloodFillComponent(cpBody *root, cpBody *body)
{
	// Rogue bodies cannot be put to sleep and prevent bodies they are touching from sleepining anyway.
	// Static bodies (which are a type of rogue body) are effectively sleeping all the time.
	if(!cpBodyIsRogue(body)){
		cpBody *other_root = ComponentRoot(body);
		if(other_root == NULL){
			ComponentAdd(root, body);
			CP_BODY_FOREACH_ARBITER(body, arb) FloodFillComponent(root, (body == arb->body_a ? arb->body_b : arb->body_a));
			CP_BODY_FOREACH_CONSTRAINT(body, constraint) FloodFillComponent(root, (body == constraint->a ? constraint->b : constraint->a));
		} else {
			cpAssertSoft(other_root == root, "Internal Error: Inconsistency dectected in the contact graph.");
		}
	}
}

static inline cpBool
ComponentActive(cpBody *root, cpFloat threshold)
{
	CP_BODY_FOREACH_COMPONENT(root, body){
		if(body->node.idleTime < threshold) return cpTrue;
	}
	
	return cpFalse;
}

void
cpSpaceProcessComponents(cpSpace *space, cpFloat dt)
{
	cpBool sleep = (space->sleepTimeThreshold != INFINITY);
	cpArray *bodies = space->bodies;
	
#ifndef NDEBUG
	for(int i=0; i<bodies->num; i++){
		cpBody *body = (cpBody*)bodies->arr[i];
		
		cpAssertSoft(body->node.next == NULL, "Internal Error: Dangling next pointer detected in contact graph.");
		cpAssertSoft(body->node.root == NULL, "Internal Error: Dangling root pointer detected in contact graph.");
	}
#endif
	
	// Calculate the kinetic energy of all the bodies.
	if(sleep){
		cpFloat dv = space->idleSpeedThreshold;
		cpFloat dvsq = (dv ? dv*dv : cpvlengthsq(space->gravity)*dt*dt);
		
		// update idling and reset component nodes
		for(int i=0; i<bodies->num; i++){
			cpBody *body = (cpBody*)bodies->arr[i];
			
			// Need to deal with infinite mass objects
			cpFloat keThreshold = (dvsq ? body->m*dvsq : 0.0f);
			body->node.idleTime = (cpBodyKineticEnergy(body) > keThreshold ? 0.0f : body->node.idleTime + dt);
		}
	}
	
	// Awaken any sleeping bodies found and then push arbiters to the bodies' lists.
	cpArray *arbiters = space->arbiters;
	for(int i=0, count=arbiters->num; i<count; i++){
		cpArbiter *arb = (cpArbiter*)arbiters->arr[i];
		cpBody *a = arb->body_a, *b = arb->body_b;
		
		if(sleep){
			if((cpBodyIsRogue(b) && !cpBodyIsStatic(b)) || cpBodyIsSleeping(a)) cpBodyActivate(a);
			if((cpBodyIsRogue(a) && !cpBodyIsStatic(a)) || cpBodyIsSleeping(b)) cpBodyActivate(b);
		}
		
		cpBodyPushArbiter(a, arb);
		cpBodyPushArbiter(b, arb);
	}
	
	if(sleep){
		// Bodies should be held active if connected by a joint to a non-static rouge body.
		cpArray *constraints = space->constraints;
		for(int i=0; i<constraints->num; i++){
			cpConstraint *constraint = (cpConstraint *)constraints->arr[i];
			cpBody *a = constraint->a, *b = constraint->b;
			
			if(cpBodyIsRogue(b) && !cpBodyIsStatic(b)) cpBodyActivate(a);
			if(cpBodyIsRogue(a) && !cpBodyIsStatic(a)) cpBodyActivate(b);
		}
		
		// Generate components and deactivate sleeping ones
		for(int i=0; i<bodies->num;){
			cpBody *body = (cpBody*)bodies->arr[i];
			
			if(ComponentRoot(body) == NULL){
				// Body not in a component yet. Perform a DFS to flood fill mark 
				// the component in the contact graph using this body as the root.
				FloodFillComponent(body, body);
				
				// Check if the component should be put to sleep.
				if(!ComponentActive(body, space->sleepTimeThreshold)){
					cpArrayPush(space->sleepingComponents, body);
					CP_BODY_FOREACH_COMPONENT(body, other) cpSpaceDeactivateBody(space, other);
					
					// cpSpaceDeactivateBody() removed the current body from the list.
					// Skip incrementing the index counter.
					continue;
				}
			}
			
			i++;
			
			// Only sleeping bodies retain their component node pointers.
			body->node.root = NULL;
			body->node.next = NULL;
		}
	}
}

void
cpBodySleep(cpBody *body)
{
	cpBodySleepWithGroup(body, NULL);
}

void
cpBodySleepWithGroup(cpBody *body, cpBody *group){
	cpAssertHard(!cpBodyIsRogue(body), "Rogue (and static) bodies cannot be put to sleep.");
	
	cpSpace *space = body->space;
	cpAssertHard(!space->locked, "Bodies cannot be put to sleep during a query or a call to cpSpaceStep(). Put these calls into a post-step callback.");
	cpAssertHard(group == NULL || cpBodyIsSleeping(group), "Cannot use a non-sleeping body as a group identifier.");
	
	if(cpBodyIsSleeping(body)){
		cpAssertHard(ComponentRoot(body) == ComponentRoot(group), "The body is already sleeping and it's group cannot be reassigned.");
		return;
	}
	
	CP_BODY_FOREACH_SHAPE(body, shape) cpShapeUpdate(shape, body->p, body->rot);
	cpSpaceDeactivateBody(space, body);
	
	if(group){
		cpBody *root = ComponentRoot(group);
		
		cpComponentNode node = {root, root->node.next, 0.0f};
		body->node = node;
		
		root->node.next = body;
	} else {
		cpComponentNode node = {body, NULL, 0.0f};
		body->node = node;
		
		cpArrayPush(space->sleepingComponents, body);
	}
	
	cpArrayDeleteObj(space->bodies, body);
}

static void
activateTouchingHelper(cpShape *shape, cpContactPointSet *points, cpShape *other){
	cpBodyActivate(shape->body);
}

void
cpSpaceActivateShapesTouchingShape(cpSpace *space, cpShape *shape){
	if(space->sleepTimeThreshold != INFINITY){
		cpSpaceShapeQuery(space, shape, (cpSpaceShapeQueryFunc)activateTouchingHelper, shape);
	}
}
