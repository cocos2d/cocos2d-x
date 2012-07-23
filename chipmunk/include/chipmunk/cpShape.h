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
 
// Forward declarations required for defining other structs.
struct cpShape;
struct cpShapeClass;

typedef struct cpSegmentQueryInfo {
	struct cpShape *shape; // shape that was hit, NULL if no collision
	cpFloat t; // Distance along query segment, will always be in the range [0, 1].
	cpVect n; // normal of hit surface
} cpSegmentQueryInfo;

// Enumeration of shape types.
typedef enum cpShapeType{
	CP_CIRCLE_SHAPE,
	CP_SEGMENT_SHAPE,
	CP_POLY_SHAPE,
	CP_NUM_SHAPES
} cpShapeType;

// Shape class. Holds function pointers and type data.
typedef struct cpShapeClass {
	cpShapeType type;
	
	// Called by cpShapeCacheBB().
	cpBB (*cacheData)(struct cpShape *shape, cpVect p, cpVect rot);
	// Called to by cpShapeDestroy().
	void (*destroy)(struct cpShape *shape);
	
	// called by cpShapePointQuery().
	cpBool (*pointQuery)(struct cpShape *shape, cpVect p);
	
	// called by cpShapeSegmentQuery()
	 void (*segmentQuery)(struct cpShape *shape, cpVect a, cpVect b, cpSegmentQueryInfo *info);
} cpShapeClass;

// Basic shape struct that the others inherit from.
typedef struct cpShape{
	// The "class" of a shape as defined above 
	CP_PRIVATE(const cpShapeClass *klass);
	
	// cpBody that the shape is attached to.
	cpBody *body;

	// Cached BBox for the shape.
	cpBB bb;
	
	// Sensors invoke callbacks, but do not generate collisions
	cpBool sensor;
	
	// *** Surface properties.
	
	// Coefficient of restitution. (elasticity)
	cpFloat e;
	// Coefficient of friction.
	cpFloat u;
	// Surface velocity used when solving for friction.
	cpVect surface_v;

	// *** User Definable Fields

	// User defined data pointer for the shape.
	cpDataPointer data;
	
	// User defined collision type for the shape.
	cpCollisionType collision_type;
	// User defined collision group for the shape.
	cpGroup group;
	// User defined layer bitmask for the shape.
	cpLayers layers;
	
	// *** Internally Used Fields
	
	// Shapes form a linked list when added to space on a non-NULL body
	CP_PRIVATE(struct cpShape *next);
	
	// Unique id used as the hash value.
	CP_PRIVATE(cpHashValue hashid);
} cpShape;

// Low level shape initialization func.
cpShape* cpShapeInit(cpShape *shape, const struct cpShapeClass *klass, cpBody *body);

// Basic destructor functions. (allocation functions are not shared)
void cpShapeDestroy(cpShape *shape);
void cpShapeFree(cpShape *shape);

// Cache the BBox of the shape.
cpBB cpShapeCacheBB(cpShape *shape);

// Test if a point lies within a shape.
cpBool cpShapePointQuery(cpShape *shape, cpVect p);

#define CP_DeclareShapeGetter(struct, type, name) type struct##Get##name(cpShape *shape)

// Circle shape structure.
typedef struct cpCircleShape{
	cpShape shape;
	
	// Center in body space coordinates
	CP_PRIVATE(cpVect c);
	// Radius.
	CP_PRIVATE(cpFloat r);
	
	// Transformed center. (world space coordinates)
	CP_PRIVATE(cpVect tc);
} cpCircleShape;

// Basic allocation functions for cpCircleShape.
cpCircleShape *cpCircleShapeAlloc(void);
cpCircleShape *cpCircleShapeInit(cpCircleShape *circle, cpBody *body, cpFloat radius, cpVect offset);
cpShape *cpCircleShapeNew(cpBody *body, cpFloat radius, cpVect offset);

CP_DeclareShapeGetter(cpCircleShape, cpVect, Offset);
CP_DeclareShapeGetter(cpCircleShape, cpFloat, Radius);

// Segment shape structure.
typedef struct cpSegmentShape{
	cpShape shape;
	
	// Endpoints and normal of the segment. (body space coordinates)
	cpVect CP_PRIVATE(a), CP_PRIVATE(b), CP_PRIVATE(n);
	// Radius of the segment. (Thickness)
	cpFloat CP_PRIVATE(r);

	// Transformed endpoints and normal. (world space coordinates)
	cpVect CP_PRIVATE(ta), CP_PRIVATE(tb), CP_PRIVATE(tn);
} cpSegmentShape;

// Basic allocation functions for cpSegmentShape.
cpSegmentShape* cpSegmentShapeAlloc(void);
cpSegmentShape* cpSegmentShapeInit(cpSegmentShape *seg, cpBody *body, cpVect a, cpVect b, cpFloat radius);
cpShape* cpSegmentShapeNew(cpBody *body, cpVect a, cpVect b, cpFloat radius);

CP_DeclareShapeGetter(cpSegmentShape, cpVect, A);
CP_DeclareShapeGetter(cpSegmentShape, cpVect, B);
CP_DeclareShapeGetter(cpSegmentShape, cpVect, Normal);
CP_DeclareShapeGetter(cpSegmentShape, cpFloat, Radius);

// For determinism, you can reset the shape id counter.
void cpResetShapeIdCounter(void);

// Directed segment queries against individual shapes.
void cpSegmentQueryInfoPrint(cpSegmentQueryInfo *info);

cpBool cpShapeSegmentQuery(cpShape *shape, cpVect a, cpVect b, cpSegmentQueryInfo *info);

static inline cpVect
cpSegmentQueryHitPoint(const cpVect start, const cpVect end, const cpSegmentQueryInfo info)
{
	return cpvlerp(start, end, info.t);
}

static inline cpFloat
cpSegmentQueryHitDist(const cpVect start, const cpVect end, const cpSegmentQueryInfo info)
{
	return cpvdist(start, end)*info.t;
}
