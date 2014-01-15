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

#ifndef __CC_EXTENTIONS_CCCOMATTRIBUTE_H__
#define __CC_EXTENTIONS_CCCOMATTRIBUTE_H__

#include "CCComBase.h"

namespace cocostudio {

class ComAttribute : public cocos2d::Component
{
    DECLARE_CLASS_COMPONENT_INFO
protected:
    /**
     * @js ctor
     */
    ComAttribute(void);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ComAttribute(void);
    
public:
    static ComAttribute* create(void);
    virtual bool init() override;
    virtual bool serialize(void* r) override;
    
    void setInt(const std::string& key, int value);
    void setFloat(const std::string& key, float value);
    void setBool(const std::string& key, bool value);
    void setString(const std::string& key, const std::string& value);
    int getInt(const std::string& key, int def = 0) const;
    float getFloat(const std::string& key, float def = 0.0f) const;
    bool getBool(const std::string& key, bool def = false) const;
    std::string getString(const std::string& key, const std::string& def = "") const;
    bool parse(const std::string &jsonFile);
private:
   cocos2d::ValueMap _dict;
   rapidjson::Document _doc;
};

}

#endif  // __FUNDATION__CCCOMPONENT_H__
