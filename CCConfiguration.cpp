#include "include/CCConfiguration.h"
#include "include/ccMarcros.h"
#include "include/ccConfig.h"

using namespace std;

// singleton stuff
static CCConfiguration *g_pSharedConfiguration;
static char *g_pGlExtensions;

CCConfiguration::CCConfiguration()
{
	CCLOG("cocos2d: GL_VENDOR:     %s", glGetString(GL_VENDOR));
	CCLOG("cocos2d: GL_RENDERER:   %s", glGetString(GL_RENDERER));
	CCLOG("cocos2d: GL_VERSION:    %s", glGetString(GL_VERSION));

	g_pGlExtensions = (char *)glGetString(GL_EXTENSIONS);

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_nMaxTextureSize);
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &m_nMaxModelviewStackDepth);

	m_bSupportsPVRTC = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
	m_bSupportsNPOT = checkForGLExtension("GL_APPLE_texture_2D_limited_npot");
	m_bSupportsBGRA8888 = checkForGLExtension("GL_IMG_texture_format_BGRA888");
	m_bSupportsDiscardFramebuffer = checkForGLExtension("GL_EXT_discard_framebuffer");

	CCLOG("cocos2d: GL_MAX_TEXTURE_SIZE: %d", m_nMaxTextureSize);
	CCLOG("cocos2d: GL_MAX_MODELVIEW_STACK_DEPTH: %d",m_nMaxModelviewStackDepth);
	CCLOG("cocos2d: GL supports PVRTC: %s", (m_bSupportsPVRTC ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports BGRA8888 textures: %s", (m_bSupportsBGRA8888 ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports NPOT textures: %s", (m_bSupportsNPOT ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports discard_framebuffer: %s", (m_bSupportsDiscardFramebuffer ? "YES" : "NO"));
	CCLOG("cocos2d: compiled with NPOT support: %s",
#if CC_TEXTURE_NPOT_SUPPORT
				"YES"
#else
				"NO"
#endif // CC_TEXTURE_NPOT_SUPPORT 
			  );

	CCLOG("cocos2d: compiled with VBO support in TextureAtlas : %s",
#if CC_TEXTURE_ATLAS_USES_VBO
			  "YES"
#else
			  "NO"
#endif // CC_TEXTURE_ATLAS_USES_VBO
			  );
}

CCConfiguration* CCConfiguration::sharedConfiguration
{
	if (! g_pSharedConfiguration)
	{
		g_pSharedConfiguration = new CCConfiguration();
	}

	return g_pSharedConfiguration;
}

BOOL CCConfiguration::checkForGLExtensiton(const string &searchName)
{
	
}
