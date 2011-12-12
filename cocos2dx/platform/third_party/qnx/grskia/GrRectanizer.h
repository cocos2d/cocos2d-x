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


#ifndef GrRectanizer_DEFINED
#define GrRectanizer_DEFINED

#include "GrRect.h"
#include "GrTDArray.h"

class GrRectanizerPurgeListener {
public:
    virtual ~GrRectanizerPurgeListener() {}

    virtual void notifyPurgeStrip(void*, int yCoord) = 0;
};

class GrRectanizer {
public:
    GrRectanizer(int width, int height) : fWidth(width), fHeight(height) {
        GrAssert(width >= 0);
        GrAssert(height >= 0);
    }

    virtual ~GrRectanizer() {}

    int width() const { return fWidth; }
    int height() const { return fHeight; }

    virtual bool addRect(int width, int height, GrIPoint16* loc) = 0;
    virtual float percentFull() const = 0;

    // return the Y-coordinate of a strip that should be purged, given height
    // i.e. return the oldest such strip, or some other criteria. Return -1
    // if there is no candidate
    virtual int stripToPurge(int height) const = 0;
    virtual void purgeStripAtY(int yCoord) = 0;

    /**
     *  Our factory, which returns the subclass du jour
     */
    static GrRectanizer* Factory(int width, int height);

private:
    int fWidth;
    int fHeight;
};

#endif


