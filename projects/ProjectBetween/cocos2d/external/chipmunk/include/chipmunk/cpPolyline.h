// Copyright 2013 Howling Moon Software. All rights reserved.
// See http://chipmunk2d.net/legal.php for more information.

// Polylines are just arrays of vertexes.
// They are looped if the first vertex is equal to the last.
// cpPolyline structs are intended to be passed by value and destroyed when you are done with them.
typedef struct cpPolyline {
  int count, capacity;
  cpVect verts[];
} cpPolyline;

/// Destroy and free a polyline instance.
CP_EXPORT void cpPolylineFree(cpPolyline *line);

/// Returns true if the first vertex is equal to the last.
CP_EXPORT cpBool cpPolylineIsClosed(cpPolyline *line);

/**
	Returns a copy of a polyline simplified by using the Douglas-Peucker algorithm.
	This works very well on smooth or gently curved shapes, but not well on straight edged or angular shapes.
*/
CP_EXPORT cpPolyline *cpPolylineSimplifyCurves(cpPolyline *line, cpFloat tol);

/**
	Returns a copy of a polyline simplified by discarding "flat" vertexes.
	This works well on straigt edged or angular shapes, not as well on smooth shapes.
*/
CP_EXPORT cpPolyline *cpPolylineSimplifyVertexes(cpPolyline *line, cpFloat tol);

/// Get the convex hull of a polyline as a looped polyline.
CP_EXPORT cpPolyline *cpPolylineToConvexHull(cpPolyline *line, cpFloat tol);


/// Polyline sets are collections of polylines, generally built by cpMarchSoft() or cpMarchHard().
typedef struct cpPolylineSet {
  int count, capacity;
  cpPolyline **lines;
} cpPolylineSet;

/// Allocate a new polyline set.
CP_EXPORT cpPolylineSet *cpPolylineSetAlloc(void);

/// Initialize a new polyline set.
CP_EXPORT cpPolylineSet *cpPolylineSetInit(cpPolylineSet *set);

/// Allocate and initialize a polyline set.
CP_EXPORT cpPolylineSet *cpPolylineSetNew(void);

/// Destroy a polyline set.
CP_EXPORT void cpPolylineSetDestroy(cpPolylineSet *set, cpBool freePolylines);

CP_EXPORT /// Destroy and free a polyline set.
void cpPolylineSetFree(cpPolylineSet *set, cpBool freePolylines);

/**
	Add a line segment to a polyline set.
	A segment will either start a new polyline, join two others, or add to or loop an existing polyline.
	This is mostly intended to be used as a callback directly from cpMarchSoft() or cpMarchHard().
*/
CP_EXPORT void cpPolylineSetCollectSegment(cpVect v0, cpVect v1, cpPolylineSet *lines);

/**
	Get an approximate convex decomposition from a polyline.
	Returns a cpPolylineSet of convex hulls that match the original shape to within 'tol'.
	NOTE: If the input is a self intersecting polygon, the output might end up overly simplified.
*/

CP_EXPORT cpPolylineSet *cpPolylineConvexDecomposition(cpPolyline *line, cpFloat tol);

#define cpPolylineConvexDecomposition_BETA cpPolylineConvexDecomposition
