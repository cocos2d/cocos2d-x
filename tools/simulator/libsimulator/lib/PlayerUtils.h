
#ifndef __PLAYER_UTILS_H_
#define __PLAYER_UTILS_H_

#include "PlayerMacros.h"

#include <string>
#include <vector>

using namespace std;

PLAYER_NS_BEGIN

template<class T>
vector<T> splitString(T str, T pattern)
{
    vector<T> result;
    str += pattern;
    size_t size = str.size();

    for (size_t i = 0; i < size; i++)
    {
        size_t pos = str.find(pattern, i);
        if (pos < size)
        {
            T s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
};

PLAYER_NS_END

#endif // __PLAYER_UTILS_H_
