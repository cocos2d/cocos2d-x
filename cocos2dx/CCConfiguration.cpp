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

#include "CCConfiguration.h"
#include "ccMacros.h"
#include "ccConfig.h"
#include <string.h>
#include "cocoa/CCDictionary.h"
#include "cocoa/CCInteger.h"
#include "cocoa/CCBool.h"
#include "cocos2d.h"
#include "platform/CCFileUtils.h"

using namespace std;

NS_CC_BEGIN


Configuration* Configuration::s_gSharedConfiguration = NULL;

Configuration::Configuration(void)
: _maxTextureSize(0) 
, _maxModelviewStackDepth(0)
, _supportsPVRTC(false)
, _supportsETC(false)
, _supportsNPOT(false)
, _supportsBGRA8888(false)
, _supportsDiscardFramebuffer(false)
, _supportsShareableVAO(false)
, _maxSamplesAllowed(0)
, _maxTextureUnits(0)
, _glExtensions(NULL)
, _valueDict(NULL)
{
}

bool Configuration::init(void)
{
	_valueDict = Dictionary::create();
	_valueDict->retain();

	_valueDict->setObject( String::create( cocos2dVersion() ), "cocos2d.x.version");


#if CC_ENABLE_PROFILERS
	_valueDict->setObject( Bool::create(true), "cocos2d.x.compiled_with_profiler");
#else
	_valueDict->setObject( Bool::create(false), "cocos2d.x.compiled_with_profiler");
#endif

#if CC_ENABLE_GL_STATE_CACHE == 0
	_valueDict->setObject( Bool::create(false), "cocos2d.x.compiled_with_gl_state_cache");
#else
	_valueDict->setObject( Bool::create(true), "cocos2d.x.compiled_with_gl_state_cache");
#endif

	return true;
}

Configuration::~Configuration(void)
{
	_valueDict->release();
}

void Configuration::dumpInfo(void) const
{
	// Dump
	PrettyPrinter visitor(0);
	_valueDict->acceptVisitor(visitor);

	CCLOG("%s", visitor.getResult().c_str());


	// And Dump some warnings as well
#if CC_ENABLE_PROFILERS
    CCLOG("cocos2d: **** WARNING **** CC_ENABLE_PROFILERS is defined. Disable it when you finish profiling (from ccConfig.h)");
    printf("\n");
#endif

#if CC_ENABLE_GL_STATE_CACHE == 0
    CCLOG("");
    CCLOG("cocos2d: **** WARNING **** CC_ENABLE_GL_STATE_CACHE is disabled. To improve performance, enable it (from ccConfig.h)");
    printf("\n");
#endif

}

void Configuration::gatherGPUInfo()
{
	_valueDict->setObject( String::create( (const char*)glGetString(GL_VENDOR)), "gl.vendor");
	_valueDict->setObject( String::create( (const char*)glGetString(GL_RENDERER)), "gl.renderer");
	_valueDict->setObject( String::create( (const char*)glGetString(GL_VERSION)), "gl.version");

    _glExtensions = (char *)glGetString(GL_EXTENSIONS);

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
	_valueDict->setObject( Integer::create((int)_maxTextureSize), "gl.max_texture_size");

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
	_valueDict->setObject( Integer::create((int)_maxTextureUnits), "gl.max_texture_units");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    glGetIntegerv(GL_MAX_SAMPLES_APPLE, &_maxSamplesAllowed);
	_valueDict->setObject( Integer::create((int)_maxSamplesAllowed), "gl.max_samples_allowed");
#endif
    
    _supportsETC = checkForGLExtension("GL_OES_compressed_ETC1_RGB8_texture");
    _valueDict->setObject( Bool::create(_supportsETC), "gl.supports_ETC");
    
    _supportsPVRTC = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
	_valueDict->setObject( Bool::create(_supportsPVRTC), "gl.supports_PVRTC");

    _supportsNPOT = true;
	_valueDict->setObject( Bool::create(_supportsNPOT), "gl.supports_NPOT");
	
    _supportsBGRA8888 = checkForGLExtension("GL_IMG_texture_format_BGRA888");
	_valueDict->setObject( Bool::create(_supportsBGRA8888), "gl.supports_BGRA8888");

    _supportsDiscardFramebuffer = checkForGLExtension("GL_EXT_discard_framebuffer");
	_valueDict->setObject( Bool::create(_supportsDiscardFramebuffer), "gl.supports_discard_framebuffer");

    _supportsShareableVAO = checkForGLExtension("vertex_array_object");
	_valueDict->setObject( Bool::create(_supportsShareableVAO), "gl.supports_vertex_array_object");
    
    CHECK_GL_ERROR_DEBUG();
}

Configuration* Configuration::getInstance()
{
    if (! s_gSharedConfiguration)
    {
        s_gSharedConfiguration = new Configuration();
        s_gSharedConfiguration->init();
    }
    
    return s_gSharedConfiguration;
}

void Configuration::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_gSharedConfiguration);
}

// XXX: deprecated
Configuration* Configuration::sharedConfiguration(void)
{
    return Configuration::getInstance();
}

// XXX: deprecated
void Configuration::purgeConfiguration(void)
{
    Configuration::destroyInstance();
}


bool Configuration::checkForGLExtension(const string &searchName) const
{
    bool bRet = false;
    const char *kSearchName = searchName.c_str();
    
    if (_glExtensions && 
        strstr(_glExtensions, kSearchName))
    {
        bRet = true;
    }
    
    return bRet;
}

//
// getters for specific variables.
// Mantained for backward compatiblity reasons only.
//
int Configuration::getMaxTextureSize(void) const
{
	return _maxTextureSize;
}

int Configuration::getMaxModelviewStackDepth(void) const
{
	return _maxModelviewStackDepth;
}

int Configuration::getMaxTextureUnits(void) const
{
	return _maxTextureUnits;
}

bool Configuration::supportsNPOT(void) const
{
	return _supportsNPOT;
}

bool Configuration::supportsPVRTC(void) const
{
	return _supportsPVRTC;
}

bool Configuration::supportsETC() const
{
    //GL_ETC1_RGB8_OES is not defined in old opengl version
#ifdef GL_ETC1_RGB8_OES
    return _supportsETC;
#else
    return false;
#endif
}

bool Configuration::supportsBGRA8888(void) const
{
	return _supportsBGRA8888;
}

bool Configuration::supportsDiscardFramebuffer(void) const
{
	return _supportsDiscardFramebuffer;
}

bool Configuration::supportsShareableVAO(void) const
{
	return _supportsShareableVAO;
}

//
// generic getters for properties
//
const char *Configuration::getCString( const char *key, const char *default_value ) const
{
	Object *ret = _valueDict->objectForKey(key);
	if( ret ) {
		if( String *str=dynamic_cast<String*>(ret) )
			return str->getCString();

		CCASSERT(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

/** returns the value of a given key as a boolean */
bool Configuration::getBool( const char *key, bool default_value ) const
{
	Object *ret = _valueDict->objectForKey(key);
	if( ret ) {
		if( Bool *boolobj=dynamic_cast<Bool*>(ret) )
			return boolobj->getValue();
		if( String *strobj=dynamic_cast<String*>(ret) )
			return strobj->boolValue();
		CCASSERT(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

/** returns the value of a given key as a double */
double Configuration::getNumber( const char *key, double default_value ) const
{
	Object *ret = _valueDict->objectForKey(key);
	if( ret ) {
		if( Double *obj=dynamic_cast<Double*>(ret) )
			return obj->getValue();

		if( Integer *obj=dynamic_cast<Integer*>(ret) )
			return obj->getValue();

		if( String *strobj=dynamic_cast<String*>(ret) )
			return strobj->doubleValue();

		CCASSERT(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

Object * Configuration::getObject( const char *key ) const
{
	return _valueDict->objectForKey(key);
}

void Configuration::setObject( const char *key, Object *value )
{
	_valueDict->setObject(value, key);
}


//
// load file
//
void Configuration::loadConfigFile( const char *filename )
{
	Dictionary *dict = Dictionary::createWithContentsOfFile(filename);
	CCASSERT(dict, "cannot create dictionary");

	// search for metadata
	bool metadata_ok = false;
	Object *metadata = dict->objectForKey("metadata");
	if( metadata && dynamic_cast<Dictionary*>(metadata) ) {
		Object *format_o = static_cast<Dictionary*>(metadata)->objectForKey("format");

		// XXX: cocos2d-x returns Strings when importing from .plist. This bug will be addressed in cocos2d-x v3.x
		if( format_o && dynamic_cast<String*>(format_o) ) {
			int format = static_cast<String*>(format_o)->intValue();

			// Support format: 1
			if( format == 1 ) {
				metadata_ok = true;
			}
		}
	}

	if( ! metadata_ok ) {
		CCLOG("Invalid config format for file: %s", filename);
		return;
	}

	Object *data = dict->objectForKey("data");
	if( !data || !dynamic_cast<Dictionary*>(data) ) {
		CCLOG("Expected 'data' dict, but not found. Config file: %s", filename);
		return;
	}

	// Add all keys in the existing dictionary
	Dictionary *data_dict = static_cast<Dictionary*>(data);
    DictElement* element;
    CCDICT_FOREACH(data_dict, element)
    {
		if( ! _valueDict->objectForKey( element->getStrKey() ) )
			_valueDict->setObject(element->getObject(), element->getStrKey() );
		else
			CCLOG("Key already present. Ignoring '%s'", element->getStrKey() );
    }
}

NS_CC_END
