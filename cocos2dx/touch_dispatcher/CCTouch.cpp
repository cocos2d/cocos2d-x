/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
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

#include "support/CCPointExtension.h"
#include "CCTouch.h"
#include "CCDirector.h"

NS_CC_BEGIN

// returns the current touch location in screen coordinates
CCPoint CCTouch::getLocationInView() const 
{ 
    return _point; 
}

// returns the previous touch location in screen coordinates
CCPoint CCTouch::getPreviousLocationInView() const 
{ 
    return _prevPoint; 
}

// returns the start touch location in screen coordinates
CCPoint CCTouch::getStartLocationInView() const 
{ 
    return _startPoint; 
}

// returns the current touch location in OpenGL coordinates
CCPoint CCTouch::getLocation() const
{ 
    return CCDirector::sharedDirector()->convertToGL(_point); 
}

// returns the previous touch location in OpenGL coordinates
CCPoint CCTouch::getPreviousLocation() const
{ 
    return CCDirector::sharedDirector()->convertToGL(_prevPoint);  
}

// returns the start touch location in OpenGL coordinates
CCPoint CCTouch::getStartLocation() const
{ 
    return CCDirector::sharedDirector()->convertToGL(_startPoint);  
}

// returns the delta position between the current location and the previous location in OpenGL coordinates
CCPoint CCTouch::getDelta() const
{     
    return ccpSub(getLocation(), getPreviousLocation()); 
}

NS_CC_END