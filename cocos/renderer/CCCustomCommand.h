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


#ifndef _CC_CUSTOMCOMMAND_H_
#define _CC_CUSTOMCOMMAND_H_

#include "renderer/CCRenderCommand.h"

/**
 * @addtogroup support
 * @{
 */

NS_CC_BEGIN
/**
@class CustomCommand
@brief
@~english
Custom command is used for call custom openGL command which can not be done by other commands,
such as stencil function, depth functions etc. The render command is executed by calling a call back function.
 * @~chinese 
 * Custom command用于调用自定义openGL命令,
 * 如模板功能,深度函数等,命令通过调用回调函数来执行。
*/
class CC_DLL CustomCommand : public RenderCommand
{
public:
	/**
    @~english Constructor. 
    @~chinese 构造函数。
    */
    CustomCommand();
    /**
    @~english Destructor. 
    @~chinese 析构函数。
    */
    ~CustomCommand();
    
public:
	/**@~english
	Init function.
  * @~chinese 
  * 初始化。
	@param globalZOrder @~english GlobalZOrder of the render command.
  * @~chinese 命令的GlobalZOrder。
	@param modelViewTransform @~english When in 3D mode, depth sorting needs modelViewTransform.
  * @~chinese 在3d模式下,深度排序需要modelView矩阵。
	@param flags @~english Use to identify that the render command is 3D mode or not.
  * @~chinese 是否处于3D渲染模式。
	*/
    void init(float globalZOrder, const Mat4& modelViewTransform, uint32_t flags);
    /**@~english
    Init function. The render command will be in 2D mode.
     * @~chinese 
     * Init函数。渲染命令将在2d模式下。
    @param globalZOrder @~english GlobalZOrder of the render command.
     * @~chinese 命令的GlobalZOrder。
    */
    void init(float globalZOrder);

    /**@~english
    Execute the render command and call callback functions.
     * @~chinese 
     * 执行渲染命令和调用回调函数。
    */
    void execute();
    //TODO: This function is not used, it should be removed.
    inline bool isTranslucent() { return true; }
    /**@~english Callback function. @~chinese 回调函数。*/
    std::function<void()> func;

protected:
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif //_CC_CUSTOMCOMMAND_H_
