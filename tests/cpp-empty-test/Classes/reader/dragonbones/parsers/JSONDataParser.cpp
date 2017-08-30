#include "JSONDataParser.h"

DRAGONBONES_NAMESPACE_BEGIN

JSONDataParser::JSONDataParser() {}
JSONDataParser::~JSONDataParser() {}

ArmatureData * JSONDataParser::_parseArmature(const rapidjson::Value & rawData, float scale)
{
    const auto armature = BaseObject::borrowObject<ArmatureData>();
    armature->name = _getString(rawData, NAME, "");
    armature->frameRate = _getNumber(rawData, FRAME_RATE, this->_data->frameRate);
    armature->scale = scale;

    if (armature->frameRate == 0)
    {
        armature->frameRate = this->_data->frameRate;
    }

    if (rawData.HasMember(TYPE) && rawData[TYPE].IsString())
    {
        armature->type = _getArmatureType(rawData[TYPE].GetString());
    }
    else
    {
        armature->type = (ArmatureType)_getNumber(rawData, TYPE, (int)ArmatureType::Armature);
    }

    this->_armature = armature;
    this->_rawBones.clear();

    if (rawData.HasMember(AABB))
    {
        const auto& aabbObject = rawData[AABB];
        armature->aabb.x = _getNumber(aabbObject, X, 0.f);
        armature->aabb.y = _getNumber(aabbObject, Y, 0.f);
        armature->aabb.width = _getNumber(aabbObject, WIDTH, 0.f);
        armature->aabb.height = _getNumber(aabbObject, HEIGHT, 0.f);
    }

    if (rawData.HasMember(BONE))
    {
        const auto& bones = rawData[BONE];
        for (size_t i = 0, l = bones.Size(); i < l; ++i)
        {
            const auto bone = _parseBone(bones[i]);
            armature->addBone(bone, _getString(bones[i], PARENT, ""));
            this->_rawBones.push_back(bone);
        }
    }

    if (rawData.HasMember(IK))
    {
        const auto& iks = rawData[IK];
        for (size_t i = 0, l = iks.Size(); i < l; ++i)
        {
            _parseIK(iks[i]);
        }
    }

    if (rawData.HasMember(SLOT))
    {
        int zOrder = 0;
        const auto& slots = rawData[SLOT];
        for (size_t i = 0, l = slots.Size(); i < l; ++i)
        {
            armature->addSlot(_parseSlot(slots[i], zOrder++));
        }
    }

    if (rawData.HasMember(SKIN))
    {
        const auto& skins = rawData[SKIN];
        for (size_t i = 0, l = skins.Size(); i < l; ++i)
        {
            armature->addSkin(_parseSkin(skins[i]));
        }
    }

    if (rawData.HasMember(ANIMATION))
    {
        const auto& animations = rawData[ANIMATION];
        for (size_t i = 0, l = animations.Size(); i < l; ++i)
        {
            armature->addAnimation(_parseAnimation(animations[i]));
        }
    }

    if (rawData.HasMember(ACTIONS) || rawData.HasMember(DEFAULT_ACTIONS))
    {
        _parseActionData(rawData, armature->actions, nullptr, nullptr);
    }

    if (this->_isOldData && _getBoolean(rawData, IS_GLOBAL, true))
    {
        this->_globalToLocal(armature);
    }

    this->_armature = nullptr;
    this->_rawBones.clear();

    return armature;
}

BoneData * JSONDataParser::_parseBone(const rapidjson::Value & rawData)
{
    const auto bone = BaseObject::borrowObject<BoneData>();
    bone->name = _getString(rawData, NAME, "");
    bone->inheritTranslation = _getBoolean(rawData, INHERIT_TRANSLATION, true);
    bone->inheritRotation = _getBoolean(rawData, INHERIT_ROTATION, true);
    bone->inheritScale = _getBoolean(rawData, INHERIT_SCALE, true);
    bone->length = _getNumber(rawData, LENGTH, 0.f) * this->_armature->scale;

    if (rawData.HasMember(TRANSFORM))
    {
        _parseTransform(rawData[TRANSFORM], bone->transform);
    }

    if (this->_isOldData) 
    {
        bone->inheritScale = false;
    }

    return bone;
}

void JSONDataParser::_parseIK(const rapidjson::Value & rawData)
{
    const auto bone = this->_armature->getBone(_getString(rawData, rawData.HasMember(BONE) ? BONE : NAME, ""));
    if (bone)
    {
        bone->ik = this->_armature->getBone(_getString(rawData, TARGET, ""));
        bone->bendPositive = _getBoolean(rawData, BEND_POSITIVE, true);
        bone->chain = _getNumber(rawData, CHAIN, (unsigned)0);
        bone->weight = _getNumber(rawData, WEIGHT, 1.f);

        if (bone->chain > 0 && bone->parent && !bone->parent->ik)
        {
            bone->parent->ik = bone->ik;
            bone->parent->chainIndex = 0;
            bone->parent->chain = 0;
            bone->chainIndex = 1;
        }
        else
        {
            bone->chain = 0;
            bone->chainIndex = 0;
        }
    }
}

SlotData * JSONDataParser::_parseSlot(const rapidjson::Value& rawData, int zOrder)
{
    const auto slot = BaseObject::borrowObject<SlotData>();
    slot->name = _getString(rawData, NAME, "");
    slot->parent = this->_armature->getBone(_getString(rawData, PARENT, ""));
    slot->displayIndex = _getNumber(rawData, DISPLAY_INDEX, (int)0);
    slot->zOrder = _getNumber(rawData, Z_ORDER, zOrder);

    if (rawData.HasMember(COLOR))
    {
        slot->color = SlotData::generateColor();
        _parseColorTransform(rawData[COLOR], *slot->color);
    }
    else
    {
        slot->color = &SlotData::DEFAULT_COLOR;
    }

    if (rawData.HasMember(BLEND_MODE) && rawData[BLEND_MODE].IsString())
    {
        slot->blendMode = _getBlendMode(rawData[BLEND_MODE].GetString());
    }
    else
    {
        slot->blendMode = (BlendMode)_getNumber(rawData, BLEND_MODE, (int)BlendMode::Normal);
    }

    if (rawData.HasMember(ACTIONS) || rawData.HasMember(DEFAULT_ACTIONS))
    {
        _parseActionData(rawData, slot->actions, nullptr, nullptr);
    }

    if (this->_isOldData) 
    {
        if (rawData.HasMember(COLOR_TRANSFORM)) 
        {
            slot->color = SlotData::generateColor();
            _parseColorTransform(rawData[COLOR_TRANSFORM], *slot->color);
        }
        else 
        {
            slot->color = &SlotData::DEFAULT_COLOR;
        }
    }

    return slot;
}

SkinData * JSONDataParser::_parseSkin(const rapidjson::Value & rawData)
{
    const auto skin = BaseObject::borrowObject<SkinData>();
    skin->name = _getString(rawData, NAME, "__default");
    if (skin->name.empty())
    {
        skin->name = "__default";
    }

    if (rawData.HasMember(SLOT))
    {
        this->_skin = skin;

        int zOrder = 0;
        const auto& slots = rawData[SLOT];
        for (size_t i = 0, l = slots.Size(); i < l; ++i)
        {
            if (this->_isOldData) 
            {
                this->_armature->addSlot(_parseSlot(slots[i], zOrder++));
            }

            skin->addSlot(_parseSlotDisplaySet(slots[i]));
        }

        this->_skin = nullptr;
    }

    return skin;
}

SlotDisplayDataSet * JSONDataParser::_parseSlotDisplaySet(const rapidjson::Value & rawData)
{
    const auto slotDisplayDataSet = BaseObject::borrowObject<SlotDisplayDataSet>();
    slotDisplayDataSet->slot = this->_armature->getSlot(_getString(rawData, NAME, ""));

    if (rawData.HasMember(DISPLAY))
    {
        this->_slotDisplayDataSet = slotDisplayDataSet;

        const auto& displayObjects = rawData[DISPLAY];
        auto& displayDataSet = slotDisplayDataSet->displays;
        displayDataSet.reserve(displayObjects.Size());
        for (size_t i = 0, l = displayObjects.Size(); i < l; ++i)
        {
            displayDataSet.push_back(_parseDisplay(displayObjects[i]));
        }

        this->_slotDisplayDataSet = nullptr;
    }

    return slotDisplayDataSet;
}

DisplayData * JSONDataParser::_parseDisplay(const rapidjson::Value & rawData)
{
    const auto display = BaseObject::borrowObject<DisplayData>();
    display->name = _getString(rawData, NAME, "");

    if (rawData.HasMember(TYPE) && rawData[TYPE].IsString())
    {
        display->type = _getDisplayType(rawData[TYPE].GetString());
    }
    else
    {
        display->type = (DisplayType)_getNumber(rawData, TYPE, (int)DisplayType::Image);
    }

    display->isRelativePivot = true;
    if (rawData.HasMember(PIVOT))
    {
        const auto& pivotObject = rawData[PIVOT];
        display->pivot.x = _getNumber(pivotObject, X, 0.f);
        display->pivot.y = _getNumber(pivotObject, Y, 0.f);
    }
    else if (this->_isOldData)
    {
        const auto& transformObject = rawData[TRANSFORM];
        display->isRelativePivot = false;
        display->pivot.x = _getNumber(transformObject, PIVOT_X, 0.f) * this->_armature->scale;
        display->pivot.y = _getNumber(transformObject, PIVOT_Y, 0.f) * this->_armature->scale;
    }
    else
    {
        display->pivot.x = 0.5f;
        display->pivot.y = 0.5f;
    }

    if (rawData.HasMember(TRANSFORM))
    {
        _parseTransform(rawData[TRANSFORM], display->transform);
    }

    switch (display->type)
    {
        case DisplayType::Image:
            break;

        case DisplayType::Armature:
            break;

        case DisplayType::Mesh:
            display->mesh = _parseMesh(rawData);
            break;
    }

    return display;
}

MeshData * JSONDataParser::_parseMesh(const rapidjson::Value & rawData)
{
    const auto mesh = BaseObject::borrowObject<MeshData>();

    const auto& rawVertices = rawData[VERTICES];
    const auto& rawUVs = rawData[UVS];
    const auto& rawTriangles = rawData[TRIANGLES];

    const auto numVertices = (unsigned)(rawVertices.Size() / 2);
    const auto numTriangles = (unsigned)(rawTriangles.Size() / 3);

    std::vector<Matrix> inverseBindPose(this->_armature->getSortedBones().size(), Matrix());

    mesh->skinned = rawData.HasMember(WEIGHTS) && !rawData[WEIGHTS].Empty();
    mesh->uvs.resize(numVertices * 2);
    mesh->vertices.resize(numVertices * 2);
    mesh->vertexIndices.resize(numTriangles * 3);

    if (mesh->skinned)
    {
        mesh->boneIndices.resize(numVertices);
        mesh->weights.resize(numVertices);
        mesh->boneVertices.resize(numVertices);

        if (rawData.HasMember(SLOT_POSE))
        {
            const auto& rawSlotPose = rawData[SLOT_POSE];
            mesh->slotPose.a = rawSlotPose[0].GetDouble();
            mesh->slotPose.b = rawSlotPose[1].GetDouble();
            mesh->slotPose.c = rawSlotPose[2].GetDouble();
            mesh->slotPose.d = rawSlotPose[3].GetDouble();
            mesh->slotPose.tx = rawSlotPose[4].GetDouble() * this->_armature->scale;
            mesh->slotPose.ty = rawSlotPose[5].GetDouble() * this->_armature->scale;
        }

        if (rawData.HasMember(BONE_POSE))
        {
            const auto& rawBonePose = rawData[BONE_POSE];
            for (std::size_t i = 0, l = rawBonePose.Size(); i < l; i += 7)
            {
                const auto rawBoneIndex = rawBonePose[i].GetUint();
                auto& boneMatrix = inverseBindPose[rawBoneIndex];
                boneMatrix.a = rawBonePose[i + 1].GetDouble();
                boneMatrix.b = rawBonePose[i + 2].GetDouble();
                boneMatrix.c = rawBonePose[i + 3].GetDouble();
                boneMatrix.d = rawBonePose[i + 4].GetDouble();
                boneMatrix.tx = rawBonePose[i + 5].GetDouble() * this->_armature->scale;
                boneMatrix.ty = rawBonePose[i + 6].GetDouble() * this->_armature->scale;
                boneMatrix.invert();
            }
        }
    }

    for (std::size_t i = 0, iW = 0, l = rawVertices.Size(); i < l; i += 2)
    {
        const auto iN = i + 1;
        const auto vertexIndex = i / 2;

        auto x = mesh->vertices[i] = rawVertices[i].GetDouble() * this->_armature->scale;
        auto y = mesh->vertices[iN] = rawVertices[iN].GetDouble() * this->_armature->scale;
        mesh->uvs[i] = rawUVs[i].GetDouble();
        mesh->uvs[iN] = rawUVs[iN].GetDouble();

        if (mesh->skinned)
        {
            const auto& rawWeights = rawData[WEIGHTS];
            const auto numBones = rawWeights[iW].GetUint();
            auto& indices = mesh->boneIndices[vertexIndex];
            auto& weights = mesh->weights[vertexIndex];
            auto& boneVertices = mesh->boneVertices[vertexIndex];
            mesh->slotPose.transformPoint(x, y, _helpPoint);
            x = mesh->vertices[i] = _helpPoint.x;
            y = mesh->vertices[iN] = _helpPoint.y;

            for (std::size_t iB = 0; iB < numBones; ++iB)
            {
                const auto iI = iW + 1 + iB * 2;
                const auto rawBoneIndex = rawWeights[iI].GetUint();
                const auto boneData = this->_rawBones[rawBoneIndex];

                const auto iderator = std::find(mesh->bones.cbegin(), mesh->bones.cend(), boneData);
                std::size_t boneIndex = 0;
                if (iderator == mesh->bones.cend())
                {
                    boneIndex = mesh->bones.size();
                    mesh->bones.push_back(boneData);
                    mesh->inverseBindPose.push_back(inverseBindPose[rawBoneIndex]); // copy
                }
                else
                {
                    boneIndex = std::distance(mesh->bones.cbegin(), iderator);
                }

                mesh->inverseBindPose[boneIndex].transformPoint(x, y, _helpPoint);

                indices.push_back(boneIndex);
                weights.push_back(rawWeights[iI + 1].GetDouble());
                boneVertices.push_back(_helpPoint.x);
                boneVertices.push_back(_helpPoint.y);
            }

            iW += numBones * 2 + 1;
        }
    }

    for (std::size_t i = 0, l = rawTriangles.Size(); i < l; ++i)
    {
        mesh->vertexIndices[i] = rawTriangles[i].GetUint();
    }

    return mesh;
}

AnimationData * JSONDataParser::_parseAnimation(const rapidjson::Value & rawData) const
{
    const auto animation = BaseObject::borrowObject<AnimationData>();
    animation->name = _getString(rawData, NAME, "__default");
    if (animation->name.empty())
    {
        animation->name = "__default";
    }

    animation->frameCount = std::max(_getNumber(rawData, DURATION, (unsigned)1), (unsigned)1);
    animation->position = _getNumber(rawData, POSITION, 0.f) / this->_armature->frameRate;
    animation->duration = (float)animation->frameCount / this->_armature->frameRate;
    animation->playTimes = _getNumber(rawData, PLAY_TIMES, (unsigned)1);
    animation->fadeInTime = _getNumber(rawData, FADE_IN_TIME, 0.f);

    this->_animation = animation;

    std::string animationName = _getString(rawData, ANIMATION, "");
    if (!animationName.empty())
    {
        animation->animation = this->_armature->getAnimation(animationName);
        if (!animation->animation)
        {
        }

        return animation;
    }

    _parseTimeline<AnimationFrameData>(rawData, *animation, std::bind(&JSONDataParser::_parseAnimationFrame, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    if (rawData.HasMember(BONE))
    {
        const auto& boneTimelineObjects = rawData[BONE];
        for (size_t i = 0, l = boneTimelineObjects.Size(); i < l; ++i)
        {
            animation->addBoneTimeline(_parseBoneTimeline(boneTimelineObjects[i]));
        }
    }

    if (rawData.HasMember(SLOT))
    {
        const auto& slotTimelineObjects = rawData[SLOT];
        for (size_t i = 0, l = slotTimelineObjects.Size(); i < l; ++i)
        {
            animation->addSlotTimeline(_parseSlotTimeline(slotTimelineObjects[i]));
        }
    }

    if (rawData.HasMember(FFD))
    {
        const auto& ffdTimelineObjects = rawData[FFD];
        for (size_t i = 0, l = ffdTimelineObjects.Size(); i < l; ++i)
        {
            animation->addFFDTimeline(_parseFFDTimeline(ffdTimelineObjects[i]));
        }
    }

    if (this->_isOldData) 
    {
        this->_isAutoTween = _getBoolean(rawData, AUTO_TWEEN, true);
        this->_animationTweenEasing = _getNumber(rawData, TWEEN_EASING, 0.f) || 0.f;
        animation->playTimes = _getNumber(rawData, LOOP, (unsigned)1);

        if (rawData.HasMember(TIMELINE)) 
        {
            const auto& timelineObjects = rawData[TIMELINE];
            for (size_t i = 0, l = timelineObjects.Size(); i < l; ++i)
            {
                const auto& timelineObject = timelineObjects[i];
                animation->addBoneTimeline(_parseBoneTimeline(timelineObject));
                animation->addSlotTimeline(_parseSlotTimeline(timelineObject));
            }
        }
    }
    else 
    {
        this->_isAutoTween = false;
        this->_animationTweenEasing = 0.f;
    }

    for (const auto& pair : this->_armature->bones)
    {
        if (!animation->getBoneTimeline(pair.second->name))
        {
            const auto boneTimeline = BaseObject::borrowObject<BoneTimelineData>();
            const auto boneFrame = BaseObject::borrowObject<BoneFrameData>();
            boneTimeline->bone = pair.second;
            boneTimeline->frames.reserve(1);
            boneTimeline->frames.push_back(boneFrame);
            animation->addBoneTimeline(boneTimeline);
        }
    }

    for (const auto& pair : this->_armature->slots)
    {
        if (!animation->getSlotTimeline(pair.second->name))
        {
            const auto slotTimeline = BaseObject::borrowObject<SlotTimelineData>();
            const auto slotFrame = BaseObject::borrowObject<SlotFrameData>();
            slotTimeline->slot = pair.second;
            slotFrame->displayIndex = pair.second->displayIndex;

            if (pair.second->color == &SlotData::DEFAULT_COLOR)
            {
                slotFrame->color = &SlotFrameData::DEFAULT_COLOR;
            }
            else 
            {
                slotFrame->color = SlotFrameData::generateColor();
                *slotFrame->color = *pair.second->color; // copy
            }

            slotTimeline->frames.reserve(1);
            slotTimeline->frames.push_back(slotFrame);
            animation->addSlotTimeline(slotTimeline);

            if (this->_isOldData) 
            {
                slotFrame->displayIndex = -1;
            }
        }
    }

    this->_animation = nullptr;

    return animation;
}

BoneTimelineData * JSONDataParser::_parseBoneTimeline(const rapidjson::Value& rawData) const
{
    const auto timeline = BaseObject::borrowObject<BoneTimelineData>();
    timeline->bone = this->_armature->getBone(_getString(rawData, NAME, ""));

    _parseTimeline<BoneFrameData>(rawData, *timeline, std::bind(&JSONDataParser::_parseBoneFrame, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    auto& originTransform = timeline->originTransform;
    BoneFrameData* prevFrame = nullptr;

    for (const auto frame : timeline->frames)
    {
        if (!prevFrame)
        {
            originTransform = frame->transform; // copy
            frame->transform.identity();

            if (originTransform.scaleX == 0.f) 
            { 
                originTransform.scaleX = 0.001f;
                //frame->transform.scaleX = 0.f;
            }

            if (originTransform.scaleY == 0.f) 
            {
                originTransform.scaleY = 0.001f;
                //frame->transform.scaleY = 0.f;
            }
        }
        else if (prevFrame != frame)
        {
            frame->transform.minus(originTransform);
        }

        prevFrame = frame;
    }

    if (timeline->scale != 1.f || timeline->offset != 0.f)
    {
        this->_animation->hasAsynchronyTimeline = true;
    }

    if (
        this->_isOldData &&
        (rawData.HasMember(PIVOT_X) || rawData.HasMember(PIVOT_Y))
    ) 
    {
        this->_timelinePivot.x = _getNumber(rawData, PIVOT_X, 0.f);
        this->_timelinePivot.y = _getNumber(rawData, PIVOT_Y, 0.f);
    }
    else 
    {
        _timelinePivot.clear();
    }

    return timeline;
}

SlotTimelineData * JSONDataParser::_parseSlotTimeline(const rapidjson::Value& rawData) const
{
    const auto timeline = BaseObject::borrowObject<SlotTimelineData>();
    timeline->slot = this->_armature->getSlot(_getString(rawData, NAME, ""));

    _parseTimeline<SlotFrameData>(rawData, *timeline, std::bind(&JSONDataParser::_parseSlotFrame, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    if (timeline->scale != 1.f || timeline->offset != 0.f)
    {
        this->_animation->hasAsynchronyTimeline = true;
    }

    return timeline;
}

FFDTimelineData * JSONDataParser::_parseFFDTimeline(const rapidjson::Value& rawData) const
{
    const auto timeline = BaseObject::borrowObject<FFDTimelineData>();
    timeline->skin = this->_armature->getSkin(_getString(rawData, SKIN, ""));
    timeline->slot = timeline->skin->getSlot(_getString(rawData, SLOT, ""));

    const auto meshName = _getString(rawData, NAME, "");
    for (std::size_t i = 0, l = timeline->slot->displays.size(); i < l; ++i)
    {
        const auto displayData = timeline->slot->displays[i];
        if (displayData->mesh && displayData->name == meshName)
        {
            timeline->displayIndex = i;
            this->_mesh = displayData->mesh;
            break;
        }
    }

    _parseTimeline<ExtensionFrameData>(rawData, *timeline, std::bind(&JSONDataParser::_parseFFDFrame, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->_mesh = nullptr;

    return timeline;
}

AnimationFrameData * JSONDataParser::_parseAnimationFrame(const rapidjson::Value& rawData, unsigned frameStart, unsigned frameCount) const
{
    const auto frame = BaseObject::borrowObject<AnimationFrameData>();

    _parseFrame(rawData, *frame, frameStart, frameCount);

    if (rawData.HasMember(ACTION) || rawData.HasMember(ACTIONS))
    {
        _parseActionData(rawData, frame->actions, nullptr, nullptr);
    }

    if (rawData.HasMember(EVENT) || rawData.HasMember(SOUND))
    {
        _parseEventData(rawData, frame->events, nullptr, nullptr);
    }

    return frame;
}

BoneFrameData * JSONDataParser::_parseBoneFrame(const rapidjson::Value& rawData, unsigned frameStart, unsigned frameCount) const
{
    const auto frame = BaseObject::borrowObject<BoneFrameData>();
    frame->parent = this->_armature->getBone(_getString(rawData, PARENT, ""));
    frame->tweenRotate = _getNumber(rawData, TWEEN_ROTATE, (int)0);
    frame->tweenScale = _getBoolean(rawData, TWEEN_SCALE, true);

    _parseTweenFrame<BoneFrameData>(rawData, *frame, frameStart, frameCount);

    if (rawData.HasMember(TRANSFORM))
    {
        const auto& transformObject = rawData[TRANSFORM];
        _parseTransform(transformObject, frame->transform);

        if (this->_isOldData) 
        {
            this->_helpPoint.x = this->_timelinePivot.x + _getNumber(transformObject, PIVOT_X, 0.f);
            this->_helpPoint.y = this->_timelinePivot.y + _getNumber(transformObject, PIVOT_Y, 0.f);
            frame->transform.toMatrix(this->_helpMatrix);
            this->_helpMatrix.transformPoint(this->_helpPoint.x, this->_helpPoint.y, this->_helpPoint, true);
            frame->transform.x += this->_helpPoint.x;
            frame->transform.y += this->_helpPoint.y;
        }
    }

    const auto bone = static_cast<BoneTimelineData*>(this->_timeline)->bone;
    std::vector<ActionData*> actions;
    std::vector<EventData*> events;

    if (rawData.HasMember(ACTION) || rawData.HasMember(ACTIONS))
    {
        const auto slot = this->_armature->getSlot(bone->name);
        _parseActionData(rawData, actions, bone, slot);
    }

    if ((rawData.HasMember(EVENT) || rawData.HasMember(SOUND)))
    {
        _parseEventData(rawData, events, bone, nullptr);
    }

    if (!actions.empty() || !events.empty())
    {
        this->_mergeFrameToAnimationTimeline(frame->position, actions, events);
    }

    return frame;
}

SlotFrameData * JSONDataParser::_parseSlotFrame(const rapidjson::Value & rawData, unsigned frameStart, unsigned frameCount) const
{
    const auto frame = BaseObject::borrowObject<SlotFrameData>();
    frame->displayIndex = _getNumber(rawData, DISPLAY_INDEX, (int)0);

    _parseTweenFrame<SlotFrameData>(rawData, *frame, frameStart, frameCount);

    if (rawData.HasMember(COLOR) || rawData.HasMember(COLOR_TRANSFORM))
    {
        frame->color = SlotFrameData::generateColor();
        _parseColorTransform(rawData.HasMember(COLOR) ? rawData[COLOR] : rawData[COLOR_TRANSFORM], *frame->color);
    }
    else
    {
        frame->color = &SlotFrameData::DEFAULT_COLOR;
    }

    if (this->_isOldData)
    {
        if (_getBoolean(rawData, HIDE, false)) 
        {
            frame->displayIndex = -1;
        }
    }
    else if (rawData.HasMember(ACTION) || rawData.HasMember(ACTIONS))
    {
        const auto slot = static_cast<SlotTimelineData*>(this->_timeline)->slot;
        std::vector<ActionData*> actions;
        std::vector<EventData*> events;
        _parseActionData(rawData, actions, slot->parent, slot);

        this->_mergeFrameToAnimationTimeline(frame->position, actions, events);
    }

    return frame;
}

ExtensionFrameData * JSONDataParser::_parseFFDFrame(const rapidjson::Value & rawData, unsigned frameStart, unsigned frameCount) const
{
    const auto frame  = BaseObject::borrowObject<ExtensionFrameData>();
    frame->type = (ExtensionType)_getNumber(rawData, TYPE, (int)ExtensionType::FFD);

    _parseTweenFrame<ExtensionFrameData>(rawData, *frame, frameStart, frameCount);

    const auto hasVertices = rawData.HasMember(VERTICES);
    const auto offset = _getNumber(rawData, OFFSET, (unsigned)0);
    auto x = 0.f;
    auto y = 0.f;
    for (std::size_t i = 0, l = this->_mesh->vertices.size(); i < l; i += 2)
    {
        if (hasVertices) 
        {
            const auto& rawVertices = rawData[VERTICES];
            if (i < offset || i - offset >= rawVertices.Size())
            {
                x = 0.f;
                y = 0.f;
            }
            else
            {
                x = rawVertices[i - offset].GetDouble() * this->_armature->scale;
                y = rawVertices[i + 1 - offset].GetDouble() * this->_armature->scale;
            }
        }
        else
        {
            x = 0.f;
            y = 0.f;
        }

        if (this->_mesh->skinned)
        {
            this->_mesh->slotPose.transformPoint(x, y, _helpPoint, true);
            x = _helpPoint.x;
            y = _helpPoint.y;

            const auto& boneIndices = this->_mesh->boneIndices[(std::size_t)(i / 2)];
            for (const auto boneIndex : boneIndices)
            {
                this->_mesh->inverseBindPose[boneIndex].transformPoint(x, y, _helpPoint, true);
                frame->tweens.push_back(_helpPoint.x);
                frame->tweens.push_back(_helpPoint.y);
            }
        }
        else
        {
            frame->tweens.push_back(x);
            frame->tweens.push_back(y);
        }
    }

    return frame;
}

void JSONDataParser::_parseActionData(const rapidjson::Value& rawData, std::vector<ActionData*>& actions, BoneData * bone, SlotData * slot) const
{
    const auto& actionsObject = rawData.HasMember(ACTION) ? rawData[ACTION] : (rawData.HasMember(ACTIONS) ? rawData[ACTIONS] : rawData[DEFAULT_ACTIONS]);

    if (actionsObject.IsString())
    {
        const auto actionData = BaseObject::borrowObject<ActionData>();
        actionData->type = ActionType::FadeIn;

        auto& ints = std::get<0>(actionData->data);
        auto& floats = std::get<1>(actionData->data);
        auto& strings = std::get<2>(actionData->data);

        strings.push_back(actionsObject.GetString());
        floats.push_back(-1.f);
        ints.push_back(-1);

        actionData->bone = bone;
        actionData->slot = slot;
        actions.push_back(actionData);
    }
    else if (actionsObject.IsArray())
    {
        const char* GOTO_AND_PLAY = "gotoAndPlay";
        for (size_t i = 0, l = actionsObject.Size(); i < l; ++i)
        {
            const auto& actionObject = actionsObject[i];
            const auto isArray = actionObject.IsArray();
            const auto actionData = BaseObject::borrowObject<ActionData>();
            const auto animationName = isArray ? _getParameter(actionObject, 1, "") : _getString(actionObject, GOTO_AND_PLAY, "");

            if (isArray) 
            {
                const auto& actionType = actionObject[0];
                if (actionType.IsString())
                {
                    actionData->type = _getActionType(actionType.GetString());
                }
                else 
                {
                    actionData->type = (ActionType)_getParameter(actionObject, 0, (int)ActionType::FadeIn);
                }
            }
            else 
            {
                actionData->type = ActionType::GotoAndPlay;
            }

            auto& ints = std::get<0>(actionData->data);
            auto& floats = std::get<1>(actionData->data);
            auto& strings = std::get<2>(actionData->data);

            switch (actionData->type)
            {
                case ActionType::Play:
                    strings.push_back(animationName);
                    ints.push_back(isArray ? _getParameter(actionObject, 2, (int)-1) : -1);
                    break;

                case ActionType::Stop:
                    strings.push_back(animationName);
                    break;

                case ActionType::GotoAndPlay:
                    strings.push_back(animationName);
                    floats.push_back(isArray ? _getParameter(actionObject, 2, 0.f) : 0.f);
                    ints.push_back(isArray ? _getParameter(actionObject, 3, (int)-1) : -1);
                    break;

                case ActionType::GotoAndStop:
                    strings.push_back(animationName);
                    floats.push_back(isArray ? _getParameter(actionObject, 2, 0.f) : 0.f);
                    break;

                case ActionType::FadeIn:
                    strings.push_back(animationName);
                    floats.push_back(isArray ? _getParameter(actionObject, 2, -1.f) : -1.f);
                    ints.push_back(isArray ? _getParameter(actionObject, 3, (int)-1) : -1);
                    break;

                case ActionType::FadeOut:
                    strings.push_back(animationName);
                    floats.push_back(isArray ? _getParameter(actionObject, 2, 0.f) : 0.f);
                    break;
            }

            actionData->bone = bone;
            actionData->slot = slot;
            actions.push_back(actionData);
        }
    }
}

void JSONDataParser::_parseEventData(const rapidjson::Value& rawData, std::vector<EventData*>& events, BoneData* bone, SlotData* slot) const
{
    if (rawData.HasMember(SOUND))
    {
        const auto eventData = BaseObject::borrowObject<EventData>();
        eventData->type = EventType::Sound;
        eventData->name = rawData[SOUND].GetString();
        eventData->bone = bone;
        eventData->slot = slot;
        events.push_back(eventData);
    }

    if (rawData.HasMember(EVENT))
    {
        const auto eventData = BaseObject::borrowObject<EventData>();
        eventData->type = EventType::Frame;
        eventData->name = rawData[EVENT].GetString();
        eventData->bone = bone;
        eventData->slot = slot;

        if (rawData.HasMember(DATA))
        {
            // eventData->data = rawData[DATA]; // TODO
        }

        events.push_back(eventData);
    }
}

void JSONDataParser::_parseTransform(const rapidjson::Value& rawData, Transform& transform) const
{
    transform.x = _getNumber(rawData, X, 0.f) * this->_armature->scale;
    transform.y = _getNumber(rawData, Y, 0.f) * this->_armature->scale;
    transform.skewX = _getNumber(rawData, SKEW_X, 0.f) * ANGLE_TO_RADIAN;
    transform.skewY = _getNumber(rawData, SKEW_Y, 0.f) * ANGLE_TO_RADIAN;
    transform.scaleX = _getNumber(rawData, SCALE_X, 1.f);
    transform.scaleY = _getNumber(rawData, SCALE_Y, 1.f);
}

void JSONDataParser::_parseColorTransform(const rapidjson::Value& rawData, ColorTransform& color) const
{
    color.alphaMultiplier = _getNumber(rawData, ALPHA_MULTIPLIER, (int)100) * 0.01f;
    color.redMultiplier = _getNumber(rawData, RED_MULTIPLIER, (int)100) * 0.01f;
    color.greenMultiplier = _getNumber(rawData, GREEN_MULTIPLIER, (int)100) * 0.01f;
    color.blueMultiplier = _getNumber(rawData, BLUE_MULTIPLIER, (int)100) * 0.01f;
    color.alphaOffset = _getNumber(rawData, ALPHA_OFFSET, (int)0);
    color.redOffset = _getNumber(rawData, RED_OFFSET, (int)0);
    color.greenOffset = _getNumber(rawData, GREEN_OFFSET, (int)0);
    color.blueOffset = _getNumber(rawData, BLUE_OFFSET, (int)0);
}

DragonBonesData * JSONDataParser::parseDragonBonesData(const char* rawData, float scale)
{
    if (rawData)
    {
        rapidjson::Document document;
        document.Parse(rawData);

        std::string version = _getString(document, VERSION, "");
        this->_isOldData = version == DATA_VERSION_2_3 || version == DATA_VERSION_3_0;
        if (this->_isOldData)
        {
            this->_isGlobalTransform = _getBoolean(document, IS_GLOBAL, true);
        }
        else
        {
            this->_isGlobalTransform = false;
        }

        if (version == DATA_VERSION || version == DATA_VERSION_4_0 || this->_isOldData)
        {
            const auto data = BaseObject::borrowObject<DragonBonesData>();
            data->name = _getString(document, NAME, "");
            data->frameRate = _getNumber(document, FRAME_RATE, (unsigned)24);
            if (data->frameRate == 0)
            {
                data->frameRate = 24;
            }

            if (document.HasMember(ARMATURE))
            {
                this->_data = data;
                const auto& armatureObjects = document[ARMATURE];
                for (size_t i = 0, l = armatureObjects.Size(); i < l; ++i)
                {
                    data->addArmature(_parseArmature(armatureObjects[i], scale));
                }

                this->_data = nullptr;
            }

            return data;
        }
        else
        {
            DRAGONBONES_ASSERT(false, "Nonsupport data version.");
        }
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }

    return nullptr;
}

void JSONDataParser::parseTextureAtlasData(const char* rawData, TextureAtlasData& textureAtlasData, float scale)
{
    if (rawData)
    {
        rapidjson::Document document;
        document.Parse(rawData);

        textureAtlasData.name = _getString(document, NAME, "");
        textureAtlasData.imagePath = _getString(document, IMAGE_PATH, "");
        textureAtlasData.format = _getTextureFormat(_getString(document, FORMAT, ""));

        if (scale > 0.f)
        {
            textureAtlasData.scale = scale;
        }
        else
        {
            scale = textureAtlasData.scale = _getNumber(document, SCALE, textureAtlasData.scale);
        }

        scale = 1.f / scale;

        if (document.HasMember(SUB_TEXTURE))
        {
            const auto& textureObjects = document[SUB_TEXTURE];
            for (size_t i = 0, l = textureObjects.Size(); i < l; ++i)
            {
                const auto& textureObject = textureObjects[i];
                const auto textureData = textureAtlasData.generateTexture();
                textureData->name = _getString(textureObject, NAME, "");
                textureData->rotated = _getBoolean(textureObject, ROTATED, false);
                textureData->region.x = _getNumber(textureObject, X, 0.f) * scale;
                textureData->region.y = _getNumber(textureObject, Y, 0.f) * scale;
                textureData->region.width = _getNumber(textureObject, WIDTH, 0.f) * scale;
                textureData->region.height = _getNumber(textureObject, HEIGHT, 0.f) * scale;

                const auto frameWidth = _getNumber(textureObject, FRAME_WIDTH, -1.f);
                const auto frameHeight = _getNumber(textureObject, FRAME_HEIGHT, -1.f);
                if (frameWidth > 0.f && frameHeight > 0.f)
                {
                    textureData->frame = TextureData::generateRectangle();
                    textureData->frame->x = _getNumber(textureObject, FRAME_X, 0.f) * scale;
                    textureData->frame->y = _getNumber(textureObject, FRAME_Y, 0.f) * scale;
                    textureData->frame->width = frameWidth * scale;
                    textureData->frame->height = frameHeight * scale;
                }

                textureAtlasData.addTexture(textureData);
            }
        }
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

DRAGONBONES_NAMESPACE_END