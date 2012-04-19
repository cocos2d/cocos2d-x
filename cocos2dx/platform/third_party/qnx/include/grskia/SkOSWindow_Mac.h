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

#ifndef SkOSWindow_Mac_DEFINED
#define SkOSWindow_Mac_DEFINED

#include <Carbon/Carbon.h>
#include "SkWindow.h"

class SkOSWindow : public SkWindow {
public:
    SkOSWindow(void* hwnd);

    void*   getHWND() const { return fHWND; }
    void*   getHVIEW() const { return fHVIEW; }
    void    updateSize();

    static bool PostEvent(SkEvent* evt, SkEventSinkID, SkMSec delay);

    static OSStatus EventHandler(EventHandlerCallRef inHandler,
                                 EventRef inEvent, void* userData);

    void   doPaint(void* ctx);


    bool attachGL();
    void detachGL();
    void presentGL();

protected:
    // overrides from SkEventSink
    virtual bool onEvent(const SkEvent& evt);
    // overrides from SkWindow
    virtual void onHandleInval(const SkIRect&);
    // overrides from SkView
    virtual void onAddMenu(const SkOSMenu*);
    virtual void onSetTitle(const char[]);
    

private:
    void*   fHWND;
    void*   fHVIEW;
    void*   fAGLCtx;

    typedef SkWindow INHERITED;
};

#endif

