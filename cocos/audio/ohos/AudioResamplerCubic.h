#pragma once

#include <stdint.h>
#include <sys/types.h>

#include "AudioResampler.h"
#include "AudioBufferProvider.h"

namespace cocos2d { namespace experimental {
// ----------------------------------------------------------------------------

class AudioResamplerCubic : public AudioResampler {
public:
    AudioResamplerCubic(int inChannelCount, int32_t sampleRate) : AudioResampler(inChannelCount, sampleRate, MED_QUALITY) {
    }
    virtual size_t resample(int32_t *out, size_t outFrameCount,
                            AudioBufferProvider *provider);

private:
    // number of bits used in interpolation multiply - 14 bits avoids overflow
    static const int kNumInterpBits = 14;

    // bits to shift the phase fraction down to avoid overflow
    static const int kPreInterpShift = kNumPhaseBits - kNumInterpBits;
    typedef struct {
        int32_t a, b, c, y0, y1, y2, y3;
    } state;
    void init();
    size_t resampleMono16(int32_t *out, size_t outFrameCount,
                          AudioBufferProvider *provider);
    size_t resampleStereo16(int32_t *out, size_t outFrameCount,
                            AudioBufferProvider *provider);
    static inline int32_t interp(state *p, int32_t x) {
        return (((((p->a * x >> 14) + p->b) * x >> 14) + p->c) * x >> 14) + p->y1;
    }
    static inline void advance(state *p, int16_t in) {
        p->y0 = p->y1;
        p->y1 = p->y2;
        p->y2 = p->y3;
        p->y3 = in;
        p->a = (3 * (p->y1 - p->y2) - p->y0 + p->y3) >> 1;
        p->b = (p->y2 << 1) + p->y0 - (((5 * p->y1 + p->y3)) >> 1);
        p->c = (p->y2 - p->y0) >> 1;
    }
    state left, right;
};

// ----------------------------------------------------------------------------
}} // namespace cocos2d { namespace experimental
