/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCDISPLAYFACTORY_H__
#define __CCDISPLAYFACTORY_H__

#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCDatas.h"

namespace cocostudio {

class Skin;
class Bone;
class DecorativeDisplay;
class DisplayData;
/**
 *  @js NA
 *  @lua NA
 */
class DisplayFactory
{
public:
    static void addDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    static void createDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    static void updateDisplay(Bone *bone, float dt, bool dirty);

    static void addSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    static void createSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    static void initSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, const char *displayName, Skin *skin);


    static void addArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    static void createArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    static void updateArmatureDisplay(Bone *bone, cocos2d::Node *display, float dt);

    static void addParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
    static void createParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
    static void updateParticleDisplay(Bone *bone, cocos2d::Node *display, float dt);
};


}

#endif /*__CCDISPLAYFACTORY_H__*/
