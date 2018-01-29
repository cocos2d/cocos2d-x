/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
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

#ifndef __cocos2d_libs__NodeReaderDefine__
#define __cocos2d_libs__NodeReaderDefine__

#include <string>
#include "base/ObjectFactory.h"

//
//// Reader macro
//

#define DECLARE_CLASS_NODE_READER_INFO \
public: \
static cocos2d::ObjectFactory::TInfo __Type; \
static cocos2d::Ref* createInstance(void); \

#define IMPLEMENT_CLASS_NODE_READER_INFO(className) \
cocos2d::Ref* className::createInstance(void) \
{ \
return className::getInstance(); \
} \
cocos2d::ObjectFactory::TInfo className::__Type(#className, &className::createInstance); \

#define CREATE_CLASS_NODE_READER_INFO(className) \
cocos2d::ObjectFactory::TInfo(#className, &className::createInstance) \

#define FLATSTR_TO_BOOL(str) (str.compare("True") == 0) ? true : false

#endif /* defined(__cocos2d_libs__NodeReaderDefine__) */
