#ifndef DRAGONBONES_JSON_DATA_PARSER_H
#define DRAGONBONES_JSON_DATA_PARSER_H

#include "DataParser.h"
#include "json/document.h"

DRAGONBONES_NAMESPACE_BEGIN

class JSONDataParser : public DataParser
{
protected:
    inline static bool _getBoolean(const rapidjson::Value& rawData, const char*& key, bool defaultValue)
    {
        if (rawData.HasMember(key))
        {
            const auto& value = rawData[key];
            if (value.IsBool())
            {
                return value.GetBool();
            }
            else if (value.IsNumber())
            {
                return value.GetInt() != 0;
            }
            else if (value.IsString())
            {
                const std::string stringValue = value.GetString();
                if (
                    stringValue == "0" ||
                    stringValue == "NaN" ||
                    stringValue == "" ||
                    stringValue == "false" ||
                    stringValue == "null" ||
                    stringValue == "undefined"
                )
                {
                    return false;
                }

                return true;
            }
        }

        return defaultValue;
    }

    inline static unsigned _getNumber(const rapidjson::Value& rawData, const char*& key, unsigned defaultValue)
    {
        if (rawData.HasMember(key))
        {
            return rawData[key].GetUint();
        }

        return defaultValue;
    }

    inline static int _getNumber(const rapidjson::Value& rawData, const char*& key, int defaultValue)
    {
        if (rawData.HasMember(key))
        {
            return rawData[key].GetInt();
        }

        return defaultValue;
    }

    inline static float _getNumber(const rapidjson::Value& rawData, const char*& key, float defaultValue)
    {
        if (rawData.HasMember(key) && rawData[key].IsNumber())
        {
            return rawData[key].GetDouble();
        }

        return defaultValue;
    }

    inline static std::string _getString(const rapidjson::Value& rawData, const char*& key, const std::string& defaultValue)
    {
        if (rawData.HasMember(key))
        {
            if (rawData[key].IsString())
            {
                return rawData[key].GetString();
            }

            //
            return dragonBones::to_string(rawData[key].GetDouble());
        }

        return defaultValue;
    }

    inline static int _getParameter(const rapidjson::Value& rawData, std::size_t index, int defaultValue)
    {
        if (rawData.Size() > index)
        {
            return rawData[(int) index].GetInt();
        }

        return defaultValue;
    }

    inline static float _getParameter(const rapidjson::Value& rawData, std::size_t index, float defaultValue)
    {
        if (rawData.Size() > index)
        {
            return rawData[(int) index].GetFloat();
        }

        return defaultValue;
    }

    inline static std::string _getParameter(const rapidjson::Value& rawData, std::size_t index, const std::string& defaultValue)
    {
        if (rawData.Size() > index)
        {
            return rawData[(int) index].GetString();
        }

        return defaultValue;
    }

public:
    JSONDataParser();
    ~JSONDataParser();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(JSONDataParser);

protected:
    virtual ArmatureData* _parseArmature(const rapidjson::Value& rawData, float scale);
    virtual BoneData* _parseBone(const rapidjson::Value& rawData);
    virtual void _parseIK(const rapidjson::Value& rawData);
    virtual SlotData* _parseSlot(const rapidjson::Value& rawData, int zOrder);
    virtual SkinData* _parseSkin(const rapidjson::Value& rawData);
    virtual SlotDisplayDataSet* _parseSlotDisplaySet(const rapidjson::Value& rawData);
    virtual DisplayData* _parseDisplay(const rapidjson::Value& rawData);
    virtual MeshData* _parseMesh(const rapidjson::Value& rawData);
    virtual AnimationData* _parseAnimation(const rapidjson::Value& rawData) const;
    virtual BoneTimelineData* _parseBoneTimeline(const rapidjson::Value& rawData) const;
    virtual SlotTimelineData* _parseSlotTimeline(const rapidjson::Value& rawData) const;
    virtual FFDTimelineData* _parseFFDTimeline(const rapidjson::Value& rawData) const;
    virtual AnimationFrameData* _parseAnimationFrame(const rapidjson::Value& rawData, unsigned frameStart, unsigned frameCount) const;
    virtual BoneFrameData* _parseBoneFrame(const rapidjson::Value& rawData, unsigned frameStart, unsigned frameCount) const;
    virtual SlotFrameData* _parseSlotFrame(const rapidjson::Value& rawData, unsigned frameStart, unsigned frameCount) const;
    virtual ExtensionFrameData* _parseFFDFrame(const rapidjson::Value& rawData, unsigned frameStart, unsigned frameCount) const;
    virtual void _parseActionData(const rapidjson::Value& rawData, std::vector<ActionData*>& actions, BoneData* bone, SlotData* slot) const;
    virtual void _parseEventData(const rapidjson::Value& rawData, std::vector<EventData*>& events, BoneData* bone, SlotData* slot) const;

    template<class T>
    void _parseTweenFrame(const rapidjson::Value& rawData, TweenFrameData<T>& frame, unsigned frameStart, unsigned frameCount) const
    {
        _parseFrame(rawData, frame, frameStart, frameCount);

        if (frame.duration > 0)
        {
            if (rawData.HasMember(TWEEN_EASING))
            {
                frame.tweenEasing = _getNumber(rawData, TWEEN_EASING, NO_TWEEN);
            }
            else if (this->_isOldData)
            {
                frame.tweenEasing = this->_isAutoTween ? this->_animationTweenEasing : NO_TWEEN;
            }
            
            // TODO
            /*if (this->_isOldData && this->_animation.scale == 1.f && (static_cast<TimelineData*>(this->_timeline))->scale == 1.f && frame.duration * this->_armature->frameRate < 2.f) 
            {
                frame.tweenEasing = NO_TWEEN;
            }*/

            if (rawData.HasMember(CURVE))
            {
                auto& rawCurve = rawData[CURVE];
                std::vector<float> curve;
                curve.reserve(rawCurve.Size());

                for (size_t i = 0, l = rawCurve.Size(); i < l; ++i)
                {
                    curve.push_back(rawCurve[i].GetDouble());
                }

                TweenFrameData<T>::samplingCurve(curve, frameCount, frame.curve);
            }
        }
        else
        {
            frame.tweenEasing = NO_TWEEN;
            frame.curve.clear();
        }
    }

    template<class T>
    void _parseFrame(const rapidjson::Value& rawData, FrameData<T>& frame, unsigned frameStart, unsigned frameCount) const
    {
        frame.position = (float)frameStart / this->_armature->frameRate;
        frame.duration = (float)frameCount / this->_armature->frameRate;
    }

    template<class T>
    void _parseTimeline(
        const rapidjson::Value& rawData,
        TimelineData<T>& timeline,
        const std::function<T*(const rapidjson::Value& rawData, unsigned frameStart, unsigned frameCount)>& frameParser) const
    {
        timeline.scale = _getNumber(rawData, SCALE, 1.f);
        timeline.offset = _getNumber(rawData, OFFSET, 0.f);

        _timeline = (void*)(&timeline);

        if (rawData.HasMember(FRAME))
        {
            const auto& rawFrames = rawData[FRAME];
            if (!rawFrames.Empty())
            {
                if (rawFrames.Size() == 1)
                {
                    const auto& frameObject = rawFrames[0];
                    const auto frame = frameParser(frameObject, 0, _getNumber(frameObject, DURATION, (unsigned)1));
                    timeline.frames.reserve(1);
                    timeline.frames.push_back(frame);
                }
                else
                {
                    timeline.frames.reserve(this->_animation->frameCount + 1);

                    unsigned frameStart = 0;
                    unsigned frameCount = 0;
                    T* frame = nullptr;
                    T* prevFrame = nullptr;

                    for (unsigned i = 0, iW = 0, l = this->_animation->frameCount + 1; i < l; ++i)
                    {
                        if (frameStart + frameCount <= i && iW < rawFrames.Size())
                        {
                            const auto& frameObject = rawFrames[iW++];
                            frameStart = i;
                            frameCount = _getNumber(frameObject, DURATION, 1);
                            frame = frameParser(frameObject, frameStart, frameCount);

                            if (prevFrame)
                            {
                                prevFrame->next = frame;
                                frame->prev = prevFrame;

                                if (this->_isOldData) 
                                {
                                    const auto tweenFrame = dynamic_cast<TweenFrameData<T>*>(frame);
                                    if (tweenFrame && frameObject.HasMember(DISPLAY_INDEX) && frameObject[DISPLAY_INDEX].GetInt() == -1)
                                    {
                                        tweenFrame->tweenEasing = NO_TWEEN;
                                    }
                                }
                            }

                            prevFrame = frame;
                        }

                        timeline.frames.push_back(frame);
                    }

                    frame->duration = this->_animation->duration - frame->position;

                    frame = timeline.frames[0];
                    prevFrame->next = frame;
                    frame->prev = prevFrame;

                    if (this->_isOldData) 
                    {
                        const auto& frameObject = rawFrames[0];
                        const auto tweenFrame = dynamic_cast<TweenFrameData<T>*>(prevFrame);
                        if (tweenFrame && frameObject.HasMember(DISPLAY_INDEX) && frameObject[DISPLAY_INDEX].GetInt() == -1)
                        {
                            tweenFrame->tweenEasing = NO_TWEEN;
                        }
                    }
                }
            }
        }

        _timeline = nullptr;
    }

    virtual void _parseTransform(const rapidjson::Value& rawData, Transform& transform) const;
    virtual void _parseColorTransform(const rapidjson::Value& rawData, ColorTransform& color) const;

public:
    virtual DragonBonesData* parseDragonBonesData(const char* rawData, float scale = 1.f) override;
    virtual void parseTextureAtlasData(const char* rawData, TextureAtlasData& textureAtlasData, float scale = 0.f) override;
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_JSON_DATA_PARSER_H