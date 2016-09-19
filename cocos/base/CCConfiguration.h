/****************************************************************************
Copyright (c) 2010      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

class EventCustom;

/** @class Configuration
 * @brief Configuration contains some openGL variables
 * @since v0.99.0
 * @js NA
 */
class CC_DLL Configuration : public Ref
{
public:
    
    /** Returns a shared instance of Configuration.
     * 
     * @return An autoreleased Configuration object.
     */
    static Configuration *getInstance();

    /** Purge the shared instance of Configuration.
     */
    static void destroyInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Configuration *sharedConfiguration();

    /** @deprecated Use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeConfiguration();

public:
    /** Destructor
     * @js NA
     * @lua NA
     */
	virtual ~Configuration();

    /** OpenGL Max texture size.
     * 
     * @return The OpenGL Max texture size.
     */
	int getMaxTextureSize() const;

    /** OpenGL Max Modelview Stack Depth.
     *
     * @return The OpenGL Max Modelview Stack Depth.
     */
	int getMaxModelviewStackDepth() const;

    /** Returns the maximum texture units.
     *
     * @return The maximum texture units.
     * @since v2.0.0
     */
	int getMaxTextureUnits() const;

    /** Whether or not the GPU supports NPOT (Non Power Of Two) textures.
     OpenGL ES 2.0 already supports NPOT (iOS).
     * 
     * @return Is true if supports NPOT.
     * @since v0.99.2
     */
	bool supportsNPOT() const;

    /** Whether or not PVR Texture Compressed is supported.
     *
     * @return Is true if supports PVR Texture Compressed.
     */
	bool supportsPVRTC() const;
    
    /** Whether or not ETC Texture Compressed is supported.
     * 
     *
     * @return Is true if supports ETC Texture Compressed.
     */
    bool supportsETC() const;
    
    /** Whether or not S3TC Texture Compressed is supported.
     *
     * @return Is true if supports S3TC Texture Compressed.
     */
    bool supportsS3TC() const;
    
    /** Whether or not ATITC Texture Compressed is supported.
     *
     * @return Is true if supports ATITC Texture Compressed.
     */
    bool supportsATITC() const;
    
    /** Whether or not BGRA8888 textures are supported.
     *
     * @return Is true if supports BGRA8888 textures.
     * @since v0.99.2
     */
	bool supportsBGRA8888() const;

    /** Whether or not glDiscardFramebufferEXT is supported.
     * @return Is true if supports glDiscardFramebufferEXT.
     * @since v0.99.2
     */
	bool supportsDiscardFramebuffer() const;

    /** Whether or not shareable VAOs are supported.
     *
     * @return Is true if supports shareable VAOs.
     * @since v2.0.0
     */
	bool supportsShareableVAO() const;

    /** Whether or not OES_depth24 is supported.
     *
     * @return Is true if supports OES_depth24.
     * @since v2.0.0
     */
    bool supportsOESDepth24() const;
    
    /** Whether or not OES_Packed_depth_stencil is supported.
     *
     * @return Is true if supports OES_Packed_depth_stencil.
     * @since v2.0.0
     */
    bool supportsOESPackedDepthStencil() const;

    /** Whether or not glMapBuffer() is supported.
     *
     * On Desktop it returns `true`.
     * On Mobile it checks for the extension `GL_OES_mapbuffer`
     *
     * @return Whether or not `glMapBuffer()` is supported.
     * @since v3.13
     */
    bool supportsMapBuffer() const;

    
    /** Max support directional light in shader, for Sprite3D.
     *
     * @return Maximum supports directional light in shader.
     * @since v3.3
     */
    int getMaxSupportDirLightInShader() const;
    
    /** Max support point light in shader, for Sprite3D.
     *
     * @return Maximum supports point light in shader.
     * @since v3.3
     */
    int getMaxSupportPointLightInShader() const;
    
    /** Max support spot light in shader, for Sprite3D.
     *
     * @return Maximum supports spot light in shader.
     * @since v3.3
     */
    int getMaxSupportSpotLightInShader() const;

    /** get 3d animate quality*/
    Animate3DQuality getAnimate3DQuality() const;
    
    /** Returns whether or not an OpenGL is supported. 
     *
     * @param searchName A given search name.
     * @return Is true if an OpenGL is supported.
     */
    bool checkForGLExtension(const std::string &searchName) const;

    /** Initialize method.
     *
     * @return Is true if initialize success.
     */
    bool init();

	/** Returns the value of a given key as a double.
     *
     * @param key A given key.
     * @param defaultValue if not find the value, return the defaultValue.
     * @return 
     */
	const Value& getValue(const std::string& key, const Value& defaultValue = Value::Null) const;

	/** Sets a new key/value pair  in the configuration dictionary.
     *
     * @param key A given key.
     * @param value A given value.
     */
	void setValue(const std::string& key, const Value& value);

    /** Returns the Configuration info.
     *
     * @return The Configuration info.
     */
    std::string getInfo() const;

	/** Gathers OpenGL / GPU information.
     */
	void gatherGPUInfo();

	/** Loads a config file. If the keys are already present, then they are going to be replaced. Otherwise the new keys are added.
     * 
     * @param filename Config file name.
     */
	void loadConfigFile(const std::string& filename);
    
    static const char* CONFIG_FILE_LOADED;

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
    bool            _supportsOESMapBuffer;
    bool            _supportsOESDepth24;
    bool            _supportsOESPackedDepthStencil;
    
    GLint           _maxSamplesAllowed;
    GLint           _maxTextureUnits;
    char *          _glExtensions;
    int             _maxDirLightInShader; //max support directional light in shader
    int             _maxPointLightInShader; // max support point light in shader
    int             _maxSpotLightInShader; // max support spot light in shader
    Animate3DQuality  _animate3DQuality; // animate 3d quality
	
	ValueMap        _valueDict;
    
    EventCustom*    _loadedEvent;
};


NS_CC_END
// end of base group
/// @}

#endif // __CCCONFIGURATION_H__
