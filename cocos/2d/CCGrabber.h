/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
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
#ifndef __EFFECTS_CCGRABBER_H__
#define __EFFECTS_CCGRABBER_H__

#include "base/CCRef.h"
#include "platform/CCGL.h"

NS_CC_BEGIN

class Texture2D;

/**
 * @addtogroup _2d
 * @{
 */

/** FBO class that grabs the contents of the screen */
class Grabber : public Ref
{
public:
    /**
    Constructor.
     * @js ctor
     */
    Grabber();
    /**
    Destructor.
     * @js NA
     * @lua NA
     */
    ~Grabber();
    /**Init the grab structure, will set the texture as the FBO color attachment.*/
    void grab(Texture2D *texture);
    /**Begin capture the screen, which will save the old FBO, clear color, and set the new FBO, clear the background.*/
    void beforeRender(Texture2D *texture);
    /**After capture, will reset the old FBO and clear color.*/
    void afterRender(Texture2D *texture);

protected:
    GLuint _FBO;
    GLint _oldFBO;
    GLfloat _oldClearColor[4];
};

// end of effects group
/// @}

NS_CC_END

#endif // __EFFECTS_CCGRABBER_H__
