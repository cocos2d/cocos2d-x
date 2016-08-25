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

#include "editor-support/cocostudio/ActionTimeline/CCActionTimelineCache.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "editor-support/cocostudio/ActionTimeline/CCFrame.h"
#include "editor-support/cocostudio/ActionTimeline/CCTimeLine.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimeline.h"
#include "platform/CCFileUtils.h"
#include "2d/CCSpriteFrameCache.h"
#include "2d/CCSpriteFrame.h"

#include "editor-support/cocostudio/CSParseBinary_generated.h"

#include "tinyxml2.h"
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/util.h"

#include "editor-support/cocostudio/FlatBuffersSerialize.h"

#include <fstream>

using namespace cocos2d;
using namespace flatbuffers;

namespace cocostudio {
namespace timeline{

static const char* Property_VisibleForFrame = "VisibleForFrame";
static const char* Property_Position        = "Position";
static const char* Property_Scale           = "Scale";
static const char* Property_RotationSkew    = "RotationSkew";
static const char* Property_CColor          = "CColor";
static const char* Property_FileData        = "FileData";
static const char* Property_FrameEvent      = "FrameEvent";
static const char* Property_Alpha           = "Alpha";
static const char* Property_AnchorPoint     = "AnchorPoint";
static const char* Property_ZOrder          = "ZOrder";
static const char* Property_ActionValue     = "ActionValue";
static const char* Property_BlendValue      = "BlendFunc";

static const char* ACTION           = "action";
static const char* DURATION         = "duration";
static const char* TIMELINES        = "timelines";
static const char* FRAME_TYPE       = "frameType";
static const char* FRAMES           = "frames";
static const char* FRAME_INDEX      = "frameIndex";
static const char* TWEEN            = "tween";
static const char* TIME_SPEED       = "speed";
static const char* ACTION_TAG       = "actionTag";
static const char* INNER_ACTION     = "innerActionType";
static const char* START_FRAME      = "startFrame";

static const char* X                = "x";
static const char* Y                = "y";
static const char* ROTATION         = "rotation";
static const char* RED              = "red";
static const char* GREEN            = "green";
static const char* BLUE             = "blue";
static const char* Value            = "value";


static ActionTimelineCache* _sharedActionCache = nullptr;

ActionTimelineCache* ActionTimelineCache::getInstance()
{
    if (! _sharedActionCache)
    {
        _sharedActionCache = new (std::nothrow) ActionTimelineCache();
        _sharedActionCache->init();
    }

    return _sharedActionCache;
}

void ActionTimelineCache::destroyInstance()
{
    CC_SAFE_DELETE(_sharedActionCache);
}

void ActionTimelineCache::purge()
{
    _animationActions.clear();
}

void ActionTimelineCache::init()
{
    using namespace std::placeholders;
    /*
    _funcs.insert(Pair(FrameType_VisibleFrame,      std::bind(&ActionTimelineCache::loadVisibleFrame,      this, _1)));
    _funcs.insert(Pair(FrameType_PositionFrame,     std::bind(&ActionTimelineCache::loadPositionFrame,     this, _1)));
    _funcs.insert(Pair(FrameType_ScaleFrame,        std::bind(&ActionTimelineCache::loadScaleFrame,        this, _1)));
    _funcs.insert(Pair(FrameType_RotationFrame,     std::bind(&ActionTimelineCache::loadRotationFrame,     this, _1)));
    _funcs.insert(Pair(FrameType_SkewFrame,         std::bind(&ActionTimelineCache::loadSkewFrame,         this, _1)));
    _funcs.insert(Pair(FrameType_RotationSkewFrame, std::bind(&ActionTimelineCache::loadRotationSkewFrame, this, _1)));
    _funcs.insert(Pair(FrameType_AnchorFrame,       std::bind(&ActionTimelineCache::loadAnchorPointFrame,  this, _1)));
    _funcs.insert(Pair(FrameType_InnerActionFrame,  std::bind(&ActionTimelineCache::loadInnerActionFrame,  this, _1)));
    _funcs.insert(Pair(FrameType_ColorFrame,        std::bind(&ActionTimelineCache::loadColorFrame,        this, _1)));
    _funcs.insert(Pair(FrameType_TextureFrame,      std::bind(&ActionTimelineCache::loadTextureFrame,      this, _1)));
    _funcs.insert(Pair(FrameType_EventFrame,        std::bind(&ActionTimelineCache::loadEventFrame,        this, _1)));
    _funcs.insert(Pair(FrameType_ZOrderFrame,       std::bind(&ActionTimelineCache::loadZOrderFrame,       this, _1)));
     */

}

void ActionTimelineCache::removeAction(const std::string& fileName)
{
    if (_animationActions.find(fileName) != _animationActions.end())
    {
        _animationActions.erase(fileName);
    }
}

ActionTimeline* ActionTimelineCache::createAction(const std::string& filename)
{
    std::string path = filename;
    size_t pos = path.find_last_of('.');
    std::string suffix = path.substr(pos + 1, path.length());
    
    ActionTimelineCache* cache = ActionTimelineCache::getInstance();
    
    if (suffix == "csb")
    {
        return cache->createActionWithFlatBuffersFile(filename);
    }
    else if (suffix == "json" || suffix == "ExportJson")
    {
        return cache->createActionFromJson(filename);
    }
    
    return nullptr;
}

ActionTimeline* ActionTimelineCache::createActionFromJson(const std::string& fileName)
{
    ActionTimeline* action = _animationActions.at(fileName);
    if (action == nullptr)
    {
        action = loadAnimationActionWithFile(fileName);
    }
    return action->clone();
}

ActionTimeline* ActionTimelineCache::createActionFromContent(const std::string& fileName, const std::string& content)
{
    ActionTimeline* action = _animationActions.at(fileName);
    if (action == nullptr)
    {
        action = loadAnimationActionWithContent(fileName, content);
    }
    return action->clone();
}

ActionTimeline* ActionTimelineCache::loadAnimationActionWithFile(const std::string& fileName)
{
    // Read content from file
    std::string fullPath    = FileUtils::getInstance()->fullPathForFilename(fileName);
    std::string contentStr  = FileUtils::getInstance()->getStringFromFile(fullPath);

    return loadAnimationActionWithContent(fileName, contentStr);
}

ActionTimeline* ActionTimelineCache::loadAnimationActionWithContent(const std::string&fileName, const std::string& content)
{
    // if already exists an action with filename, then return this action
    ActionTimeline* action = _animationActions.at(fileName);
    if(action)
        return action;

    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    if (doc.HasParseError()) 
    {
        CCLOG("GetParseError %d\n", doc.GetParseError());
    }

    const rapidjson::Value& json = DICTOOL->getSubDictionary_json(doc, ACTION);

    action = ActionTimeline::create();

    action->setDuration(DICTOOL->getIntValue_json(json, DURATION));
    action->setTimeSpeed(DICTOOL->getFloatValue_json(json, TIME_SPEED, 1.0f));

    int timelineLength = DICTOOL->getArrayCount_json(json, TIMELINES);
    for (int i = 0; i<timelineLength; i++)
    {
        const rapidjson::Value& dic = DICTOOL->getSubDictionary_json(json, TIMELINES, i);
        Timeline* timeline = loadTimeline(dic);

        if(timeline)
            action->addTimeline(timeline);
    }

    _animationActions.insert(fileName, action);

    return action;
}

Timeline* ActionTimelineCache::loadTimeline(const rapidjson::Value& json)
{
    Timeline* timeline = nullptr;

    // get frame type 
    const char* frameType = DICTOOL->getStringValue_json(json, FRAME_TYPE);
    if(frameType == nullptr)
        return nullptr;

    if(frameType && _funcs.find(frameType) != _funcs.end())
    {
        timeline = Timeline::create();

        int actionTag = DICTOOL->getIntValue_json(json, ACTION_TAG);
        timeline->setActionTag(actionTag);

        FrameCreateFunc func = _funcs.at(frameType);

        int length = DICTOOL->getArrayCount_json(json, FRAMES);
        for (int i = 0; i<length; i++)
        {
            const rapidjson::Value& dic = DICTOOL->getSubDictionary_json(json, FRAMES, i);

            Frame* frame = nullptr;

            if (func != nullptr)
            {
                frame = func(dic);

                int frameIndex = DICTOOL->getIntValue_json(dic, FRAME_INDEX);
                frame->setFrameIndex(frameIndex);

                bool tween = DICTOOL->getBooleanValue_json(dic, TWEEN, false);
                frame->setTween(tween);
            }

            timeline->addFrame(frame);
        }
    }

    return timeline;
}

Frame* ActionTimelineCache::loadVisibleFrame(const rapidjson::Value& json)
{
    VisibleFrame* frame = VisibleFrame::create();

    bool visible = DICTOOL->getBooleanValue_json(json, Value);
    frame->setVisible(visible);

    return frame;
}

Frame* ActionTimelineCache::loadPositionFrame(const rapidjson::Value& json)
{
    PositionFrame* frame = PositionFrame::create();

    float x = DICTOOL->getFloatValue_json(json, X);
    float y = DICTOOL->getFloatValue_json(json, Y);
    frame->setPosition(Point(x,y));

    return frame;
}

Frame* ActionTimelineCache::loadScaleFrame(const rapidjson::Value& json)
{
   ScaleFrame* frame = ScaleFrame::create();

   float scalex = DICTOOL->getFloatValue_json(json, X);
   float scaley = DICTOOL->getFloatValue_json(json, Y);

   frame->setScaleX(scalex);
   frame->setScaleY(scaley);

    return frame;
}

Frame* ActionTimelineCache::loadSkewFrame(const rapidjson::Value& json)
{
    SkewFrame* frame = SkewFrame::create();

    float skewx = DICTOOL->getFloatValue_json(json, X);
    float skewy = DICTOOL->getFloatValue_json(json, Y);

    frame->setSkewX(skewx);
    frame->setSkewY(skewy);

    return frame;
}

Frame* ActionTimelineCache::loadRotationSkewFrame(const rapidjson::Value& json)
{
    RotationSkewFrame* frame = RotationSkewFrame::create();

    float skewx = DICTOOL->getFloatValue_json(json, X);
    float skewy = DICTOOL->getFloatValue_json(json, Y);

    frame->setSkewX(skewx);
    frame->setSkewY(skewy);

    return frame;
}

Frame* ActionTimelineCache::loadRotationFrame(const rapidjson::Value& json)
{
    RotationFrame* frame = RotationFrame::create();

    float rotation = DICTOOL->getFloatValue_json(json, ROTATION);
    frame->setRotation(rotation);

    return frame;
}

Frame* ActionTimelineCache::loadAnchorPointFrame (const rapidjson::Value& json)
{
    AnchorPointFrame* frame = AnchorPointFrame::create();

    float anchorx = DICTOOL->getFloatValue_json(json, X);
    float anchory = DICTOOL->getFloatValue_json(json, Y);

    frame->setAnchorPoint(Point(anchorx, anchory));

    return frame;
}

Frame* ActionTimelineCache::loadInnerActionFrame(const rapidjson::Value& json)
{
    InnerActionFrame* frame = InnerActionFrame::create();

    InnerActionType type = (InnerActionType)DICTOOL->getIntValue_json(json, INNER_ACTION);
    int startFrame       = DICTOOL->getIntValue_json(json, START_FRAME); 

    frame->setInnerActionType(type);
    frame->setStartFrameIndex(startFrame);

    return frame;
}

Frame* ActionTimelineCache::loadColorFrame(const rapidjson::Value& json)
{
    ColorFrame* frame = ColorFrame::create();

    GLubyte red   = (GLubyte)DICTOOL->getIntValue_json(json, RED);
    GLubyte green = (GLubyte)DICTOOL->getIntValue_json(json, GREEN);
    GLubyte blue  = (GLubyte)DICTOOL->getIntValue_json(json, BLUE);

    frame->setColor(Color3B(red, green, blue));

    return frame;
}

Frame* ActionTimelineCache::loadTextureFrame(const rapidjson::Value& json)
{
    TextureFrame* frame = TextureFrame::create();

    const char* texture = DICTOOL->getStringValue_json(json, Value);

    if(texture != nullptr)
    {
        std::string path = texture;

        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(path);
        if(spriteFrame == nullptr)
        {
            std::string jsonPath = CSLoader::getInstance()->getJsonPath();
            path = jsonPath + texture;
        }

        frame->setTextureName(path);
    }
    return frame;
}

Frame* ActionTimelineCache::loadEventFrame(const rapidjson::Value& json)
{
    EventFrame* frame = EventFrame::create();

    const char* evnt = DICTOOL->getStringValue_json(json, Value);

    if(evnt != nullptr)
        frame->setEvent(evnt);

    return frame;
}

Frame* ActionTimelineCache::loadZOrderFrame(const rapidjson::Value& json)
{
    ZOrderFrame* frame = ZOrderFrame::create();

    int zorder = DICTOOL->getIntValue_json(json, Value);
    frame->setZOrder(zorder);

    return frame;
}

ActionTimeline* ActionTimelineCache::createActionWithFlatBuffersFile(const std::string &fileName)
{
    ActionTimeline* action = _animationActions.at(fileName);
    if (action == NULL)
    {
        action = loadAnimationActionWithFlatBuffersFile(fileName);
    }
    return action->clone();
}

ActionTimeline* ActionTimelineCache::createActionWithDataBuffer(Data data, const std::string &fileName)
{
    ActionTimeline* action = _animationActions.at(fileName);
    if (action == NULL)
    {
        action = loadAnimationWithDataBuffer(data, fileName);
    }
    return action->clone();
}

ActionTimeline* ActionTimelineCache::loadAnimationActionWithFlatBuffersFile(const std::string &fileName)
{
    // if already exists an action with filename, then return this action
    ActionTimeline* action = _animationActions.at(fileName);
    if (action)
        return action;
    
    std::string path = fileName;
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    
    CC_ASSERT(FileUtils::getInstance()->isFileExist(fullPath));
    
    Data buf = FileUtils::getInstance()->getDataFromFile(fullPath);
    action = createActionWithDataBuffer(buf);
    _animationActions.insert(fileName, action);

    return action;
}

ActionTimeline* ActionTimelineCache::loadAnimationWithDataBuffer(const cocos2d::Data& data, const std::string& fileName)
{
    // if already exists an action with filename, then return this action
    ActionTimeline* action = _animationActions.at(fileName);
    if (action)
        return action;

    std::string path = fileName;

    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);

    CC_ASSERT(FileUtils::getInstance()->isFileExist(fullPath));

    action = createActionWithDataBuffer(data);
    _animationActions.insert(fileName, action);

    return action;
}

ActionTimeline* ActionTimelineCache::createActionWithDataBuffer(const cocos2d::Data& data)
{
    auto csparsebinary = GetCSParseBinary(data.getBytes());

    auto nodeAction = csparsebinary->action();
    auto action = ActionTimeline::create();

    int duration = nodeAction->duration();
    action->setDuration(duration);
    float speed = nodeAction->speed();
    action->setTimeSpeed(speed);
    
    auto animationlist = csparsebinary->animationList();
    int animationcount = animationlist->size();
    for (int i = 0; i < animationcount; i++)
    {
        auto animationdata = animationlist->Get(i);
        AnimationInfo info;
        info.name = animationdata->name()->c_str();
        info.startIndex = animationdata->startIndex();
        info.endIndex = animationdata->endIndex();
        action->addAnimationInfo(info);
    }

    auto timeLines = nodeAction->timeLines();
    int timelineLength = timeLines->size();
    std::multimap<std::string,timeline::Timeline*> properTimelineMap;// order the timelines depends property name
    for (int i = 0; i < timelineLength; i++)
    {
        auto timelineFlatBuf = timeLines->Get(i);
        Timeline* timeline = loadTimelineWithFlatBuffers(timelineFlatBuf);
        if (timeline)
        {
            properTimelineMap.insert(std::make_pair(timelineFlatBuf->property()->c_str(), timeline));
        }
    }

    for (const auto& properTimelinePair : properTimelineMap)
    {
        action->addTimeline(properTimelinePair.second);
    }
    return action;
}

Timeline* ActionTimelineCache::loadTimelineWithFlatBuffers(const flatbuffers::TimeLine *flatbuffers)
{
    Timeline* timeline = nullptr;
    
    // property
    std::string property = flatbuffers->property()->c_str();
    if(property == "")
        return nullptr;
    
    
    if(property != "")
    {
        timeline = Timeline::create();
        
        int actionTag = flatbuffers->actionTag();
        timeline->setActionTag(actionTag);
        
        
        auto framesFlatbuf = flatbuffers->frames();
        int length = framesFlatbuf->size();
        for (int i = 0; i < length; i++)
        {
            auto frameFlatbuf = framesFlatbuf->Get(i);
            Frame* frame = nullptr;
            
            if (property == Property_VisibleForFrame)
            {
                auto boolFrame = frameFlatbuf->boolFrame();
                frame = loadVisibleFrameWithFlatBuffers(boolFrame);
            }
            else if (property == Property_Position)
            {
                auto potisionFrame = frameFlatbuf->pointFrame();
                frame = loadPositionFrameWithFlatBuffers(potisionFrame);
            }
            else if (property == Property_Scale)
            {
                auto scaleFrame = frameFlatbuf->scaleFrame();
                frame = loadScaleFrameWithFlatBuffers(scaleFrame);
            }
            else if (property == Property_RotationSkew)
            {
                auto scaleFrame = frameFlatbuf->scaleFrame();
                frame = loadRotationSkewFrameWithFlatBuffers(scaleFrame);
            }
            else if (property == Property_CColor)
            {
                auto colorFrame = frameFlatbuf->colorFrame();
                frame = loadColorFrameWithFlatBuffers(colorFrame);
            }
            else if (property == Property_FrameEvent)
            {
                auto eventFrame = frameFlatbuf->eventFrame();
                frame = loadEventFrameWithFlatBuffers(eventFrame);
            }
            else if (property == Property_FileData)
            {
                auto textureFrame = frameFlatbuf->textureFrame();
                frame = loadTextureFrameWithFlatBuffers(textureFrame);
            }
            else if (property == Property_Alpha)
            {
                auto intFrame = frameFlatbuf->intFrame();
                frame = loadAlphaFrameWithFlatBuffers(intFrame);
            }
            else if (property == Property_AnchorPoint)
            {
                auto scaleFrame = frameFlatbuf->scaleFrame();
                frame = loadAnchorPointFrameWithFlatBuffers(scaleFrame);
            }
            else if (property == Property_ZOrder)
            {
                auto intFrame = frameFlatbuf->intFrame();
                frame = loadZOrderFrameWithFlatBuffers(intFrame);
            }
            else if (property == Property_ActionValue)
            {
                auto innerActionFrame = frameFlatbuf->innerActionFrame();
                frame = loadInnerActionFrameWithFlatBuffers(innerActionFrame);
            }
            else if (property == Property_BlendValue)
            {
                auto blendFrame = frameFlatbuf->blendFrame();
                frame = loadBlendFrameWithFlatBuffers(blendFrame);
            }

            if (!frame)
            {
                CCLOG("frame is invalid.");
                continue;
            }
            timeline->addFrame(frame);
        }
    }
    
    return timeline;
}
    
Frame* ActionTimelineCache::loadVisibleFrameWithFlatBuffers(const flatbuffers::BoolFrame *flatbuffers)
{
    VisibleFrame* frame = VisibleFrame::create();
    
    bool visible = flatbuffers->value() != 0;
    
    frame->setVisible(visible);
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}
    
Frame* ActionTimelineCache::loadPositionFrameWithFlatBuffers(const flatbuffers::PointFrame *flatbuffers)
{
    PositionFrame* frame = PositionFrame::create();
    
    auto f_position = flatbuffers->postion();
    Vec2 position(f_position->x(), f_position->y());
    frame->setPosition(position);
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}

Frame* ActionTimelineCache::loadScaleFrameWithFlatBuffers(const flatbuffers::ScaleFrame *flatbuffers)
{
    ScaleFrame* frame = ScaleFrame::create();
    
    auto f_scale = flatbuffers->scale();
    Vec2 scale(f_scale->scaleX(), f_scale->scaleY());
    frame->setScaleX(scale.x);
    frame->setScaleY(scale.y);
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}

Frame* ActionTimelineCache::loadRotationSkewFrameWithFlatBuffers(const flatbuffers::ScaleFrame *flatbuffers)
{
    RotationSkewFrame* frame = RotationSkewFrame::create();
    
    auto f_scale = flatbuffers->scale();
    Vec2 rotationSkew(f_scale->scaleX(), f_scale->scaleY());
    frame->setSkewX(rotationSkew.x);
    frame->setSkewY(rotationSkew.y);
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}

Frame* ActionTimelineCache::loadColorFrameWithFlatBuffers(const flatbuffers::ColorFrame *flatbuffers)
{
    ColorFrame* frame = ColorFrame::create();
    
    auto f_color = flatbuffers->color();
    Color3B color(f_color->r(), f_color->g(), f_color->b());
    frame->setColor(color);        
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}

Frame* ActionTimelineCache::loadTextureFrameWithFlatBuffers(const flatbuffers::TextureFrame *flatbuffers)
{
    std::string path = "";
    int resourceType = 0;
    std::string plist = "";
    
    TextureFrame* frame = TextureFrame::create();
    
    auto fileNameData = flatbuffers->textureFile();
    
    resourceType = fileNameData->resourceType();
    switch (resourceType)
    {
        case 0:
        {
            path = fileNameData->path()->c_str();
            if (FileUtils::getInstance()->isFileExist(path))
            {
                std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
                path = fullPath;
            }
            else
            {
                path = "";
            }
            break;
        }
            
        case 1:
        {
            plist = fileNameData->plistFile()->c_str();
            if (FileUtils::getInstance()->isFileExist(plist))
            {
                path = fileNameData->path()->c_str();
            }
            else
            {
                path = "";
            }
            break;
        }
            
        default:
            break;
    }
    
    frame->setTextureName(path);
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}
    
Frame* ActionTimelineCache::loadEventFrameWithFlatBuffers(const flatbuffers::EventFrame *flatbuffers)
{
    EventFrame* frame = EventFrame::create();
    
    std::string event = flatbuffers->value()->c_str();
    
    if (event != "")
        frame->setEvent(event);    
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}
    
Frame* ActionTimelineCache::loadAlphaFrameWithFlatBuffers(const flatbuffers::IntFrame *flatbuffers)
{
    AlphaFrame* frame = AlphaFrame::create();
    
    int alpha = flatbuffers->value();
    
    frame->setAlpha(alpha);
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    return frame;
}
    
Frame* ActionTimelineCache::loadAnchorPointFrameWithFlatBuffers(const flatbuffers::ScaleFrame *flatbuffers)
{
    AnchorPointFrame* frame = AnchorPointFrame::create();
    
    auto f_scale = flatbuffers->scale();
    Vec2 scale(f_scale->scaleX(), f_scale->scaleY());
    frame->setAnchorPoint(scale);
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}
    
Frame* ActionTimelineCache::loadZOrderFrameWithFlatBuffers(const flatbuffers::IntFrame *flatbuffers)
{
    ZOrderFrame* frame = ZOrderFrame::create();
    
    int zorder = flatbuffers->value();
    
    frame->setZOrder(zorder);
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}
    
Frame* ActionTimelineCache::loadInnerActionFrameWithFlatBuffers(const flatbuffers::InnerActionFrame *flatbuffers)
{
    InnerActionFrame* frame = InnerActionFrame::create();
    
    InnerActionType innerActionType = (InnerActionType)flatbuffers->innerActionType();
    
    std::string currentAnimationFrame = flatbuffers->currentAniamtionName()->c_str();
    
    int singleFrameIndex = flatbuffers->singleFrameIndex();
    
    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);
    
    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);
    
    frame->setInnerActionType(innerActionType);
    frame->setSingleFrameIndex(singleFrameIndex);
    
    frame->setEnterWithName(true);
    frame->setAnimationName(currentAnimationFrame);
    
    auto easingData = flatbuffers->easingData();
    if (easingData)
    {
        loadEasingDataWithFlatBuffers(frame, easingData);
    }
    
    return frame;
}
    
Frame* ActionTimelineCache::loadBlendFrameWithFlatBuffers(const flatbuffers::BlendFrame* flatbuffers)
{
    BlendFuncFrame* frame = BlendFuncFrame::create();
    cocos2d::BlendFunc blend;
    blend.src = GL_ONE;
    blend.dst = GL_ONE_MINUS_SRC_ALPHA;
    if (nullptr != flatbuffers->blendFunc())
    {
        blend.src = flatbuffers->blendFunc()->src();
        blend.dst = flatbuffers->blendFunc()->dst();
    }
    frame->setBlendFunc(blend);

    int frameIndex = flatbuffers->frameIndex();
    frame->setFrameIndex(frameIndex);

    bool tween = flatbuffers->tween() != 0;
    frame->setTween(tween);

    // easing data won't use in blend frame
    //auto easingData = flatbuffers->easingData();
    //if (easingData)
    //{
    //    loadEasingDataWithFlatBuffers(frame, easingData);
    //}

    return frame;
}

void ActionTimelineCache::loadEasingDataWithFlatBuffers(cocostudio::timeline::Frame *frame,
                                                        const flatbuffers::EasingData *flatbuffers)
{
    int type = flatbuffers->type();
    frame->setTweenType((cocos2d::tweenfunc::TweenType)type);
    auto points = flatbuffers->points();
    if (points)
    {
        std::vector<float> easings;
        for (auto it = points->begin(); it != points->end(); ++it)
        {
            easings.push_back(it->x());
            easings.push_back(it->y());
        }
        frame->setEasingParams(easings);
    }
}
    
ActionTimeline* ActionTimelineCache::createActionWithFlatBuffersForSimulator(const std::string& fileName)
{
    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
    fbs->_isSimulator = true;
    auto builder = fbs->createFlatBuffersWithXMLFileForSimulator(fileName);
    
    ActionTimeline* action = ActionTimeline::create();
    
    auto csparsebinary = GetCSParseBinary(builder->GetBufferPointer());
    auto nodeAction = csparsebinary->action();
    
    action = ActionTimeline::create();
    
    int duration = nodeAction->duration();
    action->setDuration(duration);
    
    float speed = nodeAction->speed();
    action->setTimeSpeed(speed);
    
    auto animationlist = csparsebinary->animationList();
    int animationcount = animationlist->size();
    for (int i = 0; i < animationcount; i++)
    {
        auto animationdata = animationlist->Get(i);
        AnimationInfo info;
        info.name = animationdata->name()->c_str();
        info.startIndex = animationdata->startIndex();
        info.endIndex = animationdata->endIndex();
        action->addAnimationInfo(info);
    }

    auto timeLines = nodeAction->timeLines();
    int timelineLength = timeLines->size();
    std::multimap<std::string, cocostudio::timeline::Timeline*> properTimelineMap;// order the timelines depends property name
    for (int i = 0; i < timelineLength; i++)
    {
        auto timelineFlatBuf = timeLines->Get(i);
        Timeline* timeline = loadTimelineWithFlatBuffers(timelineFlatBuf);
        if (timeline)
        {
            properTimelineMap.insert(std::make_pair(timelineFlatBuf->property()->c_str(), timeline));
        }
    }

    for (const auto& properTimelinePair : properTimelineMap)
    {
        action->addTimeline(properTimelinePair.second);
    }
    fbs->deleteFlatBufferBuilder();
    return action;
}

}
}
