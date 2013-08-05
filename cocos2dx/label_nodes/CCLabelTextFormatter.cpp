/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 
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

#include "cocos2d.h"
#include "support/ccUTF8.h"
#include "CCLabelTextFormatter.h"

using namespace std;

NS_CC_BEGIN

bool LabelTextFormatter::multilineText(LabelTextFormatProtocol *theLabel)
{
    // to do if (m_fWidth > 0)
    if (theLabel->getMaxLineWidth())
    {
        // Step 1: Make multiline
        vector<unsigned short> strWhole = cc_utf16_vec_from_utf16_str(theLabel->getUTF8String());
        unsigned int stringLength        = strWhole.size();
        
        vector<unsigned short> multiline_string;
        multiline_string.reserve( stringLength );
        
        vector<unsigned short> last_word;
        last_word.reserve( stringLength );
        
        unsigned int line = 1, i = 0;
        
        bool   start_line  = false, start_word = false;
        float  startOfLine = -1, startOfWord   = -1;
        
        int skip = 0;
        
        Array* children = theLabel->getChildrenLetters();
        
        for (unsigned int j = 0; j < children->count(); j++)
        {
            Sprite* characterSprite;
            unsigned int justSkipped = 0;
            
            while (!(characterSprite = theLabel->getSpriteChild(j + skip + justSkipped)))
            {
                justSkipped++;
            }
            
            skip += justSkipped;
            
            if (!characterSprite->isVisible())
                continue;
            
            if (i >= stringLength)
                break;
            
            unsigned short character = strWhole[i];
            
            if (!start_word)
            {
                startOfWord = theLabel->getLetterPosXLeft( characterSprite );
                start_word = true;
            }
            
            if (!start_line)
            {
                startOfLine = startOfWord;
                start_line  = true;
            }
            
            // Newline.
            if (character == '\n')
            {
                cc_utf8_trim_ws(&last_word);
                
                last_word.push_back('\n');
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();
                start_word = false;
                start_line = false;
                startOfWord = -1;
                startOfLine = -1;
                i+=justSkipped;
                line++;
                
                if (i >= stringLength)
                    break;
                
                character = strWhole[i];
                
                if (!startOfWord)
                {
                    startOfWord = theLabel->getLetterPosXLeft( characterSprite );
                    start_word = true;
                }
                if (!startOfLine)
                {
                    startOfLine  = startOfWord;
                    start_line = true;
                }
            }
            
            // Whitespace.
            if (isspace_unicode(character))
            {
                last_word.push_back(character);
                multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                last_word.clear();
                start_word = false;
                startOfWord = -1;
                i++;
                continue;
            }
            
            // Out of bounds.
            if ( theLabel->getLetterPosXRight( characterSprite ) - startOfLine > theLabel->getMaxLineWidth() )
            {
                if (!theLabel->breakLineWithoutSpace())
                {
                    last_word.push_back(character);
                    
                    int found = cc_utf8_find_last_not_char(multiline_string, ' ');
                    if (found != -1)
                        cc_utf8_trim_ws(&multiline_string);
                    else
                        multiline_string.clear();
                    
                    if (multiline_string.size() > 0)
                        multiline_string.push_back('\n');
                    
                    line++;
                    start_line = false;
                    startOfLine = -1;
                    i++;
                }
                else
                {
                    cc_utf8_trim_ws(&last_word);
                    
                    last_word.push_back('\n');
                    multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
                    last_word.clear();
                    start_word = false;
                    start_line = false;
                    startOfWord = -1;
                    startOfLine = -1;
                    line++;
                    
                    if (i >= stringLength)
                        break;
                    
                    if (!startOfWord)
                    {
                        startOfWord = theLabel->getLetterPosXLeft( characterSprite );
                        start_word = true;
                    }
                    if (!startOfLine)
                    {
                        startOfLine  = startOfWord;
                        start_line = true;
                    }
                    
                    j--;
                }
                
                continue;
            }
            else
            {
                // Character is normal.
                last_word.push_back(character);
                i++;
                continue;
            }
        }
        
        multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());
        
        int size = multiline_string.size();
        unsigned short* str_new = new unsigned short[size + 1];
        
        for (int i = 0; i < size; ++i)
        {
            str_new[i] = multiline_string[i];
        }
        
        str_new[size] = 0;
        theLabel->assignNewUTF8String(str_new);
        
        return true;
    }
    else
    {
        return false;
    }
}

bool LabelTextFormatter::alignText(LabelTextFormatProtocol *theLabel)
{
    int i = 0;
    
    int lineNumber = 0;
    int str_len = cc_wcslen(theLabel->getUTF8String());
    vector<unsigned short> last_line;
    for (int ctr = 0; ctr <= str_len; ++ctr)
    {
        unsigned char currentChar = theLabel->getCharAtStringPosition(ctr);
        
        if (currentChar == '\n' || currentChar == 0)
        {
            float lineWidth = 0.0f;
            unsigned int line_length = last_line.size();
            
            // if last line is empty we must just increase lineNumber and work with next line
            if (line_length == 0)
            {
                lineNumber++;
                continue;
            }
            int index = i + line_length - 1 + lineNumber;
            if (index < 0) continue;
            
            Sprite* lastChar = theLabel->getSpriteChild(index);
            if ( lastChar == NULL )
                continue;
            
            lineWidth = lastChar->getPosition().x + lastChar->getContentSize().width / 2.0f;
            
            float shift = 0;
            switch (theLabel->getTextAlignment())
            {
                case TextHAlignment::CENTER:
                    shift = theLabel->getLabelContentSize().width/2.0f - lineWidth/2.0f;
                    break;
                case TextHAlignment::RIGHT:
                    shift = theLabel->getLabelContentSize().width - lineWidth;
                    break;
                default:
                    break;
            }
            
            if (shift != 0)
            {
                for (unsigned j = 0; j < line_length; j++)
                {
                    index = i + j + lineNumber;
                    if (index < 0) continue;
                    
                    Sprite* characterSprite = theLabel->getSpriteChild(index);
                    
                    if (characterSprite)
                        characterSprite->setPosition( characterSprite->getPosition() + Point(shift, 0.0f));
                }
            }
            
            i += line_length;
            lineNumber++;
            
            last_line.clear();
            continue;
        }
        
        last_line.push_back(currentChar);
    }
    
    return true;
}

bool LabelTextFormatter::createStringSprites(LabelTextFormatProtocol *theLabel)
{
    // check for string
    unsigned int stringLen = theLabel->getStringLenght();
    
    // no string
    if (stringLen == 0)
        return false;
    
    int nextFontPositionX       = 0;
    int nextFontPositionY       = 0;
    
    unsigned short prev         = -1;
    
    
    Size tmpSize              = Size::ZERO;
    
    int longestLine             = 0;
    unsigned int totalHeight    = 0;
    
    
    int quantityOfLines         = theLabel->getStringNumLines();
    int commonLineHeight        = theLabel->getCommonLineHeight();
    
    totalHeight                 =     commonLineHeight * quantityOfLines;
    nextFontPositionY           = 0 - ( commonLineHeight - totalHeight );
    
    Rect      rect;

    Rect charRect;
    int charXOffset = 0;
    int charYOffset = 0;
    int charAdvance = 0;
    
    for (unsigned int i = 0; i < stringLen; i++)
    {
        // get the current character
        unsigned short c    = theLabel->getCharAtStringPosition(i);
        
        charXOffset         = theLabel->getXOffsetForChar(c);
        charYOffset         = theLabel->getYOffsetForChar(c);
        charAdvance         = theLabel->getAdvanceForChar(c, i);
        charRect            = theLabel->getRectForChar(c);
        
        int kerningAmount   = theLabel->getKerningForCharsPair(prev, c);
        
        if (c == '\n')
        {
            nextFontPositionX  = 0;
            nextFontPositionY -= commonLineHeight;
            continue;
        }
        
        // get the sprite to this letter
        Sprite *pLetterSprite = theLabel->getSpriteForChar(c, i);
        
        if (!pLetterSprite)
        {
            log("WARNING: can't find letter definition in font file for letter: %c", c);
            continue;
        }
        
        // See issue 1343. cast( signed short + unsigned integer ) == unsigned integer (sign is lost!)
        int yOffset = commonLineHeight - charYOffset;
        
        
        Point fontPos = Point( (float)nextFontPositionX + charXOffset +   charRect.size.width  *  0.5f + kerningAmount,
                             (float)nextFontPositionY + yOffset     -   charRect.size.height *  0.5f );
        
        // set the sprite position
        pLetterSprite->setPosition(CC_POINT_PIXELS_TO_POINTS(fontPos));
        
        // update kerning
        nextFontPositionX += charAdvance + kerningAmount;
        prev = c;
        
        if (longestLine < nextFontPositionX)
        {
            longestLine = nextFontPositionX;
        }
    }
    
    // If the last character processed has an xAdvance which is less that the width of the characters image, then we need
    // to adjust the width of the string to take this into account, or the character will overlap the end of the bounding
    // box
    if (charAdvance < charRect.size.width)
    {
        tmpSize.width = longestLine + charRect.size.width - charAdvance;
    }
    else
    {
        tmpSize.width = longestLine;
    }
    
    tmpSize.height = totalHeight;
    theLabel->setLabelContentSize(CC_SIZE_PIXELS_TO_POINTS(tmpSize));    
    return true;
}

NS_CC_END