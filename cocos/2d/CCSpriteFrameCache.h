/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#ifndef __SPRITE_CCSPRITE_FRAME_CACHE_H__
#define __SPRITE_CCSPRITE_FRAME_CACHE_H__

/*@~english
 * To create sprite frames and texture atlas, use this tool:
 * http://zwoptex.zwopple.com/
 * @~chinese 
 * 使用这个工具制作 SpriteFrame 和纹理集:
 * http://zwoptex.zwopple.com/
 */
#include <set>
#include <string>
#include "2d/CCSpriteFrame.h"
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "base/CCMap.h"

NS_CC_BEGIN

class Sprite;
class Texture2D;
class PolygonInfo;

/**
 * @addtogroup _2d
 * @{
 */

/** @class SpriteFrameCache
 * @brief @~english Singleton that handles the loading of the sprite frames.

 The SpriteFrameCache loads SpriteFrames from a .plist file.
 A SpriteFrame contains information about how to use a sprite
 located in a sprite sheet.
 
 The .plist file contains the following elements:

 - `frames`:
   Dictionary of sprites. Key is the sprite's name, value a dict containing the sprite frame data.
   A sprite frame consists of the following values:
    - `spriteOffset`:     difference vector between the original sprite's center and the center of the trimmed sprite
    - `spriteSize`:       size of the trimmed sprite
    - `spriteSourceSize`: size of the original sprite
    - `textureRect`:      the position of the sprite in the sprite sheet
    - `textureRotated`:   true if the sprite is rotated clockwise
   Optional values when using polygon outlines
    - `triangles`:        3 indices per triangle, pointing to vertices and verticesUV coordinates
    - `vertices`:         vertices in sprite coordinates, each vertex consists of a pair of x and y coordinates
    - `verticesUV`:       vertices in the sprite sheet, each vertex consists of a pair of x and y coordinates
 
 - `metadata`:
   Dictionary containing additional information about the sprite sheet:
     - `format`:          plist file format, currently 3
     - `size`:            size of the texture (optional)
     - `textureFileName`: name of the texture's image file
 
 Use one of the following tools to create the .plist file and sprite sheet:
 - [TexturePacker](https://www.codeandweb.com/texturepacker/cocos2d)
 - [Zwoptex](https://zwopple.com/zwoptex/)
 
 * @~chinese 用于加载 SpriteFrame 的单例，缓存所有的 SpriteFrame。
 @since v0.9
 @js cc.spriteFrameCache
 */
class CC_DLL SpriteFrameCache : public Ref
{
public:
    /** @~english Returns the shared instance of the Sprite Frame cache.
     *
     * @~chinese 返回 SpriteFrameCache 的实例。
     * 
     * @return @~english The instance of the Sprite Frame Cache.
     * @~chinese SpriteFrameCache 的实例。
     * @js NA
     */
    static SpriteFrameCache* getInstance();

    /** @deprecated Use getInstance() instead
     @js NA
	*/
    CC_DEPRECATED_ATTRIBUTE static SpriteFrameCache* sharedSpriteFrameCache() { return SpriteFrameCache::getInstance(); }

    /** @~english Destroys the cache. It releases all the Sprite Frames and the retained instance.
     * @~chinese 销毁 SpriteFrameCache 的实例。会释放所有的 SpriteFrame 和 retain 的实例。
	 * @js NA
     */
    static void destroyInstance();

    /** @deprecated Use destroyInstance() instead
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedSpriteFrameCache() { return SpriteFrameCache::destroyInstance(); }

    /** @~english Destructor.
     * @~chinese 析构函数。
     * @js NA
     * @lua NA
     */
    virtual ~SpriteFrameCache();
    
    /** @~english Initialize method.
     *
     * @~chinese 初始化方法。
     * 
     * @return @~english if success return true.
     * @~chinese 如果成功返回true。
     */
    bool init();

    /** @~english Adds multiple Sprite Frames from a plist file.
     * A texture will be loaded automatically.
     * When texture file is not specified in plist file, the texture name will composed by replacing the .plist suffix with .png.
     * If you want to use another texture, you should use the `addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName)` method.
     * @~chinese 从 plist 文件添加多个 SpriteFrame。
     * 会自动加载相应的纹理。
     * 当 plist 文件中未指定使用的 texture 文件时，plist 文件的扩展名替换为 .png 即为纹理文件的名称。
     * 如果需要使用指定的纹理文件，请使用 `addSpriteFramesWithFile(const std::string& plist,const std::string& textureFileName)` 方法。
     * @param plist @~english Plist file name.
     * @~chinese plist 文件路径。
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist);

    /** @~english Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
     * @~chinese 使用指定的 plist 文件与纹理文件加载 SpriteFrame。
     @since v0.99.5

     * @param plist @~english Plist file name.
     * @~chinese plist文件路径。
     * @param textureFileName @~english Texture file name.
     * @~chinese 纹理文件路径。
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName);

    /** @~english Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames. 
     * @~chinese 使用指定的 plist 文件和纹理加载 SpriteFrame。
     * @param plist @~english Plist file name.
     * @~chinese plist文件路径。
     * @param texture @~english Texture pointer.
     * @~chinese 指定的纹理。
     *
     * @js addSpriteFrames
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFile(const std::string&plist, Texture2D *texture);

    /** @~english Adds multiple Sprite Frames from a plist file content. The texture will be associated with the created sprite frames. 
     * @~chinese 使用指定的 plist 文件内容与纹理加载 SpriteFrame。
     *
     * @param plist_content @~english Plist file content string.
     * @~chinese plist 文件内容的字符串。
     * @param texture @~english Texture pointer.
     * @~chinese 指定的纹理。
     *
     * @js NA
     * @lua addSpriteFrames
     */
    void addSpriteFramesWithFileContent(const std::string& plist_content, Texture2D *texture);

    /** @~english Adds an sprite frame with a given name.
     If the name already exists, then the contents of the old name will be replaced with the new one.
     *
     * @~chinese 添加一个 SpriteFrame 并指定其名称。
     * 如果名称已经存在，那么将其对应的 SpriteFrame 更换为 frame 参数的值。
     * 
     * @param frame @~english A certain sprite frame.
     * @~chinese 指定的 SpriteFrame。
     * @param frameName @~english The name of the sprite frame.
     * @~chinese 指定的 SpriteFrame 名称。
     */
    void addSpriteFrame(SpriteFrame *frame, const std::string& frameName);

    /** @~english Check if multiple Sprite Frames from a plist file have been loaded.
     * @~chinese 检查一个 plist 文件是否已经被加载。
     *
     * @param plist @~english Plist file name.
     * @~chinese plist 文件路径。
     * @return @~english True if the file is loaded.
     * @~chinese 如果文件已被加载，返回 true；否则返回 false。
     * @js NA
     * @lua NA
     */
    bool isSpriteFramesWithFileLoaded(const std::string& plist) const;

    /** @~english Purges the dictionary of loaded sprite frames.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     * @~chinese 清理已加载的 SpriteFrame。
     * 可以调用这个方法来释放 SpriteFrame 占用的内存。
     * 在短期内:可以释放内存以防止应用程序被中止。
     * 在中期内:会分配更多的资源。
     * 从长远来看:没有什么区别。
     */
    void removeSpriteFrames();

    /** @~english Removes unused sprite frames.
     * Sprite Frames that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
     * @~chinese 释放未使用的 SpriteFrame。
     * 引用计数为 1 的 SpriteFrame 将被删除。
     * 在进入一个新的场景时，可以通过调用该方法方便的释放不再使用的 SpriteFrame。
	 * @js NA
     */
    void removeUnusedSpriteFrames();

    /** @~english Deletes an sprite frame from the sprite frame cache. 
     *
     * @~chinese 根据指定的名称从缓存中删除一个 SpriteFrame。
     * 
     * @param name @~english The name of the sprite frame that needs to removed.
     * @~chinese 需要删除的 SpriteFrame 名称。
     */
    void removeSpriteFrameByName(const std::string& name);

    /** @~english Removes multiple Sprite Frames from a plist file.
     * Sprite Frames stored in this file will be removed.
     * It is convenient to call this method when a specific texture needs to be removed.
     * @~chinese 将指定的 plist 文件中的 SpriteFrame 从缓存中删除。
     * 调用这个方法可以方便的从缓存中删除指定的 plist 中的 SpriteFrame。
     * @since v0.99.5
     *
     * @param plist @~english The name of the plist that needs to removed.
     * @~chinese 需要删除 SpriteFrame 所使用的 plist 文件路径。
     */
    void removeSpriteFramesFromFile(const std::string& plist);

    /** @~english Removes multiple Sprite Frames from a plist file content.
     * Sprite Frames stored in this file will be removed.
     * It is convenient to call this method when a specific texture needs to be removed.
     *
     * @~chinese 将指定的 plist 文件内容中的 SpriteFrame 从缓存中删除。
     * 调用这个方法可以方便的从缓存中删除指定的 plist 中的 SpriteFrame。
     * 
     * @param plist_content @~english The string of the plist content used to find the corresponding SpriteFrame.
     * @~chinese 需要删除的 SpriteFrame 所使用的 plist 文件内容。
     * @js NA
     */
    void removeSpriteFramesFromFileContent(const std::string& plist_content);

    /** @~english Removes all Sprite Frames associated with the specified textures.
     * It is convenient to call this method when a specific texture needs to be removed.
     * @~chinese 将使用指定纹理的 SpriteFrame 从缓存中删除。
     * 调用这个方法可以方便的从缓存中删除使用指定纹理的 SpriteFrame。
     * @since v0.995.
     *
     * @param texture @~english The texture used to find the corresponding SpriteFrame.
     * @~chinese 需要删除的 SpriteFrame 所使用的纹理。
     */
    void removeSpriteFramesFromTexture(Texture2D* texture);

    /** @~english Returns an Sprite Frame that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it.
     * @~chinese 获取指定名称的 SpriteFrame。
     * 如果没有找到这个名字它将返回 nullptr。
     * 在使用返回值的过程中，应该对其进行 retain。
     *
     * @param name @~english A certain sprite frame name.
     * @~chinese 指定的 SpriteFrame 名称。
     * @return @~english The sprite frame.
     * @~chinese SpriteFrame 实例。
     * @js getSpriteFrame
     * @lua getSpriteFrame
     */
    SpriteFrame* getSpriteFrameByName(const std::string& name);

    /** @deprecated use getSpriteFrameByName() instead */
    CC_DEPRECATED_ATTRIBUTE SpriteFrame* spriteFrameByName(const std::string&name) { return getSpriteFrameByName(name); }

protected:
    // MARMALADE: Made this protected not private, as deriving from this class is pretty useful
    SpriteFrameCache(){}

    /*@~english Adds multiple Sprite Frames with a dictionary. The texture will be associated with the created sprite frames.
     * @~chinese 使用指定的 ValueMap 与纹理添加多个 SpriteFrame。
     */
    void addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture);

    /** @~english Removes multiple Sprite Frames from Dictionary.
     * @~chinese 将指定的 ValueMap 中的 SpriteFrame 从缓存中删除。
    * @since v0.99.5
    */
    void removeSpriteFramesFromDictionary(ValueMap& dictionary);

    /** Parses list of space-separated integers */
    void parseIntegerList(const std::string &string, std::vector<int> &res);
    
    /** Configures PolygonInfo class with the passed sizes + triangles */
    void initializePolygonInfo(const Size &textureSize,
                               const Size &spriteSize,
                               const std::vector<int> &vertices,
                               const std::vector<int> &verticesUV,
                               const std::vector<int> &triangleIndices,
                               PolygonInfo &polygonInfo);

    Map<std::string, SpriteFrame*> _spriteFrames;
    ValueMap _spriteFramesAliases;
    std::set<std::string>*  _loadedFileNames;
};

// end of _2d group
/// @}

NS_CC_END

#endif // __SPRITE_CCSPRITE_FRAME_CACHE_H__
