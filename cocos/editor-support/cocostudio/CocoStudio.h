/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#ifndef __EDITOR_SUPPORT_COCOSTUDIO_H__
#define __EDITOR_SUPPORT_COCOSTUDIO_H__

#include "editor-support/cocostudio/CCActionFrame.h"
#include "editor-support/cocostudio/CCActionFrameEasing.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "editor-support/cocostudio/CCActionNode.h"
#include "editor-support/cocostudio/CCActionObject.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "editor-support/cocostudio/CCBone.h"
#include "editor-support/cocostudio/CCArmatureAnimation.h"
#include "editor-support/cocostudio/CCProcessBase.h"
#include "editor-support/cocostudio/CCTween.h"
#include "editor-support/cocostudio/CCDatas.h"
#include "editor-support/cocostudio/CCBatchNode.h"
#include "editor-support/cocostudio/CCDecorativeDisplay.h"
#include "editor-support/cocostudio/CCDisplayFactory.h"
#include "editor-support/cocostudio/CCDisplayManager.h"
#include "editor-support/cocostudio/CCSkin.h"
#include "editor-support/cocostudio/CCColliderDetector.h"
#include "editor-support/cocostudio/CCArmatureDataManager.h"
#include "editor-support/cocostudio/CCArmatureDefine.h"
#include "editor-support/cocostudio/CCDataReaderHelper.h"
#include "editor-support/cocostudio/CCTransformHelp.h"
#include "editor-support/cocostudio/CCUtilMath.h"
#include "editor-support/cocostudio/CCComBase.h"
#include "editor-support/cocostudio/CCComAttribute.h"
#include "editor-support/cocostudio/CCComAudio.h"
#include "editor-support/cocostudio/CCComController.h"
#include "editor-support/cocostudio/CCComRender.h"
#include "editor-support/cocostudio/CCInputDelegate.h"
#include "editor-support/cocostudio/DictionaryHelper.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCSSceneReader.h"
#include "editor-support/cocostudio/TriggerBase.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimelineCache.h"
#include "editor-support/cocostudio/ActionTimeline/CCFrame.h"
#include "editor-support/cocostudio/ActionTimeline/CCTimeLine.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimeline.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimelineNode.h"
#include "editor-support/cocostudio/ActionTimeline/CCBoneNode.h"
#include "editor-support/cocostudio/ActionTimeline/CCSkeletonNode.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "editor-support/cocostudio/CocosStudioExport.h"

namespace cocostudio
{
    void CC_STUDIO_DLL destroyCocosStudio();
}

#endif
