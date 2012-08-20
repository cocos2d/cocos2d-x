#ifndef SkTouchGesture_DEFINED
#define SkTouchGesture_DEFINED

#include "SkTDArray.h"
#include "SkMatrix.h"

struct SkFlingState {
    SkFlingState() : fActive(false) {}
    
    bool isActive() const { return fActive; }
    void stop() { fActive = false; }
    
    void reset(float sx, float sy);
    bool evaluateMatrix(SkMatrix* matrix);
    
private:
    SkPoint     fDirection;
    SkScalar    fSpeed0;
    double      fTime0;
    bool        fActive;
};

class SkTouchGesture {
public:
    SkTouchGesture();
    ~SkTouchGesture();

    void touchBegin(void* owner, float x, float y);
    void touchMoved(void* owner, float x, float y);
    void touchEnd(void* owner);
    void reset();

    bool isActive() { return fFlinger.isActive(); }
    void stop() { fFlinger.stop(); }

    const SkMatrix& localM();
    const SkMatrix& globalM() const { return fGlobalM; }

private:
    enum State {
        kEmpty_State,
        kTranslate_State,
        kZoom_State,
    };

    struct Rec {
        void*   fOwner;
        float   fStartX, fStartY;
        float   fPrevX, fPrevY;
        float   fLastX, fLastY;
        SkMSec  fPrevT, fLastT;
    };
    SkTDArray<Rec> fTouches;

    State           fState;
    SkMatrix        fLocalM, fGlobalM;
    SkFlingState    fFlinger;
    SkMSec          fLastUpT;
    SkPoint         fLastUpP;


    void flushLocalM();
    int findRec(void* owner) const;
    void appendNewRec(void* owner, float x, float y);
    float computePinch(const Rec&, const Rec&);
    float limitTotalZoom(float scale) const;
    bool handleDblTap(float, float);
};

#endif


