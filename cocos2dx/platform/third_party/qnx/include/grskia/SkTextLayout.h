#ifndef SkTextLayout_DEFINED
#define SkTextLayout_DEFINED

#include "SkPaint.h"
#include "SkRefCnt.h"

class SkTextStyle : public SkRefCnt {
public:
    SkTextStyle();
    SkTextStyle(const SkTextStyle&);
    explicit SkTextStyle(const SkPaint&);
    virtual ~SkTextStyle();

    const SkPaint& paint() const { return fPaint; }
    SkPaint& paint() { return fPaint; }
    
    // todo: bidi-override, language

private:
    SkPaint fPaint;
};

class SkTextLayout {
public:
    SkTextLayout();
    ~SkTextLayout();

    void setText(const char text[], size_t length);
    void setBounds(const SkRect& bounds);

    SkTextStyle* getDefaultStyle() const { return fDefaultStyle; }
    SkTextStyle* setDefaultStyle(SkTextStyle*);

//    SkTextStyle* setStyle(SkTextStyle*, size_t offset, size_t length);

    void draw(SkCanvas* canvas);

private:
    SkTDArray<char> fText;
    SkTextStyle*    fDefaultStyle;
    SkRect          fBounds;

    // cache
    struct Line;
    struct GlyphRun;
    SkTDArray<Line*> fLines;
};

#endif

