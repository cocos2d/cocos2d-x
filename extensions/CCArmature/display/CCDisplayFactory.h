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

#ifndef __CCDISPLAYFACTORY_H__
#define __CCDISPLAYFACTORY_H__

#include "../utils/CCArmatureDefine.h"
#include "../datas/CCDatas.h"

namespace cocos2d { namespace extension { namespace armature {

class Skin;
class Bone;
class DecorativeDisplay;
class DisplayData;

class DisplayFactory
{
public:
	static void addDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
	static void createDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
	static void updateDisplay(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty);

	static void addSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
	static void createSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
	static void updateSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty);

	static void addArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
	static void createArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
	static void updateArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty);

	static void addParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
	static void createParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay);
	static void updateParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty);

	static void addShaderDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
	static void createShaderDisplay(Bone *bone, DecorativeDisplay *decoDisplay);

};


}}} // namespace cocos2d { namespace extension { namespace armature {

#endif /*__CCDISPLAYFACTORY_H__*/
