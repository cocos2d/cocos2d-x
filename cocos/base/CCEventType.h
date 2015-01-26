/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCEVENT_TYPE_H__
#define __CCEVENT_TYPE_H__

/**
 * This header is used for defining event types using in NotificationCenter
 */

// The application will come to foreground.
// This message is posted in cocos/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp.
#define EVENT_COME_TO_FOREGROUND    "event_come_to_foreground"

// The renderer[android:GLSurfaceView.Renderer  WP8:Cocos2dRenderer] was recreated.
// This message is used for reloading resources before renderer is recreated on Android/WP8.
// This message is posted in cocos/platform/android/javaactivity.cpp and cocos\platform\wp8-xaml\cpp\Cocos2dRenderer.cpp.
#define EVENT_RENDERER_RECREATED    "event_renderer_recreated"

// The application will come to background.
// This message is used for doing something before coming to background, such as save RenderTexture.
// This message is posted in cocos/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxRenderer.cpp and cocos\platform\wp8-xaml\cpp\Cocos2dRenderer.cpp.
#define EVENT_COME_TO_BACKGROUND    "event_come_to_background"

#endif // __CCEVENT_TYPE_H__
