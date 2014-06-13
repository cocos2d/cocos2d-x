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
#include "cocostudio/DictionaryHelper.h"


namespace cocostudio {
namespace timeline{

class TimelineActionCache
{
public:
    /** Gets the singleton */
    static TimelineActionCache* getInstance();

    /** Destroys the singleton */
    static void destroyInstance();

    void purge();

    void init();

    /** Remove action with filename, and also remove other resource relate with this file */
    void removeAction(const std::string& fileName);

    /** Clone a action with the specified name from the container. */
    cocos2d::TimelineAction* createAction(const std::string& fileName);

    cocos2d::TimelineAction* loadAnimationActionWithFile(const std::string& fileName);
    cocos2d::TimelineAction* loadAnimationActionWithContent(const std::string&fileName, const std::string& content);
protected:

    cocos2d::Timeline* loadTimeline(const rapidjson::Value& json);

    cocos2d::Frame* loadVisibleFrame     (const rapidjson::Value& json);
    cocos2d::Frame* loadPositionFrame    (const rapidjson::Value& json);
    cocos2d::Frame* loadScaleFrame       (const rapidjson::Value& json);
    cocos2d::Frame* loadSkewFrame        (const rapidjson::Value& json);
    cocos2d::Frame* loadRotationSkewFrame(const rapidjson::Value& json);
    cocos2d::Frame* loadRotationFrame    (const rapidjson::Value& json);
    cocos2d::Frame* loadAnchorPointFrame (const rapidjson::Value& json);
    cocos2d::Frame* loadInnerActionFrame (const rapidjson::Value& json);
    cocos2d::Frame* loadColorFrame       (const rapidjson::Value& json);
    cocos2d::Frame* loadTextureFrame     (const rapidjson::Value& json);
    cocos2d::Frame* loadEventFrame       (const rapidjson::Value& json);
    cocos2d::Frame* loadZOrderFrame      (const rapidjson::Value& json);

protected:

    typedef std::function<cocos2d::Frame*(const rapidjson::Value& json)> FrameCreateFunc;
    typedef std::pair<std::string, FrameCreateFunc> Pair;

    std::unordered_map<std::string, FrameCreateFunc> _funcs;
    cocos2d::Map<std::string, cocos2d::TimelineAction*> _animationActions;
};

}
}


#endif /*__CCTIMELINE_ACTION_CACHE_H__*/
