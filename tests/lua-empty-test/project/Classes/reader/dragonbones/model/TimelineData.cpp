#include "TimelineData.h"

DRAGONBONES_NAMESPACE_BEGIN

Matrix* BoneTimelineData::cacheFrame(std::vector<Matrix*>& cacheFrames, std::size_t cacheFrameIndex, const Matrix& globalTransformMatrix)
{
    const auto cacheMatrix = cacheFrames[cacheFrameIndex] = new Matrix();
    *cacheMatrix = globalTransformMatrix;

    return cacheMatrix;
}

BoneTimelineData::BoneTimelineData()
{
    _onClear();
}
BoneTimelineData::~BoneTimelineData()
{
    _onClear();
}

void BoneTimelineData::_onClear()
{
    TimelineData::_onClear();

    bone = nullptr;
    originTransform.identity();

    Matrix* prevMatrix = nullptr;
    for (const auto matrix : cachedFrames)
    {
        if (matrix)
        {
            if (prevMatrix && prevMatrix != matrix)
            {
                delete prevMatrix;
            }

            prevMatrix = matrix;
        }
    }

    cachedFrames.clear();
}

void BoneTimelineData::cacheFrames(std::size_t cacheFrameCount)
{
    Matrix* prevMatrix = nullptr;
    for (const auto matrix : cachedFrames)
    {
        if (matrix)
        {
            if (prevMatrix && prevMatrix != matrix)
            {
                delete prevMatrix;
            }

            prevMatrix = matrix;
        }
    }

    cachedFrames.clear();
    cachedFrames.resize(cacheFrameCount, nullptr);
}

Matrix* SlotTimelineData::cacheFrame(std::vector<Matrix*>& cacheFrames, std::size_t cacheFrameIndex, const Matrix& globalTransformMatrix)
{
    const auto cacheMatrix = cacheFrames[cacheFrameIndex] = new Matrix();
    *cacheMatrix = globalTransformMatrix;

    return cacheMatrix;
}

SlotTimelineData::SlotTimelineData()
{
    _onClear();
}
SlotTimelineData::~SlotTimelineData()
{
    _onClear();
}

void SlotTimelineData::_onClear()
{
    TimelineData::_onClear();

    slot = nullptr;

    Matrix* prevMatrix = nullptr;
    for (const auto matrix : cachedFrames)
    {
        if (matrix)
        {
            if (prevMatrix && prevMatrix != matrix)
            {
                delete prevMatrix;
            }

            prevMatrix = matrix;
        }
    }

    cachedFrames.clear();
}

void SlotTimelineData::cacheFrames(std::size_t cacheFrameCount)
{
    Matrix* prevMatrix = nullptr;
    for (const auto matrix : cachedFrames)
    {
        if (matrix)
        {
            if (prevMatrix && prevMatrix != matrix)
            {
                delete prevMatrix;
            }

            prevMatrix = matrix;
        }
    }

    cachedFrames.clear();
    cachedFrames.resize(cacheFrameCount, nullptr);
}

FFDTimelineData::FFDTimelineData()
{
    _onClear();
}
FFDTimelineData::~FFDTimelineData()
{
    _onClear();
}

void FFDTimelineData::_onClear()
{
    TimelineData::_onClear();

    displayIndex = 0;
    skin = nullptr;
    slot = nullptr;
}

DRAGONBONES_NAMESPACE_END