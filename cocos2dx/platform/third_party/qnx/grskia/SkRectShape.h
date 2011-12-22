#ifndef SkRectShape_DEFINED
#define SkRectShape_DEFINED

#include "SkShape.h"
#include "SkPaint.h"
#include "SkSize.h"

class SkPaintShape : public SkShape {
public:
    SkPaintShape();

    SkPaint& paint() { return fPaint; }
    const SkPaint& paint() const { return fPaint; }

    // overrides
    virtual void flatten(SkFlattenableWriteBuffer&);
    
protected:
    SkPaintShape(SkFlattenableReadBuffer& buffer);
    
private:
    SkPaint fPaint;
    
    typedef SkShape INHERITED;
};

class SkRectShape : public SkPaintShape {
public:
    SkRectShape();
    
    void setRect(const SkRect&);
    void setOval(const SkRect&);
    void setCircle(SkScalar x, SkScalar y, SkScalar radius);
    void setRRect(const SkRect&, SkScalar rx, SkScalar ry);

    // overrides
    virtual Factory getFactory();
    virtual void flatten(SkFlattenableWriteBuffer&);

    // public for Registrar
    static SkFlattenable* CreateProc(SkFlattenableReadBuffer&);

protected:
    SkRectShape(SkFlattenableReadBuffer&);

    // overrides
    virtual void onDraw(SkCanvas*);

private:
    SkRect  fBounds;
    SkSize  fRadii;

    typedef SkPaintShape INHERITED;
};

#endif
