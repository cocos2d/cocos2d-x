/****************************************************************************
Copyright (c) 2010      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCCONFIGURATION_H__
#define __CCCONFIGURATION_H__

#include <string>

#include "base/CCRef.h"
#include "base/CCValue.h"
#include "platform/CCGL.h"
#include "3d/CCAnimate3D.h"


/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN


/** @class Configuration
 * @brief @~english Configuration contains some openGL variables
 * @~chinese Configuration包含了一些openGL配置变量
 * @since v0.99.0
 * @js NA
 */
class CC_DLL Configuration : public Ref
{
public:
    

    /** @~english Returns a shared instance of Configuration.
     * 
     * @~chinese 返回一个Configuration单例。
     * 
     * @return @~english An autoreleased Configuration object.
     * @~chinese 一个autoreleased Configuration对象。
     */
    static Configuration *getInstance();


    /** @~english Purge the shared instance of Configuration.
     * @~chinese 销毁Configuration单例。
     */
    static void destroyInstance();


    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Configuration *sharedConfiguration();


    /** @deprecated Use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeConfiguration();

public:

    /** @~english Destructor
     * @~chinese 析构函数
     * @js NA
     * @lua NA
     */
	virtual ~Configuration();


    /** @~english OpenGL Max texture size.
     * 
     * @~chinese OpenGL最大纹理尺寸。
     * 
     * @return @~english The OpenGL Max texture size.
     * @~chinese OpenGL最大纹理大小。
     */
	int getMaxTextureSize() const;


    /** @~english OpenGL Max Modelview Stack Depth.
     *
     * @~chinese OpenGL最大视点矩阵堆栈深度。
     * 
     * @return @~english The OpenGL Max Modelview Stack Depth.
     * @~chinese OpenGL最大视点矩阵堆栈深度。
     */
	int getMaxModelviewStackDepth() const;


    /** @~english Returns the maximum texture units.
     *
     * @~chinese 返回的最大纹理单位。
     * 
     * @return @~english The maximum texture units.
     * @~chinese 最大的纹理单位。
     * @since v2.0.0
     */
	int getMaxTextureUnits() const;


    /** @~english Whether or not the GPU supports NPOT (Non Power Of Two) textures.
     OpenGL ES 2.0 already supports NPOT (iOS).
     * 
     * @~chinese 是否GPU支持NPOT(非2的次方)的纹理。
     * OpenGL ES 2.0已经支持NPOT(iOS)。
     * 
     * @return @~english Is true if supports NPOT.
     * @~chinese 如果支持NPOT返回真。
     * @since v0.99.2
     */
	bool supportsNPOT() const;


    /** @~english Whether or not PVR Texture Compressed is supported.
     *
     * @~chinese 是否支持PVR纹理压缩格式。
     * 
     * @return @~english Is true if supports PVR Texture Compressed.
     * @~chinese 如果支持PVR纹理压缩格式返回真。
     */
	bool supportsPVRTC() const;
    

    /** @~english Whether or not ETC Texture Compressed is supported.
     * 
     *
     * @~chinese 是否支持ETC纹理压缩格式。
     * 
     * 
     * @return @~english Is true if supports ETC Texture Compressed.
     * @~chinese 如果支持ETC纹理压缩格式返回真。
     */
    bool supportsETC() const;
    

    /** @~english Whether or not S3TC Texture Compressed is supported.
     *
     * @~chinese 是否支持S3TC纹理压缩格式。
     * 
     * @return @~english Is true if supports S3TC Texture Compressed.
     * @~chinese 如果支持S3TC纹理压缩格式返回真。
     */
    bool supportsS3TC() const;
    

    /** @~english Whether or not ATITC Texture Compressed is supported.
     *
     * @~chinese 是否支持ATITC纹理压缩格式。
     * 
     * @return @~english Is true if supports ATITC Texture Compressed.
     * @~chinese 如果支持ATITC纹理压缩格式返回真。
     */
    bool supportsATITC() const;
    

    /** @~english Whether or not BGRA8888 textures are supported.
     *
     * @~chinese 是否支持BGRA8888纹理格式。
     * 
     * @return @~english Is true if supports BGRA8888 textures.
     * @~chinese 如果支持BGRA8888纹理格式返回真。
     * @since v0.99.2
     */
	bool supportsBGRA8888() const;


    /** @~english Whether or not glDiscardFramebufferEXT is supported.
     * @~chinese 是否支持glDiscardFramebufferEXT。
     * @return @~english Is true if supports glDiscardFramebufferEXT.
     * @~chinese 如果支持glDiscardFramebufferEXT返回真。
     * @since v0.99.2
     */
	bool supportsDiscardFramebuffer() const;


    /** @~english Whether or not shareable VAOs are supported.
     *
     * @~chinese 是否可共享的支持共享VAO。
     * 
     * @return @~english Is true if supports shareable VAOs.
     * @~chinese 如果支持共享VAO返回真。
     * @since v2.0.0
     */
	bool supportsShareableVAO() const;
    

    /** @~english Max support directional light in shader, for Sprite3D.
     *
     * @~chinese 获取Sprite3D中shader支持的方向光最大数量。
     * 
     * @return @~english Maximum supports directional light in shader.
     * @~chinese Sprite3D中shader支持的方向光最大数量。
     * @since v3.3
     */
    int getMaxSupportDirLightInShader() const;
    

    /** @~english Max support point light in shader, for Sprite3D.
     *
     * @~chinese 获取Sprite3D中shader支持的点光源最大数量。
     * 
     * @return @~english Maximum supports point light in shader.
     * @~chinese Sprite3D中shader支持的点光源最大数量。
     * @since v3.3
     */
    int getMaxSupportPointLightInShader() const;
    

    /** @~english Max support spot light in shader, for Sprite3D.
     *
     * @~chinese 获取Sprite3D中shader支持的聚光灯光源最大数量。
     * 
     * @return @~english Maximum supports spot light in shader.
     * @~chinese Sprite3D中shader支持的聚光灯光源最大数量。
     * @since v3.3
     */
    int getMaxSupportSpotLightInShader() const;


    /** @~english get 3d animate quality @~chinese 获得3d动画质量
     * @return @~english 3d animate quality.
     * @return @~english 3d动画质量。
     */
    Animate3DQuality getAnimate3DQuality() const;
    

    /** @~english Returns whether or not an OpenGL is supported. 
     *
     * @~chinese 返回一个是否支持某个OpenGL。
     * 
     * @param searchName @~english A given search name.
     * @~chinese 一个给定的搜索的名字。
     * @return @~english Is true if an OpenGL is supported.
     * @~chinese 如果支持某个OpenGL返回真。
     */
    bool checkForGLExtension(const std::string &searchName) const;


    /** @~english Initialize method.
     *
     * @~chinese 初始化方法。
     * 
     * @return @~english Is true if initialize success.
     * @~chinese 如果初始化成功返回真。
     */
    bool init();


	/** @~english Returns the value of a given key as a double.
     *
  * @~chinese 根据给定的键返回值
  * 
     * @param key @~english A given key.
  * @~chinese 一个给定的键。
     * @param defaultValue @~english if not find the value, return the defaultValue.
  * @~chinese 如果找不到值，则返回默认值。
     * @return 
     */
	const Value& getValue(const std::string& key, const Value& defaultValue = Value::Null) const;


	/** @~english Sets a new key/value pair  in the configuration dictionary.
     *
  * @~chinese 在配置字典中设置一个新的键值对。
  * 
     * @param key @~english A given key.
  * @~chinese 一个给定的键。
     * @param value @~english A given value.
  * @~chinese 一个给定的值。
     */
	void setValue(const std::string& key, const Value& value);


    /** @~english Returns the Configuration info.
     *
     * @~chinese 返回配置信息。
     * 
     * @return @~english The Configuration info.
     * @~chinese 配置信息。
     */
    std::string getInfo() const;


	/** @~english Gathers OpenGL / GPU information.
  * @~chinese 收集OpenGL/GPU 信息。
     */
	void gatherGPUInfo();


	/** @~english Loads a config file. If the keys are already present, then they are going to be replaced. Otherwise the new keys are added.
     * 
  * @~chinese 加载配置文件。如果键已经存在,那么将被替换。否则添加新的键。
  * 
     * @param filename @~english Config file name.
  * @~chinese 配置文件名。
     */
	void loadConfigFile(const std::string& filename);

private:
    Configuration(void);
    static Configuration    *s_sharedConfiguration;
	static std::string		s_configfile;
    
protected:
    GLint           _maxTextureSize;
    GLint           _maxModelviewStackDepth;
    bool            _supportsPVRTC;
    bool            _supportsETC1;
    bool            _supportsS3TC;
    bool            _supportsATITC;
    bool            _supportsNPOT;
    bool            _supportsBGRA8888;
    bool            _supportsDiscardFramebuffer;
    bool            _supportsShareableVAO;
    GLint           _maxSamplesAllowed;
    GLint           _maxTextureUnits;
    char *          _glExtensions;
    int             _maxDirLightInShader; //max support directional light in shader
    int             _maxPointLightInShader; // max support point light in shader
    int             _maxSpotLightInShader; // max support spot light in shader
    Animate3DQuality  _animate3DQuality; // animate 3d quality
	
	ValueMap        _valueDict;
};


NS_CC_END
// end of base group
/// @}

#endif // __CCCONFIGURATION_H__
