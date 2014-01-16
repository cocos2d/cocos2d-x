/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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
#include "CCInputDelegate.h"

NS_CC_EXT_BEGIN
/**
 *  @lua NA
 */
class CCComController : public cocos2d::CCComponent, public CCInputDelegate
{
	DECLARE_CLASS_COMPONENT_INFO
public:
   /**
    *  @js ctor
    */
   CCComController(void);
   /**
    *  @js NA
    */
   virtual ~CCComController(void);
   virtual bool init();
   virtual void onEnter();
   virtual void onExit();
   virtual void update(float delta);
   virtual bool isEnabled() const;
   virtual void setEnabled(bool b);
    
   static CCComController* create(void);
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
