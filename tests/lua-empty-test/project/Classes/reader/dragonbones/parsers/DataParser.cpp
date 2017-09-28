#include "DataParser.h"
#include "../animation/BaseTimelineState.h"

DRAGONBONES_NAMESPACE_BEGIN

const char* DataParser::DATA_VERSION_2_3 = "2.3";
const char* DataParser::DATA_VERSION_3_0 = "3.0";
const char* DataParser::DATA_VERSION_4_0 = "4.0";
const char* DataParser::DATA_VERSION = "4.5";

const char* DataParser::TEXTURE_ATLAS = "TextureAtlas";
const char* DataParser::SUB_TEXTURE = "SubTexture";
const char* DataParser::FORMAT = "format";
const char* DataParser::IMAGE_PATH = "imagePath";
const char* DataParser::WIDTH = "width";
const char* DataParser::HEIGHT = "height";
const char* DataParser::ROTATED = "rotated";
const char* DataParser::FRAME_X = "frameX";
const char* DataParser::FRAME_Y = "frameY";
const char* DataParser::FRAME_WIDTH = "frameWidth";
const char* DataParser::FRAME_HEIGHT = "frameHeight";

const char* DataParser::DRADON_BONES = "dragonBones";
const char* DataParser::ARMATURE = "armature";
const char* DataParser::BONE = "bone";
const char* DataParser::IK = "ik";
const char* DataParser::SLOT = "slot";
const char* DataParser::SKIN = "skin";
const char* DataParser::DISPLAY = "display";
const char* DataParser::ANIMATION = "animation";
const char* DataParser::FFD = "ffd";
const char* DataParser::FRAME = "frame";

const char* DataParser::PIVOT = "pivot";
const char* DataParser::TRANSFORM = "transform";
const char* DataParser::AABB = "aabb";
const char* DataParser::COLOR = "color";
const char* DataParser::FILTER = "filter";

const char* DataParser::VERSION = "version";
const char* DataParser::IS_GLOBAL = "isGlobal";
const char* DataParser::FRAME_RATE = "frameRate";
const char* DataParser::TYPE = "type";
const char* DataParser::NAME = "name";
const char* DataParser::PARENT = "parent";
const char* DataParser::LENGTH = "length";
const char* DataParser::DATA = "data";
const char* DataParser::DISPLAY_INDEX = "displayIndex";
const char* DataParser::Z_ORDER = "z";
const char* DataParser::BLEND_MODE = "blendMode";
const char* DataParser::INHERIT_TRANSLATION = "inheritTranslation";
const char* DataParser::INHERIT_ROTATION = "inheritRotation";
const char* DataParser::INHERIT_SCALE = "inheritScale";
const char* DataParser::TARGET = "target";
const char* DataParser::BEND_POSITIVE = "bendPositive";
const char* DataParser::CHAIN = "chain";
const char* DataParser::WEIGHT = "weight";

const char* DataParser::FADE_IN_TIME = "fadeInTime";
const char* DataParser::PLAY_TIMES = "playTimes";
const char* DataParser::SCALE = "scale";
const char* DataParser::OFFSET = "offset";
const char* DataParser::POSITION = "position";
const char* DataParser::DURATION = "duration";
const char* DataParser::TWEEN_EASING = "tweenEasing";
const char* DataParser::TWEEN_ROTATE = "tweenRotate";
const char* DataParser::TWEEN_SCALE = "tweenScale";
const char* DataParser::CURVE = "curve";
const char* DataParser::EVENT = "event";
const char* DataParser::SOUND = "sound";
const char* DataParser::ACTION = "action";
const char* DataParser::ACTIONS = "actions";
const char* DataParser::DEFAULT_ACTIONS = "defaultActions";

const char* DataParser::X = "x";
const char* DataParser::Y = "y";
const char* DataParser::SKEW_X = "skX";
const char* DataParser::SKEW_Y = "skY";
const char* DataParser::SCALE_X = "scX";
const char* DataParser::SCALE_Y = "scY";

const char* DataParser::ALPHA_OFFSET = "aO";
const char* DataParser::RED_OFFSET = "rO";
const char* DataParser::GREEN_OFFSET = "gO";
const char* DataParser::BLUE_OFFSET = "bO";
const char* DataParser::ALPHA_MULTIPLIER = "aM";
const char* DataParser::RED_MULTIPLIER = "rM";
const char* DataParser::GREEN_MULTIPLIER = "gM";
const char* DataParser::BLUE_MULTIPLIER = "bM";

const char* DataParser::UVS = "uvs";
const char* DataParser::VERTICES = "vertices";
const char* DataParser::TRIANGLES = "triangles";
const char* DataParser::WEIGHTS = "weights";
const char* DataParser::SLOT_POSE = "slotPose";
const char* DataParser::BONE_POSE = "bonePose";

const char* DataParser::TWEEN = "tween";
const char* DataParser::KEY = "key";

const char* DataParser::COLOR_TRANSFORM = "colorTransform";
const char* DataParser::TIMELINE = "timeline";
const char* DataParser::PIVOT_X = "pX";
const char* DataParser::PIVOT_Y = "pY";
const char* DataParser::LOOP = "loop";
const char* DataParser::AUTO_TWEEN = "autoTween";
const char* DataParser::HIDE = "hide";

TextureFormat DataParser::_getTextureFormat(const std::string& value)
{
    auto lower = value;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "rgba8888")
    {
        return TextureFormat::RGBA8888;
    }
    else if (lower == "bgra8888")
    {
        return TextureFormat::BGRA8888;
    }
    else if (lower == "rgba4444")
    {
        return TextureFormat::RGBA4444;
    }
    else if (lower == "rgb888")
    {
        return TextureFormat::RGB888;
    }
    else if (lower == "rgb565")
    {
        return TextureFormat::RGB565;
    }
    else if (lower == "rgba5551")
    {
        return TextureFormat::RGBA5551;
    }

    return TextureFormat::DEFAULT;
}

ArmatureType DataParser::_getArmatureType(const std::string& value)
{
    auto lower = value;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "armature")
    {
        return ArmatureType::Armature;
    }
    else if (lower == "movieClip")
    {
        return ArmatureType::MovieClip;
    }
    else if (lower == "stage")
    {
        return ArmatureType::Stage;
    }

    return ArmatureType::Armature;
}

DisplayType DataParser::_getDisplayType(const std::string& value)
{
    auto lower = value;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "image")
    {
        return DisplayType::Image;
    }
    else if (lower == "armature")
    {
        return DisplayType::Armature;
    }
    else if (lower == "mesh")
    {
        return DisplayType::Mesh;
    }

    return DisplayType::Image;
}

BlendMode DataParser::_getBlendMode(const std::string& value)
{
    auto lower = value;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "normal")
    {
        return BlendMode::Normal;
    }
    else if (lower == "add")
    {
        return BlendMode::Add;
    }
    else if (lower == "alpha")
    {
        return BlendMode::Alpha;
    }
    else if (lower == "darken")
    {
        return BlendMode::Darken;
    }
    else if (lower == "difference")
    {
        return BlendMode::Difference;
    }
    else if (lower == "erase")
    {
        return BlendMode::Erase;
    }
    else if (lower == "hardlight")
    {
        return BlendMode::HardLight;
    }
    else if (lower == "invert")
    {
        return BlendMode::Invert;
    }
    else if (lower == "layer")
    {
        return BlendMode::Layer;
    }
    else if (lower == "lighten")
    {
        return BlendMode::Lighten;
    }
    else if (lower == "multiply")
    {
        return BlendMode::Multiply;
    }
    else if (lower == "overlay")
    {
        return BlendMode::Overlay;
    }
    else if (lower == "screen")
    {
        return BlendMode::Screen;
    }
    else if (lower == "subtract")
    {
        return BlendMode::Subtract;
    }

    return BlendMode::Normal;
}

ActionType DataParser::_getActionType(const std::string& value)
{
    auto lower = value;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "fadeIn")
    {
        return ActionType::FadeIn;
    }
    else if (lower == "play")
    {
        return ActionType::Play;
    }
    else if (lower == "stop")
    {
        return ActionType::Stop;
    }
    else if (lower == "gotoandplay")
    {
        return ActionType::GotoAndPlay;
    }
    else if (lower == "gotoandstop")
    {
        return ActionType::GotoAndStop;
    }
    else if (lower == "fadeout")
    {
        return ActionType::FadeOut;
    }

    return ActionType::FadeIn;
}

DataParser::DataParser() :
    _data(nullptr),
    _armature(nullptr),
    _skin(nullptr),
    _slotDisplayDataSet(nullptr),
    _mesh(nullptr),
    _animation(nullptr),
    _timeline(nullptr),

    _isOldData(false),
    _isGlobalTransform(false),
    _isAutoTween(false),
    _animationTweenEasing(0.f),
    _timelinePivot(),

    _helpPoint(),
    _helpTransformA(),
    _helpTransformB(),
    _helpMatrix(),
    _rawBones()
{}
DataParser::~DataParser() {}

void DataParser::_getTimelineFrameMatrix(const AnimationData& animation, BoneTimelineData& timeline, float position, Transform& transform) const
{
    const auto frameIndex = unsigned(position * animation.frameCount / animation.duration); // floor
    if (timeline.frames.size() == 1 || frameIndex >= timeline.frames.size()) 
    {
        transform = timeline.frames[0]->transform; // copy
    }
    else 
    {
        const auto frame = timeline.frames[frameIndex];
        auto tweenProgress = 0.f;

        if (frame->duration > 0.f && frame->tweenEasing != NO_TWEEN) 
        {
            tweenProgress = (position - frame->position) / frame->duration;
            if (frame->tweenEasing != 0.f) 
            {
                tweenProgress = TweenTimelineState<BoneFrameData, BoneTimelineData>::_getEasingValue(tweenProgress, frame->tweenEasing);
            }
        }
        else if (!frame->curve.empty()) 
        {
            tweenProgress = (position - frame->position) / frame->duration;
            tweenProgress = TweenTimelineState<BoneFrameData, BoneTimelineData>::_getCurveEasingValue(tweenProgress, frame->curve);
        }

        const auto nextFrame = frame->next;

        transform.x = nextFrame->transform.x - frame->transform.x;
        transform.y = nextFrame->transform.y - frame->transform.y;
        transform.skewX = Transform::normalizeRadian(nextFrame->transform.skewX - frame->transform.skewX);
        transform.skewY = Transform::normalizeRadian(nextFrame->transform.skewY - frame->transform.skewY);
        transform.scaleX = nextFrame->transform.scaleX - frame->transform.scaleX;
        transform.scaleY = nextFrame->transform.scaleY - frame->transform.scaleY;

        transform.x = frame->transform.x + transform.x * tweenProgress;
        transform.y = frame->transform.y + transform.y * tweenProgress;
        transform.skewX = frame->transform.skewX + transform.skewX * tweenProgress;
        transform.skewY = frame->transform.skewY + transform.skewY * tweenProgress;
        transform.scaleX = frame->transform.scaleX + transform.scaleX * tweenProgress;
        transform.scaleY = frame->transform.scaleY + transform.scaleY * tweenProgress;
    }

    transform.add(timeline.originTransform);
}

void DataParser::_globalToLocal(ArmatureData* armature) const
{
    std::vector<BoneFrameData*> keyFrames;
    auto bones = armature->getSortedBones(); // copy
    bones.reserve(bones.size());

    for (const auto bone : bones) 
    {
        if (bone->parent) 
        {
            bone->parent->transform.toMatrix(_helpMatrix);
            _helpMatrix.invert();
            _helpMatrix.transformPoint(bone->transform.x, bone->transform.y, _helpPoint);
            bone->transform.x = _helpPoint.x;
            bone->transform.y = _helpPoint.y;
            bone->transform.setRotation(bone->transform.getRotation() - bone->parent->transform.getRotation());
        }

        for (const auto& animationPair : armature->animations)
        {
            const auto animation = animationPair.second;
            const auto timeline = animation->getBoneTimeline(bone->name);

            if (!timeline)
            {
                continue;
            }

            const auto parentTimeline = bone->parent ? animation->getBoneTimeline(bone->parent->name) : nullptr;
            _helpTransformB = timeline->originTransform; // copy
            keyFrames.clear();

            auto isFirstFrame = true;
            for (const auto frame : timeline->frames)
            {
                if (std::find(keyFrames.cbegin(), keyFrames.cend(), frame) != keyFrames.cend())
                {
                    continue;
                }

                keyFrames.push_back(frame);

                if (parentTimeline)
                {
                    _getTimelineFrameMatrix(*animation, *parentTimeline, frame->position, _helpTransformA);
                    frame->transform.add(_helpTransformB);
                    _helpTransformA.toMatrix(_helpMatrix);
                    _helpMatrix.invert();
                    _helpMatrix.transformPoint(frame->transform.x, frame->transform.y, _helpPoint);
                    frame->transform.setRotation(frame->transform.getRotation() - _helpTransformA.getRotation());
                }
                else
                {
                    frame->transform.add(_helpTransformB);
                }

                frame->transform.minus(bone->transform);

                if (isFirstFrame)
                {
                    isFirstFrame = false;
                    timeline->originTransform = frame->transform;
                    frame->transform.identity();
                }
                else
                {
                    frame->transform.minus(timeline->originTransform);
                }
            }
        }
    }
}

void DataParser::_mergeFrameToAnimationTimeline(float framePosition, const std::vector<ActionData*>& actions, const std::vector<EventData*>& events) const
{
    const auto frameStart = std::floor(framePosition * _armature->frameRate);
    auto& frames = _animation->frames;

    if (frames.empty()) 
    {
        const auto startFrame = BaseObject::borrowObject<AnimationFrameData>();
        startFrame->position = 0.f;

        if (_animation->frameCount > 1) 
        {
            frames.resize(_animation->frameCount + 1, nullptr);

            const auto endFrame = BaseObject::borrowObject<AnimationFrameData>();
            endFrame->position = _animation->frameCount / _armature->frameRate;

            frames[0] = startFrame;
            frames[_animation->frameCount] = endFrame;
        }
    }

    auto insertedFrame = (AnimationFrameData*)nullptr;
    const auto replacedFrame = frames[frameStart];

    if (replacedFrame && (frameStart == 0 || frames[frameStart - 1] == replacedFrame->prev)) 
    {
        insertedFrame = replacedFrame;
    }
    else 
    {
        insertedFrame = BaseObject::borrowObject<AnimationFrameData>();
        insertedFrame->position = frameStart / _armature->frameRate;
        frames[frameStart] = insertedFrame;

        for (size_t i = frameStart + 1, l = frames.size(); i < l; ++i) 
        {
            if (replacedFrame && frames[i] == replacedFrame) 
            {
                frames[i] = nullptr;
            }
        }
    }

    if (!actions.empty()) 
    {
        for (const auto action : actions)
        {
            insertedFrame->actions.push_back(action);
        }
    }

    if (!events.empty()) 
    {
        for (const auto event : events) 
        {
            insertedFrame->events.push_back(event);
        }
    }

    auto prevFrame = (AnimationFrameData*)nullptr;
    auto nextFrame = (AnimationFrameData*)nullptr;
    for (size_t i = 0, l = frames.size(); i < l; ++i) 
    {
        const auto currentFrame = frames[i];
        if (currentFrame && nextFrame != currentFrame) 
        {
            nextFrame = currentFrame;

            if (prevFrame) {
                nextFrame->prev = prevFrame;
                prevFrame->next = nextFrame;
                prevFrame->duration = nextFrame->position - prevFrame->position;
            }

            prevFrame = nextFrame;
        }
        else 
        {
            frames[i] = prevFrame;
        }
    }

    nextFrame->duration = _animation->duration - nextFrame->position;

    nextFrame = frames[0];
    prevFrame->next = nextFrame;
    nextFrame->prev = prevFrame;
}


DRAGONBONES_NAMESPACE_END
