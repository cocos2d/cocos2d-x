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

#include "chipmunk_private.h"
#include "constraints/util.h"

cpContact*
cpContactInit(cpContact *con, cpVect p, cpVect n, cpFloat dist, cpHashValue hash)
{
	con->p = p;
	con->n = n;
	con->dist = dist;
	
	con->jnAcc = 0.0f;
	con->jtAcc = 0.0f;
	con->jBias = 0.0f;
	
	con->hash = hash;
		
	return con;
}

// TODO make this generic so I can reuse it for constraints also.
static inline void
unthreadHelper(cpArbiter *arb, cpBody *body)
{
	struct cpArbiterThread *thread = cpArbiterThreadForBody(arb, body);
	cpArbiter *prev = thread->prev;
	cpArbiter *next = thread->next;
	
	if(prev){
		cpArbiterThreadForBody(prev, body)->next = next;
	} else {
		body->arbiterList = next;
	}
	
	if(next) cpArbiterThreadForBody(next, body)->prev = prev;
	
	thread->prev = NULL;
	thread->next = NULL;
}

void
cpArbiterUnthread(cpArbiter *arb)
{
	unthreadHelper(arb, arb->body_a);
	unthreadHelper(arb, arb->body_b);
}

cpBool cpArbiterIsFirstContact(const cpArbiter *arb)
{
	return arb->CP_PRIVATE(state) == cpArbiterStateFirstColl;
}

int cpArbiterGetCount(const cpArbiter *arb)
{
	// Return 0 contacts if we are in a separate callback.
	return (arb->CP_PRIVATE(state) != cpArbiterStateCached ? arb->CP_PRIVATE(numContacts) : 0);
}

cpVect
cpArbiterGetNormal(const cpArbiter *arb, int i)
{
	cpAssertHard(0 <= i && i < cpArbiterGetCount(arb), "Index error: The specified contact index is invalid for this arbiter");
	
	cpVect n = arb->contacts[i].n;
	return arb->swappedColl ? cpvneg(n) : n;
}

cpVect
cpArbiterGetPoint(const cpArbiter *arb, int i)
{
	cpAssertHard(0 <= i && i < cpArbiterGetCount(arb), "Index error: The specified contact index is invalid for this arbiter");
	
	return arb->CP_PRIVATE(contacts)[i].CP_PRIVATE(p);
}

cpFloat
cpArbiterGetDepth(const cpArbiter *arb, int i)
{
	cpAssertHard(0 <= i && i < cpArbiterGetCount(arb), "Index error: The specified contact index is invalid for this arbiter");
	
	return arb->CP_PRIVATE(contacts)[i].CP_PRIVATE(dist);
}

cpContactPointSet
cpArbiterGetContactPointSet(const cpArbiter *arb)
{
	cpContactPointSet set;
	set.count = cpArbiterGetCount(arb);
	
	int i;
	for(i=0; i<set.count; i++){
		set.points[i].point = arb->CP_PRIVATE(contacts)[i].CP_PRIVATE(p);
		set.points[i].normal = arb->CP_PRIVATE(contacts)[i].CP_PRIVATE(n);
		set.points[i].dist = arb->CP_PRIVATE(contacts)[i].CP_PRIVATE(dist);
	}
	
	return set;
}


cpVect
cpArbiterTotalImpulse(const cpArbiter *arb)
{
	cpContact *contacts = arb->contacts;
	cpVect sum = cpvzero;
	
	for(int i=0, count=cpArbiterGetCount(arb); i<count; i++){
		cpContact *con = &contacts[i];
		sum = cpvadd(sum, cpvmult(con->n, con->jnAcc));
	}
	
	return (arb->swappedColl ? sum : cpvneg(sum));
}

cpVect
cpArbiterTotalImpulseWithFriction(const cpArbiter *arb)
{
	cpContact *contacts = arb->contacts;
	cpVect sum = cpvzero;
	
	for(int i=0, count=cpArbiterGetCount(arb); i<count; i++){
		cpContact *con = &contacts[i];
		sum = cpvadd(sum, cpvrotate(con->n, cpv(con->jnAcc, con->jtAcc)));
	}
		
	return (arb->swappedColl ? sum : cpvneg(sum));
}

cpFloat
cpArbiterTotalKE(const cpArbiter *arb)
{
	cpFloat eCoef = (1 - arb->e)/(1 + arb->e);
	cpFloat sum = 0.0;
	
	cpContact *contacts = arb->contacts;
	for(int i=0, count=cpArbiterGetCount(arb); i<count; i++){
		cpContact *con = &contacts[i];
		cpFloat jnAcc = con->jnAcc;
		cpFloat jtAcc = con->jtAcc;
		
		sum += eCoef*jnAcc*jnAcc/con->nMass + jtAcc*jtAcc/con->tMass;
	}
	
	return sum;
}

//cpFloat
//cpContactsEstimateCrushingImpulse(cpContact *contacts, int numContacts)
//{
//	cpFloat fsum = 0.0f;
//	cpVect vsum = cpvzero;
//	
//	for(int i=0; i<numContacts; i++){
//		cpContact *con = &contacts[i];
//		cpVect j = cpvrotate(con->n, cpv(con->jnAcc, con->jtAcc));
//		
//		fsum += cpvlength(j);
//		vsum = cpvadd(vsum, j);
//	}
//	
//	cpFloat vmag = cpvlength(vsum);
//	return (1.0f - vmag/fsum);
//}

void
cpArbiterIgnore(cpArbiter *arb)
{
	arb->state = cpArbiterStateIgnore;
}

cpArbiter*
cpArbiterInit(cpArbiter *arb, cpShape *a, cpShape *b)
{
	arb->handler = NULL;
	arb->swappedColl = cpFalse;
	
	arb->e = 0.0f;
	arb->u = 0.0f;
	arb->surface_vr = cpvzero;
	
	arb->numContacts = 0;
	arb->contacts = NULL;
	
	arb->a = a; arb->body_a = a->body;
	arb->b = b; arb->body_b = b->body;
	
	arb->thread_a.next = NULL;
	arb->thread_b.next = NULL;
	arb->thread_a.prev = NULL;
	arb->thread_b.prev = NULL;
	
	arb->stamp = 0;
	arb->state = cpArbiterStateFirstColl;
	
	arb->data = NULL;
	
	return arb;
}

void
cpArbiterUpdate(cpArbiter *arb, cpContact *contacts, int numContacts, cpCollisionHandler *handler, cpShape *a, cpShape *b)
{
	// Arbiters without contact data may exist if a collision function rejected the collision.
	if(arb->contacts){
		// Iterate over the possible pairs to look for hash value matches.
		for(int i=0; i<arb->numContacts; i++){
			cpContact *old = &arb->contacts[i];
			
			for(int j=0; j<numContacts; j++){
				cpContact *new_contact = &contacts[j];
				
				// This could trigger false positives, but is fairly unlikely nor serious if it does.
				if(new_contact->hash == old->hash){
					// Copy the persistant contact information.
					new_contact->jnAcc = old->jnAcc;
					new_contact->jtAcc = old->jtAcc;
				}
			}
		}
	}
	
	arb->contacts = contacts;
	arb->numContacts = numContacts;
	
	arb->handler = handler;
	arb->swappedColl = (a->collision_type != handler->a);
	
	arb->e = a->e * b->e;
	arb->u = a->u * b->u;
	arb->surface_vr = cpvsub(a->surface_v, b->surface_v);
	
	// For collisions between two similar primitive types, the order could have been swapped.
	arb->a = a; arb->body_a = a->body;
	arb->b = b; arb->body_b = b->body;
	
	// mark it as new if it's been cached
	if(arb->state == cpArbiterStateCached) arb->state = cpArbiterStateFirstColl;
}

void
cpArbiterPreStep(cpArbiter *arb, cpFloat dt, cpFloat slop, cpFloat bias)
{
	cpBody *a = arb->body_a;
	cpBody *b = arb->body_b;
	
	for(int i=0; i<arb->numContacts; i++){
		cpContact *con = &arb->contacts[i];
		
		// Calculate the offsets.
		con->r1 = cpvsub(con->p, a->p);
		con->r2 = cpvsub(con->p, b->p);
		
		// Calculate the mass normal and mass tangent.
		con->nMass = 1.0f/k_scalar(a, b, con->r1, con->r2, con->n);
		con->tMass = 1.0f/k_scalar(a, b, con->r1, con->r2, cpvperp(con->n));
				
		// Calculate the target bias velocity.
		con->bias = -bias*cpfmin(0.0f, con->dist + slop)/dt;
		con->jBias = 0.0f;
		
		// Calculate the target bounce velocity.
		con->bounce = normal_relative_velocity(a, b, con->r1, con->r2, con->n)*arb->e;
	}
}

void
cpArbiterApplyCachedImpulse(cpArbiter *arb, cpFloat dt_coef)
{
	if(cpArbiterIsFirstContact(arb)) return;
	
	cpBody *a = arb->body_a;
	cpBody *b = arb->body_b;
	
	for(int i=0; i<arb->numContacts; i++){
		cpContact *con = &arb->contacts[i];
		cpVect j = cpvrotate(con->n, cpv(con->jnAcc, con->jtAcc));
		apply_impulses(a, b, con->r1, con->r2, cpvmult(j, dt_coef));
	}
}

// TODO is it worth splitting velocity/position correction?

void
cpArbiterApplyImpulse(cpArbiter *arb)
{
	cpBody *a = arb->body_a;
	cpBody *b = arb->body_b;
	cpVect surface_vr = arb->surface_vr;
	cpFloat friction = arb->u;

	for(int i=0; i<arb->numContacts; i++){
		cpContact *con = &arb->contacts[i];
		cpFloat nMass = con->nMass;
		cpVect n = con->n;
		cpVect r1 = con->r1;
		cpVect r2 = con->r2;
		
		cpVect vb1 = cpvadd(a->v_bias, cpvmult(cpvperp(r1), a->w_bias));
		cpVect vb2 = cpvadd(b->v_bias, cpvmult(cpvperp(r2), b->w_bias));
		cpVect vr = relative_velocity(a, b, r1, r2);
		
		cpFloat vbn = cpvdot(cpvsub(vb2, vb1), n);
		cpFloat vrn = cpvdot(vr, n);
		cpFloat vrt = cpvdot(cpvadd(vr, surface_vr), cpvperp(n));
		
		cpFloat jbn = (con->bias - vbn)*nMass;
		cpFloat jbnOld = con->jBias;
		con->jBias = cpfmax(jbnOld + jbn, 0.0f);
		
		cpFloat jn = -(con->bounce + vrn)*nMass;
		cpFloat jnOld = con->jnAcc;
		con->jnAcc = cpfmax(jnOld + jn, 0.0f);
		
		cpFloat jtMax = friction*con->jnAcc;
		cpFloat jt = -vrt*con->tMass;
		cpFloat jtOld = con->jtAcc;
		con->jtAcc = cpfclamp(jtOld + jt, -jtMax, jtMax);
		
		apply_bias_impulses(a, b, r1, r2, cpvmult(n, con->jBias - jbnOld));
		apply_impulses(a, b, r1, r2, cpvrotate(n, cpv(con->jnAcc - jnOld, con->jtAcc - jtOld)));
	}
}
