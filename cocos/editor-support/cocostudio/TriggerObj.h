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

#ifndef __TRIGGEROBJ_H__
#define __TRIGGEROBJ_H__

#include "editor-support/cocostudio/CocoStudio.h"
#include "base/CCVector.h"
#include "base/CCEventListenerCustom.h"


namespace cocostudio {

class CC_STUDIO_DLL BaseTriggerCondition : public cocos2d::Ref
{
protected:
    BaseTriggerCondition(void);
public:
    virtual ~BaseTriggerCondition(void);
    virtual bool init();
    virtual bool detect();
    virtual void serialize(const rapidjson::Value &val);
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    virtual void removeAll();
};

class CC_STUDIO_DLL BaseTriggerAction : public cocos2d::Ref
{
protected:
    BaseTriggerAction(void);
public:
    virtual ~BaseTriggerAction(void);
    virtual bool init();
    virtual void done();
    virtual void serialize(const rapidjson::Value &val);
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    virtual void removeAll();
};


class CC_STUDIO_DLL TriggerObj : public cocos2d::Ref
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
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    unsigned int getId();
    void setEnabled(bool enabled);
  
private:
    cocos2d::Vector<BaseTriggerCondition*> _cons;
    cocos2d::Vector<BaseTriggerAction*> _acts;
    unsigned int _id;
    bool _enabled;
    cocos2d::Vector<cocos2d::EventListenerCustom*> _listeners;
};

}

#endif


