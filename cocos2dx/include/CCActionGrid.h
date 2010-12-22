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

#include "CCActionInterval.h"
#include "CCActionInstant.h"

namespace cocos2d
{
	class CCGridBase;

	/** @brief Base class for Grid actions */
	class CCX_DLL CCGridAction : public CCIntervalAction
	{
	public:
		virtual NSObject* copyWithZone(NSZone* pZone);
		virtual void startWithTarget(CCNode *pTarget);
		virtual CCIntervalAction* reverse(void);

		/** initializes the action with size and duration */
		virtual bool initWithSize(ccGridSize gridSize, ccTime duration);
		/** returns the grid */
		virtual CCGridBase* getGrid(void);

	public:
		/** creates the action with size and duration */
		static CCGridAction* actionWithSize(ccGridSize gridSize, ccTime duration);

	protected:
		ccGridSize m_sGridSize;
	};

	/** 
	 @brief Base class for CCGrid3D actions.
	 Grid3D actions can modify a non-tiled grid.
	 */
	class CCX_DLL CCGrid3DAction : public CCGridAction
	{
	public:
		/** returns the grid */
		virtual CCGridBase* getGrid(void);
		/** returns the vertex than belongs to certain position in the grid */
		ccVertex3F vertex(ccGridSize pos);
		/** returns the non-transformed vertex than belongs to certain position in the grid */
		ccVertex3F originalVertex(ccGridSize pos);
		/** sets a new vertex to a certain position of the grid */
		void setVertex(ccGridSize pos, ccVertex3F vertex);

	public:
		/** creates the action with size and duration */
        static CCGrid3DAction* actionWithSize(ccGridSize gridSize, ccTime duration);
	};

	/** @brief Base class for CCTiledGrid3D actions */
	class CCX_DLL CCTiledGrid3DAction : public CCGridAction
	{
	public:
		/** returns the tile that belongs to a certain position of the grid */
		ccQuad3 tile(ccGridSize pos);
		/** returns the non-transformed tile that belongs to a certain position of the grid */
		ccQuad3 originalTile(ccGridSize pos);
		/** sets a new tile to a certain position of the grid */
		void setTile(ccGridSize pos, ccQuad3 coords);

		/** returns the grid */
		virtual CCGridBase* getGrid(void);

	public:
		/** creates the action with size and duration */
        static CCTiledGrid3DAction* actionWithSize(ccGridSize gridSize, ccTime duration);
	};

	/** @brief CCAccelDeccelAmplitude action */
	class CCX_DLL CCAccelDeccelAmplitude : public CCIntervalAction
	{
	public:
		virtual ~CCAccelDeccelAmplitude(void);
		/** initializes the action with an inner action that has the amplitude property, and a duration time */
		bool initWithAction(CCAction *pAction, ccTime duration);

		virtual void startWithTarget(CCNode *pTarget);
		virtual void update(ccTime time);
        virtual CCIntervalAction* reverse(void);

		/** get amplitude rate */
		inline float getRate(void) { return m_fRate; }
		/** set amplitude rate */
		inline void setRate(float fRate) { m_fRate = fRate; }

	public:
		/** creates the action with an inner action that has the amplitude property, and a duration time */
		static CCAccelDeccelAmplitude* actionWithAction(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCIntervalAction *m_pOther;
	};

	/** @brief CCAccelAmplitude action */
	class CCX_DLL CCAccelAmplitude : public CCIntervalAction
	{
	public:
		~CCAccelAmplitude(void);
		/** initializes the action with an inner action that has the amplitude property, and a duration time */
		bool initWithAction(CCAction *pAction, ccTime duration);

		/** get amplitude rate */
		inline float getRate(void) { return m_fRate; }
		/** set amplitude rate */
		inline void setRate(float fRate) { m_fRate = fRate; }

		virtual void startWithTarget(CCNode *pTarget);
		virtual void update(ccTime time);
        virtual CCIntervalAction* reverse(void);

	public:
		/** creates the action with an inner action that has the amplitude property, and a duration time */
		static CCAccelAmplitude* actionWithAction(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCIntervalAction *m_pOther;
	};

	/** @brief CCDeccelAmplitude action */
	class CCX_DLL CCDeccelAmplitude : public CCIntervalAction
	{
	public:
		~CCDeccelAmplitude(void);
		/** initializes the action with an inner action that has the amplitude property, and a duration time */
		bool initWithAction(CCAction *pAction, ccTime duration);

		/** get amplitude rate */
		inline float getRate(void) { return m_fRate; }
		/** set amplitude rate */
		inline void setRate(float fRate) { m_fRate = fRate; }

		virtual void startWithTarget(CCNode *pTarget);
		virtual void update(ccTime time);
        virtual CCIntervalAction* reverse(void);

	public:
		/** creates the action with an inner action that has the amplitude property, and a duration time */
        static CCDeccelAmplitude* actionWithAction(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCIntervalAction *m_pOther;
	};

	/** @brief CCStopGrid action.
	 @warning Don't call this action if another grid action is active.
	 Call if you want to remove the the grid effect. Example:
	 CCSequence::actions(Lens::action(...), CCStopGrid::action(...), NULL);
	 */
	class CCX_DLL CCStopGrid : public CCInstantAction
	{
	public:
		virtual void startWithTarget(CCNode *pTarget);

	public:
		/** Allocates and initializes the action */
		static CCStopGrid* action(void);
	};

	/** @brief CCReuseGrid action */
	class CCX_DLL CCReuseGrid : public CCInstantAction
	{
	public:
		/** initializes an action with the number of times that the current grid will be reused */
        bool initWithTimes(int times);

		virtual void startWithTarget(CCNode *pTarget);

	public:
		/** creates an action with the number of times that the current grid will be reused */
		static CCReuseGrid* actionWithTimes(int times);

	protected:
		int m_nTimes;
	};

} // end of namespace cocos2d

#endif // __ACTION_CCGRID_ACTION_H__
