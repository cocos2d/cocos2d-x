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

#ifndef __CC_EXTENTIONS_CCCOMCONTROLLER_H__
#define __CC_EXTENTIONS_CCCOMCONTROLLER_H__

#include "CCComBase.h"
#include "cocostudio/CCInputDelegate.h"
#include "cocostudio/CocosStudioExport.h"
#include "2d/CCComponent.h"

namespace cocostudio {
 /** 
 @类名 ComController
 @主题 逻辑组件
 @细节 实现对象逻辑的组件，可以获取输入以及每帧调用
 @组 组件
 */
class CC_STUDIO_DLL ComController : public cocos2d::Component, public InputDelegate
{

    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     *  @js ctor
     */
    /**
    @主题 逻辑组件构造函数
    */
    ComController(void);
    
public:
    /**
     * @js NA
     * @lua NA
     */
    /**
    @主题 逻辑组件析构函数
    */
    virtual ~ComController(void);

    /**
    @主题 初始化逻辑组件
    @返回 true 初始化成功，否则false
    */
    virtual bool init() override;
    /**
    @主题 node调用onEnter的时候，会调用组件的onEnter
    @返回 无
    */
    virtual void onEnter() override;
    /**
    @主题 node调用onExit的时候，会调用组件的onExit
    @返回 无
    */
    virtual void onExit() override;
    /**
    @主题 node update会回调到逻辑组件的update方法
    @参数 delta 两帧之间的时间间隔
    @返回 无
    */
    virtual void update(float delta) override;
    /**
    @主题 判断逻辑组件是否可用
    @返回 可用返回true，否则返回false
    */
    virtual bool isEnabled() const override;
    /**
    @主题 设置当前逻辑组件是否可用
    @参数 b true为可用，false为不可用
    @返回 无
    */
    virtual void setEnabled(bool b) override;
   /**
    @主题 创建逻辑组件
    @返回 逻辑组件指针
    */
    static ComController* create(void);
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
