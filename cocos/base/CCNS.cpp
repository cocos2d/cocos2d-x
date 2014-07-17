/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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
#include "base/CCNS.h"
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>

#include "base/ccUtils.h"

using namespace std;

NS_CC_BEGIN

typedef std::vector<std::string> strArray;

// string toolkit
static inline void split(const std::string& src, const std::string& token, strArray& vect)
{
    size_t nend = 0;
    size_t nbegin = 0;
    size_t tokenSize = token.size();
    while(nend != std::string::npos)
    {
        nend = src.find(token, nbegin);
        if(nend == std::string::npos)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + tokenSize;
    }
}

// first, judge whether the form of the string like this: {x,y}
// if the form is right,the string will be split into the parameter strs;
// or the parameter strs will be empty.
// if the form is right return true,else return false.
static bool splitWithForm(const std::string& content, strArray& strs)
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(content.empty());

        size_t nPosLeft  = content.find('{');
        size_t nPosRight = content.find('}');

        // don't have '{' and '}'
        CC_BREAK_IF(nPosLeft == std::string::npos || nPosRight == std::string::npos);
        // '}' is before '{'
        CC_BREAK_IF(nPosLeft > nPosRight);

        const std::string pointStr = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        // nothing between '{' and '}'
        CC_BREAK_IF(pointStr.length() == 0);

        size_t nPos1 = pointStr.find('{');
        size_t nPos2 = pointStr.find('}');
        // contain '{' or '}' 
        CC_BREAK_IF(nPos1 != std::string::npos || nPos2 != std::string::npos);

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

Rect RectFromString(const std::string& str)
{
    Rect result = Rect::ZERO;

    do 
    {
        CC_BREAK_IF(str.empty());
        std::string content = str;

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
        const std::string pointStr = content.substr(0, nPointEnd);
        const std::string sizeStr  = content.substr(nPointEnd + 1, content.length() - nPointEnd);

        // split the string with ','
        strArray pointInfo;
        CC_BREAK_IF(!splitWithForm(pointStr.c_str(), pointInfo));
        strArray sizeInfo;
        CC_BREAK_IF(!splitWithForm(sizeStr.c_str(), sizeInfo));

        float x = (float) utils::atof(pointInfo[0].c_str());
        float y = (float) utils::atof(pointInfo[1].c_str());
        float width  = (float) utils::atof(sizeInfo[0].c_str());
        float height = (float) utils::atof(sizeInfo[1].c_str());

        result = Rect(x, y, width, height);
    } while (0);

    return result;
}

Vec2 PointFromString(const std::string& str)
{
    Vec2 ret = Vec2::ZERO;

    do 
    {
        strArray strs;
        CC_BREAK_IF(!splitWithForm(str, strs));

        float x = (float) utils::atof(strs[0].c_str());
        float y = (float) utils::atof(strs[1].c_str());

        ret = Vec2(x, y);
    } while (0);

    return ret;
}

Size SizeFromString(const std::string& pszContent)
{
    Size ret = Size::ZERO;

    do 
    {
        strArray strs;
        CC_BREAK_IF(!splitWithForm(pszContent, strs));

        float width  = (float) utils::atof(strs[0].c_str());
        float height = (float) utils::atof(strs[1].c_str());

        ret = Size(width, height);
    } while (0);

    return ret;
}

NS_CC_END
