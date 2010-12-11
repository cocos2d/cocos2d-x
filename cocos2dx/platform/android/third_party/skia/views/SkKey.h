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

#ifndef SkKey_DEFINED
#define SkKey_DEFINED

#include "SkTypes.h"

enum SkKey {
    //reordering these to match android.app.KeyEvent 
    kNONE_SkKey,    //corresponds to android's UNKNOWN
    
    kLeftSoftKey_SkKey,
    kRightSoftKey_SkKey,

    kHome_SkKey,    //!< the home key - added to match android
    kBack_SkKey,    //!< (CLR)
    kSend_SkKey,    //!< the green (talk) key
    kEnd_SkKey,     //!< the red key
    
    k0_SkKey,
    k1_SkKey,
    k2_SkKey,
    k3_SkKey,
    k4_SkKey,
    k5_SkKey,
    k6_SkKey,
    k7_SkKey,
    k8_SkKey,
    k9_SkKey,
    kStar_SkKey,    //!< the * key
    kHash_SkKey,    //!< the # key

    kUp_SkKey,
    kDown_SkKey,
    kLeft_SkKey,
    kRight_SkKey,

    kOK_SkKey,      //!< the center key

    kVolUp_SkKey,   //!< volume up - match android
    kVolDown_SkKey, //!< volume down - same
    kPower_SkKey,   //!< power button - same
    kCamera_SkKey,  //!< camera         - same

    kSkKeyCount
};

#endif

