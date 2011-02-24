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

#ifndef SkOSSound_DEFINED
#define SkOSSound_DEFINED

#include "SkTypes.h"

class SkOSSound {
public:
    static void Play(const char path[]);
    static void Pause();
    static void Resume();
    static bool TogglePause();  // returns true if we are now playing, or false if we're now paused
    static void Stop();

    //  volume runs from 0 (silent) to 0xFF (max-volume)
    static uint8_t GetVolume();
    static void SetVolume(U8CPU volume);
};

#endif

