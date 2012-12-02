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

/// @defgroup cpPolyShape cpPolyShape
/// @{

/// @private
typedef struct cpSplittingPlane {
	cpVect n;
	cpFloat d;
} cpSplittingPlane;

/// @private
typedef struct cpPolyShape {
	cpShape shape;
	
	int numVerts;
	cpVect *verts, *tVerts;
	cpSplittingPlane *planes, *tPlanes;
} cpPolyShape;

/// Allocate a polygon shape.
cpPolyShape* cpPolyShapeAlloc(void);
/// Initialize a polygon shape.
/// A convex hull will be created from the vertexes.
cpPolyShape* cpPolyShapeInit(cpPolyShape *poly, cpBody *body, int numVerts, const cpVect *verts, cpVect offset);
/// Allocate and initialize a polygon shape.
/// A convex hull will be created from the vertexes.
cpShape* cpPolyShapeNew(cpBody *body, int numVerts, cpVect *verts, cpVect offset);

/// Initialize a box shaped polygon shape.
cpPolyShape* cpBoxShapeInit(cpPolyShape *poly, cpBody *body, cpFloat width, cpFloat height);
/// Initialize an offset box shaped polygon shape.
cpPolyShape* cpBoxShapeInit2(cpPolyShape *poly, cpBody *body, cpBB box);
/// Allocate and initialize a box shaped polygon shape.
cpShape* cpBoxShapeNew(cpBody *body, cpFloat width, cpFloat height);
/// Allocate and initialize an offset box shaped polygon shape.
cpShape* cpBoxShapeNew2(cpBody *body, cpBB box);

/// Check that a set of vertexes is convex and has a clockwise winding.
/// NOTE: Due to floating point precision issues, hulls created with cpQuickHull() are not guaranteed to validate!
cpBool cpPolyValidate(const cpVect *verts, const int numVerts);

/// Get the number of verts in a polygon shape.
int cpPolyShapeGetNumVerts(cpShape *shape);
/// Get the @c ith vertex of a polygon shape.
cpVect cpPolyShapeGetVert(cpShape *shape, int idx);

/// @}
