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

#include <vector>

#include "ccUTF8.h"
#include "CCLabelTextFormatter.h"
#include "CCDirector.h"
#include "CCLabel.h"

using namespace std;

NS_CC_BEGIN

bool LabelTextFormatter::multilineText(Label *theLabel)
{
    int strLen = theLabel->getStringLenght();
    auto strWhole = theLabel->getUTF16String();

    vector<unsigned short> multiline_string;
    multiline_string.reserve( strLen );

    vector<unsigned short> last_word;
    last_word.reserve( strLen );

    unsigned int line = 1;

    bool   isStartOfLine  = false, isStartOfWord = false;
    float  startOfLine = -1, startOfWord   = -1;

    int skip = 0;
    
    std::vector<LetterInfo>  *leterInfo = theLabel->getLettersInfo();
    int tIndex = 0;
    float scalsX = theLabel->getScaleX();
    float lineWidth = theLabel->getMaxLineWidth();
    bool breakLineWithoutSpace = theLabel->breakLineWithoutSpace();

    for (int j = 0; j+skip < strLen; j++)
    {            
        LetterInfo* info = &leterInfo->at(j+skip);

        unsigned int justSkipped = 0;

        while (info->def.validDefinition == false)
        {
            justSkipped++;
            tIndex = j+skip+justSkipped;
            if (strWhole[tIndex-1] == '\n')
            {
                cc_utf8_trim_ws(&last_word);

                last_word.push_back('\n');
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();
                isStartOfWord = false;
                isStartOfLine = false;
                startOfWord = -1;
                startOfLine = -1;
                ++line;
            }
            if(tIndex < strLen)
            {
                info = &leterInfo->at( tIndex );
            }
            else
                break;
        }
        skip += justSkipped;
        tIndex = j + skip;

        if (tIndex >= strLen)
            break;

        unsigned short character = strWhole[tIndex];

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

        // Whitespace.
        if (isspace_unicode(character))
        {
            last_word.push_back(character);
            multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
            last_word.clear();
            isStartOfWord = false;
            startOfWord = -1;
            continue;
        }

        float posRight = (info->position.x + info->contentSize.width) * scalsX;
        // Out of bounds.
        if (posRight - startOfLine > lineWidth)
        {
            if (!breakLineWithoutSpace)
            {
                last_word.push_back(character);

                int found = cc_utf8_find_last_not_char(multiline_string, ' ');
                if (found != -1)
                    cc_utf8_trim_ws(&multiline_string);
                else
                    multiline_string.clear();

                if (multiline_string.size() > 0)
                    multiline_string.push_back('\n');

                ++line;
                isStartOfLine = false;
                startOfLine = -1;
            }
            else
            {
                cc_utf8_trim_ws(&last_word);

                last_word.push_back('\n');
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();
                isStartOfWord = false;
                isStartOfLine = false;
                startOfWord = -1;
                startOfLine = -1;
                ++line;
                --j;
            }
        }
        else
        {
            // Character is normal.
            last_word.push_back(character);
        }
    }

    multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());

    size_t size = multiline_string.size();
    unsigned short* strNew = new unsigned short[size + 1];

    for (size_t j = 0; j < size; ++j)
    {
        strNew[j] = multiline_string[j];
    }

    strNew[size] = 0;
    theLabel->assignNewUTF16String(strNew);

    return true;
}

bool LabelTextFormatter::alignText(Label *theLabel)
{
    int i = 0;
    
    int lineNumber = 0;
    int strLen = cc_wcslen(theLabel->getUTF16String());
    vector<unsigned short> lastLine;
    std::vector<LetterInfo>  *leterInfo = theLabel->getLettersInfo();
    auto strWhole = theLabel->getUTF16String();

    for (int ctr = 0; ctr <= strLen; ++ctr)
    { 
        unsigned short currentChar = strWhole[ctr];

        if (currentChar == '\n' || currentChar == 0)
        {
            float lineWidth = 0.0f;
            size_t lineLength = lastLine.size();
            
            // if last line is empty we must just increase lineNumber and work with next line
            if (lineLength == 0)
            {
                lineNumber++;
                continue;
            }
            int index = static_cast<int>(i + lineLength - 1 + lineNumber);
            if (index < 0) continue;
            
            LetterInfo* info = &leterInfo->at( index );
            if(info->def.validDefinition == false)
                continue;
            lineWidth = info->position.x + info->contentSize.width;
            
            float shift = 0;
            switch (theLabel->getTextAlignment())
            {
                case TextHAlignment::CENTER:
                    shift = theLabel->getContentSize().width/2.0f - lineWidth/2.0f;
                    break;
                case TextHAlignment::RIGHT:
                    shift = theLabel->getContentSize().width - lineWidth;
                    break;
                default:
                    break;
            }
            
            if (shift != 0)
            {
                for (unsigned j = 0; j < lineLength; ++j)
                {
                    index = i + j + lineNumber;
                    if (index < 0) continue;
                    
                    info = &leterInfo->at( index );
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
    unsigned int stringLen = theLabel->getStringLenght();
    
    // no string
    if (stringLen == 0)
        return false;
    
    int nextFontPositionX       = 0;
    int nextFontPositionY       = 0;
    
    unsigned short prev         = -1;
    
    Size tmpSize                = Size::ZERO;
    
    int longestLine             = 0;
    unsigned int totalHeight    = 0;
    
    int quantityOfLines         = theLabel->getStringNumLines();
    int commonLineHeight        = theLabel->getCommonLineHeight();
    
    totalHeight                 = commonLineHeight * quantityOfLines;
    nextFontPositionY           = totalHeight;
    
    Rect charRect;
    int charXOffset = 0;
    int charYOffset = 0;
    int charAdvance = 0;

    auto strWhole = theLabel->getUTF16String();
    FontAtlas* fontAtlas = theLabel->getFontAtlas();
    FontLetterDefinition tempDefinition;
    auto kernings = theLabel->getKernings();
    
    for (unsigned int i = 0; i < stringLen; i++)
    {
        unsigned short c    = strWhole[i];
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
            nextFontPositionX  = 0;
            nextFontPositionY -= commonLineHeight;
            
            theLabel->recordPlaceholderInfo(i);
            continue;
        }
        
        Point fontPos = Point((float)nextFontPositionX + charXOffset + kernings[i],
            (float)nextFontPositionY - charYOffset);
               
        if( theLabel->recordLetterInfo(CC_POINT_PIXELS_TO_POINTS(fontPos),c,i) == false)
        {
            log("WARNING: can't find letter definition in font file for letter: %c", c);
            continue;
        }

        // update kerning
        nextFontPositionX += charAdvance + kernings[i];
        prev = c;
        
        if (longestLine < nextFontPositionX)
        {
            longestLine = nextFontPositionX;
        }
    }
    
    float lastCharWidth = tempDefinition.width * CC_CONTENT_SCALE_FACTOR();
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
    theLabel->setContentSize(CC_SIZE_PIXELS_TO_POINTS(tmpSize));
    return true;
}

NS_CC_END