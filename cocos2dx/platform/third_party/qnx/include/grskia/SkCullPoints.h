/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkCullPoints_DEFINED
#define SkCullPoints_DEFINED

#include "SkRect.h"

class SkCullPoints {
public:
    SkCullPoints();
    SkCullPoints(const SkIRect& r);
    
    void    reset(const SkIRect& r);
    
    /** Start a contour at (x,y). Follow this with call(s) to lineTo(...)
    */
    void    moveTo(int x, int y);
    
    enum LineToResult {
        kNo_Result,             //!< line segment was completely clipped out
        kLineTo_Result,         //!< path.lineTo(pts[1]);
        kMoveToLineTo_Result    //!< path.moveTo(pts[0]); path.lineTo(pts[1]);
    };
    /** Connect a line to the previous call to lineTo (or moveTo).
    */
    LineToResult lineTo(int x, int y, SkIPoint pts[2]);

private:
    SkIRect      fR;             // the caller's rectangle
    SkIPoint     fAsQuad[4];     // cache of fR as 4 points
    SkIPoint     fPrevPt;        // private state
    LineToResult fPrevResult;   // private state
    
    bool sect_test(int x0, int y0, int x1, int y1) const;
};

/////////////////////////////////////////////////////////////////////////////////

class SkPath;

/** \class SkCullPointsPath

    Similar to SkCullPoints, but this class handles the return values
    from lineTo, and automatically builds a SkPath with the result(s).
*/
class SkCullPointsPath {
public:
    SkCullPointsPath();
    SkCullPointsPath(const SkIRect& r, SkPath* dst);

    void reset(const SkIRect& r, SkPath* dst);
    
    void    moveTo(int x, int y);
    void    lineTo(int x, int y);

private:
    SkCullPoints    fCP;
    SkPath*         fPath;
};

#endif
