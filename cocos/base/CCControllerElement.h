/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __cocos2d_libs__CCControllerElement__
#define __cocos2d_libs__CCControllerElement__

#include "CCPlatformMacros.h"

NS_CC_BEGIN

/**
 Every controller element knows which collection it belongs to and whether its input value is analog or digital.
 */
class ControllerElement
{
public:
    /**
     Each element can be part of a wider collection of inputs that map to a single logical element. A directional pad (dpad)
     is a logical collection of two axis inputs and thus each axis belongs to the same collection element - the dpad.
     */
    ControllerElement * getCollection();
    
    /**
     Check if the element can support more than just digital values, such as decimal ranges between 0 and 1.
     */
	bool isAnalog() const;
    
protected:
    
    ControllerElement();
    virtual ~ControllerElement();
    
    void setAnalog(bool isAnalog);
    void setCollection(ControllerElement* collection);
    
    bool _isAnalog;
    ControllerElement* _collection;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCControllerElement__) */
