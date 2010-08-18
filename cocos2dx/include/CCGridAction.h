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
#ifndef __ACTION_CCGRID_ACTION_H__
#define __ACTION_CCGRID_ACTION_H__

#include "CCIntervalAction.h"
#include "CCInstantAction.h"

namespace cocos2d
{
	class CCGridBase;

	/** Base class for Grid actions */
	class CCX_DLL CCGridAction : public CCIntervalAction
	{
	public:
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void startWithTarget(NSObject *pTarget);
		virtual CCIntervalAction* reverse(void);

		/** initializes the action with size and duration */
		virtual bool initWithSize(ccGridSize gridSize, ccTime duration);
		/** returns the grid */
		virtual CCGridBase* grid(void);

	public:
		/** creates the action with size and duration */
		static CCGridAction* actionWithSize(ccGridSize gridSize, ccTime duration);

	protected:
		ccGridSize m_sGridSize;
	};

	/** Base class for CCGrid3D actions.
	 Grid3D actions can modify a non-tiled grid.
	 */
	class CCX_DLL CCGrid3DAction : public CCGridAction
	{
	public:
		virtual CCGridBase* grid(void);
		ccVertex3F vertex(ccGridSize pos);
		ccVertex3F originalVertex(ccGridSize pos);
		void setVertex(ccGridSize pos, ccVertex3F vertex);

	public:
        static CCGrid3DAction* actionWithSize(ccGridSize gridSize, ccTime duration);
	};

	/** Base class for CCTiledGrid3D actions */
	class CCX_DLL CCTiledGrid3DAction : public CCGridAction
	{
	public:
		ccQuad3 tile(ccGridSize pos);
		ccQuad3 originalTile(ccGridSize pos);
		void setTile(ccGridSize pos, ccQuad3 coords);

		virtual CCGridBase* grid(void);

	public:
        static CCTiledGrid3DAction* actionWithSize(ccGridSize gridSize, ccTime duration);
	};

	/** CCAccelDeccelAmplitude action */
	class CCX_DLL CCAccelDeccelAmplitude : public CCIntervalAction
	{
	public:
		virtual ~CCAccelDeccelAmplitude(void);
		bool initWithAction(CCAction *pAction, ccTime duration);

		virtual void startWithTarget(NSObject *pTarget);
		virtual void update(ccTime time);
        virtual CCIntervalAction* reverse(void);

		inline float getRate(void) { return m_fRate; }
		inline void setRate(float fRate) { m_fRate = fRate; }

	public:
		static CCAccelDeccelAmplitude* actionWithAction(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCIntervalAction *m_pOther;
	};

	/** CCAccelAmplitude action */
	class CCX_DLL CCAccelAmplitude : public CCIntervalAction
	{
	public:
		~CCAccelAmplitude(void);
		bool initWithAction(CCAction *pAction, ccTime duration);

		virtual void startWithTarget(NSObject *pTarget);
		virtual void update(ccTime time);
        virtual CCIntervalAction* reverse(void);

	public:
		static CCAccelAmplitude* actionWithAction(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCIntervalAction *m_pOther;
	};

	/** CCDeccelAmplitude action */
	class CCX_DLL CCDeccelAmplitude : public CCIntervalAction
	{
	public:
		~CCDeccelAmplitude(void);
		bool initWithAction(CCAction *pAction, ccTime duration);

		virtual void startWithTarget(NSObject *pTarget);
		virtual void update(ccTime time);
        virtual CCIntervalAction* reverse(void);

	public:
        static CCDeccelAmplitude* actionWithAction(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCIntervalAction *m_pOther;
	};

	/** CCStopGrid action.
	 Don't call this action if another grid action is active.
	 Call if you want to remove the the grid effect. Example:
	 [Sequence actions:[Lens ...], [StopGrid action], nil];
	 */
	class CCX_DLL CCStopGrid : public CCInstantAction
	{
	public:
		virtual void startWithTarget(NSObject *pTarget);

	public:
		static CCStopGrid* action(void);
	};

	/** CCReuseGrid action */
	class CCX_DLL CCReuseGrid : public CCInstantAction
	{
	public:
        bool initWithTimes(int times);

		virtual void startWithTarget(NSObject *pTarget);

	public:
		static CCReuseGrid* actionWithTimes(int times);

	protected:
		int m_nTimes;
	};

} // end of namespace cocos2d

#endif // __ACTION_CCGRID_ACTION_H__
