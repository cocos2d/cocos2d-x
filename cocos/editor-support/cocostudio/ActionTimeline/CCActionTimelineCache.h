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
}

NS_TIMELINE_BEGIN

class ActionTimeline;
class Timeline;
class Frame;

class CC_STUDIO_DLL ActionTimelineCache
{
public:    

    /** @~english Gets the singleton.
    *   @~chinese 获取单例。
    * @return @~english The singleton.
    * @~chinese 单例。
    */
    static ActionTimelineCache* getInstance();

    /** @~english Destroys the singleton.
    *   @~chinese 释放单例。
    */
    static void destroyInstance();

    /** @~english Clear action time lines.
    *   @~chinese 清空时间轴列表。
    */
    void purge();

    void init();

    /** @~english Remove action with filename, and also remove other resource relate with this file.
    *   @~chinese 通过文件名移除动作，同时移除与该文件相关的其他资源。
    * @param fileName @~english File name.
    * @~chinese 文件名。
    */
    void removeAction(const std::string& fileName);
    
    /** @~english Create action timeline by file.
    *   @~chinese 通过文件名创建时间轴动画。
    * @param fileName @~english File name.
    * @~chinese 文件名。
    * @return @~english ActionTimeline.
    * @~chinese 时间轴动画。
    */
    static ActionTimeline* createAction(const std::string& fileName);

    /** @~english Clone an action with the specified name from the container. 
    *   @~chinese 通过来自其他容器的指定名称复制一个动画。
    * @param fileName @~english File name.
    * @~chinese 文件名。
    * @return @~english ActionTimeline.
    * @~chinese 时间轴动画。
    */
    ActionTimeline* createActionFromJson(const std::string& fileName);

    /** @~english Load an action time line from file.
    *   @~chinese 从文件中载入时间轴动画。
    * @param fileName @~english File name.
    * @~chinese 文件名。
    * @return @~english ActionTimeline.
    * @~chinese 时间轴动画。
    */
    ActionTimeline* loadAnimationActionWithFile(const std::string& fileName);
    /** @~english Load an action time line from file and content string.
    *   @~chinese 从文件和内容字符串中中载入时间轴动画。
    * @param fileName @~english File name.
    * @~chinese 文件名。
    * @param content @~english Content string.
    * @~chinese 内容字符串。
    * @return @~english ActionTimeline.
    * @~chinese 时间轴动画。
    */
    ActionTimeline* loadAnimationActionWithContent(const std::string&fileName, const std::string& content);
    
    /** @~english Create an action time line from flatbuffer file.
    *   @~chinese 从flatbuffer二进制文件中创建时间轴动画。
    * @param fileName @~english File name.
    * @~chinese 文件名。
    * @return @~english ActionTimeline.
    * @~chinese 时间轴动画。
    */
    ActionTimeline* createActionWithFlatBuffersFile(const std::string& fileName);
    /** @~english Load na action time line from flatbuffer file.
    *   @~chinese 从flatbuffer二进制文件中载入时间轴动画。
    * @param fileName @~english File name.
    * @~chinese 文件名。
    * @return @~english ActionTimeline.
    * @~chinese 时间轴动画。
    */
    ActionTimeline* loadAnimationActionWithFlatBuffersFile(const std::string& fileName);
    
    /** @~english Create an action time line from flatbuffer file for simulator.
    *   @~chinese 从flatbuffer二进制文件中创建时间轴动画(用于模拟器)。
    * @param fileName @~english File name.
    * @~chinese 文件名。
    * @return @~english ActionTimeline.
    * @~chinese 时间轴动画。
    */
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
    
    void loadEasingDataWithFlatBuffers(Frame* frame, const flatbuffers::EasingData* flatbuffers);

protected:

    typedef std::function<Frame*(const rapidjson::Value& json)> FrameCreateFunc;
    typedef std::pair<std::string, FrameCreateFunc> Pair;

    std::unordered_map<std::string, FrameCreateFunc> _funcs;
    cocos2d::Map<std::string, ActionTimeline*> _animationActions;
};

NS_TIMELINE_END

#endif /*__CCTIMELINE_ACTION_CACHE_H__*/
