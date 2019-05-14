#include "DeviceInfoGL.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

bool DeviceInfoGL::init()
{
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxAttributes);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
    _extensions = glGetString(GL_EXTENSIONS);
    return true;
}

const char* DeviceInfoGL::getVendor() const
{
    return glGetString(GL_VENDOR);
}
const char* DeviceInfoGL::getRenderer() const
{
    return glGetString(GL_RENDERER);
}

const char* DeviceInfoGL::getVersion() const
{
    return glGetString(GL_VERSION);
}

const char* DeviceInfoGL::getExtension() const
{
    return _extensions.c_str();
}

bool DeviceInfoGL::checkForFeatureSupported(const FeaturesInfo& feature)
{
    bool featureSupported = false;
    switch (feature)
    {
    case FeaturesInfo::ETC1:
#ifdef GL_ETC1_RGB8_OES //GL_ETC1_RGB8_OES is not defined in old opengl version
        featureSupported = checkForGLExtension("GL_OES_compressed_ETC1_RGB8_texture");
#endif
        break;
    case FeaturesInfo::S3TC:
#ifdef GL_EXT_texture_compression_s3tc
        featureSupported = checkForGLExtension("GL_EXT_texture_compression_s3tc");
#endif
        break;
    case FeaturesInfo::AMD_COMPRESSED_ATC:
        featureSupported = checkForGLExtension("GL_AMD_compressed_ATC_texture");
        break;
    case FeaturesInfo::PVRTC:
        featureSupported = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
        break;
    case FeaturesInfo::IMG_FORMAT_BGRA8888:
        featureSupported = checkForGLExtension("GL_IMG_texture_format_BGRA8888");
        break;
    case FeaturesInfo::DISCARD_FRAMEBUFFER:
        featureSupported = checkForGLExtension("GL_EXT_discard_framebuffer");
        break;
    case FeaturesInfo::PACKED_DEPTH_STENCIL:
        featureSupported = checkForGLExtension("GL_OES_packed_depth_stencil");
        break;
    case FeaturesInfo::VAO:
#ifdef CC_PLATFORM_PC
        featureSupported = checkForGLExtension("vertex_array_object");
#else
        featureSupported = checkForGLExtension("GL_OES_vertex_array_object");
#endif
        break;
    case FeaturesInfo::MAPBUFFER:
        featureSupported = checkForGLExtension("GL_OES_mapbuffer");
        break;
    case FeaturesInfo::DEPTH24:
        featureSupported = checkForGLExtension("GL_OES_depth24");
        break;
    default:
        break;
    }
    return featureSupported;
}

bool DeviceInfoGL::checkForGLExtension(const std::string &searchName) const
{
    return _glExtensions.find(searchName) != std::string::npos;
}

CC_BACKEND_END
