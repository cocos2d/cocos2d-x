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

#define CP_DefineClassGetter(t)													\
const cpConstraintClass * t##GetClass(void);									\
const cpConstraintClass * t##GetClass(){return (cpConstraintClass *)&klass;}

void cpConstraintInit(cpConstraint *constraint, const cpConstraintClass *klass, cpBody *a, cpBody *b);

#define J_MAX(constraint, dt) (((cpConstraint *)constraint)->maxForce*(dt))

// Get valid body pointers and exit early if the bodies are idle
#define CONSTRAINT_BEGIN(constraint, a_var, b_var) \
cpBody *a_var, *b_var; { \
	a_var = ((cpConstraint *)constraint)->a; \
	b_var = ((cpConstraint *)constraint)->b; \
	if( \
		(cpBodyIsSleeping(a_var) || cpBodyIsStatic(a_var)) && \
		(cpBodyIsSleeping(b_var) || cpBodyIsStatic(b_var)) \
	) return; \
}

static inline cpVect
relative_velocity(cpBody *a, cpBody *b, cpVect r1, cpVect r2){
	cpVect v1_sum = cpvadd(a->v, cpvmult(cpvperp(r1), a->w));
	cpVect v2_sum = cpvadd(b->v, cpvmult(cpvperp(r2), b->w));
	
	return cpvsub(v2_sum, v1_sum);
}

static inline cpFloat
normal_relative_velocity(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect n){
	return cpvdot(relative_velocity(a, b, r1, r2), n);
}

static inline void
apply_impulse(cpBody *body, cpVect j, cpVect r){
	body->v = cpvadd(body->v, cpvmult(j, body->m_inv));
	body->w += body->i_inv*cpvcross(r, j);
}

static inline void
apply_impulses(cpBody *a , cpBody *b, cpVect r1, cpVect r2, cpVect j)
{
	apply_impulse(a, cpvneg(j), r1);
	apply_impulse(b, j, r2);
}

static inline void
apply_bias_impulse(cpBody *body, cpVect j, cpVect r)
{
	body->v_bias = cpvadd(body->v_bias, cpvmult(j, body->m_inv));
	body->w_bias += body->i_inv*cpvcross(r, j);
}

static inline void
apply_bias_impulses(cpBody *a , cpBody *b, cpVect r1, cpVect r2, cpVect j)
{
	apply_bias_impulse(a, cpvneg(j), r1);
	apply_bias_impulse(b, j, r2);
}

static inline cpVect
clamp_vect(cpVect v, cpFloat len)
{
	return cpvclamp(v, len);
//	return (cpvdot(v,v) > len*len) ? cpvmult(cpvnormalize(v), len) : v;
}

static inline cpFloat
k_scalar(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect n)
{
	cpFloat mass_sum = a->m_inv + b->m_inv;
	cpFloat r1cn = cpvcross(r1, n);
	cpFloat r2cn = cpvcross(r2, n);
	
	cpFloat value = mass_sum + a->i_inv*r1cn*r1cn + b->i_inv*r2cn*r2cn;
	cpAssert(value != 0.0, "Unsolvable collision or constraint.");
	
	return value;
}

static inline void
k_tensor(cpBody *a, cpBody *b, cpVect r1, cpVect r2, cpVect *k1, cpVect *k2)
{
	// calculate mass matrix
	// If I wasn't lazy and wrote a proper matrix class, this wouldn't be so gross...
	cpFloat k11, k12, k21, k22;
	cpFloat m_sum = a->m_inv + b->m_inv;
	
	// start with I*m_sum
	k11 = m_sum; k12 = 0.0f;
	k21 = 0.0f;  k22 = m_sum;
	
	// add the influence from r1
	cpFloat a_i_inv = a->i_inv;
	cpFloat r1xsq =  r1.x * r1.x * a_i_inv;
	cpFloat r1ysq =  r1.y * r1.y * a_i_inv;
	cpFloat r1nxy = -r1.x * r1.y * a_i_inv;
	k11 += r1ysq; k12 += r1nxy;
	k21 += r1nxy; k22 += r1xsq;
	
	// add the influnce from r2
	cpFloat b_i_inv = b->i_inv;
	cpFloat r2xsq =  r2.x * r2.x * b_i_inv;
	cpFloat r2ysq =  r2.y * r2.y * b_i_inv;
	cpFloat r2nxy = -r2.x * r2.y * b_i_inv;
	k11 += r2ysq; k12 += r2nxy;
	k21 += r2nxy; k22 += r2xsq;
	
	// invert
	cpFloat determinant = k11*k22 - k12*k21;
	cpAssert(determinant != 0.0, "Unsolvable constraint.");
	
	cpFloat det_inv = 1.0f/determinant;
	*k1 = cpv( k22*det_inv, -k12*det_inv);
	*k2 = cpv(-k21*det_inv,  k11*det_inv);
}

static inline cpVect
mult_k(cpVect vr, cpVect k1, cpVect k2)
{
	return cpv(cpvdot(vr, k1), cpvdot(vr, k2));
}
