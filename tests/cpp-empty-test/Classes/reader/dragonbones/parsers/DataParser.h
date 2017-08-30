#ifndef DRAGONBONES_DATA_PARSER_H
#define DRAGONBONES_DATA_PARSER_H

#include "../core/DragonBones.h"
#include "../model/DragonBonesData.h"
#include "../textures/TextureData.h"

DRAGONBONES_NAMESPACE_BEGIN

/**
 * @private
 */
class DataParser
{
protected:
    static const char* DATA_VERSION_2_3;
    static const char* DATA_VERSION_3_0;
    static const char* DATA_VERSION_4_0;
    static const char* DATA_VERSION;
    static const char* TEXTURE_ATLAS;
    static const char* SUB_TEXTURE;
    static const char* FORMAT;
    static const char* IMAGE_PATH;
    static const char* WIDTH;
    static const char* HEIGHT;
    static const char* ROTATED;
    static const char* FRAME_X;
    static const char* FRAME_Y;
    static const char* FRAME_WIDTH;
    static const char* FRAME_HEIGHT;

    static const char* DRADON_BONES;
    static const char* ARMATURE;
    static const char* BONE;
    static const char* IK;
    static const char* SLOT;
    static const char* SKIN;
    static const char* DISPLAY;
    static const char* ANIMATION;
    static const char* FFD;
    static const char* FRAME;

    static const char* PIVOT;
    static const char* TRANSFORM;
    static const char* AABB;
    static const char* COLOR;
    static const char* FILTER;

    static const char* VERSION;
    static const char* IS_GLOBAL;
    static const char* FRAME_RATE;
    static const char* TYPE;
    static const char* NAME;
    static const char* PARENT;
    static const char* LENGTH;
    static const char* DATA;
    static const char* DISPLAY_INDEX;
    static const char* Z_ORDER;
    static const char* BLEND_MODE;
    static const char* INHERIT_TRANSLATION;
    static const char* INHERIT_ROTATION;
    static const char* INHERIT_SCALE;
    static const char* TARGET;
    static const char* BEND_POSITIVE;
    static const char* CHAIN;
    static const char* WEIGHT;

    static const char* FADE_IN_TIME;
    static const char* PLAY_TIMES;
    static const char* SCALE;
    static const char* OFFSET;
    static const char* POSITION;
    static const char* DURATION;
    static const char* TWEEN_EASING;
    static const char* TWEEN_ROTATE;
    static const char* TWEEN_SCALE;
    static const char* CURVE;
    static const char* EVENT;
    static const char* SOUND;
    static const char* ACTION;
    static const char* ACTIONS;
    static const char* DEFAULT_ACTIONS;

    static const char* X;
    static const char* Y;
    static const char* SKEW_X;
    static const char* SKEW_Y;
    static const char* SCALE_X;
    static const char* SCALE_Y;

    static const char* ALPHA_OFFSET;
    static const char* RED_OFFSET;
    static const char* GREEN_OFFSET;
    static const char* BLUE_OFFSET;
    static const char* ALPHA_MULTIPLIER;
    static const char* RED_MULTIPLIER;
    static const char* GREEN_MULTIPLIER;
    static const char* BLUE_MULTIPLIER;

    static const char* UVS;
    static const char* VERTICES;
    static const char* TRIANGLES;
    static const char* WEIGHTS;
    static const char* SLOT_POSE;
    static const char* BONE_POSE;

    static const char* TWEEN;
    static const char* KEY;

    static const char* COLOR_TRANSFORM;
    static const char* TIMELINE;
    static const char* PIVOT_X;
    static const char* PIVOT_Y;
    static const char* LOOP;
    static const char* AUTO_TWEEN;
    static const char* HIDE;

    static TextureFormat _getTextureFormat(const std::string& value);
    static ArmatureType _getArmatureType(const std::string& value);
    static DisplayType _getDisplayType(const std::string& value);
    static BlendMode _getBlendMode(const std::string& value);
    static ActionType _getActionType(const std::string& value);

protected:
    DragonBonesData* _data;
    ArmatureData* _armature;
    SkinData* _skin;
    SlotDisplayDataSet* _slotDisplayDataSet;
    mutable MeshData* _mesh;
    mutable AnimationData* _animation;
    mutable void* _timeline; // TimelineData*

    bool _isOldData;
    bool _isGlobalTransform;
    mutable bool _isAutoTween;
    mutable float _animationTweenEasing;
    mutable Point _timelinePivot;

    mutable Point _helpPoint;
    mutable Transform _helpTransformA;
    mutable Transform _helpTransformB;
    mutable Matrix _helpMatrix;
    std::vector<BoneData*> _rawBones;

public:
    DataParser();
    virtual ~DataParser() = 0;

    virtual DragonBonesData* parseDragonBonesData(const char* rawData, float scale = 1.f) = 0;
    virtual void parseTextureAtlasData(const char* rawData, TextureAtlasData& textureAtlasData, float scale = 0.f) = 0;

private:
    void _getTimelineFrameMatrix(const AnimationData& animation, BoneTimelineData& timeline, float position, Transform& transform) const;

protected:
    void _globalToLocal(ArmatureData* armature) const;

    void _mergeFrameToAnimationTimeline(float framePosition, const std::vector<ActionData*>& actions, const std::vector<EventData*>& events) const;
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_DATA_PARSER_H