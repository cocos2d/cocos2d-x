/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef __CCARMATUREDEFINE_H__
#define __CCARMATUREDEFINE_H__

//#define _USRDLL 1

#include "cocos2d.h"
#include "ExtensionMacros.h"

#define VERSION_COMBINED 0.25f

#ifndef ENABLE_PHYSICS_BOX2D_DETECT
#define ENABLE_PHYSICS_BOX2D_DETECT 0
#endif

#ifndef ENABLE_PHYSICS_CHIPMUNK_DETECT
#define ENABLE_PHYSICS_CHIPMUNK_DETECT 1
#endif

#define MAX_VERTEXZ_VALUE 5000000.0f
#define ARMATURE_MAX_CHILD 50.0f
#define ARMATURE_MAX_ZORDER 100
#define ARMATURE_MAX_COUNT ((MAX_VERTEXZ_VALUE) / (ARMATURE_MAX_CHILD) / ARMATURE_MAX_ZORDER)

#define CS_RETURN_IF(cond) if (cond) return
#define CS_RETURN_NULL_IF(cond) if (cond) return NULL;

#endif /*__CCARMATUREDEFINE_H__*/
