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

#ifndef SkLayerRasterizer_DEFINED
#define SkLayerRasterizer_DEFINED

#include "SkRasterizer.h"
#include "SkDeque.h"
#include "SkScalar.h"

class SkPaint;

class SkLayerRasterizer : public SkRasterizer {
public:
            SkLayerRasterizer();
    virtual ~SkLayerRasterizer();
    
    void addLayer(const SkPaint& paint)
    {
        this->addLayer(paint, 0, 0);
    }

	/**	Add a new layer (above any previous layers) to the rasterizer.
		The layer will extract those fields that affect the mask from
		the specified paint, but will not retain a reference to the paint
		object itself, so it may be reused without danger of side-effects.
	*/
    void addLayer(const SkPaint& paint, SkScalar dx, SkScalar dy);

    // overrides from SkFlattenable
    virtual Factory getFactory();
    virtual void    flatten(SkFlattenableWriteBuffer&);

protected:
    SkLayerRasterizer(SkFlattenableReadBuffer&);

    // override from SkRasterizer
    virtual bool onRasterize(const SkPath& path, const SkMatrix& matrix,
                             const SkIRect* clipBounds,
                             SkMask* mask, SkMask::CreateMode mode);

private:
    SkDeque fLayers;
    
    static SkFlattenable* CreateProc(SkFlattenableReadBuffer&);

    typedef SkRasterizer INHERITED;
};

#endif
