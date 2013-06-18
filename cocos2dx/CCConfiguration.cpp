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


CCConfiguration* CCConfiguration::s_gSharedConfiguration = NULL;

CCConfiguration::CCConfiguration(void)
: _maxTextureSize(0) 
, _maxModelviewStackDepth(0)
, _supportsPVRTC(false)
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

bool CCConfiguration::init(void)
{
	_valueDict = CCDictionary::create();
	_valueDict->retain();

	_valueDict->setObject( CCString::create( cocos2dVersion() ), "cocos2d.x.version");


#if CC_ENABLE_PROFILERS
	_valueDict->setObject( CCBool::create(true), "cocos2d.x.compiled_with_profiler");
#else
	_valueDict->setObject( CCBool::create(false), "cocos2d.x.compiled_with_profiler");
#endif

#if CC_ENABLE_GL_STATE_CACHE == 0
	_valueDict->setObject( CCBool::create(false), "cocos2d.x.compiled_with_gl_state_cache");
#else
	_valueDict->setObject( CCBool::create(true), "cocos2d.x.compiled_with_gl_state_cache");
#endif

	return true;
}

CCConfiguration::~CCConfiguration(void)
{
	_valueDict->release();
}

void CCConfiguration::dumpInfo(void) const
{
	// Dump
	CCPrettyPrinter visitor(0);
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

void CCConfiguration::gatherGPUInfo()
{
	_valueDict->setObject( CCString::create( (const char*)glGetString(GL_VENDOR)), "gl.vendor");
	_valueDict->setObject( CCString::create( (const char*)glGetString(GL_RENDERER)), "gl.renderer");
	_valueDict->setObject( CCString::create( (const char*)glGetString(GL_VERSION)), "gl.version");

    _glExtensions = (char *)glGetString(GL_EXTENSIONS);

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
	_valueDict->setObject( CCInteger::create((int)_maxTextureSize), "gl.max_texture_size");

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
	_valueDict->setObject( CCInteger::create((int)_maxTextureUnits), "gl.max_texture_units");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    glGetIntegerv(GL_MAX_SAMPLES_APPLE, &_maxSamplesAllowed);
	_valueDict->setObject( CCInteger::create((int)_maxSamplesAllowed), "gl.max_samples_allowed");
#endif

    _supportsPVRTC = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
	_valueDict->setObject( CCBool::create(_supportsPVRTC), "gl.supports_PVRTC");

    _supportsNPOT = true;
	_valueDict->setObject( CCBool::create(_supportsNPOT), "gl.supports_NPOT");
	
    _supportsBGRA8888 = checkForGLExtension("GL_IMG_texture_format_BGRA888");
	_valueDict->setObject( CCBool::create(_supportsBGRA8888), "gl.supports_BGRA8888");

    _supportsDiscardFramebuffer = checkForGLExtension("GL_EXT_discard_framebuffer");
	_valueDict->setObject( CCBool::create(_supportsDiscardFramebuffer), "gl.supports_discard_framebuffer");

    _supportsShareableVAO = checkForGLExtension("vertex_array_object");
	_valueDict->setObject( CCBool::create(_supportsShareableVAO), "gl.supports_vertex_array_object");
    
    CHECK_GL_ERROR_DEBUG();
}

CCConfiguration* CCConfiguration::sharedConfiguration(void)
{
    if (! s_gSharedConfiguration)
    {
        s_gSharedConfiguration = new CCConfiguration();
        s_gSharedConfiguration->init();
    }
    
    return s_gSharedConfiguration;
}

void CCConfiguration::purgeConfiguration(void)
{
    CC_SAFE_RELEASE_NULL(s_gSharedConfiguration);
}

bool CCConfiguration::checkForGLExtension(const string &searchName) const
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
int CCConfiguration::getMaxTextureSize(void) const
{
	return _maxTextureSize;
}

int CCConfiguration::getMaxModelviewStackDepth(void) const
{
	return _maxModelviewStackDepth;
}

int CCConfiguration::getMaxTextureUnits(void) const
{
	return _maxTextureUnits;
}

bool CCConfiguration::supportsNPOT(void) const
{
	return _supportsNPOT;
}

bool CCConfiguration::supportsPVRTC(void) const
{
	return _supportsPVRTC;
}

bool CCConfiguration::supportsBGRA8888(void) const
{
	return _supportsBGRA8888;
}

bool CCConfiguration::supportsDiscardFramebuffer(void) const
{
	return _supportsDiscardFramebuffer;
}

bool CCConfiguration::supportsShareableVAO(void) const
{
	return _supportsShareableVAO;
}

//
// generic getters for properties
//
const char *CCConfiguration::getCString( const char *key, const char *default_value ) const
{
	CCObject *ret = _valueDict->objectForKey(key);
	if( ret ) {
		if( CCString *str=dynamic_cast<CCString*>(ret) )
			return str->getCString();

		CCAssert(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

/** returns the value of a given key as a boolean */
bool CCConfiguration::getBool( const char *key, bool default_value ) const
{
	CCObject *ret = _valueDict->objectForKey(key);
	if( ret ) {
		if( CCBool *boolobj=dynamic_cast<CCBool*>(ret) )
			return boolobj->getValue();
		if( CCString *strobj=dynamic_cast<CCString*>(ret) )
			return strobj->boolValue();
		CCAssert(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

/** returns the value of a given key as a double */
double CCConfiguration::getNumber( const char *key, double default_value ) const
{
	CCObject *ret = _valueDict->objectForKey(key);
	if( ret ) {
		if( CCDouble *obj=dynamic_cast<CCDouble*>(ret) )
			return obj->getValue();

		if( CCInteger *obj=dynamic_cast<CCInteger*>(ret) )
			return obj->getValue();

		if( CCString *strobj=dynamic_cast<CCString*>(ret) )
			return strobj->doubleValue();

		CCAssert(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

CCObject * CCConfiguration::getObject( const char *key ) const
{
	return _valueDict->objectForKey(key);
}

void CCConfiguration::setObject( const char *key, CCObject *value )
{
	_valueDict->setObject(value, key);
}


//
// load file
//
void CCConfiguration::loadConfigFile( const char *filename )
{
	CCDictionary *dict = CCDictionary::createWithContentsOfFile(filename);
	CCAssert(dict, "cannot create dictionary");

	// search for metadata
	bool metadata_ok = false;
	CCObject *metadata = dict->objectForKey("metadata");
	if( metadata && dynamic_cast<CCDictionary*>(metadata) ) {
		CCObject *format_o = static_cast<CCDictionary*>(metadata)->objectForKey("format");

		// XXX: cocos2d-x returns CCStrings when importing from .plist. This bug will be addressed in cocos2d-x v3.x
		if( format_o && dynamic_cast<CCString*>(format_o) ) {
			int format = static_cast<CCString*>(format_o)->intValue();

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

	CCObject *data = dict->objectForKey("data");
	if( !data || !dynamic_cast<CCDictionary*>(data) ) {
		CCLOG("Expected 'data' dict, but not found. Config file: %s", filename);
		return;
	}

	// Add all keys in the existing dictionary
	CCDictionary *data_dict = static_cast<CCDictionary*>(data);
    CCDictElement* element;
    CCDICT_FOREACH(data_dict, element)
    {
		if( ! _valueDict->objectForKey( element->getStrKey() ) )
			_valueDict->setObject(element->getObject(), element->getStrKey() );
		else
			CCLOG("Key already present. Ignoring '%s'", element->getStrKey() );
    }
}

NS_CC_END
