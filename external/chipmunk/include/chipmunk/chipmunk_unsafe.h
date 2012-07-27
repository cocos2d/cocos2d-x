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

/* This header defines a number of "unsafe" operations on Chipmunk objects.
 * In this case "unsafe" is referring to operations which may reduce the
 * physical accuracy or numerical stability of the simulation, but will not
 * cause crashes.
 *
 * The prime example is mutating collision shapes. Chipmunk does not support
 * this directly. Mutating shapes using this API will caused objects in contact
 * to be pushed apart using Chipmunk's overlap solver, but not using real
 * persistent velocities. Probably not what you meant, but perhaps close enough.
 */

/// @defgroup unsafe Chipmunk Unsafe Shape Operations
/// These functions are used for mutating collision shapes.
/// Chipmunk does not have any way to get velocity information on changing shapes,
/// so the results will be unrealistic. You must explicity include the chipmunk_unsafe.h header to use them.
/// @{

#ifndef CHIPMUNK_UNSAFE_HEADER
#define CHIPMUNK_UNSAFE_HEADER

#ifdef __cplusplus
extern "C" {
#endif

/// Set the radius of a circle shape.
void cpCircleShapeSetRadius(cpShape *shape, cpFloat radius);
/// Set the offset of a circle shape.
void cpCircleShapeSetOffset(cpShape *shape, cpVect offset);

/// Set the endpoints of a segment shape.
void cpSegmentShapeSetEndpoints(cpShape *shape, cpVect a, cpVect b);
/// Set the radius of a segment shape.
void cpSegmentShapeSetRadius(cpShape *shape, cpFloat radius);

/// Set the vertexes of a poly shape.
void cpPolyShapeSetVerts(cpShape *shape, int numVerts, cpVect *verts, cpVect offset);

#ifdef __cplusplus
}
#endif
#endif
/// @}
