#ifndef C3DSTAT_H_
#define C3DSTAT_H_

#include "cocos3d.h"

#include "cocos2d.h"

namespace cocos3d
{

    /**
     *  class for statistic the 3D scene
	 *  stat the total triangles, drawing triangles, and draw calls 
     */
    class C3DStat
    {
        
    public:
	/**
     * Destructor
     */
        ~C3DStat();
        
		/**
         * get singleton
         */
        static C3DStat* getInstance();

		static void destroyInstance();
        
		/**
         * begin & end stat
         */
        void beginStat();
        void endStat();
        
		/**
         * add draw triangles 
         */
        void incTriangleDraw(int nTriangle){ if (_bStart) _nTriangleDraw += nTriangle; }
        
		/**
         * add total triangles
         */
        void incTriangleTotal(int nTriangle){ if (_bStart) _nTriangleTotal += nTriangle; }
        
		/**
         * add draw calls
         */
        void incDrawCall(int nDrawCall) { if (_bStart) _nDrawCall += nDrawCall; }
        
		/**
         * get & set stat enable
         */
        void setStatEnable(bool bEnable);
        bool isStatEnable() const { return _bEnable; }
        
		/**
         * get drawing triangles
         */
        int getTriangleDraw() const { return _nTriangleDraw; }
		/**
         * get total triangles
         */
        int getTriangleTotal() const { return _nTriangleTotal; }
		/**
         * get draw calls
         */
        int getDrawCall() const { return _nDrawCall; }
        
        
        
    protected:
		/**
         * Constructor
         */
        C3DStat();
        
		// properties

        int _nTriangleDraw; // triangle rendered (total triangle substract those culled by camera frustum)
        
        int _nTriangleTotal; // total triangle in the scene
        
        int _nDrawCall;
        
        bool _bStart; // start stat
        
        bool _bEnable; // enable stat or not
        
    };

	class C3DStatRender
	{
	public:
		C3DStatRender(cocos2d::CCNode* parent, float statfont = 10.f);
		~C3DStatRender();

		void setUpdateInterval(long interval) { _UpdateInterval = interval; }
		long getUpdateInterval() const { return _UpdateInterval; }

		void setStatFont(float fontsize);

		void setStatLabelPos(const cocos2d::CCPoint& pt);

		/**
         * update label string
		 */
        void update(long elapsedTime);

	private:

		long _UpdateInterval; // update show stat label every _UpdateInterval ms

		long _UpdateIntervalAcc; // accumlate of deltaTime of update

		cocos2d::CCLabelTTF* _TriangleDrawLabel;
		cocos2d::CCLabelTTF* _TriangleTotalLabel;
		cocos2d::CCLabelTTF* _DrawCallLabel;
		float _fontSize;

		cocos2d::CCNode* _parent;
	};

}



#endif
