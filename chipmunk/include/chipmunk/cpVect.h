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

/// @defgroup cpVect cpVect
/// Chipmunk's 2D vector type along with a handy 2D vector math lib.
/// @{

/// Constant for the zero vector.
static const cpVect cpvzero = {0.0f,0.0f};

/// Convenience constructor for cpVect structs.
static inline cpVect cpv(const cpFloat x, const cpFloat y)
{
	cpVect v = {x, y};
	return v;
}

/// Returns the length of v.
cpFloat cpvlength(const cpVect v);

/// Spherical linearly interpolate between v1 and v2.
cpVect cpvslerp(const cpVect v1, const cpVect v2, const cpFloat t);

/// Spherical linearly interpolate between v1 towards v2 by no more than angle a radians
cpVect cpvslerpconst(const cpVect v1, const cpVect v2, const cpFloat a);

/// Returns the unit length vector for the given angle (in radians).
cpVect cpvforangle(const cpFloat a);

/// Returns the angular direction v is pointing in (in radians).
cpFloat cpvtoangle(const cpVect v);

///	Returns a string representation of v. Intended mostly for debugging purposes and not production use.
///	@attention The string points to a static local and is reset every time the function is called.
///	If you want to print more than one vector you will have to split up your printing onto separate lines.
char* cpvstr(const cpVect v);

/// Check if two vectors are equal. (Be careful when comparing floating point numbers!)
static inline cpBool cpveql(const cpVect v1, const cpVect v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

/// Add two vectors
static inline cpVect cpvadd(const cpVect v1, const cpVect v2)
{
	return cpv(v1.x + v2.x, v1.y + v2.y);
}

/// Subtract two vectors.
static inline cpVect cpvsub(const cpVect v1, const cpVect v2)
{
	return cpv(v1.x - v2.x, v1.y - v2.y);
}

/// Negate a vector.
static inline cpVect cpvneg(const cpVect v)
{
	return cpv(-v.x, -v.y);
}

/// Scalar multiplication.
static inline cpVect cpvmult(const cpVect v, const cpFloat s)
{
	return cpv(v.x*s, v.y*s);
}

/// Vector dot product.
static inline cpFloat cpvdot(const cpVect v1, const cpVect v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

/// 2D vector cross product analog.
/// The cross product of 2D vectors results in a 3D vector with only a z component.
/// This function returns the magnitude of the z value.
static inline cpFloat cpvcross(const cpVect v1, const cpVect v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}

/// Returns a perpendicular vector. (90 degree rotation)
static inline cpVect cpvperp(const cpVect v)
{
	return cpv(-v.y, v.x);
}

/// Returns a perpendicular vector. (-90 degree rotation)
static inline cpVect cpvrperp(const cpVect v)
{
	return cpv(v.y, -v.x);
}

/// Returns the vector projection of v1 onto v2.
static inline cpVect cpvproject(const cpVect v1, const cpVect v2)
{
	return cpvmult(v2, cpvdot(v1, v2)/cpvdot(v2, v2));
}

/// Uses complex number multiplication to rotate v1 by v2. Scaling will occur if v1 is not a unit vector.
static inline cpVect cpvrotate(const cpVect v1, const cpVect v2)
{
	return cpv(v1.x*v2.x - v1.y*v2.y, v1.x*v2.y + v1.y*v2.x);
}

/// Inverse of cpvrotate().
static inline cpVect cpvunrotate(const cpVect v1, const cpVect v2)
{
	return cpv(v1.x*v2.x + v1.y*v2.y, v1.y*v2.x - v1.x*v2.y);
}

/// Returns the squared length of v. Faster than cpvlength() when you only need to compare lengths.
static inline cpFloat cpvlengthsq(const cpVect v)
{
	return cpvdot(v, v);
}

/// Linearly interpolate between v1 and v2.
static inline cpVect cpvlerp(const cpVect v1, const cpVect v2, const cpFloat t)
{
	return cpvadd(cpvmult(v1, 1.0f - t), cpvmult(v2, t));
}

/// Returns a normalized copy of v.
static inline cpVect cpvnormalize(const cpVect v)
{
	return cpvmult(v, 1.0f/cpvlength(v));
}

/// Returns a normalized copy of v or cpvzero if v was already cpvzero. Protects against divide by zero errors.
static inline cpVect cpvnormalize_safe(const cpVect v)
{
	return (v.x == 0.0f && v.y == 0.0f ? cpvzero : cpvnormalize(v));
}

/// Clamp v to length len.
static inline cpVect cpvclamp(const cpVect v, const cpFloat len)
{
	return (cpvdot(v,v) > len*len) ? cpvmult(cpvnormalize(v), len) : v;
}

/// Linearly interpolate between v1 towards v2 by distance d.
static inline cpVect cpvlerpconst(cpVect v1, cpVect v2, cpFloat d)
{
	return cpvadd(v1, cpvclamp(cpvsub(v2, v1), d));
}

/// Returns the distance between v1 and v2.
static inline cpFloat cpvdist(const cpVect v1, const cpVect v2)
{
	return cpvlength(cpvsub(v1, v2));
}

/// Returns the squared distance between v1 and v2. Faster than cpvdist() when you only need to compare distances.
static inline cpFloat cpvdistsq(const cpVect v1, const cpVect v2)
{
	return cpvlengthsq(cpvsub(v1, v2));
}

/// Returns true if the distance between v1 and v2 is less than dist.
static inline cpBool cpvnear(const cpVect v1, const cpVect v2, const cpFloat dist)
{
	return cpvdistsq(v1, v2) < dist*dist;
}
/// @}
