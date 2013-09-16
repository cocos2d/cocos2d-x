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

#include "UIActionFrame.h"
#include "../../Json/DictionaryHelper.h"

NS_CC_EXT_BEGIN

UIActionFrame::UIActionFrame()
{

}
UIActionFrame::~UIActionFrame()
{

}

void UIActionFrame::initWithDictionary(cs::JsonDictionary *dic)
{
    setFrameId(DICTOOL->getIntValue_json(dic, "frameid"));
    setStartTime(DICTOOL->getFloatValue_json(dic, "starttime"));
    setPosition(Point(DICTOOL->getFloatValue_json(dic, "positionx"), DICTOOL->getFloatValue_json(dic, "positiony")));
    setScaleX(DICTOOL->getFloatValue_json(dic, "scalex"));
    setScaleY(DICTOOL->getFloatValue_json(dic, "scaley"));
    setRotation(DICTOOL->getFloatValue_json(dic, "rotation"));
    setOpacity(DICTOOL->getIntValue_json(dic, "opacity"));
    setColor(Color3B(DICTOOL->getIntValue_json(dic, "colorr"), DICTOOL->getIntValue_json(dic, "colorg"), DICTOOL->getIntValue_json(dic, "colorb")));
}

NS_CC_EXT_END