#ifndef GrTouchGesture_DEFINED
#define GrTouchGesture_DEFINED

#include "GrTypes.h"
#include "SkTDArray.h"
#include "SkMatrix.h"

#include "FlingState.h"

class GrTouchGesture {
public:
    GrTouchGesture();
    ~GrTouchGesture();

    void touchBegin(void* owner, float x, float y);
    void touchMoved(void* owner, float x, float y);
    void touchEnd(void* owner);
    void reset();

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

    State    fState;
    SkMatrix fLocalM, fGlobalM;
    FlingState  fFlinger;
    SkMSec  fLastUpT;
    SkPoint fLastUpP;


    void flushLocalM();
    int findRec(void* owner) const;
    void appendNewRec(void* owner, float x, float y);
    float computePinch(const Rec&, const Rec&);
    float limitTotalZoom(float scale) const;
    bool handleDblTap(float, float);
};

#endif


