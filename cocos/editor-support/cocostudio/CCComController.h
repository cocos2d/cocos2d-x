/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "editor-support/cocostudio/CCComBase.h"
#include "editor-support/cocostudio/CCInputDelegate.h"
#include "editor-support/cocostudio/CocosStudioExport.h"
#include "2d/CCComponent.h"

namespace cocostudio {

class CC_STUDIO_DLL ComController : public cocos2d::Component, public InputDelegate
{
    DECLARE_CLASS_COMPONENT_INFO
public:
    /**
     *  @js ctor
     */
    ComController();
    
public:
    const static std::string COMPONENT_NAME;

    static ComController* create();

    /**
     * @js NA
     * @lua NA
     */
    virtual ~ComController();

    virtual bool init() override;

    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter() override;

    /**
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;

    /**
    * @js NA
    * @lua NA
    */
    virtual void onAdd() override;

    /**
    * @js NA
    * @lua NA
    */
    virtual void onRemove() override;
    virtual void update(float delta) override;
};

}

#endif  // __CC_EXTENTIONS_CCCOMCONTROLLER_H__
