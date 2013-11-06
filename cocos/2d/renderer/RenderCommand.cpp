//
// Created by NiTe Luo on 10/31/13.
//


#include "RenderCommand.h"

NS_CC_BEGIN

RenderCommand::RenderCommand()
:_viewport(0)
,_isTranslucent(false)
,_isCommand(false)
,_depth(0)
,_materialID(0)
{

}

void RenderCommand::generateID()
{
    _renderCommandId = 0;

    //Generate Material ID
    //TODO fix shader ID generation
    CCASSERT(_shaderID < 64, "ShaderID is greater than 64");
    //TODO fix texture ID generation
    CCASSERT(_textureID < 1024, "TextureID is greater than 1024");

    //TODO fix blend id generation
    int blendID = 0;
    if(_blendType == BlendFunc::DISABLE)
    {
        blendID = 0;
    }
    else if(_blendType == BlendFunc::ALPHA_PREMULTIPLIED)
    {
        blendID = 1;
    }
    else if(_blendType == BlendFunc::ALPHA_NON_PREMULTIPLIED)
    {
        blendID = 2;
    }
    else if(_blendType == BlendFunc::ADDITIVE)
    {
        blendID = 3;
    }
    else
    {
        blendID = 4;
    }

    _materialID = (int32_t)_shaderID << 28
                | (int32_t)blendID << 24
                | (int32_t)_textureID << 14;

    //Generate RenderCommandID
    _renderCommandId = (int64_t)_viewport << 61
                    | (int64_t)_isTranslucent << 60
                    | (int64_t)_isCommand << 59
                    | (int64_t)_depth << 35
                    | (int64_t)_materialID << 11;
}

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = b[i] & (1<<j);
            byte >>= j;
            printf("%u", byte);
        }
    }
    puts("");
}

void RenderCommand::printID()
{
    printf("CommandID: ");
    printBits(sizeof(_renderCommandId), &_renderCommandId);
    printf("\n");
}

void RenderCommand::setKeyData(int viewport, bool isTranslucent, bool isCommand, int32_t depth)
{
    _viewport = viewport;
    _isTranslucent = isTranslucent;
    _isCommand = isCommand;
    _depth = depth;
}

void RenderCommand::setMaterialData(GLuint textureID, GLuint shaderID, BlendFunc blendType)
{
    _textureID = textureID;
    _shaderID = shaderID;
    _blendType = blendType;
}

void RenderCommand::setQuadData(kmMat4 *transform, V3F_C4B_T2F_Quad quad)
{
    kmMat4Assign(&_transform, transform);
    _quad = quad;
}

NS_CC_END