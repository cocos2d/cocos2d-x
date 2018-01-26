/*
 * Copyright (C) 2014 The Android Open Source Project
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

#ifndef ANDROID_AUDIO_PRIVATE_H
#define ANDROID_AUDIO_PRIVATE_H

#include <stdint.h>

__BEGIN_DECLS

/* Defines not necessary for external use but kept here to be common
 * to the audio_utils library.
 */

/* struct representation of 3 bytes for packed PCM 24 bit data.
 * The naming follows the ARM NEON convention.
 */
typedef struct {uint8_t c[3];} __attribute__((__packed__)) uint8x3_t;

__END_DECLS

#endif /*ANDROID_AUDIO_PRIVATE_H*/
