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

#include <unordered_map>
#include "base/CCMap.h"

#include "cocostudio/DictionaryHelper.h"
#include "CCTimelineMacro.h"
#include "cocostudio/CocosStudioExport.h"

namespace protocolbuffers
{
    class NodeAction;
    class TimeLine;
    class Frame;
    class TimeLineBoolFrame;
    class TimeLinePointFrame;
    class TimeLineIntFrame;
    class TimeLineColorFrame;
    class TimeLineTextureFrame;
    class TimeLineStringFrame;
}

namespace tinyxml2
{
    class XMLElement;
}

NS_TIMELINE_BEGIN

class ActionTimeline;
class Timeline;
class Frame;

class CC_STUDIO_DLL ActionTimelineCache
{
public:
    /** Gets the singleton */
    static ActionTimelineCache* getInstance();

    /** Destroys the singleton */
    static void destroyInstance();

    void purge();

    void init();

    /** Remove action with filename, and also remove other resource relate with this file */
    void removeAction(const std::string& fileName);
    
    static ActionTimeline* createAction(const std::string& fileName);

    /** Clone a action with the specified name from the container. */
    ActionTimeline* createActionFromJson(const std::string& fileName);

    ActionTimeline* loadAnimationActionWithFile(const std::string& fileName);
    ActionTimeline* loadAnimationActionWithContent(const std::string&fileName, const std::string& content);
    
    ActionTimeline* createActionFromProtocolBuffers(const std::string& fileName);
    ActionTimeline* loadAnimationActionWithFileFromProtocolBuffers(const std::string& fileName);
    
    ActionTimeline* createActionFromXML(const std::string& fileName);
    ActionTimeline* loadAnimationActionWithFileFromXML(const std::string& fileName);
    ActionTimeline* loadActionTimelineFromXML(const tinyxml2::XMLElement* animationElement);
    
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
    
    Timeline* loadTimelineFromProtocolBuffers(const protocolbuffers::TimeLine& timelineProtobuf);
    
    Frame* loadVisibleFrameFromProtocolBuffers     (const protocolbuffers::TimeLineBoolFrame& frameProtobuf);
    Frame* loadPositionFrameFromProtocolBuffers    (const protocolbuffers::TimeLinePointFrame& frameProtobuf);
    Frame* loadScaleFrameFromProtocolBuffers       (const protocolbuffers::TimeLinePointFrame& frameProtobuf);
	Frame* loadRotationSkewFrameFromProtocolBuffers(const protocolbuffers::TimeLinePointFrame& frameProtobuf);
    Frame* loadAnchorPointFrameFromProtocolBuffers (const protocolbuffers::TimeLinePointFrame& frameProtobuf);
    Frame* loadColorFrameFromProtocolBuffers       (const protocolbuffers::TimeLineColorFrame& frameProtobuf);
    Frame* loadTextureFrameFromProtocolBuffers     (const protocolbuffers::TimeLineTextureFrame& frameProtobuf);
    Frame* loadEventFrameFromProtocolBuffers       (const protocolbuffers::TimeLineStringFrame& frameProtobuf);
    Frame* loadZOrderFrameFromProtocolBuffers      (const protocolbuffers::TimeLineIntFrame& frameProtobuf);
    
    Timeline* loadTimelineFromXML(const tinyxml2::XMLElement* timelineElement);
    
    Frame* loadVisibleFrameFromXML     (const tinyxml2::XMLElement* frameElement);
    Frame* loadPositionFrameFromXML    (const tinyxml2::XMLElement* frameElement);
    Frame* loadScaleFrameFromXML       (const tinyxml2::XMLElement* frameElement);
	Frame* loadRotationSkewFrameFromXML(const tinyxml2::XMLElement* frameElement);
    Frame* loadAnchorPointFrameFromXML (const tinyxml2::XMLElement* frameElement);
    Frame* loadColorFrameFromXML       (const tinyxml2::XMLElement* frameElement);
    Frame* loadTextureFrameFromXML     (const tinyxml2::XMLElement* frameElement);
    Frame* loadEventFrameFromXML       (const tinyxml2::XMLElement* frameElement);
    Frame* loadZOrderFrameFromXML      (const tinyxml2::XMLElement* frameElement);

protected:

    typedef std::function<Frame*(const rapidjson::Value& json)> FrameCreateFunc;
    typedef std::pair<std::string, FrameCreateFunc> Pair;

    std::unordered_map<std::string, FrameCreateFunc> _funcs;
    cocos2d::Map<std::string, ActionTimeline*> _animationActions;
};

NS_TIMELINE_END

#endif /*__CCTIMELINE_ACTION_CACHE_H__*/
