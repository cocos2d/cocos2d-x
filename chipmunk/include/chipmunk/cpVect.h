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

static const cpVect cpvzero={0.0f,0.0f};

static inline cpVect
cpv(const cpFloat x, const cpFloat y)
{
	cpVect v = {x, y};
	return v;
}

// non-inlined functions
cpFloat cpvlength(const cpVect v);
cpVect cpvslerp(const cpVect v1, const cpVect v2, const cpFloat t);
cpVect cpvslerpconst(const cpVect v1, const cpVect v2, const cpFloat a);
cpVect cpvforangle(const cpFloat a); // convert radians to a normalized vector
cpFloat cpvtoangle(const cpVect v); // convert a vector to radians
char *cpvstr(const cpVect v); // get a string representation of a vector

static inline cpVect
cpvadd(const cpVect v1, const cpVect v2)
{
	return cpv(v1.x + v2.x, v1.y + v2.y);
}

static inline cpVect
cpvneg(const cpVect v)
{
	return cpv(-v.x, -v.y);
}

static inline cpVect
cpvsub(const cpVect v1, const cpVect v2)
{
	return cpv(v1.x - v2.x, v1.y - v2.y);
}

static inline cpVect
cpvmult(const cpVect v, const cpFloat s)
{
	return cpv(v.x*s, v.y*s);
}

static inline cpFloat
cpvdot(const cpVect v1, const cpVect v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

static inline cpFloat
cpvcross(const cpVect v1, const cpVect v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}

static inline cpVect
cpvperp(const cpVect v)
{
	return cpv(-v.y, v.x);
}

static inline cpVect
cpvrperp(const cpVect v)
{
	return cpv(v.y, -v.x);
}

static inline cpVect
cpvproject(const cpVect v1, const cpVect v2)
{
	return cpvmult(v2, cpvdot(v1, v2)/cpvdot(v2, v2));
}

static inline cpVect
cpvrotate(const cpVect v1, const cpVect v2)
{
	return cpv(v1.x*v2.x - v1.y*v2.y, v1.x*v2.y + v1.y*v2.x);
}

static inline cpVect
cpvunrotate(const cpVect v1, const cpVect v2)
{
	return cpv(v1.x*v2.x + v1.y*v2.y, v1.y*v2.x - v1.x*v2.y);
}

static inline cpFloat
cpvlengthsq(const cpVect v)
{
	return cpvdot(v, v);
}

static inline cpVect
cpvlerp(const cpVect v1, const cpVect v2, const cpFloat t)
{
	return cpvadd(cpvmult(v1, 1.0f - t), cpvmult(v2, t));
}

static inline cpVect
cpvnormalize(const cpVect v)
{
	return cpvmult(v, 1.0f/cpvlength(v));
}

static inline cpVect
cpvnormalize_safe(const cpVect v)
{
	return (v.x == 0.0f && v.y == 0.0f ? cpvzero : cpvnormalize(v));
}

static inline cpVect
cpvclamp(const cpVect v, const cpFloat len)
{
	return (cpvdot(v,v) > len*len) ? cpvmult(cpvnormalize(v), len) : v;
}

static inline cpVect
cpvlerpconst(cpVect v1, cpVect v2, cpFloat d)
{
	return cpvadd(v1, cpvclamp(cpvsub(v2, v1), d));
}

static inline cpFloat
cpvdist(const cpVect v1, const cpVect v2)
{
	return cpvlength(cpvsub(v1, v2));
}

static inline cpFloat
cpvdistsq(const cpVect v1, const cpVect v2)
{
	return cpvlengthsq(cpvsub(v1, v2));
}

static inline int
cpvnear(const cpVect v1, const cpVect v2, const cpFloat dist)
{
	return cpvdistsq(v1, v2) < dist*dist;
}
