/*
    Copyright 2011 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#ifndef GrPathUtils_DEFINED
#define GrPathUtils_DEFINED

#include "GrNoncopyable.h"
#include "GrPoint.h"
#include "GrPath.h"

/**
 *  Utilities for evaluating paths.
 */
class GrPathUtils : public GrNoncopyable {
public:
    /// Since we divide by tol if we're computing exact worst-case bounds,
    /// very small tolerances will be increased to gMinCurveTol.
    static int worstCasePointCount(const GrPath&,
                                   int* subpaths,
                                   GrScalar tol);
    /// Since we divide by tol if we're computing exact worst-case bounds,
    /// very small tolerances will be increased to gMinCurveTol.
    static uint32_t quadraticPointCount(const GrPoint points[], GrScalar tol);
    static uint32_t generateQuadraticPoints(const GrPoint& p0,
                                            const GrPoint& p1,
                                            const GrPoint& p2,
                                            GrScalar tolSqd,
                                            GrPoint** points,
                                            uint32_t pointsLeft);
    /// Since we divide by tol if we're computing exact worst-case bounds,
    /// very small tolerances will be increased to gMinCurveTol.
    static uint32_t cubicPointCount(const GrPoint points[], GrScalar tol);
    static uint32_t generateCubicPoints(const GrPoint& p0,
                                        const GrPoint& p1,
                                        const GrPoint& p2,
                                        const GrPoint& p3,
                                        GrScalar tolSqd,
                                        GrPoint** points,
                                        uint32_t pointsLeft);

private:
    static const GrScalar gMinCurveTol;
};
#endif
