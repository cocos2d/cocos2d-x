/* Copyright (c) 2013 Scott Lembcke and Howling Moon Software
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

/// @defgroup cpShape cpShape
/// The cpShape struct defines the shape of a rigid body.
/// @{

/// Point query info struct.
typedef struct cpPointQueryInfo {
	/// The nearest shape, NULL if no shape was within range.
	const cpShape *shape;
	/// The closest point on the shape's surface. (in world space coordinates)
	cpVect point;
	/// The distance to the point. The distance is negative if the point is inside the shape.
	cpFloat distance;
	/// The gradient of the signed distance function.
	/// The value should be similar to info.p/info.d, but accurate even for very small values of info.d.
	cpVect gradient;
} cpPointQueryInfo;

/// Segment query info struct.
typedef struct cpSegmentQueryInfo {
	/// The shape that was hit, or NULL if no collision occured.
	const cpShape *shape;
	/// The point of impact.
	cpVect point;
	/// The normal of the surface hit.
	cpVect normal;
	/// The normalized distance along the query segment in the range [0, 1].
	cpFloat alpha;
} cpSegmentQueryInfo;

/// Fast collision filtering type that is used to determine if two objects collide before calling collision or query callbacks.
typedef struct cpShapeFilter {
	/// Two objects with the same non-zero group value do not collide.
	/// This is generally used to group objects in a composite object together to disable self collisions.
	cpGroup group;
	/// A bitmask of user definable categories that this object belongs to.
	/// The category/mask combinations of both objects in a collision must agree for a collision to occur.
	cpBitmask categories;
	/// A bitmask of user definable category types that this object object collides with.
	/// The category/mask combinations of both objects in a collision must agree for a collision to occur.
	cpBitmask mask;
} cpShapeFilter;

/// Collision filter value for a shape that will collide with anything except CP_SHAPE_FILTER_NONE.
static const cpShapeFilter CP_SHAPE_FILTER_ALL = {CP_NO_GROUP, CP_ALL_CATEGORIES, CP_ALL_CATEGORIES};
/// Collision filter value for a shape that does not collide with anything.
static const cpShapeFilter CP_SHAPE_FILTER_NONE = {CP_NO_GROUP, ~CP_ALL_CATEGORIES, ~CP_ALL_CATEGORIES};

/// Create a new collision filter.
static inline cpShapeFilter
cpShapeFilterNew(cpGroup group, cpBitmask categories, cpBitmask mask)
{
	cpShapeFilter filter = {group, categories, mask};
	return filter;
}

/// Destroy a shape.
CP_EXPORT void cpShapeDestroy(cpShape *shape);
/// Destroy and Free a shape.
CP_EXPORT void cpShapeFree(cpShape *shape);

/// Update, cache and return the bounding box of a shape based on the body it's attached to.
CP_EXPORT cpBB cpShapeCacheBB(cpShape *shape);
/// Update, cache and return the bounding box of a shape with an explicit transformation.
CP_EXPORT cpBB cpShapeUpdate(cpShape *shape, cpTransform transform);

/// Perform a nearest point query. It finds the closest point on the surface of shape to a specific point.
/// The value returned is the distance between the points. A negative distance means the point is inside the shape.
CP_EXPORT cpFloat cpShapePointQuery(const cpShape *shape, cpVect p, cpPointQueryInfo *out);

/// Perform a segment query against a shape. @c info must be a pointer to a valid cpSegmentQueryInfo structure.
CP_EXPORT cpBool cpShapeSegmentQuery(const cpShape *shape, cpVect a, cpVect b, cpFloat radius, cpSegmentQueryInfo *info);

/// Return contact information about two shapes.
CP_EXPORT cpContactPointSet cpShapesCollide(const cpShape *a, const cpShape *b);

/// The cpSpace this body is added to.
CP_EXPORT cpSpace* cpShapeGetSpace(const cpShape *shape);

/// The cpBody this shape is connected to.
CP_EXPORT cpBody* cpShapeGetBody(const cpShape *shape);
/// Set the cpBody this shape is connected to.
/// Can only be used if the shape is not currently added to a space.
CP_EXPORT void cpShapeSetBody(cpShape *shape, cpBody *body);

/// Get the mass of the shape if you are having Chipmunk calculate mass properties for you.
cpFloat cpShapeGetMass(cpShape *shape);
/// Set the mass of this shape to have Chipmunk calculate mass properties for you.
CP_EXPORT void cpShapeSetMass(cpShape *shape, cpFloat mass);

/// Get the density of the shape if you are having Chipmunk calculate mass properties for you.
CP_EXPORT cpFloat cpShapeGetDensity(cpShape *shape);
/// Set the density  of this shape to have Chipmunk calculate mass properties for you.
CP_EXPORT void cpShapeSetDensity(cpShape *shape, cpFloat density);

/// Get the calculated moment of inertia for this shape.
CP_EXPORT cpFloat cpShapeGetMoment(cpShape *shape);
/// Get the calculated area of this shape.
CP_EXPORT cpFloat cpShapeGetArea(cpShape *shape);
/// Get the centroid of this shape.
CP_EXPORT cpVect cpShapeGetCenterOfGravity(cpShape *shape);

/// Get the bounding box that contains the shape given it's current position and angle.
CP_EXPORT cpBB cpShapeGetBB(const cpShape *shape);

/// Get if the shape is set to be a sensor or not.
CP_EXPORT cpBool cpShapeGetSensor(const cpShape *shape);
/// Set if the shape is a sensor or not.
CP_EXPORT void cpShapeSetSensor(cpShape *shape, cpBool sensor);

/// Get the elasticity of this shape.
CP_EXPORT cpFloat cpShapeGetElasticity(const cpShape *shape);
/// Set the elasticity of this shape.
CP_EXPORT void cpShapeSetElasticity(cpShape *shape, cpFloat elasticity);

/// Get the friction of this shape.
CP_EXPORT cpFloat cpShapeGetFriction(const cpShape *shape);
/// Set the friction of this shape.
CP_EXPORT void cpShapeSetFriction(cpShape *shape, cpFloat friction);

/// Get the surface velocity of this shape.
CP_EXPORT cpVect cpShapeGetSurfaceVelocity(const cpShape *shape);
/// Set the surface velocity of this shape.
CP_EXPORT void cpShapeSetSurfaceVelocity(cpShape *shape, cpVect surfaceVelocity);

/// Get the user definable data pointer of this shape.
CP_EXPORT cpDataPointer cpShapeGetUserData(const cpShape *shape);
/// Set the user definable data pointer of this shape.
CP_EXPORT void cpShapeSetUserData(cpShape *shape, cpDataPointer userData);

/// Set the collision type of this shape.
CP_EXPORT cpCollisionType cpShapeGetCollisionType(const cpShape *shape);
/// Get the collision type of this shape.
CP_EXPORT void cpShapeSetCollisionType(cpShape *shape, cpCollisionType collisionType);

/// Get the collision filtering parameters of this shape.
CP_EXPORT cpShapeFilter cpShapeGetFilter(const cpShape *shape);
/// Set the collision filtering parameters of this shape.
CP_EXPORT void cpShapeSetFilter(cpShape *shape, cpShapeFilter filter);


/// @}
/// @defgroup cpCircleShape cpCircleShape

/// Allocate a circle shape.
CP_EXPORT cpCircleShape* cpCircleShapeAlloc(void);
/// Initialize a circle shape.
CP_EXPORT cpCircleShape* cpCircleShapeInit(cpCircleShape *circle, cpBody *body, cpFloat radius, cpVect offset);
/// Allocate and initialize a circle shape.
CP_EXPORT cpShape* cpCircleShapeNew(cpBody *body, cpFloat radius, cpVect offset);

/// Get the offset of a circle shape.
CP_EXPORT cpVect cpCircleShapeGetOffset(const cpShape *shape);
/// Get the radius of a circle shape.
CP_EXPORT cpFloat cpCircleShapeGetRadius(const cpShape *shape);

/// @}
/// @defgroup cpSegmentShape cpSegmentShape

/// Allocate a segment shape.
CP_EXPORT cpSegmentShape* cpSegmentShapeAlloc(void);
/// Initialize a segment shape.
CP_EXPORT cpSegmentShape* cpSegmentShapeInit(cpSegmentShape *seg, cpBody *body, cpVect a, cpVect b, cpFloat radius);
/// Allocate and initialize a segment shape.
CP_EXPORT cpShape* cpSegmentShapeNew(cpBody *body, cpVect a, cpVect b, cpFloat radius);

/// Let Chipmunk know about the geometry of adjacent segments to avoid colliding with endcaps.
CP_EXPORT void cpSegmentShapeSetNeighbors(cpShape *shape, cpVect prev, cpVect next);

/// Get the first endpoint of a segment shape.
CP_EXPORT cpVect cpSegmentShapeGetA(const cpShape *shape);
/// Get the second endpoint of a segment shape.
CP_EXPORT cpVect cpSegmentShapeGetB(const cpShape *shape);
/// Get the normal of a segment shape.
CP_EXPORT cpVect cpSegmentShapeGetNormal(const cpShape *shape);
/// Get the first endpoint of a segment shape.
CP_EXPORT cpFloat cpSegmentShapeGetRadius(const cpShape *shape);

/// @}
