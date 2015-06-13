/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __ccRandom_H_
#define __ccRandom_H_

#include <random>
#include <cstdlib>

#include "platform/CCPlatformMacros.h"

/**
* @addtogroup base
* @{
*/
NS_CC_BEGIN


/**
 * @class RandomHelper
 * @brief @~english A helper class for creating random number.
 * @~chinese 用于生成随机数的工具类。
 */
class CC_DLL RandomHelper {
public:
    /**
     * @brief @~english The templat method for random real numbers.
     * @~chinese 用于获取随机实数的模板函数。
     * @param min @~english The minimum value of the random value.
     * @~chinese 随机数的最小值。
     * @param max @~english The maximum value of the random value.
     * @~chinese 随机数的最大值。
     * @return @~english The random real value between min & max. 
     * @~chinese 介于 min 和 max 之间的随机实数。
     */
    template<typename T>
    static inline T random_real(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        auto &mt = RandomHelper::getEngine();
        return dist(mt);
    }

    /**
     * @brief @~english The templat method for random integer numbers.
     * @~chinese 用于获取随机整数的模板函数。
     * @param min @~english The minimum value of the random value.
     * @~chinese 随机数的最小值。
     * @param max @~english The maximum value of the random value.
     * @~chinese 随机数的最大值。
     * @return @~english The random integer value between min & max. 
     * @~chinese 介于 min 和 max 之间的随机整数。
     */
    template<typename T>
    static inline T random_int(T min, T max) {
        std::uniform_int_distribution<T> dist(min, max);
        auto &mt = RandomHelper::getEngine();
        return dist(mt);
    }
private:
    static std::mt19937 &getEngine();
};

/**@~english
 * Returns a random value between `min` and `max`.
 * @~chinese 
 * 根据指定的最小值与最大值返回一个随机数。
 */
template<typename T>
inline T random(T min, T max) {
    return RandomHelper::random_int<T>(min, max);
}

/**@~english
 * Returns a random float value between `min` and `max`.
 * @~chinese 
 * 根据指定的最小值与最大值返回一个随机浮点数。
 */
template<>
inline float random(float min, float max) {
    return RandomHelper::random_real(min, max);
}

/**@~english
 * Returns a random long double value between `min` and `max`.
 * @~chinese 
 * 根据指定的最小值与最大值返回一个随机长双精度浮点数。
 */
template<>
inline long double random(long double min, long double max) {
    return RandomHelper::random_real(min, max);
}

/**@~english
 * Returns a random double value between `min` and `max`.
 * @~chinese 
 * 根据指定的最小值与最大值返回一个随机双精度浮点数。
 */
template<>
inline double random(double min, double max) {
    return RandomHelper::random_real(min, max);
}

/**@~english
 * Returns a random int between 0 and RAND_MAX.
 * @~chinese 
 * 返回一个 0 到 `RAND_MAX` 之间的随机整数。
 */
inline int random() {
    return cocos2d::random(0, RAND_MAX);
};

/**@~english
 * Returns a random float between -1 and 1.
 * It can be seeded using std::srand(seed);
 * @~chinese 
 * 返回一个 -1 到 1 之间的随机浮点数。
 * 可以使用 std::srand(seed) 函数指定随机数种子。
 */
inline float rand_minus1_1() {
    // FIXME: using the new c++11 random engine generator
    // without a proper way to set a seed is not useful.
    // Resorting to the old random method since it can
    // be seeded using std::srand()
    return ((std::rand() / (float)RAND_MAX) * 2) -1;

//    return cocos2d::random(-1.f, 1.f);
};

/**@~english
 * Returns a random float between 0 and 1.
 * It can be seeded using std::srand(seed);
 * @~chinese 
 * 返回一个 0 到 1 之间的随机浮点数。
 * 可以使用 std::srand(seed) 函数指定随机数种子。
 */
inline float rand_0_1() {
    // FIXME: using the new c++11 random engine generator
    // without a proper way to set a seed is not useful.
    // Resorting to the old random method since it can
    // be seeded using std::srand()
    return std::rand() / (float)RAND_MAX;

//    return cocos2d::random(0.f, 1.f);
};


NS_CC_END
// end group
/// @}
#endif //__ccRandom_H_
