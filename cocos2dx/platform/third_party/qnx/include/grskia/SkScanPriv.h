/* libs/graphics/sgl/SkScanPriv.h
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef SkScanPriv_DEFINED
#define SkScanPriv_DEFINED

#include "SkScan.h"
#include "SkBlitter.h"

class SkScanClipper {
public:
    SkScanClipper(SkBlitter* blitter, const SkRegion* clip, const SkIRect& bounds);

    SkBlitter*      getBlitter() const { return fBlitter; }
    const SkIRect*  getClipRect() const { return fClipRect; }

private:
    SkRectClipBlitter   fRectBlitter;
    SkRgnClipBlitter    fRgnBlitter;
    SkBlitter*          fBlitter;
    const SkIRect*      fClipRect;
};

// clipRect == null means path is entirely inside the clip
void sk_fill_path(const SkPath& path, const SkIRect* clipRect,
                  SkBlitter* blitter, int start_y, int stop_y, int shiftEdgesUp,
                  const SkRegion& clipRgn);

// blit the rects above and below avoid, clipped to clip
void sk_blit_above(SkBlitter*, const SkIRect& avoid, const SkRegion& clip);
void sk_blit_below(SkBlitter*, const SkIRect& avoid, const SkRegion& clip);

#endif

