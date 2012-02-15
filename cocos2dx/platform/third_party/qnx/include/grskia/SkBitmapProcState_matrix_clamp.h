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
 * This is for the ClampX_ClampY instance
 *
 */


#if	!defined(__ARM_HAVE_NEON)
#error	this file can be used only when the NEON unit is enabled
#endif

#include <arm_neon.h>

/*
 * This has been modified on the knowledge that (at the time)
 * we had the following macro definitions in the parent file
 *
 * #define MAKENAME(suffix)        ClampX_ClampY ## suffix
 * #define TILEX_PROCF(fx, max)    SkClampMax((fx) >> 16, max)
 * #define TILEY_PROCF(fy, max)    SkClampMax((fy) >> 16, max)
 * #define TILEX_LOW_BITS(fx, max) (((fx) >> 12) & 0xF)
 * #define TILEY_LOW_BITS(fy, max) (((fy) >> 12) & 0xF)
 * #define CHECK_FOR_DECAL
 */

/* SkClampMax(val,max) -- bound to 0..max */

#define SCALE_NOFILTER_NAME     MAKENAME(_nofilter_scale_neon)
#define SCALE_FILTER_NAME       MAKENAME(_filter_scale_neon)
#define AFFINE_NOFILTER_NAME    MAKENAME(_nofilter_affine_neon)
#define AFFINE_FILTER_NAME      MAKENAME(_filter_affine_neon)
#define PERSP_NOFILTER_NAME     MAKENAME(_nofilter_persp_neon)
#define PERSP_FILTER_NAME       MAKENAME(_filter_persp_neon)

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
        return;
    }
#endif

    int i;

	/* very much like done in decal_nofilter, but with
	 * an extra clamping function applied.
	 * TILEX_PROCF(fx,max) SkClampMax((fx)>>16, max)
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

	    /* build my template(s) */
	    /* avoid the 'lbase unitialized' warning */
	    lbase = vdupq_n_s32(fx);
	    lbase = vsetq_lane_s32(fx1, lbase, 1);
	    lbase = vsetq_lane_s32(fx2, lbase, 2);
	    lbase = vsetq_lane_s32(fx3, lbase, 3);

	    hbase = vaddq_s32(lbase, vdupq_n_s32(dx4));

	    /* store & bump */
	    do {
	        int32x4_t lout;
            int32x4_t hout;
            int16x8_t hi16;

            /* get the hi 16s of all those 32s */
            lout = lbase;
            hout = hbase;
            /* this sets up all lout's then all hout's in hout */
            asm ("vuzpq.16 %q0, %q1" : "+w" (lout), "+w" (hout));
            hi16 = vreinterpretq_s16_s32(hout);

            /* clamp & output */
            hi16 = vmaxq_s16(hi16, vdupq_n_s16(0));
            hi16 = vminq_s16(hi16, vdupq_n_s16(maxX));
            vst1q_s16(dst16, hi16);

            /* but preserving base & on to the next */
            lbase = vaddq_s32 (lbase, vdupq_n_s32(dx8));
            hbase = vaddq_s32 (hbase, vdupq_n_s32(dx8));
            dst16 += 8;
            count -= 8;
            fx += dx8;
	    } while (count >= 8);
	    xy = (uint32_t *) dst16;
	}

    uint16_t* xx = (uint16_t*)xy;
    for (i = count; i > 0; --i) {
        *xx++ = TILEX_PROCF(fx, maxX); fx += dx;
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
    
    /* NEON lets us do an 8x unrolling */
    if (count >= 8) {
        /* SkFixed is 16.16 fixed point */
        SkFixed dx4 = dx * 4;
        SkFixed dy4 = dy * 4;
        SkFixed dx8 = dx * 8;
        SkFixed dy8 = dy * 8;

        int32x4_t xbase, ybase;
        int32x4_t x2base, y2base;
        int16_t *dst16 = (int16_t *) xy;

        /* my sets of maxx/maxy for clamping */
        int32_t maxpair = (maxX&0xffff) | ((maxY&0xffff)<<16);
        int16x8_t maxXY = vreinterpretq_s16_s32(vdupq_n_s32(maxpair));

        /* now build fx/fx+dx/fx+2dx/fx+3dx */
        /* avoid the 'xbase unitialized' warning...*/
        xbase = vdupq_n_s32(fx);
        xbase = vsetq_lane_s32(fx+dx, xbase, 1);
        xbase = vsetq_lane_s32(fx+dx+dx, xbase, 2);
        xbase = vsetq_lane_s32(fx+dx+dx+dx, xbase, 3);

        /* same for fy */
        /* avoid the 'ybase unitialized' warning...*/
        ybase = vdupq_n_s32(fy);
        ybase = vsetq_lane_s32(fy+dy, ybase, 1);
        ybase = vsetq_lane_s32(fy+dy+dy, ybase, 2);
        ybase = vsetq_lane_s32(fy+dy+dy+dy, ybase, 3);

        x2base = vaddq_s32(xbase, vdupq_n_s32(dx4));
        y2base = vaddq_s32(ybase, vdupq_n_s32(dy4));

        /* store & bump */
        do {
            int32x4_t xout, yout;
            int32x4_t x2out, y2out;
            int16x8_t hi16, hi16_2;

            xout = xbase;
            yout = ybase;

            /* overlay y's low16 with hi16 from x */
            /* so we properly shifted xyxyxyxy */
            yout = vsriq_n_s32(yout, xout, 16);
            hi16 = vreinterpretq_s16_s32 (yout);

            /* do the clamping; both guys get 0's */
            hi16 = vmaxq_s16 (hi16, vdupq_n_s16(0));
            hi16 = vminq_s16 (hi16, maxXY);

            vst1q_s16 (dst16, hi16);

            /* and for the other 4 pieces of this iteration */
            x2out = x2base;
            y2out = y2base;

            /* overlay y's low16 with hi16 from x */
            /* so we properly shifted xyxyxyxy */
            y2out = vsriq_n_s32(y2out, x2out, 16);
            hi16_2 = vreinterpretq_s16_s32 (y2out);

            /* do the clamping; both guys get 0's */
            hi16_2 = vmaxq_s16 (hi16_2, vdupq_n_s16(0));
            hi16_2 = vminq_s16 (hi16_2, maxXY);

            /* RBE: gcc regenerates dst16+8 all the time instead
             * of folding it into an addressing mode. *sigh* */
            vst1q_s16 (dst16+8, hi16_2);

            /* moving base and on to the next */
            xbase = vaddq_s32 (xbase, vdupq_n_s32 (dx8));
            ybase = vaddq_s32 (ybase, vdupq_n_s32 (dy8));
            x2base = vaddq_s32 (x2base, vdupq_n_s32 (dx8));
            y2base = vaddq_s32 (y2base, vdupq_n_s32 (dy8));

            dst16 += 16;		/* 8x32 aka 16x16 */
            count -= 8;
            fx += dx8;
            fy += dy8;
        } while (count >= 8);
        xy = (uint32_t *) dst16;
    }

    for (int i = count; i > 0; --i) {
        *xy++ = (TILEY_PROCF(fy, maxY) << 16) | TILEX_PROCF(fx, maxX);
        fx += dx; fy += dy;
    }
}

#undef	DEBUG_PERSP_NOFILTER

static void PERSP_NOFILTER_NAME(const SkBitmapProcState& s,
                                uint32_t* SK_RESTRICT xy,
                                int count, int x, int y) {
    SkASSERT(s.fInvType & SkMatrix::kPerspective_Mask);
    
    PREAMBLE(s);
    /* max{X,Y} are int here, but later shown/assumed to fit in 16 bits */
    int maxX = s.fBitmap->width() - 1;
    int maxY = s.fBitmap->height() - 1;
    
    SkPerspIter   iter(*s.fInvMatrix,
                       SkIntToScalar(x) + SK_ScalarHalf,
                       SkIntToScalar(y) + SK_ScalarHalf, count);
    
    while ((count = iter.next()) != 0) {
        const SkFixed* SK_RESTRICT srcXY = iter.getXY();

#if defined(DEBUG_PERSP_NOFILTER)
	/* debugging stuff */
	const SkFixed *end_srcXY = srcXY + (count*2);
	uint32_t *end_xy = xy + (count);
	const SkFixed *base_srcXY = srcXY;
	uint32_t *base_xy = xy;
	int base_count = count;
#endif

#if 1
        // 2009/9/30: crashes in ApiDemos - Views - Animation - 3D Transition
	// 2009/10/9: reworked to avoid illegal (but allowed by gas) insn

        /* srcXY is a batch of 32 bit numbers X0,Y0,X1,Y1...
         * but we immediately discard the low 16 bits...
         * so what we're going to do is vld4, which will give us
         * xlo,xhi,ylo,yhi distribution and we can ignore the 'lo'
         * parts....
         */
        if (count >= 8) {
            int16_t *mysrc = (int16_t *) srcXY;
            int16_t *mydst = (int16_t *) xy;
            int16x4_t maxX4 = vdup_n_s16((int16_t)maxX);
            int16x4_t maxY4 = vdup_n_s16((int16_t)maxY);
            int16x4_t zero4 = vdup_n_s16(0);

	    /* The constructs with local blocks for register assignments
	     * and asm() instructions is to make keep any hard register
	     * assignments to as small a scope as possible. and to avoid
	     * burning call-preserved hard registers on the vld/vst 
	     * instructions.
	     */

            do {
                int16x4_t xlo, xhi, ylo, yhi;
                int16x4_t x2lo, x2hi, y2lo, y2hi;

                /* vld4 does the de-interleaving for us */
		{
                    register int16x4_t t_xlo asm("d0");
                    register int16x4_t t_xhi asm("d1");
                    register int16x4_t t_ylo asm("d2");
                    register int16x4_t t_yhi asm("d3");

                    asm ("vld4.16	{d0-d3},[%4]  /* xlo=%P0 xhi=%P1 ylo=%P2 yhi=%P3 */"
                        : "=w" (t_xlo), "=w" (t_xhi), "=w" (t_ylo), "=w" (t_yhi)
                        : "r" (mysrc)
                    );
		    xlo = t_xlo;
		    xhi = t_xhi;
		    ylo = t_ylo;
		    yhi = t_yhi;
		}

                /* clamp X>>16 (aka xhi) to 0..maxX */
                xhi = vmax_s16(xhi, zero4);	/* now 0.. */
                xhi = vmin_s16(xhi, maxX4);	/* now 0..maxX */

                /* clamp Y>>16 (aka yhi) to 0..maxY */
                yhi = vmax_s16(yhi, zero4);	/* now 0.. */
                yhi = vmin_s16(yhi, maxY4);	/* now 0..maxY */

		/* deal with the second set of numbers */
		{
                    register int16x4_t t_xlo asm("d4");
                    register int16x4_t t_xhi asm("d5");
                    register int16x4_t t_ylo asm("d6");
                    register int16x4_t t_yhi asm("d7");

                    /* offset == 256 bits == 32 bytes == 8 longs == 16 shorts */
                    asm ("vld4.16	{d4-d7},[%4]  /* xlo=%P0 xhi=%P1 ylo=%P2 yhi=%P3 */"
                        : "=w" (t_xlo), "=w" (t_xhi), "=w" (t_ylo), "=w" (t_yhi)
                        : "r" (mysrc+16)
                    );
		    x2lo = t_xlo;
		    x2hi = t_xhi;
		    y2lo = t_ylo;
		    y2hi = t_yhi;
		}

                /* clamp the second 4 here */

		if (0) { extern void rbe(void); rbe(); }

                /* clamp X>>16 (aka xhi) to 0..maxX */
                x2hi = vmax_s16(x2hi, zero4);	/* now 0.. */
                x2hi = vmin_s16(x2hi, maxX4);	/* now 0..maxX */

                /* clamp Y>>16 (aka yhi) to 0..maxY */
                y2hi = vmax_s16(y2hi, zero4);	/* now 0.. */
                y2hi = vmin_s16(y2hi, maxY4);	/* now 0..maxY */

                /* we're storing as {x,y}s: x is [0], y is [1] */
                /* we'll use vst2 to make this happen */

		{
                    register int16x4_t out_x asm("d16") = xhi;
                    register int16x4_t out_y asm("d17") = yhi;

                    asm ("vst2.16	{d16-d17},[%2]  /* xlo=%P0 xhi=%P1 */"
			:
			: "w" (out_x), "w" (out_y), "r" (mydst)
			);
		}
		{
                    register int16x4_t out_x asm("d18") = x2hi;
                    register int16x4_t out_y asm("d19") = y2hi;

                    asm ("vst2.16	{d18-d19},[%2]  /* xlo=%P0 xhi=%P1 */"
			:
			: "w" (out_x), "w" (out_y), "r" (mydst+8)
			);
		}

                /* XXX: gcc isn't interleaving these with the NEON ops
                 * but i think that all the scoreboarding works out */
                count -= 8;	/* 8 iterations */
                mysrc += 32;	/* 16 longs, aka 32 shorts */
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

#if defined(DEBUG_PERSP_NOFILTER)
	/* for checking our NEON-produced results against vanilla code */
	{
	    int bad = (-1);
	    for (int i = 0; i < base_count; i++) {
            uint32_t val;
            val = (TILEY_PROCF (base_srcXY[i * 2 + 1], maxY) << 16) |
                    TILEX_PROCF (base_srcXY[i * 2 + 0], maxX);

            if (val != base_xy[i]) {
                bad = i;
                break;
            }
	    }
	    if (bad >= 0) {
            SkDebugf("clamp-nofilter-persp failed piece %d\n", bad);
            SkDebugf("    maxX %08x maxY %08x\n", maxX, maxY);
            bad -= (bad & 0x7);	       /* align */
            for (int i = bad; i < bad + 8; i++) {
                uint32_t val;
                val = (TILEY_PROCF (base_srcXY[i * 2 + 1], maxY) << 16) |
                TILEX_PROCF (base_srcXY[i * 2 + 0], maxX);

                SkDebugf("%d: got %08x want %08x srcXY[0] %08x srcXY[1] %08x\n",
                          i, base_xy[i], val, base_srcXY[i * 2 + 0],
                 base_srcXY[i * 2 + 1]);
            }
            SkDebugf ("---\n");
	    }

	    if (end_xy != xy) {
            SkDebugf("xy ended at %08x, should be %08x\n", xy, end_xy);
	    }
	    if (end_srcXY != srcXY) {
            SkDebugf("srcXY ended at %08x, should be %08x\n", srcXY,
                      end_srcXY);
	    }
	}
#endif
    }
}

#undef	DEBUG_PERSP_NOFILTER

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

    if (count >= 4) {
        int32x4_t wide_dx, wide_one;
        int32x4_t wide_fx, wide_fx1, wide_i, wide_lo;
    #if 0
        /* verification hooks -- see below */
        SkFixed debug_fx = fx;
        int count_done = 0;
    #endif

        wide_fx = vdupq_n_s32(fx);
        wide_fx = vsetq_lane_s32(fx+dx, wide_fx, 1);
        wide_fx = vsetq_lane_s32(fx+dx+dx, wide_fx, 2);
        wide_fx = vsetq_lane_s32(fx+dx+dx+dx, wide_fx, 3);

        wide_dx = vdupq_n_s32(dx);
        wide_one = vdupq_n_s32(one);

        while (count >= 4) {
            /* original expands to: 
             * unsigned i = SkClampMax((f) >> 16, max);
             * i = (i << 4) | (((f) >> 12) & 0xF);
             * return (i << 14) | (SkClampMax(((f + one)) >> 16, max));
             */

            /* i = SkClampMax(f>>16, maxX) */
            wide_i = vmaxq_s32(vshrq_n_s32(wide_fx,16), vdupq_n_s32(0));
            wide_i = vminq_s32(wide_i, vdupq_n_s32(maxX));

            /* i<<4 | TILEX_LOW_BITS(fx) */
            wide_lo = vshrq_n_s32(wide_fx, 12);
            wide_i = vsliq_n_s32(wide_lo, wide_i, 4);

            /* i<<14 */
            wide_i = vshlq_n_s32(wide_i, 14);

            /* SkClampMax(((f + one)) >> 16, max) */
            wide_fx1 = vaddq_s32(wide_fx, wide_one);
            wide_fx1 = vmaxq_s32(vshrq_n_s32(wide_fx1,16), vdupq_n_s32(0));
            wide_fx1 = vminq_s32(wide_fx1, vdupq_n_s32(maxX));

            /* final combination */
            wide_i = vorrq_s32(wide_i, wide_fx1);

            vst1q_u32(xy, vreinterpretq_u32_s32(wide_i));

    #if 0
            /* having a verification hook is a good idea */
            /* use debug_fx, debug_fx+dx, etc. */

            for (int i=0;i<4;i++) {
            uint32_t want = PACK_FILTER_X_NAME(debug_fx, maxX, one PREAMBLE_ARG_X);
                    if (xy[i] != want)
                {
                /* print a nastygram */
                SkDebugf("clamp-filter-scale fails\n");
                SkDebugf("got %08x want %08x\n", xy[i], want);
                SkDebugf("fx %08x debug_fx %08x dx %08x done %d\n",
                fx, debug_fx, dx, count_done);
                SkDebugf(" maxX %08x one %08x\n", maxX, one);

                }
            debug_fx += dx;
            count_done++;
            }
    #endif
            wide_fx += vdupq_n_s32(dx+dx+dx+dx);
            fx += dx+dx+dx+dx;
            xy += 4;
            count -= 4;
        }
    }
   
    while (--count >= 0) {
        *xy++ = PACK_FILTER_X_NAME(fx, maxX, one PREAMBLE_ARG_X);
        fx += dx;
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
    
    if (count >= 4) {
        int32x4_t wide_one, wide_i, wide_lo;
        int32x4_t wide_dx, wide_fx, wide_onex, wide_fx1;
        int32x4_t wide_dy, wide_fy, wide_oney, wide_fy1;

    #undef	AFFINE_DEBUG
    #if	defined(AFFINE_DEBUG)
        SkFixed fyp = fy;
        SkFixed fxp = fx;
        uint32_t *xyp = xy;
        int count_done = 0;
    #endif

        wide_fx = vdupq_n_s32(fx);
        wide_fx = vsetq_lane_s32(fx+dx, wide_fx, 1);
        wide_fx = vsetq_lane_s32(fx+dx+dx, wide_fx, 2);
        wide_fx = vsetq_lane_s32(fx+dx+dx+dx, wide_fx, 3);
        wide_dx = vdupq_n_s32(dx);

        wide_fy = vdupq_n_s32(fy);
        wide_fy = vsetq_lane_s32(fy+dy, wide_fy, 1);
        wide_fy = vsetq_lane_s32(fy+dy+dy, wide_fy, 2);
        wide_fy = vsetq_lane_s32(fy+dy+dy+dy, wide_fy, 3);
        wide_dy = vdupq_n_s32(dy);

        wide_onex = vdupq_n_s32(oneX);
        wide_oney = vdupq_n_s32(oneY);

        while (count >= 4) {
            int32x4_t wide_x;
            int32x4_t wide_y;

            /* do the X side, then the Y side, then interleave them */

            /* original expands to: 
             * unsigned i = SkClampMax((f) >> 16, max);
             * i = (i << 4) | (((f) >> 12) & 0xF);
             * return (i << 14) | (SkClampMax(((f + one)) >> 16, max));
             */

            /* i = SkClampMax(f>>16, maxX) */
            wide_i = vmaxq_s32(vshrq_n_s32(wide_fx,16), vdupq_n_s32(0));
            wide_i = vminq_s32(wide_i, vdupq_n_s32(maxX));

            /* i<<4 | TILEX_LOW_BITS(fx) */
            wide_lo = vshrq_n_s32(wide_fx, 12);
            wide_i = vsliq_n_s32(wide_lo, wide_i, 4);

            /* i<<14 */
            wide_i = vshlq_n_s32(wide_i, 14);

            /* SkClampMax(((f + one)) >> 16, max) */
            wide_fx1 = vaddq_s32(wide_fx, wide_onex);
            wide_fx1 = vmaxq_s32(vshrq_n_s32(wide_fx1,16), vdupq_n_s32(0));
            wide_fx1 = vminq_s32(wide_fx1, vdupq_n_s32(maxX));

            /* final combination */
            wide_x = vorrq_s32(wide_i, wide_fx1);

            /* And now the Y side */

            /* i = SkClampMax(f>>16, maxX) */
            wide_i = vmaxq_s32(vshrq_n_s32(wide_fy,16), vdupq_n_s32(0));
            wide_i = vminq_s32(wide_i, vdupq_n_s32(maxY));

            /* i<<4 | TILEX_LOW_BITS(fx) */
            wide_lo = vshrq_n_s32(wide_fy, 12);
            wide_i = vsliq_n_s32(wide_lo, wide_i, 4);

            /* i<<14 */
            wide_i = vshlq_n_s32(wide_i, 14);

            /* SkClampMax(((f + one)) >> 16, max) */
            wide_fy1 = vaddq_s32(wide_fy, wide_oney);
            wide_fy1 = vmaxq_s32(vshrq_n_s32(wide_fy1,16), vdupq_n_s32(0));
            wide_fy1 = vminq_s32(wide_fy1, vdupq_n_s32(maxY));

            /* final combination */
            wide_y = vorrq_s32(wide_i, wide_fy1);

            /* interleave as YXYXYXYX as part of the storing */
	    {
                /* vst2.32 needs side-by-side registers */
                register int32x4_t t_x asm("q1");
                register int32x4_t t_y asm("q0");

		t_x = wide_x; t_y = wide_y;
                asm ("vst2.32	{q0-q1},[%2]  /* y=%q0 x=%q1 */"
                    :
                    : "w" (t_y), "w" (t_x), "r" (xy)
                    );
	    }

    #if	defined(AFFINE_DEBUG)
            /* make sure we're good here -- check the 4 we just output */
            for (int i = 0; i<4;i++) {
            uint32_t val;
            val = PACK_FILTER_Y_NAME(fyp, maxY, oneY PREAMBLE_ARG_Y);
            if (val != xy[i*2+0]) {
                /* print a nastygram */
                SkDebugf("clamp-filter-affine fails\n");
                SkDebugf("[bad-y] got %08x want %08x\n", xy[i*2+0], val);
                SkDebugf("fy %08x fxp %08x fyp %08x dx %08x dy %08x done %d\n",
                fy, fxp, fyp, dx, dy, count_done);
                SkDebugf(" maxY %08x oneY %08x\n", maxY, oneY);
                }
            val = PACK_FILTER_X_NAME(fxp, maxX, oneX PREAMBLE_ARG_X);
            if (val != xy[i*2+1]) {
                /* print a nastygram */
                SkDebugf("clamp-filter-affine fails\n");
                SkDebugf("[bad-x] got %08x want %08x\n", xy[i*2+1], val);
                SkDebugf("fx %08x fxp %08x fyp %08x dx %08x dy %08x done %d\n",
                fx, fxp, fyp, dx, dy, count_done);
                SkDebugf(" maxX %08x one %08x\n", maxX, oneX);
            }
            fyp += dy;
            fxp += dx;
            count_done++;
            }
    #endif

            wide_fx += vdupq_n_s32(dx+dx+dx+dx);
            fx += dx+dx+dx+dx;
            wide_fy += vdupq_n_s32(dy+dy+dy+dy);
            fy += dy+dy+dy+dy;
            xy += 8;		/* 4 x's, 4 y's */
            count -= 4;
        }
    }

    while (--count >= 0) {
        /* NB: writing Y/X */
        *xy++ = PACK_FILTER_Y_NAME(fy, maxY, oneY PREAMBLE_ARG_Y);
        fy += dy;
        *xy++ = PACK_FILTER_X_NAME(fx, maxX, oneX PREAMBLE_ARG_X);
        fx += dx;
    }
}

static void PERSP_FILTER_NAME(const SkBitmapProcState& s,
                              uint32_t* SK_RESTRICT xy, int count,
                              int x, int y) {
    SkASSERT(s.fInvType & SkMatrix::kPerspective_Mask);

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

        if (count >= 4) {
            int32x4_t wide_one, wide_i, wide_lo;
            int32x4_t wide_fx1;
            int32x4_t wide_fy1;
            int32x4_t wide_x, wide_y;

            while (count >= 4) {
                /* RBE: it's good, but:
                 * -- we spill a constant that could be easily regnerated
                 *    [perhaps tweak gcc's NEON constant costs?]
                 */

                /* load src:  x-y-x-y-x-y-x-y */
		{
		    register int32x4_t q0 asm ("q0");
		    register int32x4_t q1 asm ("q1");
                    asm ("vld2.32	{q0-q1},[%2]  /* x=%q0 y=%q1 */"
                         : "=w" (q0), "=w" (q1)
                         : "r" (srcXY));
		    wide_x = q0; wide_y = q1;
		}

                /* do the X side, then the Y side, then interleave them */

                wide_x = vsubq_s32(wide_x, vdupq_n_s32 (oneX>>1));

                /* original expands to: 
                 * unsigned i = SkClampMax((f) >> 16, max);
                 * i = (i << 4) | (((f) >> 12) & 0xF);
                 * return (i << 14) | (SkClampMax(((f + one)) >> 16, max));
                 */

                /* i = SkClampMax(f>>16, maxX) */
                wide_i = vmaxq_s32 (vshrq_n_s32 (wide_x, 16), vdupq_n_s32 (0));
                wide_i = vminq_s32 (wide_i, vdupq_n_s32 (maxX));

                /* i<<4 | TILEX_LOW_BITS(fx) */
                wide_lo = vshrq_n_s32 (wide_x, 12);
                wide_i = vsliq_n_s32 (wide_lo, wide_i, 4);

                /* i<<14 */
                wide_i = vshlq_n_s32 (wide_i, 14);

                /* SkClampMax(((f + one)) >> 16, max) */
                wide_fx1 = vaddq_s32 (wide_x, vdupq_n_s32(oneX));
                wide_fx1 = vmaxq_s32 (vshrq_n_s32 (wide_fx1, 16), vdupq_n_s32 (0));
                wide_fx1 = vminq_s32 (wide_fx1, vdupq_n_s32 (maxX));

                /* final combination */
                wide_x = vorrq_s32 (wide_i, wide_fx1);


                /* And now the Y side */

                wide_y = vsubq_s32(wide_y, vdupq_n_s32 (oneY>>1));

                /* i = SkClampMax(f>>16, maxX) */
                wide_i = vmaxq_s32 (vshrq_n_s32 (wide_y, 16), vdupq_n_s32 (0));
                wide_i = vminq_s32 (wide_i, vdupq_n_s32 (maxY));

                /* i<<4 | TILEX_LOW_BITS(fx) */
                wide_lo = vshrq_n_s32 (wide_y, 12);
                wide_i = vsliq_n_s32 (wide_lo, wide_i, 4);

                /* i<<14 */
                wide_i = vshlq_n_s32 (wide_i, 14);

                /* SkClampMax(((f + one)) >> 16, max) */

                /* wide_fy1_1 and wide_fy1_2 are just temporary variables to
                 * work-around an ICE in debug */
                int32x4_t wide_fy1_1 = vaddq_s32 (wide_y, vdupq_n_s32(oneY));
                int32x4_t wide_fy1_2 = vmaxq_s32 (vshrq_n_s32 (wide_fy1_1, 16),
                                                  vdupq_n_s32 (0));
                wide_fy1 = vminq_s32 (wide_fy1_2, vdupq_n_s32 (maxY));

                /* final combination */
                wide_y = vorrq_s32 (wide_i, wide_fy1);

                /* switch them around; have to do it this way to get them
                 * in the proper registers to match our instruction */

                /* iteration bookkeeping, ahead of the asm() for scheduling */
                srcXY += 2*4;
                count -= 4;

                /* store interleaved as y-x-y-x-y-x-y-x (NB != read order) */
		{
		    register int32x4_t q0 asm ("q0") = wide_y;
		    register int32x4_t q1 asm ("q1") = wide_x;
			
                    asm ("vst2.32	{q0-q1},[%2]  /* y=%q0 x=%q1 */"
                        :
                        : "w" (q0), "w" (q1), "r" (xy));
		}

                /* on to the next iteration */
                /* count, srcXY are handled above */
                xy += 2*4;
            }
        }

        /* was do-while; NEON code invalidates original count>0 assumption */
        while (--count >= 0) { 
	    /* NB: we read x/y, we write y/x */
            *xy++ = PACK_FILTER_Y_NAME(srcXY[1] - (oneY >> 1), maxY,
                                       oneY PREAMBLE_ARG_Y);
            *xy++ = PACK_FILTER_X_NAME(srcXY[0] - (oneX >> 1), maxX,
                                       oneX PREAMBLE_ARG_X);
            srcXY += 2;
        }
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
