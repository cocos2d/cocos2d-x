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

#ifndef __CC_EXTENTIONS_CCCOMATTRIBUTE_H__
#define __CC_EXTENTIONS_CCCOMATTRIBUTE_H__

#include "CCComBase.h"

NS_CC_EXT_BEGIN
/**
 *  @lua NA
 */
class CC_EX_DLL CCComAttribute : public cocos2d::CCComponent
{
	DECLARE_CLASS_COMPONENT_INFO
protected:
    /**
     *  @js ctor
     */
    CCComAttribute(void);
    /**
     *  @js NA
     */
    virtual ~CCComAttribute(void);
    
public:
   virtual bool init();
   static CCComAttribute* create(void);
   virtual bool serialize(void* r);
   
   void setInt(const char *key, int value);
   void setFloat(const char *key, float value);
   void setBool(const char *key, bool value);
   void setCString(const char *key, const char *value);
   
   int    getInt(const char *key, int def = 0) const;
   float  getFloat(const char *key, float def = 0.0f) const;
   bool   getBool(const char *key, bool def = false) const;
   const char* getCString(const char *key, const char *def = NULL) const;
   
   bool parse(const std::string &jsonPath);
private:
   cocos2d::CCDictionary *_dict;
   rapidjson::Document _doc;
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
