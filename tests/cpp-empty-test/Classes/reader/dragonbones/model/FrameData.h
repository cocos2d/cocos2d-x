#ifndef DRAGONBONES_FRAME_DATA_H
#define DRAGONBONES_FRAME_DATA_H

#include "../core/BaseObject.h"
#include "../geom/Transform.h"
#include "../geom/ColorTransform.h"

DRAGONBONES_NAMESPACE_BEGIN

class BoneData;
class SlotData;

/**
 * @private
 */
class ActionData final : public BaseObject
{
    BIND_CLASS_TYPE(ActionData);

public:
    ActionType type;
    BoneData* bone;
    SlotData* slot;
    std::tuple<std::vector<int>, std::vector<float>, std::vector<std::string>> data;

    ActionData();
    ~ActionData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(ActionData);

protected:
    void _onClear() override;
};

/**
 * @private
 */
class EventData final : public BaseObject
{
    BIND_CLASS_TYPE(EventData);

public:
    EventType type;
    std::string name;
    //void* data; //TODO
    BoneData* bone;
    SlotData* slot;

    EventData();
    ~EventData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(EventData);

protected:
    void _onClear() override;
};

/**
 * @private
 */
template<class T>
class FrameData : public BaseObject
{
public:
    float position;
    float duration;
    T* prev;
    T* next;

    std::vector<ActionData*> actions;
    std::vector<EventData*> events;

    FrameData() {}
    virtual ~FrameData() {}

protected:
    virtual void _onClear() override
    {
        position = 0.f;
        duration = 0.f;
        prev = nullptr;
        next = nullptr;

        for (const auto action : actions)
        {
            action->returnToPool();
        }

        for (const auto event : events)
        {
            event->returnToPool();
        }

        actions.clear();
        events.clear();
    }
};

/**
 * @private
 */
template<class T>
class TweenFrameData : public FrameData<T>
{
public:
    static void samplingCurve(std::vector<float>& curve, unsigned frameCount, std::vector<float>& sampling)
    {
        if (curve.empty() || frameCount == 0)
        {
            return;
        }

        const auto curveCount = curve.size();
        const auto samplingTimes = frameCount + 2;
        const auto samplingStep = 1.f / samplingTimes;
        sampling.resize((samplingTimes - 1) * 2);

        int stepIndex = -2;
        for (std::size_t i = 0; i < samplingTimes - 1; ++i)
        {
            const auto step = samplingStep * (i + 1);
            while ((stepIndex + 6 < curveCount ? curve[stepIndex + 6] : 1.f) < step) // stepIndex + 3 * 2
            {
                stepIndex += 6; // stepIndex += 3 * 2
            }

            const auto isInCurve = stepIndex >= 0 && stepIndex + 6 < curveCount;
            const auto x1 = isInCurve ? curve[stepIndex] : 0.f;
            const auto y1 = isInCurve ? curve[stepIndex + 1] : 0.f;
            const auto x4 = isInCurve ? curve[stepIndex + 6] : 1.f;
            const auto y4 = isInCurve ? curve[stepIndex + 7] : 1.f;

            const auto t = (step - x1) / (x4 - x1);
            const auto l_t = 1.f - t;

            const auto powA = l_t * l_t;
            const auto powB = t * t;

            const auto kA = l_t * powA;
            const auto kB = 3.f * t * powA;
            const auto kC = 3.f * l_t * powB;
            const auto kD = t * powB;

            sampling[i * 2] = kA * x1 + kB * curve[stepIndex + 2] + kC * curve[stepIndex + 4] + kD * x4;
            sampling[i * 2 + 1] = kA * y1 + kB * curve[stepIndex + 3] + kC * curve[stepIndex + 5] + kD * y4;
        }
    }

public:
    float tweenEasing;
    std::vector<float> curve;

    TweenFrameData() {}
    virtual ~TweenFrameData() {}

protected:
    virtual void _onClear() override
    {
        FrameData<T>::_onClear();

        tweenEasing = 0.f;
        curve.clear();
    }
};

/**
 * @private
 */
class AnimationFrameData final : public FrameData<AnimationFrameData>
{
    BIND_CLASS_TYPE(AnimationFrameData);

public:
    AnimationFrameData();
    ~AnimationFrameData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(AnimationFrameData);

protected:
    void _onClear() override;
};

/**
 * @private
 */
class BoneFrameData final : public TweenFrameData<BoneFrameData>
{
    BIND_CLASS_TYPE(BoneFrameData);

public:
    bool tweenScale;
    int tweenRotate;
    BoneData* parent;
    Transform transform;

    BoneFrameData();
    ~BoneFrameData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(BoneFrameData);

protected:
    void _onClear() override;
};

/**
 * @private
 */
class SlotFrameData final : public TweenFrameData<SlotFrameData>
{
    BIND_CLASS_TYPE(SlotFrameData);

public:
    static ColorTransform DEFAULT_COLOR;
    static ColorTransform* generateColor();

public:
    int displayIndex;
    int zOrder;
    ColorTransform* color;

    SlotFrameData();
    ~SlotFrameData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(SlotFrameData);

protected:
    void _onClear() override;
};

/**
 * @private
 */
class ExtensionFrameData final : public TweenFrameData<ExtensionFrameData>
{
    BIND_CLASS_TYPE(ExtensionFrameData);

public:
    ExtensionType type;
    std::vector<float> tweens;
    std::vector<float> keys;

    ExtensionFrameData();
    ~ExtensionFrameData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(ExtensionFrameData);

protected:
    void _onClear() override;
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_FRAME_DATA_H