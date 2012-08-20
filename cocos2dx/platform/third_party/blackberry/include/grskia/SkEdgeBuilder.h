#ifndef SkEdgeBuilder_DEFINED
#define SkEdgeBuilder_DEFINED

#include "SkChunkAlloc.h"
#include "SkRect.h"
#include "SkTDArray.h"

struct SkEdge;
class SkEdgeClipper;
class SkPath;

class SkEdgeBuilder {
public:
    SkEdgeBuilder();
    
    int build(const SkPath& path, const SkIRect* clip, int shiftUp);

    SkEdge** edgeList() { return fList.begin(); }

private:
    SkChunkAlloc        fAlloc;
    SkTDArray<SkEdge*>  fList;
    int                 fShiftUp;

    void addLine(const SkPoint pts[]);
    void addQuad(const SkPoint pts[]);
    void addCubic(const SkPoint pts[]);
    void addClipper(SkEdgeClipper*);
};

#endif
