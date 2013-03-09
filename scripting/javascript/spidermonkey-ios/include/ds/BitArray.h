/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BitArray_h__
#define BitArray_h__

#include "jstypes.h" 

#include "js/TemplateLib.h" 

namespace js {

template <size_t nbits>
class BitArray {
  private:
    uintptr_t map[nbits / JS_BITS_PER_WORD + (nbits % JS_BITS_PER_WORD == 0 ? 0 : 1)];

  public:
    void clear(bool value) {
        if (value)
            memset(map, 0xFF, sizeof(map));
        else
            memset(map, 0, sizeof(map));
    }

    inline bool get(size_t offset) const {
        uintptr_t index, mask;
        getMarkWordAndMask(offset, &index, &mask);
        return map[index] & mask;
    }

    inline void set(size_t offset) {
        uintptr_t index, mask;
        getMarkWordAndMask(offset, &index, &mask);
        map[index] |= mask;
    }

    inline void unset(size_t offset) {
        uintptr_t index, mask;
        getMarkWordAndMask(offset, &index, &mask);
        map[index] &= ~mask;
    }

  private:
    inline void getMarkWordAndMask(size_t offset,
                                   uintptr_t *indexp, uintptr_t *maskp) const {
        *indexp = offset >> tl::FloorLog2<JS_BITS_PER_WORD>::result;
        *maskp = uintptr_t(1) << (offset & (JS_BITS_PER_WORD - 1));
    }
};

} /* namespace js */

#endif
