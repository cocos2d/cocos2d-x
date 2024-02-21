/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "Utils.h"

#if CC_PLATFORM == CC_PLATFORM_IOS || CC_PLATFORM == CC_PLATFORM_MACOS
    #include <sys/time.h>
#endif

#include <cmath>
#include <cstdlib>
#include <cstring>

#define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED


namespace cocos2d { namespace experimental {
namespace utils {

#define MAX_ITOA_BUFFER_SIZE 256
double atof(const char *str) {
    if (str == nullptr) {
        return 0.0;
    }

    char buf[MAX_ITOA_BUFFER_SIZE];
    strncpy(buf, str, MAX_ITOA_BUFFER_SIZE);

    // strip string, only remain 7 numbers after '.'
    char *dot = strchr(buf, '.');
    if (dot != nullptr && dot - buf + 8 < MAX_ITOA_BUFFER_SIZE) {
        dot[8] = '\0';
    }

    return ::atof(buf);
}

uint32_t nextPOT(uint32_t x) {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
}

// painfully slow to execute, use with caution
std::string getStacktrace(uint32_t skip, uint32_t maxDepth) {
    return "not support for 2dx";
}

} // namespace utils

#if USE_MEMORY_LEAK_DETECTOR

    // Make sure GMemoryHook to be initialized first.
    #if (CC_COMPILER == CC_COMPILER_MSVC)
        #pragma warning(push)
        #pragma warning(disable : 4073)
        #pragma init_seg(lib)
MemoryHook GMemoryHook;
        #pragma warning(pop)
    #elif (CC_COMPILER == CC_COMPILER_GNUC || CC_COMPILER == CC_COMPILER_CLANG)
MemoryHook GMemoryHook __attribute__((init_priority(101)));
    #endif

#endif
}} // namespace cc
