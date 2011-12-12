#ifndef SkDrawProcs_DEFINED
#define SkDrawProcs_DEFINED

#include "SkDraw.h"

class SkBlitter;

struct SkDraw1Glyph {
    const SkDraw*   fDraw;
	SkBounder*		fBounder;
	const SkRegion*	fClip;
	SkBlitter*		fBlitter;
	SkGlyphCache*	fCache;
	SkIRect			fClipBounds;
	
    // The fixed x,y have been pre-rounded (i.e. 1/2 has already been added),
    // so the impls need just trunc down to an int
	typedef void (*Proc)(const SkDraw1Glyph&, SkFixed x, SkFixed y, const SkGlyph&);
	
	Proc init(const SkDraw* draw, SkBlitter* blitter, SkGlyphCache* cache);
};

struct SkDrawProcs {
    SkDraw1Glyph::Proc  fD1GProc;
};

#endif

