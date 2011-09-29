/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009      Sindesso Pty Ltd http://www.sindesso.com/

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
#ifndef __ACTION_CCPAGETURN3D_ACTION_H__
#define __ACTION_CCPAGETURN3D_ACTION_H__

#include "CCActionGrid3D.h"

namespace cocos2d
{
	/**
	 @brief This action simulates a page turn from the bottom right hand corner of the screen.
	 It's not much use by itself but is used by the PageTurnTransition.
	 
	 Based on an original paper by L Hong et al.
	 http://www.parc.com/publication/1638/turning-pages-of-3d-electronic-books.html
	  
	 @since v0.8.2
	 */
	class CC_DLL CCPageTurn3D : public CCGrid3DAction
	{
	public:
		virtual void update(ccTime time);

	public:
		/** create the action */
		static CCPageTurn3D* actionWithSize(const ccGridSize& gridSize, ccTime time);
	};
}

#endif // __ACTION_CCPAGETURN3D_ACTION_H__
