/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkBGViewArtist_DEFINED
#define SkBGViewArtist_DEFINED

#include "SkView.h"
#include "SkPaint.h"

class SkBGViewArtist : public SkView::Artist {
public:
            SkBGViewArtist(SkColor c = SK_ColorWHITE);
    virtual ~SkBGViewArtist();

    const SkPaint&  paint() const { return fPaint; }
    SkPaint&        paint() { return fPaint; }

protected:
    // overrides
    virtual void onDraw(SkView*, SkCanvas*);
    virtual void onInflate(const SkDOM&, const SkDOM::Node*);

private:
    SkPaint fPaint;
};

#endif

