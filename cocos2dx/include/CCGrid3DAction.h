/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#ifndef __ACTION_CCGRID3D_ACTION_H__
#define __ACTION_CCGRID3D_ACTION_H__

#include "CCGridAction.h"

namespace cocos2d
{
	/** CCWaves3D action */
	class CCX_DLL CCWaves3D : public CCGrid3DAction
	{
	public:
		/** amplitude of the wave */
		inline float getAmplitude(void) { return m_fAmplitude; }
		inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }
		/** amplitude rate of the wave */
		inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
		inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

		bool initWithWaves(int wav, float amp, ccGridSize gridSize, ccTime duration);

		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void update(ccTime time);

	public:
		static CCWaves3D* actionWithWaves(int wav, float amp, ccGridSize gridSize, ccTime duration);

	protected:
		int m_nWaves;
		float m_fAmplitude;
		float m_fAmplitudeRate;
	};

	/** CCFlipX3D action */
	class CCX_DLL CCFlipX3D : public CCGrid3DAction
	{
	public:
		bool initWithDuration(ccTime duration);
		virtual bool initWithSize(ccGridSize gridSize, ccTime duration);
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void update(ccTime time);

	public:
		static CCFlipX3D* actionWithDuration(ccTime duration);
	};

	/** CCFlipY3D action */
	class CCX_DLL CCFlipY3D : public CCFlipX3D
	{
	public:
		virtual void update(ccTime time);
		virtual NSObject* copyWithZone(NSZone* pZone);

	public:
		static CCFlipY3D* actionWithDuration(ccTime duration);
	};

	/** CCLens3D action */
	class CCX_DLL CCLens3D : public CCGrid3DAction
	{
	public:
		/** lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect */
		inline float getLensEffect(void) { return m_fLensEffect; }
		inline void setLensEffect(float fLensEffect) { m_fLensEffect = fLensEffect; }
		/** lens center position */
		inline CGPoint getPosition(void) { return m_position; }
		inline void setPosition(CGPoint position) { m_position = position; }

		bool initWithPosition(CGPoint pos, float r, ccGridSize gridSize, ccTime duration);
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void update(ccTime time);

	public:
        static CCLens3D* actionWithPosition(CGPoint pos, float r, ccGridSize gridSize, ccTime duration);
	protected:
		CGPoint m_position;
		float m_fRadius;
		float m_fLensEffect;
		CGPoint m_lastPosition;
	};

	/** CCRipple3D action */
	class CCX_DLL CCRipple3D : public CCGrid3DAction
	{
	public:
		/** center position */
		inline CGPoint getPosition(void) { return m_position; }
		inline void setPosition(CGPoint position) { m_position = position; }
		/** amplitude */
		inline float getAmplitude(void) { return m_fAmplitude; }
		inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }
		/** amplitude rate */
		inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
		inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

		bool initWithPosition(CGPoint pos, float r, int wav, float amp, 
			ccGridSize gridSize, ccTime duration);
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void update(ccTime time);

	public:
		static CCRipple3D* actionWithPosition(CGPoint pos, float r, int wav, float amp, 
			ccGridSize gridSize, ccTime duration);
	protected:
		CGPoint m_position;
		float m_fRadius;
		int m_nWaves;
		float m_fAmplitude;
		float m_fAmplitudeRate;
	};

	/** CCShaky3D action */
	class CCX_DLL CCShaky3D : public CCGrid3DAction
	{
	public:
		bool initWithRange(int range, bool shakeZ, ccGridSize gridSize, ccTime duration);
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void update(ccTime time);

	public:
        static CCShaky3D* actionWithRange(int range, bool shakeZ, ccGridSize gridSize, ccTime duration);

	protected:
		int m_nRandrange;
		bool m_bShakeZ;
	};

	/** CCLiquid action */
	class CCX_DLL CCLiquid : public CCGrid3DAction
	{
	public:
		/** amplitude */
		inline float getAmplitude(void) { return m_fAmplitude; }
		inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }
		/** amplitude rate */
		inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
		inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

		bool initWithWaves(int wav, float amp, ccGridSize gridSize, ccTime duration);
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void update(ccTime time);

	public:
		static CCLiquid* actionWithWaves(int wav, float amp, ccGridSize gridSize, ccTime duration);

	protected:
		int m_nWaves;
		float m_fAmplitude;
		float m_fAmplitudeRate;
	};

	/** CCWaves action */
	class CCX_DLL CCWaves : public CCGrid3DAction
	{
	public:
		/** amplitude */
		inline float getAmplitude(void) { return m_fAmplitude; }
		inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }
		/** amplitude rate */
		inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
		inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

		bool initWithWaves(int wav, float amp, bool h, bool v, ccGridSize gridSize,
			ccTime duration);
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void update(ccTime time);

	public:
        static CCWaves* actionWithWaves(int wav, float amp, bool h, bool v, ccGridSize gridSize,
			ccTime duration);
	protected:
		int m_nWaves;
		float m_fAmplitude;
		float m_fAmplitudeRate;
		bool m_bVertical;
		bool m_bHorizontal;
	};

	/** CCTwirl action */
	class CCX_DLL CCTwirl : public CCGrid3DAction
	{
	public:
		/** twirl center */
		inline CGPoint getPosition(void) { return m_position; }
		inline void setPosition(CGPoint position) { m_position = position; }
		/** amplitude */
		inline float getAmplitude(void) { return m_fAmplitude; }
		inline void setAmplitude(float fAmplitude) { m_fAmplitude = fAmplitude; }
		/** amplitude rate */
		inline float getAmplitudeRate(void) { return m_fAmplitudeRate; }
		inline void setAmplitudeRate(float fAmplitudeRate) { m_fAmplitudeRate = fAmplitudeRate; }

		bool initWithPosition(CGPoint pos, int t, float amp, ccGridSize gridSize,
			ccTime duration);
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void update(ccTime time);

	public:
		static CCTwirl* actionWithPosition(CGPoint pos, int t, float amp, ccGridSize gridSize,
			ccTime duration);
	protected:
		CGPoint m_position;
		int m_nTwirls;
		float m_fAmplitude;
		float m_fAmplitudeRate;
	};
}

#endif // __ACTION_CCGRID3D_ACTION_H__
