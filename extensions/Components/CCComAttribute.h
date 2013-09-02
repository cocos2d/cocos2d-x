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

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCArmature/external_tool/Json/CSContentJsonDictionary.h"
#include <string>

NS_CC_EXT_BEGIN

class CCComAttribute : public cocos2d::CCComponent
{
protected:
    CCComAttribute(void);
	CCComAttribute(const char *pszFileName);
    virtual ~CCComAttribute(void);
    
public:
   virtual bool init();
   static CCComAttribute* create(const char *pszFileName);
   static CCComAttribute* create(void);

   void setInt(const char *key, int value);
   void setDouble(const char *key, double value);
   void setFloat(const char *key, float value);
   void setBool(const char *key, bool value);
   void setCString(const char *key, const char *value);
   void setObject(const char *key, CCObject *value);
   
   int    getInt(const char *key) const;
   double getDouble(const char *key) const;
   float  getFloat(const char *key) const;
   bool   getBool(const char *key) const;
   const char* getCString(const char *key) const;
   CCObject* getObject(const char *key) const;
   
   cs::CSJsonDictionary* getDict();
private:
   CCDictionary *m_pAttributes;  
   cs::CSJsonDictionary *m_pJsonDict;
   std::string m_strFileName;
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
