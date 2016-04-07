/****************************************************************************
 Copyright (c) 2016 Yuki Kuwabara <do_low@hotmail.com>
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

#ifndef TapRecorder_Util_h
#define TapRecorder_Util_h

#include <string>
#include <sstream>
#include <istream>
#include <vector>
#include "extensions/ExtensionMacros.h"

NS_CC_EXT_BEGIN

namespace TapRecorder { namespace Util {

/**
 * Android NDK does not support std::to_string by default.
 */
template <typename N=int> static inline std::string to_string(N number)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::stringstream ss;
    ss << number;
    
    return ss.str();
#else
    return std::to_string(number);
#endif
}

static inline std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::vector<std::string> strs;
    std::stringstream ss(str);
    std::string item;
    
    while (std::getline(ss, item, delimiter)) {
        strs.push_back(item);
    }
    return strs;
}

#endif /* TapRecorder_Util_h */

}}

NS_CC_EXT_END