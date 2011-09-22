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

#include "chipmunk_private.h"
#include "constraints/util.h"

cpFloat cpContactsEstimateCrushingImpulse(cpContact *contacts, int numContacts);
cpArbiter* cpArbiterAlloc(void);
cpArbiter* cpArbiterNew(cpShape *a, cpShape *b);
void cpArbiterDestroy(cpArbiter *arb);
void cpArbiterFree(cpArbiter *arb);


cpFloat cp_bias_coef = 0.1f;
cpFloat cp_collision_slop = 0.1f;

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

cpVect
cpArbiterTotalImpulse(cpArbiter *arb)
{
	cpContact *contacts = arb->contacts;
	cpVect sum = cpvzero;
	
	for(int i=0, count=arb->numContacts; i<count; i++){
		cpContact *con = &contacts[i];
		sum = cpvadd(sum, cpvmult(con->n, con->jnAcc));
	}
		
	return sum;
}

cpVect
cpArbiterTotalImpulseWithFriction(cpArbiter *arb)
{
	cpContact *contacts = arb->contacts;
	cpVect sum = cpvzero;
	
	for(int i=0, count=arb->numContacts; i<count; i++){
		cpContact *con = &contacts[i];
		sum = cpvadd(sum, cpvrotate(con->n, cpv(con->jnAcc, con->jtAcc)));
	}
		
	return sum;
}

cpFloat
cpContactsEstimateCrushingImpulse(cpContact *contacts, int numContacts)
{
	cpFloat fsum = 0.0f;
	cpVect vsum = cpvzero;
	
	for(int i=0; i<numContacts; i++){
		cpContact *con = &contacts[i];
		cpVect j = cpvrotate(con->n, cpv(con->jnAcc, con->jtAcc));
		
		fsum += cpvlength(j);
		vsum = cpvadd(vsum, j);
	}
	
	cpFloat vmag = cpvlength(vsum);
	return (1.0f - vmag/fsum);
}

void
cpArbiterIgnore(cpArbiter *arb)
{
	arb->state = cpArbiterStateIgnore;
}

cpArbiter*
cpArbiterAlloc(void)
{
	return (cpArbiter *)cpcalloc(1, sizeof(cpArbiter));
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
	
	arb->a = a;
	arb->b = b;
	
	arb->stamp = 0;
	arb->state = cpArbiterStateFirstColl;
	
	return arb;
}

cpArbiter*
cpArbiterNew(cpShape *a, cpShape *b)
{
	return cpArbiterInit(cpArbiterAlloc(), a, b);
}

void
cpArbiterDestroy(cpArbiter *arb)
{
//	if(arb->contacts) cpfree(arb->contacts);
}

void
cpArbiterFree(cpArbiter *arb)
{
	if(arb){
		cpArbiterDestroy(arb);
		cpfree(arb);
	}
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
	arb->a = a;
	arb->b = b;
	
	// mark it as new if it's been cached
	if(arb->state == cpArbiterStateCached) arb->state = cpArbiterStateFirstColl;
}

void
cpArbiterPreStep(cpArbiter *arb, cpFloat dt_inv)
{
	cpBody *a = arb->a->body;
	cpBody *b = arb->b->body;
	
	for(int i=0; i<arb->numContacts; i++){
		cpContact *con = &arb->contacts[i];
		
		// Calculate the offsets.
		con->r1 = cpvsub(con->p, a->p);
		con->r2 = cpvsub(con->p, b->p);
		
		// Calculate the mass normal and mass tangent.
		con->nMass = 1.0f/k_scalar(a, b, con->r1, con->r2, con->n);
		con->tMass = 1.0f/k_scalar(a, b, con->r1, con->r2, cpvperp(con->n));
				
		// Calculate the target bias velocity.
		con->bias = -cp_bias_coef*dt_inv*cpfmin(0.0f, con->dist + cp_collision_slop);
		con->jBias = 0.0f;
		
		// Calculate the target bounce velocity.
		con->bounce = normal_relative_velocity(a, b, con->r1, con->r2, con->n)*arb->e;//cpvdot(con->n, cpvsub(v2, v1))*e;
	}
}

void
cpArbiterApplyCachedImpulse(cpArbiter *arb)
{
	cpShape *shapea = arb->a;
	cpShape *shapeb = arb->b;
		
	arb->u = shapea->u * shapeb->u;
	arb->surface_vr = cpvsub(shapeb->surface_v, shapea->surface_v);

	cpBody *a = shapea->body;
	cpBody *b = shapeb->body;
	
	for(int i=0; i<arb->numContacts; i++){
		cpContact *con = &arb->contacts[i];
		apply_impulses(a, b, con->r1, con->r2, cpvrotate(con->n, cpv(con->jnAcc, con->jtAcc)));
	}
}

void
cpArbiterApplyImpulse(cpArbiter *arb, cpFloat eCoef)
{
	cpBody *a = arb->a->body;
	cpBody *b = arb->b->body;

	for(int i=0; i<arb->numContacts; i++){
		cpContact *con = &arb->contacts[i];
		cpVect n = con->n;
		cpVect r1 = con->r1;
		cpVect r2 = con->r2;
		
		// Calculate the relative bias velocities.
		cpVect vb1 = cpvadd(a->v_bias, cpvmult(cpvperp(r1), a->w_bias));
		cpVect vb2 = cpvadd(b->v_bias, cpvmult(cpvperp(r2), b->w_bias));
		cpFloat vbn = cpvdot(cpvsub(vb2, vb1), n);
		
		// Calculate and clamp the bias impulse.
		cpFloat jbn = (con->bias - vbn)*con->nMass;
		cpFloat jbnOld = con->jBias;
		con->jBias = cpfmax(jbnOld + jbn, 0.0f);
		jbn = con->jBias - jbnOld;
		
		// Apply the bias impulse.
		apply_bias_impulses(a, b, r1, r2, cpvmult(n, jbn));

		// Calculate the relative velocity.
		cpVect vr = relative_velocity(a, b, r1, r2);
		cpFloat vrn = cpvdot(vr, n);
		
		// Calculate and clamp the normal impulse.
		cpFloat jn = -(con->bounce*eCoef + vrn)*con->nMass;
		cpFloat jnOld = con->jnAcc;
		con->jnAcc = cpfmax(jnOld + jn, 0.0f);
		jn = con->jnAcc - jnOld;
		
		// Calculate the relative tangent velocity.
		cpFloat vrt = cpvdot(cpvadd(vr, arb->surface_vr), cpvperp(n));
		
		// Calculate and clamp the friction impulse.
		cpFloat jtMax = arb->u*con->jnAcc;
		cpFloat jt = -vrt*con->tMass;
		cpFloat jtOld = con->jtAcc;
		con->jtAcc = cpfclamp(jtOld + jt, -jtMax, jtMax);
		jt = con->jtAcc - jtOld;
		
		// Apply the final impulse.
		apply_impulses(a, b, r1, r2, cpvrotate(n, cpv(jn, jt)));
	}
}
