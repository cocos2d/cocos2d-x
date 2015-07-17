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

    bool lineIsEmpty = true;
    bool calculateLineStart = false;
    float startOfLine = 0.f;

    int skip = 0;  
    int tIndex = 0;
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

                calculateLineStart = false;
                startOfLine = 0.f;
                lineIsEmpty = true;
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

        if (calculateLineStart)
        {
            startOfLine = info->position.x - info->def.offsetX - theLabel->_horizontalKernings[tIndex];
            calculateLineStart = false;
            lineIsEmpty = true;
        }

        auto character = strWhole[tIndex];     
        if (breakLineWithoutSpace)
        {
            float posRight = info->position.x + info->contentSize.width;
            if (posRight - startOfLine > lineWidth)
            {
                //issue #8492:endless loop if not using system font, and constrained length is less than one character width
                if (last_word.empty())
                    last_word.push_back(character);
                else
                    --j;

                last_word.push_back('\n');
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();

                startOfLine += lineWidth;
            }
            else
            {
                last_word.push_back(character);
            }
        }
        //Break line with space.
        else
        {
            std::vector<char16_t> nonCJKword;
            int wordIndex = tIndex;
            for (; wordIndex < limit; ++wordIndex)
            {
                auto ch = strWhole[wordIndex];
                if (ch == '\n' || StringUtils::isUnicodeSpace(ch) || StringUtils::isCJKUnicode(ch))
                {
                    break;
                }
                
                nonCJKword.push_back(ch);
            }

            if (!nonCJKword.empty())
            {
                auto wordLenth = nonCJKword.size();
                auto lastCharacterInfo = &theLabel->_lettersInfo.at(tIndex + wordLenth - 1);

                float posRight = lastCharacterInfo->position.x + lastCharacterInfo->contentSize.width;
                if (posRight - startOfLine > lineWidth)
                {
                    if (last_word.empty())
                    {
                        nonCJKword.push_back('\n');
                        multiline_string.insert(multiline_string.end(), nonCJKword.begin(), nonCJKword.end());

                        calculateLineStart = true;
                    }
                    else
                    {
                        last_word.push_back('\n');
                        multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                        last_word.clear();

                        startOfLine = info->position.x - info->def.offsetX - theLabel->_horizontalKernings[tIndex];
                        if (posRight - startOfLine > lineWidth)
                        {
                            nonCJKword.push_back('\n');
                            multiline_string.insert(multiline_string.end(), nonCJKword.begin(), nonCJKword.end());
                            calculateLineStart = true;
                        } 
                        else
                        {
                            multiline_string.insert(multiline_string.end(), nonCJKword.begin(), nonCJKword.end());
                            lineIsEmpty = false;
                            calculateLineStart = false;
                        }
                    }
                } 
                else
                {
                    multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                    last_word.clear();

                    multiline_string.insert(multiline_string.end(), nonCJKword.begin(), nonCJKword.end());
                    lineIsEmpty = false;
                }

                j += wordLenth - 1;
                continue;
            }          

            float posRight = info->position.x + info->contentSize.width;
            if (posRight - startOfLine > lineWidth)
            {
                //issue #8492:endless loop if not using system font, and constrained length is less than one character width
                if (lineIsEmpty && last_word.empty())
                    last_word.push_back(character);
                else
                    --j;

                last_word.push_back('\n');
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();

                calculateLineStart = true;
            }
            else
            {
                last_word.push_back(character);
            }
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
    theLabel->_limitShowCount = 0;
    // check for string
    int stringLen = theLabel->getStringLength();
    if (stringLen <= 0)
        return false;
    
    auto totalHeight = theLabel->_commonLineHeight * theLabel->_currNumLines;
    auto longestLine = 0.0f;
    auto nextFontPositionX = 0.0f;
    auto nextFontPositionY = totalHeight;
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
    
    int charXOffset = 0;
    int charYOffset = 0;
    int charAdvance = 0;

    auto strWhole = theLabel->_currentUTF16String;
    auto fontAtlas = theLabel->_fontAtlas;
    FontLetterDefinition tempDefinition;
    Vec2 letterPosition;
    const auto& kernings = theLabel->_horizontalKernings;
    CCASSERT(kernings, "kernings must's be nullptr!!!");

    float clipTop = 0;
    float clipBottom = 0;
    int lineIndex = 0;
    bool lineStart = true;
    bool clipBlank = false;
    if (theLabel->_currentLabelType == Label::LabelType::TTF && theLabel->_clipEnabled)
    {
        clipBlank = true;
    }
    
    for (int i = 0; i < stringLen; i++)
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
            if (nextFontPositionY < theLabel->_commonLineHeight)
                break;

            lineStart = true;
            continue;     
        }
        else if (clipBlank && tempDefinition.height > 0.0f)
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
        
        letterPosition.x = (nextFontPositionX + charXOffset) / contentScaleFactor;
        letterPosition.y = (nextFontPositionY - charYOffset) / contentScaleFactor;
               
        if( theLabel->recordLetterInfo(letterPosition, tempDefinition, i) == false)
        {
            log("WARNING: can't find letter definition in font file for letter: %c", c);
            continue;
        }
        
        nextFontPositionX += charAdvance + theLabel->_additionalKerning;
        if (i < stringLen - 1)
        {
            nextFontPositionX += kernings[i + 1];
        }
        
        auto letterRight = letterPosition.x + tempDefinition.width;
        if (longestLine < letterRight)
        {
            longestLine = letterRight;
        }
    }
    
    Size tmpSize(longestLine * contentScaleFactor, totalHeight);
    if (theLabel->_labelHeight > 0)
    {
        tmpSize.height = theLabel->_labelHeight * contentScaleFactor;
    }

    if (clipBlank)
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
