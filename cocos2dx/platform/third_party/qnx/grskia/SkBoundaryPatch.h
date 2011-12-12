#ifndef SkBoundaryPatch_DEFINED
#define SkBoundaryPatch_DEFINED

#include "SkPoint.h"
#include "SkRefCnt.h"

class SkBoundary : public SkRefCnt {
public:
    // These must be 0, 1, 2, 3 for efficiency in the subclass implementations
    enum Edge {
        kTop    = 0,
        kRight  = 1,
        kBottom = 2,
        kLeft   = 3
    };
    // Edge index goes clockwise around the boundary, beginning at the "top"
    virtual SkPoint eval(Edge, SkScalar unitInterval) = 0;
};

class SkBoundaryPatch {
public:
    SkBoundaryPatch();
    ~SkBoundaryPatch();

    SkBoundary* getBoundary() const { return fBoundary; }
    SkBoundary* setBoundary(SkBoundary*);

    SkPoint eval(SkScalar unitU, SkScalar unitV);
    bool evalPatch(SkPoint verts[], int rows, int cols);

private:
    SkBoundary* fBoundary;
};

////////////////////////////////////////////////////////////////////////

class SkLineBoundary : public SkBoundary {
public:
    SkPoint fPts[4];
    
    // override
    virtual SkPoint eval(Edge, SkScalar);
};

class SkCubicBoundary : public SkBoundary {
public:
    // the caller sets the first 12 entries. The 13th is used by the impl.
    SkPoint fPts[13];
    
    // override
    virtual SkPoint eval(Edge, SkScalar);
};

#endif

