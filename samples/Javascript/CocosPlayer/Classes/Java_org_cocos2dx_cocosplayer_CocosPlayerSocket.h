/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#ifndef __Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_H__
#define __Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_H__

#include <string>

extern "C" {
  extern void updatePairing(const char *code);
  extern void cleanCacheDirJNI();
  extern void setDeviceResolutionJNI(const char* res);
  extern void sendLogMsg(const char* log);
  extern void resetCocosApp();
  extern void runJSApp();
  extern void handle_ccb_run();
  extern void handle_set_orient(bool isPortrait);
  extern void setOrientationJNI(int orient);
}

#endif
