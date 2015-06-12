/****************************************************************************
Copyright (c) 2009      On-Core
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (C) 2013-2014 Chukong Technologies Inc.
 
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

/** @~english FBO class that grabs the the contents of the screen  @~chinese 帧缓冲区对象抓取器类(Grabber),它可以用来抓取屏幕上绘制的内容*/
class Grabber : public Ref
{
public:
    /**@~english
     * Constructor.
     * @~chinese 
     * 构造函数。
     * @js ctor
     */
    Grabber(void);
    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     * @js NA
     * @lua NA
     */
    ~Grabber(void);
    /**@~english Init the grab structure, will set the texture as the FBO color attachment.
     * @~chinese 初始化抓取器,把纹理设置成帧缓冲区对象的颜色附件。
     */
    void grab(Texture2D *texture);

    /**@~english Begin capture the screen, which will save the old FBO, clear color, and set the new FBO, clear the background.
     * @~chinese 开始抓取屏幕,它将会保存旧的帧缓冲区对象,清除颜色缓冲区,并设置新的帧缓冲区对象,同时清除背景。
     */
    void beforeRender(Texture2D *texture);

    /**@~english After capture, will reset the old FBO and clear color.
     * @~chinese 在屏幕抓取之后,将重置旧的帧缓冲区对象并清除颜色缓冲区。
     */
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
