#include "DeviceInfoGL.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

bool DeviceInfoGL::init()
{
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxAttributes);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
    
    return true;
}
CC_BACKEND_END
