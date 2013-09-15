/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada

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

#include "cocoa/CCObject.h"
#include "CCGL.h"
#include "cocoa/CCString.h"
#include <string>



NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */
/**
 @brief Configuration contains some openGL variables
 @since v0.99.0
 */
class CC_DLL Configuration : public Object
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

    /** returns whether or not an OpenGL is supported */
    bool checkForGLExtension(const std::string &searchName) const;

    bool init();

	/** returns the value of a given key as a string.
	 If the key is not found, it will return the default value */
	const char* getCString(const char *key, const char *defaultValue = nullptr) const;

	/** returns the value of a given key as a boolean.
	 If the key is not found, it will return the default value */
	bool getBool(const char *key, bool defaultValue = false) const;

	/** returns the value of a given key as a double.
	 If the key is not found, it will return the default value */
	double getNumber(const char *key, double defaultValue = 0.0) const;

	/** returns the value of a given key as a double */
	Object * getObject(const char *key) const;

	/** sets a new key/value pair  in the configuration dictionary */
	void setObject(const char *key, Object *value);

	/** dumps the current configuration on the console */
	void dumpInfo() const;

	/** gathers OpenGL / GPU information */
	void gatherGPUInfo();

	/** Loads a config file. If the keys are already present, then they are going to be replaced. Otherwise the new keys are added. */
	void loadConfigFile(const char *filename);

private:
    Configuration(void);
    static Configuration    *s_sharedConfiguration;
	static std::string		s_configfile;
    
protected:
    GLint           _maxTextureSize;
    GLint           _maxModelviewStackDepth;
    bool            _supportsPVRTC;
    bool            _supportsETC;
    bool            _supportsS3TC;
    bool            _supportsATITC;
    bool            _supportsNPOT;
    bool            _supportsBGRA8888;
    bool            _supportsDiscardFramebuffer;
    bool            _supportsShareableVAO;
    GLint           _maxSamplesAllowed;
    GLint           _maxTextureUnits;
    char *          _glExtensions;
	
	Dictionary	*_valueDict;
};

// end of global group
/// @}

NS_CC_END

#endif // __CCCONFIGURATION_H__
