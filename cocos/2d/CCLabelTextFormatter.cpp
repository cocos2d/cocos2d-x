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

#include "2d/CCLabelTextFormatter.h"

#include <vector>

#include "base/ccUTF8.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"

NS_CC_BEGIN

bool LabelTextFormatter::multilineText(Label *theLabel)
{
    auto limit = theLabel->_limitShowCount;
    auto strWhole = theLabel->_currentUTF16String;

    std::vector<char16_t> multiline_string;
    multiline_string.reserve( limit );

    std::vector<char16_t> last_word;
    last_word.reserve( 25 );

    bool   isStartOfLine  = false, isStartOfWord = false;
    float  startOfLine = -1, startOfWord   = -1;

    int skip = 0;
    
    int tIndex = 0;
    float scalsX = theLabel->getScaleX();
    float lineWidth = theLabel->_maxLineWidth;
    bool breakLineWithoutSpace = theLabel->_lineBreakWithoutSpaces;
    Label::LetterInfo* info = nullptr;

    for (int j = 0; j+skip < limit; j++)
    {            
        info = & theLabel->_lettersInfo.at(j+skip);

        unsigned int justSkipped = 0;

        while (info->def.validDefinition == false)
        {
            justSkipped++;
            tIndex = j+skip+justSkipped;
            if (strWhole[tIndex-1] == '\n')
            {
                StringUtils::trimUTF16Vector(last_word);

                last_word.push_back('\n');
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();
                isStartOfWord = false;
                isStartOfLine = false;
                startOfWord = -1;
                startOfLine = -1;
            }
            if(tIndex < limit)
            {
                info = & theLabel->_lettersInfo.at( tIndex );
            }
            else
                break;
        }
        skip += justSkipped;
        tIndex = j + skip;

        if (tIndex >= limit)
            break;

        char16_t character = strWhole[tIndex];

        if (!isStartOfWord)
        {
            startOfWord = info->position.x * scalsX;
            isStartOfWord = true;
        }

        if (!isStartOfLine)
        {
            startOfLine = startOfWord;
            isStartOfLine  = true;
        }
        
        // 1) Whitespace.
        // 2) This character is non-CJK, but the last character is CJK
        bool isspace = StringUtils::isUnicodeSpace(character);
        bool isCJK = false;
        if(!isspace)
        {
            isCJK = StringUtils::isCJKUnicode(character);
        }

        if (isspace ||
            (!last_word.empty() && StringUtils::isCJKUnicode(last_word.back()) && !isCJK))
        {
            // if current character is white space, put it into the current word
            if (isspace) last_word.push_back(character);
            multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
            last_word.clear();
            isStartOfWord = false;
            startOfWord = -1;
            // put the CJK character in the last word
            // and put the non-CJK(ASCII) character in the current word
            if (!isspace) last_word.push_back(character);
            continue;
        }
        
        float posRight = (info->position.x + info->contentSize.width) * scalsX;
        // Out of bounds.
        if (posRight - startOfLine > lineWidth)
        {
            if (!breakLineWithoutSpace && !isCJK)
            {
                last_word.push_back(character);
                
                int found = StringUtils::getIndexOfLastNotChar16(multiline_string, ' ');
                if (found != -1)
                    StringUtils::trimUTF16Vector(multiline_string);
                else
                    multiline_string.clear();

                if (multiline_string.size() > 0)
                    multiline_string.push_back('\n');

                isStartOfLine = false;
                startOfLine = -1;
            }
            else
            {
                StringUtils::trimUTF16Vector(last_word);
                //issue #8492:endless loop if not using system font, and constrained length is less than one character width
                if (isStartOfLine && last_word.size() == 0)
                    last_word.push_back(character);
                else
                    --j;

                last_word.push_back('\n');
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();
                
                isStartOfWord = false;
                isStartOfLine = false;
                startOfWord = -1;
                startOfLine = -1;
            }
        }
        else
        {
            // Character is normal.
            last_word.push_back(character);
        }
    }

    multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());

    std::u16string strNew(multiline_string.begin(), multiline_string.end());
    
    theLabel->_currentUTF16String = strNew;
    theLabel->computeStringNumLines();
    theLabel->computeHorizontalKernings(theLabel->_currentUTF16String);

    return true;
}

bool LabelTextFormatter::alignText(Label *theLabel)
{
    int i = 0;
    
    int lineNumber = 0;
    int strLen = theLabel->_limitShowCount;
    std::vector<char16_t> lastLine;
    auto strWhole = theLabel->_currentUTF16String;

    if (theLabel->_labelWidth > theLabel->_contentSize.width)
    {
        theLabel->setContentSize(Size(theLabel->_labelWidth,theLabel->_contentSize.height));
    }

    for (int ctr = 0; ctr <= strLen; ++ctr)
    { 
        char16_t currentChar = strWhole[ctr];

        if (currentChar == '\n' || currentChar == 0)
        {
            auto lineLength = lastLine.size();
            
            // if last line is empty we must just increase lineNumber and work with next line
            if (lineLength == 0)
            {
                lineNumber++;
                continue;
            }
            int index = static_cast<int>(i + lineLength - 1 + lineNumber);
            if (index < 0) continue;
            
            auto info = & theLabel->_lettersInfo.at( index );
            if(info->def.validDefinition == false)
                continue;
            
            float shift = 0;
            switch (theLabel->_hAlignment)
            {
                case TextHAlignment::CENTER:
                    {
                        float lineWidth = info->position.x + info->contentSize.width;
                        shift = theLabel->_contentSize.width/2.0f - lineWidth/2.0f;
                        break;
                    }
                case TextHAlignment::RIGHT:
                    {
                        float lineWidth = info->position.x + info->contentSize.width;
                        shift = theLabel->_contentSize.width - lineWidth;
                        break;
                    }
                default:
                    break;
            }
            
            if (shift != 0)
            {
                for (unsigned j = 0; j < lineLength; ++j)
                {
                    index = i + j + lineNumber;
                    if (index < 0) continue;
                    
                    info = & theLabel->_lettersInfo.at( index );
                    if(info)
                    {
                        info->position.x += shift;
                    }
                }
            }
            
            i += lineLength;
            ++lineNumber;
            
            lastLine.clear();
            continue;
        }
        
        lastLine.push_back(currentChar);
    }
    
    return true;
}

bool LabelTextFormatter::createStringSprites(Label *theLabel)
{
    // check for string
    unsigned int stringLen = theLabel->getStringLength();
    theLabel->_limitShowCount = 0;

    // no string
    if (stringLen == 0)
        return false;
    
    int longestLine             = 0;
    unsigned int totalHeight    = theLabel->_commonLineHeight * theLabel->_currNumLines;
    int nextFontPositionX       = 0;
    int nextFontPositionY       = totalHeight;
    auto contentScaleFactor = CC_CONTENT_SCALE_FACTOR();

    if (theLabel->_labelHeight > 0)
    {
        auto labelHeightPixel = theLabel->_labelHeight * contentScaleFactor;
        if (totalHeight > labelHeightPixel)
        {
            int numLines = labelHeightPixel / theLabel->_commonLineHeight;
            totalHeight = numLines * theLabel->_commonLineHeight;
        }
        switch (theLabel->_vAlignment)
        {
        case TextVAlignment::TOP:
            nextFontPositionY = labelHeightPixel;
            break;
        case TextVAlignment::CENTER:
            nextFontPositionY = (labelHeightPixel + totalHeight) / 2.0f;
            break;
        case TextVAlignment::BOTTOM:
            nextFontPositionY = totalHeight;
            break;
        default:
            break;
        }
    }
    
    Rect charRect;
    int charXOffset = 0;
    int charYOffset = 0;
    int charAdvance = 0;

    auto strWhole = theLabel->_currentUTF16String;
    auto fontAtlas = theLabel->_fontAtlas;
    FontLetterDefinition tempDefinition;
    Vec2 letterPosition;
    const auto& kernings = theLabel->_horizontalKernings;

    float clipTop = 0;
    float clipBottom = 0;
    int lineIndex = 0;
    bool lineStart = true;
    bool clip = false;
    if (theLabel->_currentLabelType == Label::LabelType::TTF && theLabel->_clipEnabled)
    {
        clip = true;
    }
    
    for (unsigned int i = 0; i < stringLen; i++)
    {
        char16_t c    = strWhole[i];
        if (fontAtlas->getLetterDefinitionForChar(c, tempDefinition))
        {
            charXOffset         = tempDefinition.offsetX;
            charYOffset         = tempDefinition.offsetY;
            charAdvance         = tempDefinition.xAdvance;
        }
        else
        {
            charXOffset         = -1;
            charYOffset         = -1;
            charAdvance         = -1;
        }

        if (c == '\n')
        {
            lineIndex++;
            nextFontPositionX  = 0;
            nextFontPositionY -= theLabel->_commonLineHeight;
            
            theLabel->recordPlaceholderInfo(i);
            if(nextFontPositionY < theLabel->_commonLineHeight)
                break;

            lineStart = true;
            continue;     
        }
        else if (clip && tempDefinition.height > 0.0f)
        {
            if (lineStart)
            {
                if (lineIndex == 0)
                {
                    clipTop = charYOffset;
                }
                lineStart = false;
                clipBottom = tempDefinition.clipBottom;
            }
            else if(tempDefinition.clipBottom < clipBottom)
            {
                clipBottom = tempDefinition.clipBottom;
            }

            if (lineIndex == 0 && charYOffset < clipTop)
            {
                clipTop = charYOffset;
            }
        }
        
        letterPosition.x = (nextFontPositionX + charXOffset + kernings[i]) / contentScaleFactor;
        letterPosition.y = (nextFontPositionY - charYOffset) / contentScaleFactor;
               
        if( theLabel->recordLetterInfo(letterPosition,tempDefinition,i) == false)
        {
            log("WARNING: can't find letter definition in font file for letter: %c", c);
            continue;
        }

        nextFontPositionX += charAdvance + kernings[i] + theLabel->_additionalKerning;
        
        if (longestLine < nextFontPositionX)
        {
            longestLine = nextFontPositionX;
        }
    }
    
    float lastCharWidth = tempDefinition.width * contentScaleFactor;
    Size tmpSize;
    // If the last character processed has an xAdvance which is less that the width of the characters image, then we need
    // to adjust the width of the string to take this into account, or the character will overlap the end of the bounding
    // box
    if(charAdvance < lastCharWidth)
    {
        tmpSize.width = longestLine - charAdvance + lastCharWidth;
    }
    else
    {
        tmpSize.width = longestLine;
    }
    
    tmpSize.height = totalHeight;
    
    if (theLabel->_labelHeight > 0)
    {
        tmpSize.height = theLabel->_labelHeight * contentScaleFactor;
    }

    if (clip)
    {
        int clipTotal = (clipTop + clipBottom) / contentScaleFactor;
        tmpSize.height -= clipTotal * contentScaleFactor;
        clipBottom /= contentScaleFactor;

        for (int i = 0; i < theLabel->_limitShowCount; i++)
        {
            theLabel->_lettersInfo[i].position.y -= clipBottom;
        }
    }
    
    theLabel->setContentSize(CC_SIZE_PIXELS_TO_POINTS(tmpSize));

    return true;
}

NS_CC_END
