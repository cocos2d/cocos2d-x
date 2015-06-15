/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCSPRIT3DMATERIAL_H__
#define __CCSPRIT3DMATERIAL_H__

#include <string>
#include <unordered_map>
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

class Texture2D;

/** @class Sprite3DMaterialCache
    @brief @~english the sprite3D material is only texture for now
	@~chinese 当前的材质仅仅使用了纹理
    @js NA
    @lua NA
*/
class Sprite3DMaterialCache
{
public:
    /** @~english get & destroy cache
        @~chinese 得到此对象的实例
        @return @~english the instance of this object @~chinese 此对象的实例
    */
    static Sprite3DMaterialCache* getInstance();

    /** @~english destroy the instance
        @~chinese 销毁实例
    */
    static void destroyInstance();

    /** @~english add to cache
        @~chinese 添加到缓存中
        @param key @~english  the key of material @~chinese 材质的键
        @param tex @~english  the Texture2D to add @~chinese 添加的Texture2D
        @return @~english Whether or not the operation is successful @~chinese 是否成功
    */
    bool addSprite3DMaterial(const std::string& key, Texture2D* tex);

    /** @~english get material from cache
        @~chinese 从缓存中获得材质
        @param key @~english  the key of material @~chinese 材质的键
        @return @~english the Texture2D of the given material @~chinese 给定材质的Texture2D
    */
    Texture2D* getSprite3DMaterial(const std::string& key);

    /** @~english remove all spritematerial
        @~chinese 删除所有spritematerial
    */
    void removeAllSprite3DMaterial();

    /** @~english remove unused spritematerial
        @~chinese 删除未使用的spritematerial
    */
    void removeUnusedSprite3DMaterial();

CC_CONSTRUCTOR_ACCESS:

    Sprite3DMaterialCache();
    ~Sprite3DMaterialCache();

protected:
    static Sprite3DMaterialCache* _cacheInstance;//instance
    std::unordered_map<std::string, Texture2D*> _materials; //cached material

};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCSPRIT3DMATERIAL_H__
