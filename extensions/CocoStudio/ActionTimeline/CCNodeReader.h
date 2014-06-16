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

#ifndef __CC_NODE_READER_H__
#define __CC_NODE_READER_H__

#include "CCTimeLine.h"
#include "../Json/DictionaryHelper.h"

namespace cocos2d
{
	namespace extension
	{
		class WidgetPropertiesReader0300;
	}
}

NS_TIMELINE_BEGIN


typedef cocos2d::CCNode* (cocos2d::CCObject::*NodeCreateCallback)(const rapidjson::Value& json, cocos2d::CCNode* parent);
#define NodeCreateCallback_selector(_SELECTOR) (NodeCreateCallback)(&_SELECTOR)

class CC_EX_DLL NodeCreateCallFunc : public cocos2d::CCObject
{
public:
    static NodeCreateCallFunc* create(CCObject* target, NodeCreateCallback callback);

    NodeCreateCallFunc();
    ~NodeCreateCallFunc();
    bool init(CCObject* target, NodeCreateCallback callback);
    cocos2d::CCNode* excute(const rapidjson::Value& json, cocos2d::CCNode* parent);
    
protected:
    CCObject* _target;
    NodeCreateCallback _callback;
};


class TimelineActionData : public cocos2d::CCObject
{
public:
    static TimelineActionData* create(int actionTag);

    virtual void setActionTag(int actionTag) { _actionTag = actionTag; }
    virtual int getActionTag() const { return _actionTag; }
protected:
    TimelineActionData();
    virtual bool init(int actionTag);

    int _actionTag;
};

class CC_EX_DLL NodeReader : public cocos2d::CCObject
{
public:
    static NodeReader* getInstance();
    static void destroyInstance();
    
    NodeReader();
    virtual ~NodeReader();
    void purge();

    void init();

    cocos2d::CCNode* createNode(const std::string& filename);

    cocos2d::CCNode* loadNodeWithFile(const std::string& fileName);
    cocos2d::CCNode* loadNodeWithContent(const std::string& content);

    void setRecordJsonPath(bool record) { _recordJsonPath = record; }
    bool isRecordJsonPath() const { return _recordJsonPath; }

    void setJsonPath(std::string jsonPath) { _jsonPath = jsonPath; }
    std::string getJsonPath() const { return _jsonPath; }
protected:

    cocos2d::CCNode* loadNode(const rapidjson::Value& json, cocos2d::CCNode* parent = NULL);

    void initNode(cocos2d::CCNode* node, const rapidjson::Value& json);

    cocos2d::CCNode* loadSimpleNode(const rapidjson::Value& json, cocos2d::CCNode* parent);
    cocos2d::CCNode* loadSprite(const rapidjson::Value& json, cocos2d::CCNode* parent);
    cocos2d::CCNode* loadParticle(const rapidjson::Value& json, cocos2d::CCNode* parent);
	cocos2d::CCNode* loadWidget(const rapidjson::Value& json, cocos2d::CCNode* parent);

    bool isUiWidget(const std::string& type);

    cocos2d::CCDictionary* _funcs;  // <std::string, NodeCreateCallFunc*>

	cocos2d::extension::WidgetPropertiesReader0300* _guiReader;

    bool _recordJsonPath;
    std::string _jsonPath;
};

NS_TIMELINE_END


#endif /*__CC_NODE_READER_H__*/
