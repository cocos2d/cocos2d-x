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

#ifndef __CCTIMELINE_ACTION_CACHE_H__
#define __CCTIMELINE_ACTION_CACHE_H__

#include "cocos2d.h"
#include "../Json/DictionaryHelper.h"

#include "CCTimeLine.h"

NS_TIMELINE_BEGIN
    
class ActionTimeline;

typedef Frame* (cocos2d::CCObject::*FrameCreateCallback)(const rapidjson::Value& json);
#define FrameCreateCallback_selector(_SELECTOR) (FrameCreateCallback)(&_SELECTOR)

class CC_EX_DLL FrameCreateCallFunc : public cocos2d::CCObject
{
public:
    static FrameCreateCallFunc* create(CCObject* target, FrameCreateCallback callback);

    FrameCreateCallFunc();
    ~FrameCreateCallFunc();
    bool init(CCObject* target, FrameCreateCallback callback);
    Frame* excute(const rapidjson::Value& json);

protected:
    CCObject* _target;
    FrameCreateCallback _callback;
};

class CC_EX_DLL ActionTimelineCache : public cocos2d::CCObject
{
public:
    /** Gets the singleton */
    static ActionTimelineCache* getInstance();

    /** Destroys the singleton */
    static void destroyInstance();

    virtual ~ActionTimelineCache();
    void purge();

    void init();

    /** Remove action with filename, and also remove other resource relate with this file */
    void removeAction(const std::string& fileName);

    /** Clone a action with the specified name from the container. */
    ActionTimeline* createAction(const std::string& fileName);

    ActionTimeline* loadAnimationActionWithFile(const std::string& fileName);
    ActionTimeline* loadAnimationActionWithContent(const std::string&fileName, const std::string& content);
protected:

    Timeline* loadTimeline(const rapidjson::Value& json);

    Frame* loadVisibleFrame     (const rapidjson::Value& json);
    Frame* loadPositionFrame    (const rapidjson::Value& json);
    Frame* loadScaleFrame       (const rapidjson::Value& json);
    Frame* loadSkewFrame        (const rapidjson::Value& json);
    Frame* loadRotationSkewFrame(const rapidjson::Value& json);
    Frame* loadRotationFrame    (const rapidjson::Value& json);
    Frame* loadAnchorPointFrame (const rapidjson::Value& json);
    Frame* loadInnerActionFrame (const rapidjson::Value& json);
    Frame* loadColorFrame       (const rapidjson::Value& json);
    Frame* loadTextureFrame     (const rapidjson::Value& json);
    Frame* loadEventFrame       (const rapidjson::Value& json);
    Frame* loadZOrderFrame      (const rapidjson::Value& json);


protected:

    cocos2d::CCDictionary* _funcs;              // <std::string, FrameCreateCallFunc*>
    cocos2d::CCDictionary* _timelineActions;    // <std::string, ActionTimeline*>
};

NS_TIMELINE_END


#endif /*__CCTIMELINE_ACTION_CACHE_H__*/
