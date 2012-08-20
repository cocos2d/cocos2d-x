/*
 * Copyright (C) 2007 The Android Open Source Project
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

#ifndef SkPicture_DEFINED
#define SkPicture_DEFINED

#include "SkRefCnt.h"

class SkCanvas;
class SkPicturePlayback;
class SkPictureRecord;
class SkStream;
class SkWStream;

/** \class SkPicture

    The SkPicture class records the drawing commands made to a canvas, to
    be played back at a later time.
*/
class SK_API SkPicture : public SkRefCnt {
public:
    /** The constructor prepares the picture to record.
        @param width the width of the virtual device the picture records.
        @param height the height of the virtual device the picture records.
    */
    SkPicture();
    /** Make a copy of the contents of src. If src records more drawing after
        this call, those elements will not appear in this picture.
    */
    SkPicture(const SkPicture& src);
    explicit SkPicture(SkStream*);
    virtual ~SkPicture();
    
    /**
     *  Swap the contents of the two pictures. Guaranteed to succeed.
     */
    void swap(SkPicture& other);
    
    enum RecordingFlags {
        /*  This flag specifies that when clipPath() is called, the path will
            be faithfully recorded, but the recording canvas' current clip will
            only see the path's bounds. This speeds up the recording process
            without compromising the fidelity of the playback. The only side-
            effect for recording is that calling getTotalClip() or related
            clip-query calls will reflect the path's bounds, not the actual
            path.
         */
        kUsePathBoundsForClip_RecordingFlag = 0x01
    };

    /** Returns the canvas that records the drawing commands.
        @param width the base width for the picture, as if the recording
                     canvas' bitmap had this width.
        @param height the base width for the picture, as if the recording
                     canvas' bitmap had this height.
        @param recordFlags optional flags that control recording.
        @return the picture canvas.
    */
    SkCanvas* beginRecording(int width, int height, uint32_t recordFlags = 0);

    /** Returns the recording canvas if one is active, or NULL if recording is
        not active. This does not alter the refcnt on the canvas (if present).
    */
    SkCanvas* getRecordingCanvas() const;
    /** Signal that the caller is done recording. This invalidates the canvas
        returned by beginRecording/getRecordingCanvas, and prepares the picture
        for drawing. Note: this happens implicitly the first time the picture
        is drawn.
    */
    void endRecording();
    
    /** Replays the drawing commands on the specified canvas. This internally
        calls endRecording() if that has not already been called.
        @param surface the canvas receiving the drawing commands.
    */
    void draw(SkCanvas* surface);
    
    /** Return the width of the picture's recording canvas. This
        value reflects what was passed to setSize(), and does not necessarily
        reflect the bounds of what has been recorded into the picture.
        @return the width of the picture's recording canvas
    */
    int width() const { return fWidth; }

    /** Return the height of the picture's recording canvas. This
        value reflects what was passed to setSize(), and does not necessarily
        reflect the bounds of what has been recorded into the picture.
        @return the height of the picture's recording canvas
    */
    int height() const { return fHeight; }

    void serialize(SkWStream*) const;

    /** Signals that the caller is prematurely done replaying the drawing
        commands. This can be called from a canvas virtual while the picture
        is drawing. Has no effect if the picture is not drawing. 
    */
    void abortPlayback();
    
private:
    int fWidth, fHeight;
    SkPictureRecord* fRecord;
    SkPicturePlayback* fPlayback;

    friend class SkFlatPicture;
    friend class SkPicturePlayback;
};

class SkAutoPictureRecord : SkNoncopyable {
public:
    SkAutoPictureRecord(SkPicture* pict, int width, int height,
                        uint32_t recordingFlags = 0) {
        fPicture = pict;
        fCanvas = pict->beginRecording(width, height, recordingFlags);
    }
    ~SkAutoPictureRecord() {
        fPicture->endRecording();
    }
    
    /** Return the canvas to draw into for recording into the picture.
    */
    SkCanvas* getRecordingCanvas() const { return fCanvas; }
    
private:
    SkPicture*  fPicture;
    SkCanvas*   fCanvas;
};


#endif
