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

#ifndef SkSystemEventTypes_DEFINED
#define SkSystemEventTypes_DEFINED

/*
    The goal of these strings is two-fold:
    1) make funny strings (containing at least one char < 32) to avoid colliding with "user" strings
    2) keep them <= 4 bytes, so we can avoid an allocation in SkEvent::setType()
*/
#define SK_EventType_Delay      "\xd" "lay"
#define SK_EventType_Inval      "nv" "\xa" "l"
#define SK_EventType_Key        "key" "\x1" 
#define SK_EventType_OnEnd "on" "\xe" "n"
#define SK_EventType_Unichar    "\xc" "har"
#define SK_EventType_KeyUp      "key" "\xf"

#endif
