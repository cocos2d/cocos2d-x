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

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */
/**
 @brief Configuration contains some openGL variables
 @since v0.99.0
 */
class CC_DLL Configuration : public Ref
{
public:
    
    /** returns a shared instance of Configuration */
    static Configuration *getInstance();

    /** purge the shared instance of Configuration */
    static void destroyInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Configuration *sharedConfiguration();

    /** @deprecated Use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeConfiguration();

public:
    /**
     * @js NA
     * @lua NA
     */
	virtual ~Configuration();

    /** OpenGL Max texture size. */
	int getMaxTextureSize() const;

    /** OpenGL Max Modelview Stack Depth. */
	int getMaxModelviewStackDepth() const;

    /** returns the maximum texture units
     @since v2.0.0
     */
	int getMaxTextureUnits() const;

    /** Whether or not the GPU supports NPOT (Non Power Of Two) textures.
     OpenGL ES 2.0 already supports NPOT (iOS).
     
     @since v0.99.2
     */
	bool supportsNPOT() const;

    /** Whether or not PVR Texture Compressed is supported */
	bool supportsPVRTC() const;
    
     /** Whether or not ETC Texture Compressed is supported */
    bool supportsETC() const;
    
    /** Whether or  not S3TC Texture Compressed is supported */
    bool supportsS3TC() const;
    
    /** Whether or  not ATITC Texture Compressed is supported */
    bool supportsATITC() const;
    
    /** Whether or not BGRA8888 textures are supported.
     @since v0.99.2
     */
	bool supportsBGRA8888() const;

    /** Whether or not glDiscardFramebufferEXT is supported
     @since v0.99.2
     */
	bool supportsDiscardFramebuffer() const;

    /** Whether or not shareable VAOs are supported.
     @since v2.0.0
     */
	bool supportsShareableVAO() const;
    
    /** Max support directional light in shader, for Sprite3D
     @since v3.3
     */
    int getMaxSupportDirLightInShader() const;
    
    /** Max support point light in shader, for Sprite3D
     *since v3.3
     */
    int getMaxSupportPointLightInShader() const;
    
    /** Max support spot light in shader, for Sprite3D
     *since v3.3
     */
    int getMaxSupportSpotLightInShader() const;

    /** returns whether or not an OpenGL is supported */
    bool checkForGLExtension(const std::string &searchName) const;

    bool init();

	/** returns the value of a given key as a double */
	const Value& getValue(const std::string& key, const Value& defaultValue = Value::Null) const;

	/** sets a new key/value pair  in the configuration dictionary */
	void setValue(const std::string& key, const Value& value);

    /** returns the Configuration info */
    std::string getInfo() const;

	/** gathers OpenGL / GPU information */
	void gatherGPUInfo();

	/** Loads a config file. If the keys are already present, then they are going to be replaced. Otherwise the new keys are added. */
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
	
	ValueMap        _valueDict;
};

// end of global group
/// @}

NS_CC_END

#endif // __CCCONFIGURATION_H__
