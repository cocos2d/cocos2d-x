/****************************************************************************
Copyright (c) 2013 The Chromium Authors

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

#ifndef __CC_MODULE_H__
#define __CC_MODULE_H__

#include <ppapi/cpp/module.h>
#include "ppapi/gles2/gl2ext_ppapi.h"

class CocosPepperModule : public pp::Module
{
public:
    CocosPepperModule() : pp::Module() {}

    virtual bool Init()
    {
        return glInitializePPAPI(get_browser_interface()) == GL_TRUE;
    }

    virtual ~CocosPepperModule() {}

    virtual pp::Instance* CreateInstance(PP_Instance instance)
    {
        return new CocosPepperInstance(instance);
    }
};

#endif /* __CC_INSTANCE_H__ */
