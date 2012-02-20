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

#ifndef SkOSWindow_SDL_DEFINED
#define SkOSWindow_SDL_DEFINED

#include "SDL.h"
#include "SkWindow.h"

class SkGLCanvas;

class SkOSWindow : public SkWindow {
public:
    SkOSWindow(void* screen);
    virtual ~SkOSWindow();

    static bool PostEvent(SkEvent* evt, SkEventSinkID, SkMSec delay);

    void handleSDLEvent(const SDL_Event& event);

protected:
    // overrides from SkWindow
    virtual void onHandleInval(const SkIRect&);
    // overrides from SkView
    virtual void onAddMenu(const SkOSMenu*);
    virtual void onSetTitle(const char[]);

private:
    SDL_Surface* fScreen;
    SDL_Surface* fSurface;
    SkGLCanvas* fGLCanvas;

    void doDraw();

    typedef SkWindow INHERITED;
};

#endif

