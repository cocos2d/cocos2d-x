/* NEON optimized code (C) COPYRIGHT 2009 Motorola */
/*
 * Modifications done in-house at Motorola 
 *
 * this is a clone of SkBitmapProcState_matrix.h
 * and has been tuned to work with the NEON unit.
 *
 * Still going back and forth between whether this approach
 * (clone the entire SkBitmapProcState_matrix.h file or
 * if I should put just the modified routines in here and
 * then use a construct like #define DONT_DO_THIS_FUNCTION or
 * something like that...
 *
 * This is for the RepeatX_RepeatY part of the world
 */


#if	!defined(__ARM_HAVE_NEON)
#error	this file can be used only when the NEON unit is enabled
#endif

#include <arm_neon.h>

/*
 * This has been modified on the knowledge that (at the time)
 * we had the following macro definitions in the parent file
 *
 * #define MAKENAME(suffix)        RepeatX_RepeatY ## suffix
 * #define TILEX_PROCF(fx, max)    (((fx) & 0xFFFF) * ((max) + 1) >> 16)
 * #define TILEY_PROCF(fy, max)    (((fy) & 0xFFFF) * ((max) + 1) >> 16)
 * #define TILEX_LOW_BITS(fx, max) ((((fx) & 0xFFFF) * ((max) + 1) >> 12) & 0xF)
 * #define TILEY_LOW_BITS(fy, max) ((((fy) & 0xFFFF) * ((max) + 1) >> 12) & 0xF)
 */

/* SkClampMax(val,max) -- bound to 0..max */

#define SCALE_NOFILTER_NAME     MAKENAME(_nofilter_scale_neon)
#define SCALE_FILTER_NAME       MAKENAME(_filter_scale)
#define AFFINE_NOFILTER_NAME    MAKENAME(_nofilter_affine_neon)
#define AFFINE_FILTER_NAME      MAKENAME(_filter_affine)
#define PERSP_NOFILTER_NAME     MAKENAME(_nofilter_persp_neon)
#define PERSP_FILTER_NAME       MAKENAME(_filter_persp)

#define PACK_FILTER_X_NAME  MAKENAME(_pack_filter_x)
#define PACK_FILTER_Y_NAME  MAKENAME(_pack_filter_y)

#ifndef PREAMBLE
    #define PREAMBLE(state)
    #define PREAMBLE_PARAM_X
    #define PREAMBLE_PARAM_Y
    #define PREAMBLE_ARG_X
    #define PREAMBLE_ARG_Y
#endif

static void SCALE_NOFILTER_NAME(const SkBitmapProcState& s,
                                uint32_t xy[], int count, int x, int y) {
    SkASSERT((s.fInvType & ~(SkMatrix::kTranslate_Mask |
                             SkMatrix::kScale_Mask)) == 0);

    PREAMBLE(s);
    // we store y, x, x, x, x, x

    const unsigned maxX = s.fBitmap->width() - 1;
    SkFixed fx;
    {
        SkPoint pt;
        s.fInvProc(*s.fInvMatrix, SkIntToScalar(x) + SK_ScalarHalf,
                                  SkIntToScalar(y) + SK_ScalarHalf, &pt);
        fx = SkScalarToFixed(pt.fY);
        const unsigned maxY = s.fBitmap->height() - 1;
        *xy++ = TILEY_PROCF(fx, maxY);
        fx = SkScalarToFixed(pt.fX);
    }
    
    if (0 == maxX) {
        // all of the following X values must be 0
        memset(xy, 0, count * sizeof(uint16_t));
        return;
    }

    const SkFixed dx = s.fInvSx;

#ifdef CHECK_FOR_DECAL
    // test if we don't need to apply the tile proc
    if ((unsigned)(fx >> 16) <= maxX &&
        (unsigned)((fx + dx * (count - 1)) >> 16) <= maxX) {
        decal_nofilter_scale(xy, fx, dx, count);
    } else
#endif
    {
        int i;

#if	defined(__ARM_HAVE_NEON)
	/* RBE: very much like done in decal_nofilter ,
	 * but some processing of the 'fx' information 
         * TILEX_PROCF(fx, max)    (((fx) & 0xFFFF) * ((max) + 1) >> 16)
	 */
	if (count >= 8) {
	    /* SkFixed is 16.16 fixed point */
	    SkFixed dx2 = dx+dx;
	    SkFixed dx4 = dx2+dx2;
	    SkFixed dx8 = dx4+dx4;

	    /* now build fx/fx+dx/fx+2dx/fx+3dx */
	    SkFixed fx1, fx2, fx3;
	    int32x2_t lower, upper;
	    int32x4_t lbase, hbase;
	    int16_t *dst16 = (int16_t *)xy;

	    fx1 = fx+dx;
	    fx2 = fx1+dx;
	    fx3 = fx2+dx;

	    lbase = vdupq_n_s32(fx);
	    lbase = vsetq_lane_s32(fx1, lbase, 1);
	    lbase = vsetq_lane_s32(fx2, lbase, 2);
	    lbase = vsetq_lane_s32(fx3, lbase, 3);
	    hbase = vaddq_s32(lbase, vdupq_n_s32(dx4));

	    /* store & bump */
	    do
	    {
	        int32x4_t lout;
		int32x4_t hout;
		int16x8_t hi16;

         	/* TILEX_PROCF(fx, max) (((fx)&0xFFFF)*((max)+1)>> 16) */
		/* mask to low 16 [would like to use uzp tricks) */
	        lout = vandq_s32(lbase, vdupq_n_s32(0xffff));
	        hout = vandq_s32(hbase, vdupq_n_s32(0xffff));
		/* bare multiplication, not SkFixedMul */
		lout = vmulq_s32(lout, vdupq_n_s32(maxX+1));
		hout = vmulq_s32(hout, vdupq_n_s32(maxX+1));

		/* extraction, using uzp */
		/* this is ok -- we want all hi(lout)s then all hi(hout)s */
		asm ("vuzpq.16 %q0, %q1" : "+w" (lout), "+w" (hout));
		hi16 = vreinterpretq_s16_s32(hout);
		vst1q_s16(dst16, hi16);

		/* bump our base on to the next */
		lbase = vaddq_s32 (lbase, vdupq_n_s32(dx8));
		hbase = vaddq_s32 (hbase, vdupq_n_s32(dx8));
		dst16 += 8;
		count -= 8;
		fx += dx8;
	    } while (count >= 8);
	    xy = (uint32_t *) dst16;
	}
#else
	/* simple, portable way of looking at 4 at a crack;
	 * so gets some loop unrolling, but not full SIMD speed
	 */
        for (i = (count >> 2); i > 0; --i) {
            unsigned a, b;
            a = TILEX_PROCF(fx, maxX); fx += dx;
            b = TILEX_PROCF(fx, maxX); fx += dx;
#ifdef SK_CPU_BENDIAN
            *xy++ = (a << 16) | b;
#else
            *xy++ = (b << 16) | a;
#endif
            a = TILEX_PROCF(fx, maxX); fx += dx;
            b = TILEX_PROCF(fx, maxX); fx += dx;
#ifdef SK_CPU_BENDIAN
            *xy++ = (a << 16) | b;
#else
            *xy++ = (b << 16) | a;
#endif
        }
	/* loop doesn't adjust count */
	count -= (count>>2);
#endif
        uint16_t* xx = (uint16_t*)xy;
        for (i = count; i > 0; --i) {
            *xx++ = TILEX_PROCF(fx, maxX); fx += dx;
        }
    }
}

// note: we could special-case on a matrix which is skewed in X but not Y.
// this would require a more general setup thatn SCALE does, but could use
// SCALE's inner loop that only looks at dx


static void AFFINE_NOFILTER_NAME(const SkBitmapProcState& s,
                                 uint32_t xy[], int count, int x, int y) {
    SkASSERT(s.fInvType & SkMatrix::kAffine_Mask);
    SkASSERT((s.fInvType & ~(SkMatrix::kTranslate_Mask |
                             SkMatrix::kScale_Mask |
                             SkMatrix::kAffine_Mask)) == 0);
    
    PREAMBLE(s);
    SkPoint srcPt;
    s.fInvProc(*s.fInvMatrix,
               SkIntToScalar(x) + SK_ScalarHalf,
               SkIntToScalar(y) + SK_ScalarHalf, &srcPt);
    
    SkFixed fx = SkScalarToFixed(srcPt.fX);
    SkFixed fy = SkScalarToFixed(srcPt.fY);
    SkFixed dx = s.fInvSx;
    SkFixed dy = s.fInvKy;
    int maxX = s.fBitmap->width() - 1;
    int maxY = s.fBitmap->height() - 1;

#if 1
    int ocount = count;
    uint32_t *oxy = xy;
    SkFixed bfx = fx, bfy=fy, bdx=dx, bdy=dy;
#endif

#if	defined(__ARM_HAVE_NEON)

	if (0) { extern void rbe(void); rbe(); }

	/* RBE: benchmarks show this eats up time; can we neonize it? */
	/* RBE: very much like done in decal_nofilter ,
	 * but some processing of the 'fx' information 
         * TILEX_PROCF(fx, max)    (((fx) & 0xFFFF) * ((max) + 1) >> 16)
	 */
	if (count >= 4) {
	    /* SkFixed is 16.16 fixed point */
	    SkFixed dx4 = dx*4;
	    SkFixed dy4 = dy*4;

	    /* now build fx/fx+dx/fx+2dx/fx+3dx */
	    int32x2_t lower, upper;
	    int32x4_t xbase, ybase;
	    int16_t *dst16 = (int16_t *)xy;

	    /* synthesize 4x for both X and Y */
	    xbase = vdupq_n_s32(fx);
	    xbase = vsetq_lane_s32(fx+dx, xbase, 1);
	    xbase = vsetq_lane_s32(fx+dx+dx, xbase, 2);
	    xbase = vsetq_lane_s32(fx+dx+dx+dx, xbase, 3);

	    ybase = vdupq_n_s32(fy);
	    ybase = vsetq_lane_s32(fy+dy, ybase, 1);
	    ybase = vsetq_lane_s32(fy+dy+dy, ybase, 2);
	    ybase = vsetq_lane_s32(fy+dy+dy+dy, ybase, 3);

	    /* store & bump */
	    do {
	        int32x4_t xout;
            int32x4_t yout;
            int16x8_t hi16;

         	/* TILEX_PROCF(fx, max) (((fx)&0xFFFF)*((max)+1)>> 16) */
		/* mask to low 16 [would like to use uzp tricks) */
	        xout = vandq_s32(xbase, vdupq_n_s32(0xffff));
	        yout = vandq_s32(ybase, vdupq_n_s32(0xffff));
		/* bare multiplication, not SkFixedMul */
		xout = vmulq_s32(xout, vdupq_n_s32(maxX+1));
		yout = vmulq_s32(yout, vdupq_n_s32(maxY+1));

		/* put hi16 from xout over low16 from yout */
		yout = vsriq_n_s32(yout, xout, 16);

		/* and then yout has the interleaved upper 16's */
		hi16 = vreinterpretq_s16_s32(yout);
		vst1q_s16(dst16, hi16);

		/* bump preserved base & on to the next */
		xbase = vaddq_s32 (xbase, vdupq_n_s32(dx4));
		ybase = vaddq_s32 (ybase, vdupq_n_s32(dy4));
		dst16 += 8;	/* 8 x16 aka 4x32 */
		count -= 4;
		fx += dx4;
		fy += dy4;
	    } while (count >= 4);
	    xy = (uint32_t *) dst16;
	}

#if 0
    /* diagnostics... see whether we agree with the NEON code */
    int bad = 0;
    uint32_t *myxy = oxy;
    int myi = (-1);
    SkFixed ofx = bfx, ofy= bfy, odx= bdx, ody= bdy;
    for (myi = ocount; myi > 0; --myi) {
	uint32_t val = (TILEY_PROCF(ofy, maxY) << 16) | TILEX_PROCF(ofx, maxX);
	if (val != *myxy++) {
		bad++;
		break;
	}
        ofx += odx; ofy += ody;
    }
    if (bad) {
        SkDebugf("repeat-nofilter-affine fails\n");
        SkDebugf("count %d myi %d\n", ocount, myi);
        SkDebugf(" bfx %08x, bdx %08x, bfy %08x bdy %08x\n",
                bfx, bdx, bfy, bdy);
        SkDebugf("maxX %08x maxY %08x\n", maxX, maxY);
    }
#endif
#endif

    for (int i = count; i > 0; --i) {
	/* fx, fy, dx, dy are all 32 bit 16.16 fixed point */
	/* (((fx) & 0xFFFF) * ((max) + 1) >> 16) */
        *xy++ = (TILEY_PROCF(fy, maxY) << 16) | TILEX_PROCF(fx, maxX);
        fx += dx; fy += dy;
    }
}

static void PERSP_NOFILTER_NAME(const SkBitmapProcState& s,
                                uint32_t* SK_RESTRICT xy,
                                int count, int x, int y) {
    SkASSERT(s.fInvType & SkMatrix::kPerspective_Mask);
    
    PREAMBLE(s);
    int maxX = s.fBitmap->width() - 1;
    int maxY = s.fBitmap->height() - 1;
    
    SkPerspIter   iter(*s.fInvMatrix,
                       SkIntToScalar(x) + SK_ScalarHalf,
                       SkIntToScalar(y) + SK_ScalarHalf, count);
    
    while ((count = iter.next()) != 0) {
        const SkFixed* SK_RESTRICT srcXY = iter.getXY();

#if	defined(__ARM_HAVE_NEON)
	/* RBE: */
	/* TILEX_PROCF(fx, max) (((fx) & 0xFFFF) * ((max) + 1) >> 16) */
	/* it's a little more complicated than what I did for the
	 * clamp case -- where I could immediately snip to the top
	 * 16 bits and do my min/max games there.
	 * ... might only be able to get 4x unrolling here
	 */

	/* vld2 to get a set of 32x4's ... */
	/* do the tile[xy]_procf operations */
	/* which includes doing vuzp to get hi16's */
	/* store it */
	/* -- inner loop (other than vld2) can be had from above */

	/* srcXY is a batch of 32 bit numbers X0,Y0,X1,Y1...
	 * but we immediately discard the low 16 bits...
	 * so what we're going to do is vld4, which will give us
	 * xlo,xhi,ylo,yhi distribution and we can ignore the 'lo'
	 * parts....
	 */
	if (0) { extern void rbe(void); rbe(); }
	if (count >= 8) {
	    int32_t *mysrc = (int32_t *) srcXY;
	    int16_t *mydst = (int16_t *) xy;
	    do {
		int32x4_t x, y, x2, y2;
		int16x8_t hi, hi2;

		/* read array of x,y,x,y,x,y */
	        /* vld2 does the de-interleaving for us */
		/* isolate reg-bound scopes; gcc will minimize register
		 * motion if possible; this ensures that we don't lose
		 * a register across a debugging call because it happens
		 * to be bound into a call-clobbered register
		 */
		{
		    register int32x4_t q0 asm("q0");
		    register int32x4_t q1 asm("q1");
		    asm ("vld2.32	{q0-q1},[%2]  /* x=%q0 y=%q1 */"
		        : "=w" (q0), "=w" (q1)
		        : "r" (mysrc)
		        );
		    x = q0; y = q1;
		}

		/* offset == 256 bits == 32 bytes == 8 longs */
		{
		    register int32x4_t q2 asm("q2");
		    register int32x4_t q3 asm("q3");
		    asm ("vld2.32	{q2-q3},[%2]  /* x=%q0 y=%q1 */"
		        : "=w" (q2), "=w" (q3)
		        : "r" (mysrc+8)
		        );
		    x2 = q2; y2 = q3;
		}

         	/* TILEX_PROCF(fx, max) (((fx)&0xFFFF)*((max)+1)>> 16) */
		/* mask to low 16 [would like to use uzp tricks) */
		/* bare multiplication, not SkFixedMul */
	        x = vandq_s32(x, vdupq_n_s32(0xffff));
		x = vmulq_s32(x, vdupq_n_s32(maxX+1));
	        y = vandq_s32(y, vdupq_n_s32(0xffff));
		y = vmulq_s32(y, vdupq_n_s32(maxY+1));

	        x2 = vandq_s32(x2, vdupq_n_s32(0xffff));
		x2 = vmulq_s32(x2, vdupq_n_s32(maxX+1));
	        y2 = vandq_s32(y2, vdupq_n_s32(0xffff));
		y2 = vmulq_s32(y2, vdupq_n_s32(maxY+1));

		/* now collect interleaved high 16's */
		/* (hi-x, hi-y)4  (hi-x2; hi-y2)4 */

		/* extraction, using uzp, leaves hi16's in y */
		y = vsriq_n_s32(y, x, 16);
		hi = vreinterpretq_s16_s32(y);
		vst1q_s16(mydst, hi);

		/* and likewise for the second 8 entries */
		y2 = vsriq_n_s32(y2, x2, 16);
		hi2 = vreinterpretq_s16_s32(y2);
		vst1q_s16(mydst+8, hi2);

		/* XXX: gcc isn't interleaving these with the NEON ops
		 * but i think that all the scoreboarding works out */
		count -= 8;	/* 8 iterations */
		mysrc += 16;	/* 16 longs */
		mydst += 16;	/* 16 shorts, aka 8 longs */
	    } while (count >= 8);
	    /* get xy and srcXY fixed up */
	    srcXY = (const SkFixed *) mysrc;
	    xy = (uint32_t *) mydst;
	}
#endif
        while (--count >= 0) {
            *xy++ = (TILEY_PROCF(srcXY[1], maxY) << 16) |
                     TILEX_PROCF(srcXY[0], maxX);
            srcXY += 2;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

static inline uint32_t PACK_FILTER_Y_NAME(SkFixed f, unsigned max,
                                          SkFixed one PREAMBLE_PARAM_Y) {
    unsigned i = TILEY_PROCF(f, max);
    i = (i << 4) | TILEY_LOW_BITS(f, max);
    return (i << 14) | (TILEY_PROCF((f + one), max));
}

static inline uint32_t PACK_FILTER_X_NAME(SkFixed f, unsigned max,
                                          SkFixed one PREAMBLE_PARAM_X) {
    unsigned i = TILEX_PROCF(f, max);
    i = (i << 4) | TILEX_LOW_BITS(f, max);
    return (i << 14) | (TILEX_PROCF((f + one), max));
}

static void SCALE_FILTER_NAME(const SkBitmapProcState& s,
                              uint32_t xy[], int count, int x, int y) {
    SkASSERT((s.fInvType & ~(SkMatrix::kTranslate_Mask |
                             SkMatrix::kScale_Mask)) == 0);
    SkASSERT(s.fInvKy == 0);

    PREAMBLE(s);
    
    const unsigned maxX = s.fBitmap->width() - 1;
    const SkFixed one = s.fFilterOneX;
    const SkFixed dx = s.fInvSx;
    SkFixed fx;

    {
        SkPoint pt;
        s.fInvProc(*s.fInvMatrix, SkIntToScalar(x) + SK_ScalarHalf,
                                  SkIntToScalar(y) + SK_ScalarHalf, &pt);
        const SkFixed fy = SkScalarToFixed(pt.fY) - (s.fFilterOneY >> 1);
        const unsigned maxY = s.fBitmap->height() - 1;
        // compute our two Y values up front
        *xy++ = PACK_FILTER_Y_NAME(fy, maxY, s.fFilterOneY PREAMBLE_ARG_Y);
        // now initialize fx
        fx = SkScalarToFixed(pt.fX) - (one >> 1);
    }

#ifdef CHECK_FOR_DECAL
    // test if we don't need to apply the tile proc
    if (dx > 0 &&
            (unsigned)(fx >> 16) <= maxX &&
            (unsigned)((fx + dx * (count - 1)) >> 16) < maxX) {
        decal_filter_scale(xy, fx, dx, count);
    } else
#endif
    {
        do {
            *xy++ = PACK_FILTER_X_NAME(fx, maxX, one PREAMBLE_ARG_X);
            fx += dx;
        } while (--count != 0);
    }
}

static void AFFINE_FILTER_NAME(const SkBitmapProcState& s,
                               uint32_t xy[], int count, int x, int y) {
    SkASSERT(s.fInvType & SkMatrix::kAffine_Mask);
    SkASSERT((s.fInvType & ~(SkMatrix::kTranslate_Mask |
                             SkMatrix::kScale_Mask |
                             SkMatrix::kAffine_Mask)) == 0);
    
    PREAMBLE(s);
    SkPoint srcPt;
    s.fInvProc(*s.fInvMatrix,
               SkIntToScalar(x) + SK_ScalarHalf,
               SkIntToScalar(y) + SK_ScalarHalf, &srcPt);
    
    SkFixed oneX = s.fFilterOneX;
    SkFixed oneY = s.fFilterOneY;
    SkFixed fx = SkScalarToFixed(srcPt.fX) - (oneX >> 1);
    SkFixed fy = SkScalarToFixed(srcPt.fY) - (oneY >> 1);
    SkFixed dx = s.fInvSx;
    SkFixed dy = s.fInvKy;
    unsigned maxX = s.fBitmap->width() - 1;
    unsigned maxY = s.fBitmap->height() - 1;
    
    do {
        *xy++ = PACK_FILTER_Y_NAME(fy, maxY, oneY PREAMBLE_ARG_Y);
        fy += dy;
        *xy++ = PACK_FILTER_X_NAME(fx, maxX, oneX PREAMBLE_ARG_X);
        fx += dx;
    } while (--count != 0);
}

static void PERSP_FILTER_NAME(const SkBitmapProcState& s,
                              uint32_t* SK_RESTRICT xy, int count,
                              int x, int y) {
    SkASSERT(s.fInvType & SkMatrix::kPerspective_Mask);

    extern void rbe(void);
    
    PREAMBLE(s);
    unsigned maxX = s.fBitmap->width() - 1;
    unsigned maxY = s.fBitmap->height() - 1;
    SkFixed oneX = s.fFilterOneX;
    SkFixed oneY = s.fFilterOneY;


    
    SkPerspIter   iter(*s.fInvMatrix,
                       SkIntToScalar(x) + SK_ScalarHalf,
                       SkIntToScalar(y) + SK_ScalarHalf, count);

    while ((count = iter.next()) != 0) {
        const SkFixed* SK_RESTRICT srcXY = iter.getXY();
        do {
            *xy++ = PACK_FILTER_Y_NAME(srcXY[1] - (oneY >> 1), maxY,
                                       oneY PREAMBLE_ARG_Y);
            *xy++ = PACK_FILTER_X_NAME(srcXY[0] - (oneX >> 1), maxX,
                                       oneX PREAMBLE_ARG_X);
            srcXY += 2;
        } while (--count != 0);
    }
}

static SkBitmapProcState::MatrixProc MAKENAME(_Procs)[] = {
    SCALE_NOFILTER_NAME,
    SCALE_FILTER_NAME,
    AFFINE_NOFILTER_NAME,
    AFFINE_FILTER_NAME,
    PERSP_NOFILTER_NAME,
    PERSP_FILTER_NAME
};

#undef MAKENAME
#undef TILEX_PROCF
#undef TILEY_PROCF
#ifdef CHECK_FOR_DECAL
    #undef CHECK_FOR_DECAL
#endif

#undef SCALE_NOFILTER_NAME
#undef SCALE_FILTER_NAME
#undef AFFINE_NOFILTER_NAME
#undef AFFINE_FILTER_NAME
#undef PERSP_NOFILTER_NAME
#undef PERSP_FILTER_NAME

#undef PREAMBLE
#undef PREAMBLE_PARAM_X
#undef PREAMBLE_PARAM_Y
#undef PREAMBLE_ARG_X
#undef PREAMBLE_ARG_Y

#undef TILEX_LOW_BITS
#undef TILEY_LOW_BITS
