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

using namespace std;

//static const char *_configuration_GL_NPOT = "gl.suports_NPOT";
//static const char *_configuration_GL_BGRA8888 = "gl.supports_BGRA8888";

NS_CC_BEGIN


CCConfiguration* CCConfiguration::s_gSharedConfiguration = NULL;

CCConfiguration::CCConfiguration(void)
: m_nMaxTextureSize(0) 
, m_nMaxModelviewStackDepth(0)
, m_bSupportsPVRTC(false)
, m_bSupportsNPOT(false)
, m_bSupportsBGRA8888(false)
, m_bSupportsDiscardFramebuffer(false)
, m_bSupportsShareableVAO(false)
, m_nMaxSamplesAllowed(0)
, m_nMaxTextureUnits(0)
, m_pGlExtensions(NULL)
, m_pDefaults(NULL)
{
}

bool CCConfiguration::init(void)
{
	m_pDefaults = CCDictionary::create();

	m_pDefaults->setObject( CCString::create( cocos2dVersion() ), "cocos2d.version");

	return true;
}

CCConfiguration::~CCConfiguration(void)
{
	m_pDefaults->release();
}

void CCConfiguration::dumpInfo(void) const
{
	bool CC_UNUSED bEnableProfilers = false;

#if CC_ENABLE_PROFILERS
    bEnableProfilers = true;
#else
    bEnableProfilers = false;
#endif
    CCLOG("cocos2d: compiled with Profiling Support: %s",
		  bEnableProfilers ? "YES - *** Disable it when you finish profiling ***" : "NO");

#if CC_ENABLE_GL_STATE_CACHE == 0
    CCLOG("");
    CCLOG("cocos2d: **** WARNING **** CC_ENABLE_GL_STATE_CACHE is disabled. To improve performance, enable it by editing ccConfig.h");
    printf("\n");
#endif

//	CCDictElement* pElement = NULL;
//    CCDICT_FOREACH(m_pDefaults, pElement)
//    {
//        CCObject *obj = pElement->getObject();
//		const char *key = pElement->getStrKey();
//
//		printf("%s = %s\n", key, obj->getDescription()->getCString() );
//
//    }

	CCPrettyPrinter visitor(0);
	m_pDefaults->acceptVisitor(visitor);
	cout << visitor.getResult();

}

void CCConfiguration::gatherGPUInfo()
{
	m_pDefaults->setObject( new CCString( (const char*)glGetString(GL_VENDOR)), "gl.vendor");
	m_pDefaults->setObject( new CCString( (const char*)glGetString(GL_RENDERER)), "gl.renderer");
	m_pDefaults->setObject( new CCString( (const char*)glGetString(GL_VERSION)), "gl.version");

    m_pGlExtensions = (char *)glGetString(GL_EXTENSIONS);

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_nMaxTextureSize);
	m_pDefaults->setObject( new CCInteger((int)m_nMaxTextureSize), "gl.max_texture_size");

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_nMaxTextureUnits);
	m_pDefaults->setObject( new CCInteger((int)m_nMaxTextureUnits), "gl.max_texture_units");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    glGetIntegerv(GL_MAX_SAMPLES_APPLE, &m_nMaxSamplesAllowed);
	m_pDefaults->setObject( new CCInteger((int)m_nMaxSamplesAllowed), "gl.max_samples_allowed");
#endif

    m_bSupportsPVRTC = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
	m_pDefaults->setObject( new CCBool(m_bSupportsPVRTC), "gl.supports_PVRTC");

    m_bSupportsNPOT = true;
	m_pDefaults->setObject( new CCBool(m_bSupportsNPOT), "gl.supports_NPOT");
	
    m_bSupportsBGRA8888 = checkForGLExtension("GL_IMG_texture_format_BGRA888");
	m_pDefaults->setObject( new CCBool(m_bSupportsBGRA8888), "gl.supports_BGRA8888");

    m_bSupportsDiscardFramebuffer = checkForGLExtension("GL_EXT_discard_framebuffer");
	m_pDefaults->setObject( new CCBool(m_bSupportsDiscardFramebuffer), "gl.supports_discard_framebuffer");

    m_bSupportsShareableVAO = checkForGLExtension("vertex_array_object");
	m_pDefaults->setObject( new CCBool(m_bSupportsShareableVAO), "gl.supports_vertex_array_object");
    
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
    
    if (m_pGlExtensions && 
        strstr(m_pGlExtensions, kSearchName))
    {
        bRet = true;
    }
    
    return bRet;
}

/* getters for specific variables */
int CCConfiguration::getMaxTextureSize(void) const
{
	return m_nMaxTextureSize;
}

int CCConfiguration::getMaxModelviewStackDepth(void) const
{
	return m_nMaxModelviewStackDepth;
}

int CCConfiguration::getMaxTextureUnits(void) const
{
	return m_nMaxTextureUnits;
}

bool CCConfiguration::supportsNPOT(void) const
{
	return m_bSupportsNPOT;
}

bool CCConfiguration::supportsPVRTC(void) const
{
	return m_bSupportsPVRTC;
}

bool CCConfiguration::supportsBGRA8888(void) const
{
	return m_bSupportsBGRA8888;
}

bool CCConfiguration::supportsDiscardFramebuffer(void) const
{
	return m_bSupportsDiscardFramebuffer;
}

bool CCConfiguration::supportsShareableVAO(void) const
{
	return m_bSupportsShareableVAO;
}

const char *CCConfiguration::getCString( const char *key ) const
{
	CCObject *ret = m_pDefaults->objectForKey(key);
	if( ret )
		if( CCString *str=dynamic_cast<CCString*>(ret) )
			return str->getCString();
   return NULL;
}

/** returns the value of a given key as a boolean */
bool CCConfiguration::getBool( const char *key ) const
{
	CCObject *ret = m_pDefaults->objectForKey(key);
	if( ret )
		if( CCBool *obj=dynamic_cast<CCBool*>(ret) )
			return obj->getValue();
	return NULL;
}

/** returns the value of a given key as a double */
double CCConfiguration::getNumber( const char *key ) const
{
	CCObject *ret = m_pDefaults->objectForKey(key);
	if( ret ) {
		if( CCDouble *obj=dynamic_cast<CCDouble*>(ret) )
			return obj->getValue();

		if( CCInteger *obj=dynamic_cast<CCInteger*>(ret) )
			return obj->getValue();
	}

	return NULL;
}

ccConfigurationType CCConfiguration::getType( const char *key ) const
{
	return ConfigurationError;
}

NS_CC_END
