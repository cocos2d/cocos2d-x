/*
    Copyright 2010 Google Inc.

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


#ifndef GrPathIter_DEFINED
#define GrPathIter_DEFINED

#include "GrTypes.h"

struct GrPoint;

/**
 2D Path iterator. Porting layer creates a subclass of this. It allows Ganesh to
 parse the top-level API's 2D paths. Supports lines, quadratics, and cubic
 pieces and moves (multi-part paths).
 */
class GrPathIter {
public:
    /**
     Returned by next(). Indicates the next piece of the path. 
     */
    enum Command {
        kMove_Command,      //!< next() returns 1 pt
                            //   Starts a new subpath at
                            //   at the returned point
        kLine_Command,      //!< next() returns 2 pts
                            //   Adds a line segment
        kQuadratic_Command, //!< next() returns 3 pts
                            //   Adds a quadratic segment
        kCubic_Command,     //!< next() returns 4 pts
                            //   Adds a cubic segment
        kClose_Command,     //!< next() returns 0 pts
        kEnd_Command        //!< next() returns 0 pts
                            //   Implictly closes the last 
                            //   point
    };
    
    enum ConvexHint {
        kNone_ConvexHint,                         //<! No hint about convexity 
                                                  //   of the path
        kConvex_ConvexHint,                       //<! Path is one convex piece
        kNonOverlappingConvexPieces_ConvexHint,   //<! Multiple convex pieces, 
                                                  //   pieces are known to be
                                                  //   disjoint
        kSameWindingConvexPieces_ConvexHint,      //<! Multiple convex pieces, 
                                                  //   may or may not intersect,
                                                  //   either all wind cw or all 
                                                  //   wind ccw.
        kConcave_ConvexHint                       //<! Path is known to be 
                                                  //   concave
    };
    
    static int NumCommandPoints(Command cmd) {
        static const int numPoints[] = {
            1, 2, 3, 4, 0, 0
        };
        return numPoints[cmd];
    }
    
    virtual ~GrPathIter() {};

    /** 
     Iterates through the path. Should not be called after
     kEnd_Command has been returned once. This version retrieves the
     points for the command.
     @param points  The points relevant to returned commend. See Command
                    enum for number of points valid for each command.
     @return The next command of the path.
     */
    virtual Command next(GrPoint points[4]) = 0;

    /**
     * If the host API has knowledge of the convexity of the path
     * it can be communicated by this hint. Ganesh can make these
     * determinations itself. So it is not necessary to compute 
     * convexity status if it isn't already determined.
     *
     * @return a hint about the convexity of the path.
     */     
    virtual ConvexHint hint() const { return kNone_ConvexHint; }

     /** 
     Iterates through the path. Should not be called after
     kEnd_Command has been returned once. This version does not retrieve the
     points for the command.
     @return The next command of the path.
     */
     virtual Command next() = 0;

    /**
     Restarts iteration from the beginning.
     */
    virtual void rewind() = 0;

};

#endif
