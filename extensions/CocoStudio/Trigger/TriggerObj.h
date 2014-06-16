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

#ifndef __TRIGGEROBJ_H__
#define __TRIGGEROBJ_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../Json/DictionaryHelper.h"
#include "../Json/CocoLoader.h"
#include <vector>

NS_CC_EXT_BEGIN


class CC_EX_DLL BaseTriggerCondition : public CCObject
{
protected:
    BaseTriggerCondition(void);
public:
	virtual ~BaseTriggerCondition(void);
    virtual bool init();
    virtual bool detect();
	virtual void serialize(const rapidjson::Value &val);
	virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
    virtual void removeAll();
};

class CC_EX_DLL BaseTriggerAction : public CCObject
{
protected:
    BaseTriggerAction(void);
public:
	virtual ~BaseTriggerAction(void);
    virtual bool init();
    virtual void done();
	virtual void serialize(const rapidjson::Value &val);
	virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
    virtual void removeAll();
};


class CC_EX_DLL TriggerObj : public CCObject
{
public:
    TriggerObj(void);
    virtual ~TriggerObj(void);
    virtual bool init();
    static TriggerObj* create(void);
    
    virtual bool detect();
    virtual void done();
    virtual void removeAll();
    virtual void serialize(const rapidjson::Value &val);
	virtual void serialize(cocos2d::extension::CocoLoader *pCocoLoader, cocos2d::extension::stExpCocoNode *pCocoNode);
	unsigned int getId();
	void setEnable(bool bEnable);
	std::vector<int>& getEvents();
  
private:
    CCArray *_cons;
    CCArray *_acts;
	unsigned int _id;
	bool _bEnable;
	std::vector<int> _vInt;
};

NS_CC_EXT_END

#endif


