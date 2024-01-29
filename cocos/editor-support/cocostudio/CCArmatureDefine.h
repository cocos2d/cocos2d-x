/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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


#define VERSION_COMBINED 0.30f
#define VERSION_CHANGE_ROTATION_RANGE 1.0f
#define VERSION_COLOR_READING 1.1f

#ifndef AUTO_ADD_SPRITE_FRAME_NAME_PREFIX
#define AUTO_ADD_SPRITE_FRAME_NAME_PREFIX 0
#endif // !AUTO_ADD_SPRITE_FRAME_NAME_PREFIX


#ifndef ENABLE_PHYSICS_BOX2D_DETECT
#define ENABLE_PHYSICS_BOX2D_DETECT 0
#endif

#ifndef ENABLE_PHYSICS_CHIPMUNK_DETECT
#define ENABLE_PHYSICS_CHIPMUNK_DETECT 0
#endif

#ifndef ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX 
#define ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX 1
#endif

#define CS_RETURN_IF(cond) if (cond) return
#define CS_RETURN_NULL_IF(cond) if (cond) return nullptr;

namespace cocostudio {

const char *armatureVersion();

}

#endif /*__CCARMATUREDEFINE_H__*/
