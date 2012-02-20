/*
 * Copyright (C) 2008 The Android Open Source Project
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

#ifndef SkMovie_DEFINED
#define SkMovie_DEFINED

#include "SkRefCnt.h"
#include "SkCanvas.h"

class SkStream;

class SkMovie : public SkRefCnt {
public:
    /** Try to create a movie from the stream. If the stream format is not
        supported, return NULL.
    */
    static SkMovie* DecodeStream(SkStream*);
    /** Try to create a movie from the specified file path. If the file is not
        found, or the format is not supported, return NULL. If a movie is
        returned, the stream may be retained by the movie (via ref()) until
        the movie is finished with it (by calling unref()).
    */
    static SkMovie* DecodeFile(const char path[]);
    /** Try to create a movie from the specified memory.
        If the format is not supported, return NULL. If a movie is returned,
        the data will have been read or copied, and so the caller may free
        it.
    */
    static SkMovie* DecodeMemory(const void* data, size_t length);

    SkMSec  duration();
    int     width();
    int     height();
    int     isOpaque();
    
    /** Specify the time code (between 0...duration) to sample a bitmap
        from the movie. Returns true if this time code generated a different
        bitmap/frame from the previous state (i.e. true means you need to
        redraw).
    */
    bool setTime(SkMSec);

    // return the right bitmap for the current time code
    const SkBitmap& bitmap();
    
protected:
    struct Info {
        SkMSec  fDuration;
        int     fWidth;
        int     fHeight;
        bool    fIsOpaque;
    };

    virtual bool onGetInfo(Info*) = 0;
    virtual bool onSetTime(SkMSec) = 0;
    virtual bool onGetBitmap(SkBitmap*) = 0;

    // visible for subclasses
    SkMovie();

private:
    Info        fInfo;
    SkMSec      fCurrTime;
    SkBitmap    fBitmap;
    bool        fNeedBitmap;
    
    void ensureInfo();
};

#endif
