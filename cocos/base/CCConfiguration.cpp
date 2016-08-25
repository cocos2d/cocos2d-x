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

#include "base/CCConfiguration.h"
#include "platform/CCFileUtils.h"
#include "base/CCEventCustom.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

NS_CC_BEGIN

extern const char* cocos2dVersion();

Configuration* Configuration::s_sharedConfiguration = nullptr;

const char* Configuration::CONFIG_FILE_LOADED = "config_file_loaded";

Configuration::Configuration()
: _maxTextureSize(0) 
, _maxModelviewStackDepth(0)
, _supportsPVRTC(false)
, _supportsETC1(false)
, _supportsS3TC(false)
, _supportsATITC(false)
, _supportsNPOT(false)
, _supportsBGRA8888(false)
, _supportsDiscardFramebuffer(false)
, _supportsShareableVAO(false)
, _supportsOESDepth24(false)
, _supportsOESPackedDepthStencil(false)
, _supportsOESMapBuffer(false)
, _maxSamplesAllowed(0)
, _maxTextureUnits(0)
, _glExtensions(nullptr)
, _maxDirLightInShader(1)
, _maxPointLightInShader(1)
, _maxSpotLightInShader(1)
, _animate3DQuality(Animate3DQuality::QUALITY_LOW)
{
    _loadedEvent = new (std::nothrow) EventCustom(CONFIG_FILE_LOADED);
}

bool Configuration::init()
{
	_valueDict["cocos2d.x.version"] = Value(cocos2dVersion());


#if CC_ENABLE_PROFILERS
	_valueDict["cocos2d.x.compiled_with_profiler"] = Value(true);
#else
	_valueDict["cocos2d.x.compiled_with_profiler"] = Value(false);
#endif

#if CC_ENABLE_GL_STATE_CACHE == 0
	_valueDict["cocos2d.x.compiled_with_gl_state_cache"] = Value(false);
#else
    _valueDict["cocos2d.x.compiled_with_gl_state_cache"] = Value(true);
#endif

#if COCOS2D_DEBUG
	_valueDict["cocos2d.x.build_type"] = Value("DEBUG");
#else
    _valueDict["cocos2d.x.build_type"] = Value("RELEASE");
#endif

	return true;
}

Configuration::~Configuration()
{
    CC_SAFE_DELETE(_loadedEvent);
}

std::string Configuration::getInfo() const
{
	// And Dump some warnings as well
#if CC_ENABLE_PROFILERS
    CCLOG("cocos2d: **** WARNING **** CC_ENABLE_PROFILERS is defined. Disable it when you finish profiling (from ccConfig.h)\n");
#endif

#if CC_ENABLE_GL_STATE_CACHE == 0
    CCLOG("cocos2d: **** WARNING **** CC_ENABLE_GL_STATE_CACHE is disabled. To improve performance, enable it (from ccConfig.h)\n");
#endif

    // Dump
    Value forDump = Value(_valueDict);
    return forDump.getDescription();
}

void Configuration::gatherGPUInfo()
{
	_valueDict["gl.vendor"] = Value((const char*)glGetString(GL_VENDOR));
	_valueDict["gl.renderer"] = Value((const char*)glGetString(GL_RENDERER));
	_valueDict["gl.version"] = Value((const char*)glGetString(GL_VERSION));

    _glExtensions = (char *)glGetString(GL_EXTENSIONS);

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
	_valueDict["gl.max_texture_size"] = Value((int)_maxTextureSize);

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
	_valueDict["gl.max_texture_units"] = Value((int)_maxTextureUnits);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    glGetIntegerv(GL_MAX_SAMPLES_APPLE, &_maxSamplesAllowed);
	_valueDict["gl.max_samples_allowed"] = Value((int)_maxSamplesAllowed);
#endif
    
    _supportsETC1 = checkForGLExtension("GL_OES_compressed_ETC1_RGB8_texture");
    _valueDict["gl.supports_ETC1"] = Value(_supportsETC1);
    
    _supportsS3TC = checkForGLExtension("GL_EXT_texture_compression_s3tc");
    _valueDict["gl.supports_S3TC"] = Value(_supportsS3TC);
    
    _supportsATITC = checkForGLExtension("GL_AMD_compressed_ATC_texture");
    _valueDict["gl.supports_ATITC"] = Value(_supportsATITC);
    
    _supportsPVRTC = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
	_valueDict["gl.supports_PVRTC"] = Value(_supportsPVRTC);

    _supportsNPOT = true;
	_valueDict["gl.supports_NPOT"] = Value(_supportsNPOT);
	
    _supportsBGRA8888 = checkForGLExtension("GL_IMG_texture_format_BGRA888");
	_valueDict["gl.supports_BGRA8888"] = Value(_supportsBGRA8888);

    _supportsDiscardFramebuffer = checkForGLExtension("GL_EXT_discard_framebuffer");
	_valueDict["gl.supports_discard_framebuffer"] = Value(_supportsDiscardFramebuffer);

    _supportsShareableVAO = checkForGLExtension("vertex_array_object");
    _valueDict["gl.supports_vertex_array_object"] = Value(_supportsShareableVAO);

    _supportsOESMapBuffer = checkForGLExtension("GL_OES_mapbuffer");
    _valueDict["gl.supports_OES_map_buffer"] = Value(_supportsOESMapBuffer);

    _supportsOESDepth24 = checkForGLExtension("GL_OES_depth24");
    _valueDict["gl.supports_OES_depth24"] = Value(_supportsOESDepth24);

    
    _supportsOESPackedDepthStencil = checkForGLExtension("GL_OES_packed_depth_stencil");
    _valueDict["gl.supports_OES_packed_depth_stencil"] = Value(_supportsOESPackedDepthStencil);


    CHECK_GL_ERROR_DEBUG();
}

Configuration* Configuration::getInstance()
{
    if (! s_sharedConfiguration)
    {
        s_sharedConfiguration = new (std::nothrow) Configuration();
        s_sharedConfiguration->init();
    }
    
    return s_sharedConfiguration;
}

void Configuration::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_sharedConfiguration);
}

// FIXME: deprecated
Configuration* Configuration::sharedConfiguration()
{
    return Configuration::getInstance();
}

// FIXME: deprecated
void Configuration::purgeConfiguration()
{
    Configuration::destroyInstance();
}


bool Configuration::checkForGLExtension(const std::string &searchName) const
{
   return  (_glExtensions && strstr(_glExtensions, searchName.c_str() ) ) ? true : false;
}

//
// getters for specific variables.
// Maintained for backward compatibility reasons only.
//
int Configuration::getMaxTextureSize() const
{
	return _maxTextureSize;
}

int Configuration::getMaxModelviewStackDepth() const
{
	return _maxModelviewStackDepth;
}

int Configuration::getMaxTextureUnits() const
{
	return _maxTextureUnits;
}

bool Configuration::supportsNPOT() const
{
	return _supportsNPOT;
}

bool Configuration::supportsPVRTC() const
{
	return _supportsPVRTC;
}

bool Configuration::supportsETC() const
{
    //GL_ETC1_RGB8_OES is not defined in old opengl version
#ifdef GL_ETC1_RGB8_OES
    return _supportsETC1;
#else
    return false;
#endif
}

bool Configuration::supportsS3TC() const
{
#ifdef GL_EXT_texture_compression_s3tc
    return _supportsS3TC;
#else
    return false;
#endif
}

bool Configuration::supportsATITC() const
{
    return _supportsATITC;
}

bool Configuration::supportsBGRA8888() const
{
	return _supportsBGRA8888;
}

bool Configuration::supportsDiscardFramebuffer() const
{
	return _supportsDiscardFramebuffer;
}

bool Configuration::supportsShareableVAO() const
{
#if CC_TEXTURE_ATLAS_USE_VAO
    return _supportsShareableVAO;
#else
    return false;
#endif
}

bool Configuration::supportsMapBuffer() const
{
    // Fixes Github issue #16123
    //
    // XXX: Fixme. Should check GL ES and not iOS or Android
    // For example, linux could be compiled with GL ES. Or perhaps in the future Android will
    // support OpenGL. This is because glMapBufferOES() is an extension of OpenGL ES. And glMapBuffer()
    // is always implemented in OpenGL.

    // XXX: Warning. On iOS this is always `true`. Avoiding the comparison.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return _supportsOESMapBuffer;
#else
    return true;
#endif
}

bool Configuration::supportsOESDepth24() const
{
    return _supportsOESDepth24;
    
}
bool Configuration::supportsOESPackedDepthStencil() const
{
    return _supportsOESPackedDepthStencil;
}



int Configuration::getMaxSupportDirLightInShader() const
{
    return _maxDirLightInShader;
}

int Configuration::getMaxSupportPointLightInShader() const
{
    return _maxPointLightInShader;
}

int Configuration::getMaxSupportSpotLightInShader() const
{
    return _maxSpotLightInShader;
}

Animate3DQuality Configuration::getAnimate3DQuality() const
{
    return _animate3DQuality;
}

//
// generic getters for properties
//
const Value& Configuration::getValue(const std::string& key, const Value& defaultValue) const
{
    auto iter = _valueDict.find(key);
    if (iter != _valueDict.cend())
        return _valueDict.at(key);
	return defaultValue;
}

void Configuration::setValue(const std::string& key, const Value& value)
{
	_valueDict[key] = value;
}


//
// load file
//
void Configuration::loadConfigFile(const std::string& filename)
{
	ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(filename);
	CCASSERT(!dict.empty(), "cannot create dictionary");

	// search for metadata
	bool validMetadata = false;
	auto metadataIter = dict.find("metadata");
	if (metadataIter != dict.cend() && metadataIter->second.getType() == Value::Type::MAP)
    {
        
		const auto& metadata = metadataIter->second.asValueMap();
        auto formatIter = metadata.find("format");
        
		if (formatIter != metadata.cend())
        {
			int format = formatIter->second.asInt();

			// Support format: 1
			if (format == 1)
            {
				validMetadata = true;
			}
		}
	}

	if (! validMetadata)
    {
		CCLOG("Invalid config format for file: %s", filename.c_str());
		return;
	}

	auto dataIter = dict.find("data");
	if (dataIter == dict.cend() || dataIter->second.getType() != Value::Type::MAP)
    {
		CCLOG("Expected 'data' dict, but not found. Config file: %s", filename.c_str());
		return;
	}

	// Add all keys in the existing dictionary
    
	const auto& dataMap = dataIter->second.asValueMap();
    for (auto dataMapIter = dataMap.cbegin(); dataMapIter != dataMap.cend(); ++dataMapIter)
    {
        if (_valueDict.find(dataMapIter->first) == _valueDict.cend())
            _valueDict[dataMapIter->first] = dataMapIter->second;
        else
            CCLOG("Key already present. Ignoring '%s'",dataMapIter->first.c_str());
    }
    
    //light info
    std::string name = "cocos2d.x.3d.max_dir_light_in_shader";
	if (_valueDict.find(name) != _valueDict.end())
        _maxDirLightInShader = _valueDict[name].asInt();
    else
        _valueDict[name] = Value(_maxDirLightInShader);
    
    name = "cocos2d.x.3d.max_point_light_in_shader";
	if (_valueDict.find(name) != _valueDict.end())
        _maxPointLightInShader = _valueDict[name].asInt();
    else
        _valueDict[name] = Value(_maxPointLightInShader);
    
    name = "cocos2d.x.3d.max_spot_light_in_shader";
	if (_valueDict.find(name) != _valueDict.end())
        _maxSpotLightInShader = _valueDict[name].asInt();
    else
        _valueDict[name] = Value(_maxSpotLightInShader);
    
    name = "cocos2d.x.3d.animate_quality";
    if (_valueDict.find(name) != _valueDict.end())
        _animate3DQuality = (Animate3DQuality)_valueDict[name].asInt();
    else
        _valueDict[name] = Value((int)_animate3DQuality);
    
    Director::getInstance()->getEventDispatcher()->dispatchEvent(_loadedEvent);
}

NS_CC_END
