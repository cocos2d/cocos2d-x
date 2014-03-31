//
// Copyright (c) 2002-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef WINRT_PLATFORM_H_
#define WINRT_PLATFORM_H_


// winrplatform.h: Detects and defines the ANGLE_PLATFORM_WINRT and ANGLE_PLATFORM_WP8 platforms
#include <Windows.h>

// check if WinRT
#if defined(WINAPI_FAMILY)
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
#define ANGLE_PLATFORM_WINRT
#define ANGLE_OS_WINRT
#endif
#endif // !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#endif // #if defined(WINAPI_FAMILY)

// check if Windows Phone 8
#if defined(WINAPI_FAMILY)
#if defined(WINAPI_PARTITION_PHONE) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PHONE)
#define ANGLE_PLATFORM_WP8
#ifndef ANGLE_PLATFORM_WINRT
#define ANGLE_PLATFORM_WINRT
#endif
#define ANGLE_OS_WP8
#ifndef ANGLE_OS_WINRT
#define ANGLE_OS_WINRT
#endif // #ifndef ANGLE_OS_WINRT
#endif // #if defined(WINAPI_PARTITION_PHONE) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PHONE)
#endif // #if defined(WINAPI_FAMILY)


#endif   // WINRT_PLATFORM_H_

