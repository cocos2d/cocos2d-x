/*
    Copyright 2010 Google Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */


#ifndef GrAtlas_DEFINED
#define GrAtlas_DEFINED

#include "GrPoint.h"
#include "GrTexture.h"
#include "GrTDArray.h"

class GrGpu;
class GrRectanizer;
class GrAtlasMgr;

class GrAtlas {
public:
    GrAtlas(GrAtlasMgr*, int plotX, int plotY, GrMaskFormat);

    int getPlotX() const { return fPlot.fX; }
    int getPlotY() const { return fPlot.fY; }
    GrMaskFormat getMaskFormat() const { return fMaskFormat; }

    GrTexture* texture() const { return fTexture; }

    bool addSubImage(int width, int height, const void*, GrIPoint16*);

    static void FreeLList(GrAtlas* atlas) {
        while (atlas) {
            GrAtlas* next = atlas->fNext;
            delete atlas;
            atlas = next;
        }
    }

    // testing
    GrAtlas* nextAtlas() const { return fNext; }

private:
    ~GrAtlas(); // does not try to delete the fNext field

    GrAtlas*        fNext;
    GrTexture*      fTexture;
    GrRectanizer*   fRects;
    GrAtlasMgr*     fAtlasMgr;
    GrIPoint16      fPlot;
    GrMaskFormat    fMaskFormat;

    friend class GrAtlasMgr;
};

class GrPlotMgr;

class GrAtlasMgr {
public:
    GrAtlasMgr(GrGpu*);
    ~GrAtlasMgr();

    GrAtlas* addToAtlas(GrAtlas*, int width, int height, const void*,
                        GrMaskFormat, GrIPoint16*);

    GrTexture* getTexture(GrMaskFormat format) const {
        GrAssert((unsigned)format < kCount_GrMaskFormats);
        return fTexture[format];
    }

    // to be called by ~GrAtlas()
    void freePlot(int x, int y);

private:
    GrGpu*      fGpu;
    GrTexture*  fTexture[kCount_GrMaskFormats];
    GrPlotMgr*  fPlotMgr;
};

#endif


