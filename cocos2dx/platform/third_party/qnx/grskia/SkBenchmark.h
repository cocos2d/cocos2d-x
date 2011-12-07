#ifndef SkBenchmark_DEFINED
#define SkBenchmark_DEFINED

#include "SkRefCnt.h"
#include "SkPoint.h"
#include "SkTDict.h"
#include "SkTRegistry.h"

class SkCanvas;
class SkPaint;

class SkTriState {
public:
    enum State {
        kDefault,
        kTrue,
        kFalse
    };
};

class SkBenchmark : public SkRefCnt {
public:
    SkBenchmark(void* defineDict);

    const char* getName();
    SkIPoint getSize();
    void draw(SkCanvas*);
    
    void setForceAlpha(int alpha) {
        fForceAlpha = alpha;
    }
    
    void setForceAA(bool aa) {
        fForceAA = aa;
    }
    
    void setForceFilter(bool filter) {
        fForceFilter = filter;
    }
    
    void setDither(SkTriState::State state) {
        fDither = state;
    }

    void setStrokeWidth(SkScalar width) {
      strokeWidth = width;
      fHasStrokeWidth = true;
    }

    SkScalar getStrokeWidth() {
      return strokeWidth;
    }

    bool hasStrokeWidth() {
      return fHasStrokeWidth;
    }

    const char* findDefine(const char* key) const;
    bool findDefine32(const char* key, int32_t* value) const;
    bool findDefineScalar(const char* key, SkScalar* value) const;

protected:
    void setupPaint(SkPaint* paint);

    virtual const char* onGetName() = 0;
    virtual void onDraw(SkCanvas*) = 0;

    virtual SkIPoint onGetSize();

private:
    const SkTDict<const char*>* fDict;
    int     fForceAlpha;
    bool    fForceAA;
    bool    fForceFilter;
    SkTriState::State  fDither;
    bool    fHasStrokeWidth;
    SkScalar strokeWidth;
};

typedef SkTRegistry<SkBenchmark*, void*> BenchRegistry;

#endif
