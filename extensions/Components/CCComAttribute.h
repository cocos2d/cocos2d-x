/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org

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

#ifndef __CC_EXTENTIONS_CCCOMATTRIBUTE_H__
#define __CC_EXTENTIONS_CCCOMATTRIBUTE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "Export.h"
#include <string>

NS_CC_EXT_BEGIN

class EXPORT_DLL CCComAttribute : public cocos2d::CCComponent
{
protected:
    CCComAttribute(void);
    virtual ~CCComAttribute(void);
    
public:
   virtual bool init();
   static CCComAttribute* create(void);

   void setIntValue(const char *key, int value);
   void setDoubleValue(const char *key, double value);
   void setFloatValue(const char *key, float value);
   void setBoolValue(const char *key, bool value);
   void setStringValue(const char *key, const char *value);
   void setCCObjectValue(const char *key, CCObject *value);
   
   int    getAsInt(const char *key);
   double getAsDouble(const char *key);
   float  getAsFloat(const char *key);
   bool   getAsBool(const char *key);
   const char* getAsString(const char *key);
   CCObject* getAsCCObject(const char *key);
   
private:
   CCDictionary *m_pAttributes;  
   
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
