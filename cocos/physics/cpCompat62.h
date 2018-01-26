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

#ifndef CHIPMUNK_COMPAT_62_H
#define CHIPMUNK_COMPAT_62_H

#include "chipmunk/chipmunk.h"

//
// Body
//
inline cpVect cpBodyGetVelAtWorldPoint(const cpBody *body)
{
    return cpBodyGetVelocityAtWorldPoint(body);
}
inline cpVect cpBodyGetVelAtLocalPoint(const cpBody *body)
{
    return cpBodyGetVelocityAtLocalPoint(body);
}
inline cpVect cpBodyGetVel(const cpBody *body)
{
    return cpBodyGetVelocity(body);
}
inline void cpBodySetVel(cpBody *body, cpVect velocity)
{
    cpBodySetVelocity(body, velocity);
}
inline cpVect cpBodyGetPos(const cpBody *body)
{
    return cpBodyGetPosition(body);
}
inline void cpBodySetPos(cpBody *body, cpVect pos)
{
    cpBodySetPosition(body, pos);
}
inline cpVect cpBodyGetRot(const cpBody *body)
{
    return cpBodyGetRotation(body);
}
inline cpFloat cpBodyGetAngVel(const cpBody *body)
{
    return cpBodyGetAngularVelocity(body);
}
inline void cpBodySetAngVel(cpBody *body, cpFloat angularVelocity)
{
    cpBodySetAngularVelocity(body, angularVelocity);
}
inline cpVect cpBodyLocal2World(const cpBody *body, const cpVect point)
{
    return cpBodyLocalToWorld(body, point);
}
inline cpVect cpBodyWorld2Local(const cpBody *body, const cpVect point)
{
    return cpBodyWorldToLocal(body, point);
}
inline void cpBodyApplyImpulse(cpBody *body, const cpVect j, const cpVect r)
{
    cpBodyApplyImpulseAtWorldPoint(body, j, r);
}

//
// Shapes
//
inline void cpShapeSetLayers(cpShape* shape, unsigned int layer)
{
    cpShapeFilter filter = cpShapeGetFilter(shape);
    filter.mask = layer;
    filter.categories = layer;
    cpShapeSetFilter(shape, filter);
}
inline unsigned int cpShapeGetLayers(cpShape* shape)
{
    cpShapeFilter filter = cpShapeGetFilter(shape);
    return filter.mask;
}
inline void cpShapeSetGroup(cpShape* shape, uintptr_t group)
{
    cpShapeFilter filter = cpShapeGetFilter(shape);
    filter.group = group;
    cpShapeSetFilter(shape, filter);
}
inline uintptr_t cpShapeGetGroup(cpShape* shape)
{
    cpShapeFilter filter = cpShapeGetFilter(shape);
    return filter.group;
}
inline  int cpPolyShapeGetNumVerts(const cpShape *shape)
{
    return cpPolyShapeGetCount(shape);
}
inline cpFloat cpShapeNearestPointQuery(cpShape *shape, cpVect p, cpPointQueryInfo *out)
{
    return cpShapePointQuery(shape, p, out);
}


//
// Space
//
inline cpShape* cpSpaceAddStaticShape(cpSpace *space, cpShape *shape)
{
    return cpSpaceAddShape(space, shape);
}


#endif // CHIPMUNK_COMPAT_62_H
