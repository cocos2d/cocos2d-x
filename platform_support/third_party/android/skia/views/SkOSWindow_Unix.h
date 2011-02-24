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

#ifndef SkOSWindow_Unix_DEFINED
#define SkOSWindow_Unix_DEFINED

#include "SkWindow.h"
#include <X11/Xlib.h>

struct SkUnixWindow {
  Display* fDisplay;
  Window fWin;
  size_t fOSWin;
};

class SkOSWindow : public SkWindow {
public:
    SkOSWindow(Display* display, Window win);

    void*   getHWND() const { return (void*)fUnixWindow.fWin; }
  void* getDisplay() const { return (void*)fUnixWindow.fDisplay; }
  void* getUnixWindow() const { return (void*)&fUnixWindow; }
  void  setSize(int width, int height);
    void    updateSize();

    static bool PostEvent(SkEvent* evt, SkEventSinkID, SkMSec delay);

    static bool WndProc(SkUnixWindow* w,  XEvent &e);

protected:
    // overrides from SkWindow
    virtual void onHandleInval(const SkIRect&);
    // overrides from SkView
    virtual void onAddMenu(const SkOSMenu*);

private:
    SkUnixWindow  fUnixWindow;

    void    doPaint();

    void*   fMBar;

    typedef SkWindow INHERITED;
};

#endif

