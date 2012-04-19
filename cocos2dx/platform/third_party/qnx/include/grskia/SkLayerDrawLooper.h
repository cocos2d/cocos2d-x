#ifndef SkLayerDrawLooper_DEFINED
#define SkLayerDrawLooper_DEFINED

#include "SkDrawLooper.h"
#include "SkXfermode.h"

struct SkPoint;

class SK_API SkLayerDrawLooper : public SkDrawLooper {
public:
            SkLayerDrawLooper();
    virtual ~SkLayerDrawLooper();

    /**
     *  Bits specifies which aspects of the layer's paint should replace the
     *  corresponding aspects on the draw's paint.
     *  kEntirePaint_Bits means use the layer's paint completely.
     *  0 means ignore the layer's paint.
     */
    enum Bits {
        kStyle_Bit      = 1 << 0,   //!< use this layer's Style/stroke settings
        kTextSkewX_Bit  = 1 << 1,   //!< use this layer's textskewx
        kPathEffect_Bit = 1 << 2,   //!< use this layer's patheffect
        kMaskFilter_Bit = 1 << 3,   //!< use this layer's maskfilter
        kShader_Bit     = 1 << 4,   //!< use this layer's shader
        kColorFilter_Bit = 1 << 5,  //!< use this layer's colorfilter
        kXfermode_Bit   = 1 << 6,   //!< use this layer's xfermode
        
        kEntirePaint_Bits = -1,      //!< use this layer's paint entirely
    };
    typedef int32_t BitFlags;

    /**
     *  Info for how to apply the layer's paint and offset.
     *
     *  fFlagsMask selects which flags in the layer's paint should be applied.
     *      result = (draw-flags & ~fFlagsMask) | (layer-flags & fFlagsMask)
     *  In the extreme:
     *      If fFlagsMask is 0, we ignore all of the layer's flags
     *      If fFlagsMask is -1, we use all of the layer's flags
     *
     *  fColorMode controls how we compute the final color for the layer:
     *      The layer's paint's color is treated as the SRC
     *      The draw's paint's color is treated as the DST
     *      final-color = Mode(layers-color, draws-color);
     *  Any SkXfermode::Mode will work. Two common choices are:
     *      kSrc_Mode: to use the layer's color, ignoring the draw's
     *      kDst_Mode: to just keep the draw's color, ignoring the layer's
     */
    struct SK_API LayerInfo {
        uint32_t            fFlagsMask; // SkPaint::Flags
        BitFlags            fPaintBits;
        SkXfermode::Mode    fColorMode;
        SkVector            fOffset;
        bool                fPostTranslate; //!< applies to fOffset

        /**
         *  Initial the LayerInfo. Defaults to settings that will draw the
         *  layer with no changes: e.g.
         *      fPaintBits == 0
         *      fColorMode == kDst_Mode
         *      fOffset == (0, 0)
         */
        LayerInfo();
    };

    /**
     *  Call for each layer you want to add (from top to bottom).
     *  This returns a paint you can modify, but that ptr is only valid until
     *  the next call made to addLayer().
     */
    SkPaint* addLayer(const LayerInfo&);

    /**
     *  This layer will draw with the original paint, ad the specified offset
     */
    void addLayer(SkScalar dx, SkScalar dy);
    
    /**
     *  This layer will with the original paint and no offset.
     */
    void addLayer() { this->addLayer(0, 0); }
    
    // overrides from SkDrawLooper
    virtual void init(SkCanvas*);
    virtual bool next(SkCanvas*, SkPaint* paint);

    // must be public for Registrar :(
    static SkFlattenable* CreateProc(SkFlattenableReadBuffer& buffer) {
        return SkNEW_ARGS(SkLayerDrawLooper, (buffer));
    }
    
protected:
    SkLayerDrawLooper(SkFlattenableReadBuffer&);

    // overrides from SkFlattenable
    virtual void flatten(SkFlattenableWriteBuffer& );
    virtual Factory getFactory() { return CreateProc; }
    
private:
    struct Rec {
        Rec*    fNext;
        SkPaint fPaint;
        LayerInfo fInfo;

        static Rec* Reverse(Rec*);
    };
    Rec*    fRecs;
    int     fCount;

    // state-machine during the init/next cycle
    Rec* fCurrRec;

    static void ApplyInfo(SkPaint* dst, const SkPaint& src, const LayerInfo&);

    class MyRegistrar : public SkFlattenable::Registrar {
    public:
        MyRegistrar();
    };
    
    typedef SkDrawLooper INHERITED;
};


#endif
