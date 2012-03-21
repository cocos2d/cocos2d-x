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
 
#include <math.h>
#include <stdlib.h>

#include "chipmunk_private.h"

cpVect
cpBBClampVect(const cpBB bb, const cpVect v)
{
	cpFloat x = cpfmin(cpfmax(bb.l, v.x), bb.r);
	cpFloat y = cpfmin(cpfmax(bb.b, v.y), bb.t);
	return cpv(x, y);
}

cpVect
cpBBWrapVect(const cpBB bb, const cpVect v)
{
	cpFloat ix = cpfabs(bb.r - bb.l);
	cpFloat modx = cpfmod(v.x - bb.l, ix);
	cpFloat x = (modx > 0.0f) ? modx : modx + ix;
	
	cpFloat iy = cpfabs(bb.t - bb.b);
	cpFloat mody = cpfmod(v.y - bb.b, iy);
	cpFloat y = (mody > 0.0f) ? mody : mody + iy;
	
	return cpv(x + bb.l, y + bb.b);
}
