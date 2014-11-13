/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	DynamicAttribute::DynamicAttribute (void) :
		IElement()
	{
	}
	//-----------------------------------------------------------------------
	DynamicAttribute::~DynamicAttribute (void)
	{
	}
	//-----------------------------------------------------------------------
	DynamicAttribute::DynamicAttributeType DynamicAttribute::getType (void) const
	{
		return mType;
	}
	//-----------------------------------------------------------------------
	void DynamicAttribute::setType (DynamicAttribute::DynamicAttributeType type)
	{
		mType = type;
	}

	//-----------------------------------------------------------------------
	DynamicAttributeFixed::DynamicAttributeFixed (void) : mValue(0)
	{
		mType = DynamicAttribute::DAT_FIXED;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeFixed::DynamicAttributeFixed (const DynamicAttributeFixed& dynamicAttributeFixed)
	{
		mType = DynamicAttribute::DAT_FIXED;
		mValue = dynamicAttributeFixed.mValue;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeFixed::~DynamicAttributeFixed (void)
	{
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeFixed::setValue (Real value)
	{
		mValue = value;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeFixed::getValue (Real x)
	{
		return mValue;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeFixed::copyAttributesTo(DynamicAttribute* dynamicAttribute)
	{
		if (!dynamicAttribute || dynamicAttribute->getType() != DynamicAttribute::DAT_FIXED)
			return;

		DynamicAttributeFixed* dynAttr = static_cast<DynamicAttributeFixed*>(dynamicAttribute);
		dynAttr->mValue = mValue;
	}

	//-----------------------------------------------------------------------
	DynamicAttributeRandom::DynamicAttributeRandom (void) : mMin(0), mMax(0)
	{
		mType = DynamicAttribute::DAT_RANDOM;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeRandom::DynamicAttributeRandom (const DynamicAttributeRandom& dynamicAttributeRandom)
	{
		mType = DynamicAttribute::DAT_RANDOM;
		mMin = dynamicAttributeRandom.mMin;
		mMax = dynamicAttributeRandom.mMax;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeRandom::~DynamicAttributeRandom (void)
	{
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeRandom::getMin (void) const
	{
		return mMin;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeRandom::setMin (Real min)
	{
		mMin = min;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeRandom::getMax (void) const
	{
		return mMax;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeRandom::setMax (Real max)
	{
		mMax = max;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeRandom::setMinMax (Real min, Real max)
	{
		mMin = min;
		mMax = max;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeRandom::getValue (Real x)
	{
		return Math::RangeRandom(mMin, mMax);
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeRandom::copyAttributesTo(DynamicAttribute* dynamicAttribute)
	{
		if (!dynamicAttribute || dynamicAttribute->getType() != DynamicAttribute::DAT_RANDOM)
			return;

		DynamicAttributeRandom* dynAttr = static_cast<DynamicAttributeRandom*>(dynamicAttribute);
		dynAttr->mMin = mMin;
		dynAttr->mMax = mMax;
	}

	//-----------------------------------------------------------------------
	DynamicAttributeCurved::DynamicAttributeCurved (void) : 
		mInterpolationType(IT_LINEAR), 
		mRange(0)
	{
		mType = DynamicAttribute::DAT_CURVED;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeCurved::DynamicAttributeCurved (InterpolationType interpolationType) : 
		mInterpolationType(interpolationType), 
		mRange(0)
	{
		mType = DynamicAttribute::DAT_CURVED;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeCurved::DynamicAttributeCurved (const DynamicAttributeCurved& dynamicAttributeCurved)
	{
		mType = DynamicAttribute::DAT_CURVED;
		mInterpolationType = dynamicAttributeCurved.mInterpolationType;
		mSpline = dynamicAttributeCurved.mSpline;
		mRange = dynamicAttributeCurved.mRange;

		// Copy controlpoints
		DynamicAttributeCurved::ControlPointList::const_iterator it; // Need const_iterator here!
		DynamicAttributeCurved::ControlPointList::const_iterator itEnd = dynamicAttributeCurved.mControlPoints.end();
		for (it = dynamicAttributeCurved.mControlPoints.begin(); it != itEnd; ++it)
		{
			Vector2 controlPoint = *it;
			mControlPoints.push_back (controlPoint);
		}
		processControlPoints();
	}
	//-----------------------------------------------------------------------
	DynamicAttributeCurved::~DynamicAttributeCurved (void)
	{
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeCurved::setInterpolationType (InterpolationType interpolationType)
	{
		if (interpolationType != mInterpolationType)
		{
			// If switched to another InterpolationType, the already existing ControlPoints will be removed.
			removeAllControlPoints();
			mInterpolationType = interpolationType;
		}
	}
	//-----------------------------------------------------------------------
	InterpolationType DynamicAttributeCurved::getInterpolationType (void) const
	{
		return mInterpolationType;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeCurved::getValue (Real x)
	{
		switch (mInterpolationType)
		{
		case IT_LINEAR:
			{
				// Search the interval in which 'x' resides and apply linear interpolation
				if (mControlPoints.empty())
					return 0;

				ControlPointList::iterator it1 = _findNearestControlPointIterator(x);
				ControlPointList::iterator it2 = it1 + 1;
				if (it2 != mControlPoints.end())
				{
					// Calculate fraction: y = y1 + ((y2 - y1) * (x - x1)/(x2 - x1))
					return (*it1).y + (((*it2).y - (*it1).y) * (x - (*it1).x)/((*it2).x - (*it1).x));
				}
				else
				{
					return (*it1).y;
				}
			}
			break;

		case IT_SPLINE:
			{
				// Fit using spline
				if (mSpline.getNumPoints() < 1)
					return 0;

				Real fraction = x / mRange;
				return (mSpline.interpolate(fraction < 1.0f ? fraction : 1.0f)).y;
			}
			break;
		}

		return 0;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeCurved::addControlPoint (Real x, Real y)
	{
		mControlPoints.push_back(Vector2(x, y));
	}
	//-----------------------------------------------------------------------
	const DynamicAttributeCurved::ControlPointList& DynamicAttributeCurved::getControlPoints (void) const
	{
		return mControlPoints;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeCurved::processControlPoints(void)
	{
		if (mControlPoints.empty())
			return;

		std::sort(mControlPoints.begin(), mControlPoints.end(), ControlPointSorter());
		mRange = (*_getLastValidIterator()).x - (*_getFirstValidIterator()).x;

		if (mInterpolationType == IT_SPLINE)
		{
			// Add all sorted control points to the spline
			DynamicAttributeCurved::ControlPointList::iterator it;
			mSpline.clear();
			for (it = mControlPoints.begin(); it != mControlPoints.end(); ++it)
				mSpline.addPoint(Vector3((*it).x, (*it).y, 0));
		}
	}
	//-----------------------------------------------------------------------
	size_t DynamicAttributeCurved::getNumControlPoints(void) const
	{
		return mControlPoints.size();
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeCurved::removeAllControlPoints(void)
	{
		mControlPoints.clear();
	}
	//-----------------------------------------------------------------------
	DynamicAttributeCurved::ControlPointList::iterator DynamicAttributeCurved::_findNearestControlPointIterator(Real x)
	{
		// Assume that the ControlPointList is not empty
		ControlPointList::iterator it;
		ControlPointList::iterator itEnd = mControlPoints.end();
		for (it = mControlPoints.begin(); it != itEnd; ++it)
		{
			if (x < (*it).x)
			{
				if (it == mControlPoints.begin())
					return it;
				else
					return --it;
			}
		}

		// If not found return the last valid iterator
		return --it;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeCurved::ControlPointList::iterator DynamicAttributeCurved::_getFirstValidIterator(void)
	{
		return mControlPoints.begin();
	}
	//-----------------------------------------------------------------------
	DynamicAttributeCurved::ControlPointList::iterator DynamicAttributeCurved::_getLastValidIterator(void)
	{
		return mControlPoints.end() - 1;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeCurved::copyAttributesTo(DynamicAttribute* dynamicAttribute)
	{
		if (!dynamicAttribute || dynamicAttribute->getType() != DynamicAttribute::DAT_CURVED)
			return;

		DynamicAttributeCurved* dynAttr = static_cast<DynamicAttributeCurved*>(dynamicAttribute);
		dynAttr->mInterpolationType = mInterpolationType;
		dynAttr->mSpline = mSpline;
		dynAttr->mRange = mRange;

		// Copy controlpoints
		DynamicAttributeCurved::ControlPointList::const_iterator it; // Need const_iterator here!
		DynamicAttributeCurved::ControlPointList::const_iterator itEnd = mControlPoints.end();
		for (it = mControlPoints.begin(); it != itEnd; ++it)
		{
			Vector2 controlPoint = *it;
			dynAttr->mControlPoints.push_back(controlPoint);
		}
		dynAttr->processControlPoints();
	}


	//-----------------------------------------------------------------------
	DynamicAttributeOscillate::DynamicAttributeOscillate (void) :
		mOscillationType(DynamicAttributeOscillate::OSCT_SINE),
		mFrequency(1.0f),
		mPhase(0.0f),
		mBase(0.0f),
		mAmplitude(1.0f)
	{
		mType = DynamicAttribute::DAT_OSCILLATE;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeOscillate::DynamicAttributeOscillate (const DynamicAttributeOscillate& dynamicAttributeOscillate)
	{
		mType = DynamicAttribute::DAT_OSCILLATE;
	}
	//-----------------------------------------------------------------------
	DynamicAttributeOscillate::~DynamicAttributeOscillate (void)
	{
	}
	//-----------------------------------------------------------------------
	DynamicAttributeOscillate::OscillationType DynamicAttributeOscillate::getOscillationType (void) const
	{
		return mOscillationType;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeOscillate::setOscillationType (DynamicAttributeOscillate::OscillationType oscillationType)
	{
		mOscillationType = oscillationType;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeOscillate::getFrequency (void) const
	{
		return mFrequency;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeOscillate::setFrequency (Real frequency)
	{
		mFrequency = frequency;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeOscillate::getPhase (void) const
	{
		return mPhase;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeOscillate::setPhase (Real phase)
	{
		mPhase = phase;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeOscillate::getBase (void) const
	{
		return mBase;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeOscillate::setBase (Real base)
	{
		mBase = base;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeOscillate::getAmplitude (void) const
	{
		return mAmplitude;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeOscillate::setAmplitude (Real amplitude)
	{
		mAmplitude = amplitude;
	}
	//-----------------------------------------------------------------------
	Real DynamicAttributeOscillate::getValue (Real x)
	{
		switch (mOscillationType)
		{
			case OSCT_SINE:
			{
				return mBase + mAmplitude * Math::Sin(mPhase + mFrequency * x * Math::TWO_PI);
			}
			break;
			case OSCT_SQUARE:
			{
				return mBase + mAmplitude * Math::Sign(Math::Sin(mPhase + mFrequency * x * Math::TWO_PI));
			}
			break;
		}

		return 0;
	}
	//-----------------------------------------------------------------------
	void DynamicAttributeOscillate::copyAttributesTo(DynamicAttribute* dynamicAttribute)
	{
		if (!dynamicAttribute || dynamicAttribute->getType() != DynamicAttribute::DAT_OSCILLATE)
			return;

		DynamicAttributeOscillate* dynAttr = static_cast<DynamicAttributeOscillate*>(dynamicAttribute);
		dynAttr->mOscillationType = mOscillationType;
		dynAttr->mFrequency = mFrequency;
		dynAttr->mPhase = mPhase;
		dynAttr->mBase = mBase;
		dynAttr->mAmplitude = mAmplitude;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	Real DynamicAttributeHelper::calculate(DynamicAttribute* dyn, Real x, Real defaultValue)
	{
		if (dyn)
		{
			return dyn->getValue(x);
		}

		return defaultValue;
	}

}
