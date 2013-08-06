/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __UIACTIONFRAME_H__
#define __UIACTIONFRAME_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../../CCArmature/external_tool/Json/CSContentJsonDictionary.h"

NS_CC_EXT_BEGIN

class UIActionFrame:public CCObject
{
protected:

public:
    UIActionFrame();
    virtual ~UIActionFrame();
	//
	CC_SYNTHESIZE(int, m_frameId, FrameId);
	//
	CC_SYNTHESIZE(float, m_startTime, StartTime);
	//
	CC_SYNTHESIZE(CCPoint, m_position, Position);
	//
	CC_SYNTHESIZE(float, m_scaleX, ScaleX);
	//
	CC_SYNTHESIZE(float, m_scaleY, ScaleY);
	//
	CC_SYNTHESIZE(float, m_rotation, Rotation);
	//
	CC_SYNTHESIZE(float, m_opacity, Opacity);
	//
	CC_SYNTHESIZE(ccColor3B, m_color, Color);
    
    void initWithDictionary(cs::CSJsonDictionary* dic);

};

NS_CC_EXT_END

#endif
