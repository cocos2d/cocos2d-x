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

#include "base/CCRef.h"
#include "CCGL.h"
#include "base/CCValue.h"
#include <string>

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */
/**
 @brief 包含一些 openGL 变量的Configuration.
 @since v0.99.0
 */
class CC_DLL Configuration : public Ref
{
public:
    
    /** 返回Configuration的单例实例.*/
    static Configuration *getInstance();

    /** 销毁Configuration的单例实例. */
    static void destroyInstance();

    /** @deprecated 使用 getInstance() 代替此方法 */
    CC_DEPRECATED_ATTRIBUTE static Configuration *sharedConfiguration();

    /** @deprecated 使用 destroyInstance() 代替此方法 */
    CC_DEPRECATED_ATTRIBUTE static void purgeConfiguration();

public:
    /**
     * @js NA
     * @lua NA
     */
	virtual ~Configuration();

    /** OpenGL 最大纹理大小. */
	int getMaxTextureSize() const;

    /** OpenGL 最大模型视图栈深度(Modelview Stack Depth). */
	int getMaxModelviewStackDepth() const;

    /** 返回纹理单元的最大数目.
     @since v2.0.0
     */
	int getMaxTextureUnits() const;

    /** 无论GPU 是否支持NPOT (Non Power Of Two)纹理.
     OpenGL ES 2.0 支持 NPOT (iOS).
     
     @since v0.99.2
     */
	bool supportsNPOT() const;

    /** 是否支持 PVR 纹理压缩(Texture Compressed) */
	bool supportsPVRTC() const;
    
    /** 是否支持 ETC 纹理压缩(Texture Compressed) */
    bool supportsETC() const;
    
    /** 是否支持 S3TC 纹理压缩(Texture Compressed) */
    bool supportsS3TC() const;
    
    /** 是否支持 ATITC 纹理压缩(Texture Compressed) */
    bool supportsATITC() const;
    
    /** 是否支持 BGRA8888 格式的纹理.
     @since v0.99.2
     */
	bool supportsBGRA8888() const;

    /** 是否支持 glDiscardFramebufferEXT. 
     @since v0.99.2
     */
	bool supportsDiscardFramebuffer() const;

    /** 是否支持可共享 VAOs(shareable VAOs).
     @since v2.0.0
     */
	bool supportsShareableVAO() const;

    /** 检查是否支持 OpenGL */
    bool checkForGLExtension(const std::string &searchName) const;

    bool init();

	/** 返回指定键(key)对应的值(Value) */
	const Value& getValue(const std::string& key, const Value& defaultValue = Value::Null) const;

	/** 在Configuration的ValueMap中设置一个新的键值对 */
	void setValue(const std::string& key, const Value& value);

    /** 返回 Configuration 信息 */
    std::string getInfo() const;

	/** 收集 OpenGL / GPU 信息 */
	void gatherGPUInfo();

	/** 加载配置文件到 Configuration. 如果文件中的键已经存在于Configuration中, 将忽略文件中的值.
    否则把新的键值对添加到 Configuration.
    注: 英文原意为若key存在则替换value,但是代码与英文原意明显不同,请确认代码.
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
	
	ValueMap        _valueDict;
};

// end of global group
/// @}

NS_CC_END

#endif // __CCCONFIGURATION_H__
