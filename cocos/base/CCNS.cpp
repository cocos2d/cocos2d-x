/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCNS.h"
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

NS_CC_BEGIN

typedef std::vector<std::string> strArray;

// string toolkit
static inline void split(std::string src, const char* token, strArray& vect)
{
    long nend=0;
    long nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + strlen(token);
    }
}

// first, judge whether the form of the string like this: {x,y}
// if the form is right,the string will be split into the parameter strs;
// or the parameter strs will be empty.
// if the form is right return true,else return false.
static bool splitWithForm(const char* pStr, strArray& strs)
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(!pStr);

        // string is empty
        std::string content = pStr;
        CC_BREAK_IF(content.length() == 0);

        size_t posLeft  = content.find('{');
        size_t posRight = content.find('}');

        // don't have '{' and '}'
        CC_BREAK_IF(posLeft == std::string::npos || posRight == std::string::npos);
        // '}' is before '{'
        CC_BREAK_IF(posLeft > posRight);

        std::string pointStr = content.substr(posLeft + 1, posRight - posLeft - 1);
        // nothing between '{' and '}'
        CC_BREAK_IF(pointStr.length() == 0);

        size_t pos1 = pointStr.find('{');
        size_t pos2 = pointStr.find('}');
        // contain '{' or '}' 
        CC_BREAK_IF(pos1 != std::string::npos || pos2 != std::string::npos);

        split(pointStr, ",", strs);
        if (strs.size() != 2 || strs[0].length() == 0 || strs[1].length() == 0)
        {
            strs.clear();
            break;
        }

        bRet = true;
    } while (0);

    return bRet;
}

// implement the functions

Rect RectFromString(const char* pszContent)
{
    Rect result = Rect::ZERO;

    do 
    {
        CC_BREAK_IF(!pszContent);
        std::string content = pszContent;

        // find the first '{' and the third '}'
        size_t nPosLeft  = content.find('{');
        size_t nPosRight = content.find('}');
        for (int i = 1; i < 3; ++i)
        {
            if (nPosRight == std::string::npos)
            {
                break;
            }
            nPosRight = content.find('}', nPosRight + 1);
        }
        CC_BREAK_IF(nPosLeft == std::string::npos || nPosRight == std::string::npos);

        content = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        size_t nPointEnd = content.find('}');
        CC_BREAK_IF(nPointEnd == std::string::npos);
        nPointEnd = content.find(',', nPointEnd);
        CC_BREAK_IF(nPointEnd == std::string::npos);

        // get the point string and size string
        std::string pointStr = content.substr(0, nPointEnd);
        std::string sizeStr  = content.substr(nPointEnd + 1, content.length() - nPointEnd);

        // split the string with ','
        strArray pointInfo;
        CC_BREAK_IF(!splitWithForm(pointStr.c_str(), pointInfo));
        strArray sizeInfo;
        CC_BREAK_IF(!splitWithForm(sizeStr.c_str(), sizeInfo));

        float x = (float) atof(pointInfo[0].c_str());
        float y = (float) atof(pointInfo[1].c_str());
        float width  = (float) atof(sizeInfo[0].c_str());
        float height = (float) atof(sizeInfo[1].c_str());

        result = Rect(x, y, width, height);
    } while (0);

    return result;
}

Point PointFromString(const char* pszContent)
{
    Point ret = Point::ZERO;

    do 
    {
        strArray strs;
        CC_BREAK_IF(!splitWithForm(pszContent, strs));

        float x = (float) atof(strs[0].c_str());
        float y = (float) atof(strs[1].c_str());

        ret = Point(x, y);
    } while (0);

    return ret;
}

Size SizeFromString(const char* pszContent)
{
    Size ret = Size::ZERO;

    do 
    {
        strArray strs;
        CC_BREAK_IF(!splitWithForm(pszContent, strs));

        float width  = (float) atof(strs[0].c_str());
        float height = (float) atof(strs[1].c_str());

        ret = Size(width, height);
    } while (0);

    return ret;
}

NS_CC_END
