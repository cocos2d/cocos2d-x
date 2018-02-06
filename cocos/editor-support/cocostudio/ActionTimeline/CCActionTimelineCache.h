/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "base/CCData.h"

#include "editor-support/cocostudio/DictionaryHelper.h"
#include "editor-support/cocostudio/ActionTimeline/CCTimelineMacro.h"
#include "editor-support/cocostudio/CocosStudioExport.h"

namespace flatbuffers
{
    class FlatBufferBuilder;
    
    struct NodeAction;
    struct TimeLine;
    struct PointFrame;
    struct ScaleFrame;
    struct ColorFrame;
    struct TextureFrame;
    struct EventFrame;
    struct IntFrame;
    struct BoolFrame;
    struct InnerActionFrame;
    struct EasingData;
    struct BlendFrame;
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
    ActionTimeline* createActionFromContent(const std::string& fileName, const std::string& content);

    ActionTimeline* loadAnimationActionWithFile(const std::string& fileName);
    ActionTimeline* loadAnimationActionWithContent(const std::string&fileName, const std::string& content);
    
    ActionTimeline* createActionWithFlatBuffersFile(const std::string& fileName);
    ActionTimeline* createActionWithDataBuffer(cocos2d::Data data, const std::string &fileName);

    ActionTimeline* loadAnimationActionWithFlatBuffersFile(const std::string& fileName);
    ActionTimeline* loadAnimationWithDataBuffer(const cocos2d::Data& data, const std::string& fileName);
    
    ActionTimeline* createActionWithFlatBuffersForSimulator(const std::string& fileName);
    
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
    
    
    Timeline* loadTimelineWithFlatBuffers(const flatbuffers::TimeLine* flatbuffers);

    Frame* loadVisibleFrameWithFlatBuffers      (const flatbuffers::BoolFrame* flatbuffers);
    Frame* loadPositionFrameWithFlatBuffers     (const flatbuffers::PointFrame* flatbuffers);
    Frame* loadScaleFrameWithFlatBuffers        (const flatbuffers::ScaleFrame* flatbuffers);
    Frame* loadRotationSkewFrameWithFlatBuffers (const flatbuffers::ScaleFrame* flatbuffers);
    Frame* loadColorFrameWithFlatBuffers        (const flatbuffers::ColorFrame* flatbuffers);
    Frame* loadTextureFrameWithFlatBuffers      (const flatbuffers::TextureFrame* flatbuffers);
    Frame* loadEventFrameWithFlatBuffers        (const flatbuffers::EventFrame* flatbuffers);
    Frame* loadAlphaFrameWithFlatBuffers        (const flatbuffers::IntFrame* flatbuffers);
    Frame* loadAnchorPointFrameWithFlatBuffers  (const flatbuffers::ScaleFrame* flatbuffers);
    Frame* loadZOrderFrameWithFlatBuffers       (const flatbuffers::IntFrame* flatbuffers);
    Frame* loadInnerActionFrameWithFlatBuffers  (const flatbuffers::InnerActionFrame* flatbuffers);
    Frame* loadBlendFrameWithFlatBuffers        (const flatbuffers::BlendFrame* flatbuffers);
    void loadEasingDataWithFlatBuffers(Frame* frame, const flatbuffers::EasingData* flatbuffers);

    inline ActionTimeline* createActionWithDataBuffer(const cocos2d::Data& data);
protected:

    typedef std::function<Frame*(const rapidjson::Value& json)> FrameCreateFunc;
    typedef std::pair<std::string, FrameCreateFunc> Pair;

    std::unordered_map<std::string, FrameCreateFunc> _funcs;
    cocos2d::Map<std::string, ActionTimeline*> _animationActions;
};

NS_TIMELINE_END

#endif /*__CCTIMELINE_ACTION_CACHE_H__*/
