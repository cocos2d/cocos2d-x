#ifndef GrMesh_DEFINED
#define GrMesh_DEFINED

#include "SkRect.h"
#include "SkPoint.h"

class SkCanvas;
class SkPaint;

class GrMesh {
public:
    GrMesh();
    ~GrMesh();

    GrMesh& operator=(const GrMesh& src);

    void init(const SkRect& bounds, int rows, int cols,
              const SkRect& texture);

    const SkRect& bounds() const { return fBounds; }

    int rows() const { return fRows; }
    int cols() const { return fCols; }
    SkPoint& pt(int row, int col) {
        return fPts[row * (fRows + 1) + col];
    }

    void draw(SkCanvas*, const SkPaint&);
    void drawWireframe(SkCanvas* canvas, const SkPaint& paint);

private:
    SkRect      fBounds;
    int         fRows, fCols;
    SkPoint*    fPts;
    SkPoint*    fTex;   // just points into fPts, not separately allocated
    int         fCount;
    uint16_t*   fIndices;
    int         fIndexCount;
};

#endif

