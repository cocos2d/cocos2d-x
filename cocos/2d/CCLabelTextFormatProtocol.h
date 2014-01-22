/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
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

#ifndef _CCLabelTextFormatProtocol_h_
#define _CCLabelTextFormatProtocol_h_

#include <vector>

#include "CCFontAtlas.h"
#include "CCGeometry.h"
#include "ccTypes.h"

NS_CC_BEGIN

class Sprite;

struct LetterInfo
{
    FontLetterDefinition def;

    Point position;
    Size  contentSize;
    bool  visible;
};

class CC_DLL LabelTextFormatProtocol
{
public:

    virtual ~LabelTextFormatProtocol() {}

    virtual bool recordLetterInfo(const Point& point,unsigned short int theChar, int spriteIndex) = 0;
    virtual bool recordPlaceholderInfo(int spriteIndex) = 0;
    virtual std::vector<LetterInfo>  *getLettersInfo() = 0;
    virtual float getLetterPosXLeft(int index)  const = 0;
    virtual float getLetterPosXRight(int index) const = 0;
    // sprite related stuff
    virtual Sprite *getLetter(int ID) = 0;
    
    // font related stuff
    virtual int getCommonLineHeight()  const = 0;
    virtual int getKerningForCharsPair(unsigned short first, unsigned short second) const = 0;
    virtual int getXOffsetForChar(unsigned short c) const = 0;
    virtual int getYOffsetForChar(unsigned short c) const = 0;
    virtual int getAdvanceForChar(unsigned short c, int hintPositionInString) const = 0;
    virtual Rect getRectForChar(unsigned short c) const = 0;
    
    // string related stuff
    virtual int getStringNumLines() const = 0;
    virtual int getStringLenght() const = 0;
    virtual unsigned short getCharAtStringPosition(int position) const = 0;
    virtual unsigned short * getUTF8String() const = 0;
    virtual void assignNewUTF8String(unsigned short *newString) = 0;
    virtual TextHAlignment getTextAlignment() const = 0;
    
    // label related stuff
    virtual float getMaxLineWidth() const = 0;
    virtual bool breakLineWithoutSpace() const = 0;
    virtual cocos2d::Size getLabelContentSize() const = 0;
    virtual void setLabelContentSize(const Size &newSize) = 0;
};

NS_CC_END

#endif 
