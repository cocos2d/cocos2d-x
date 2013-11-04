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

void RenderCommand::setData(int viewport, bool isTranslucent, bool isCommand, int32_t depth)
{
    _viewport = viewport;
    _isTranslucent = isTranslucent;
    _isCommand = isCommand;
    _depth = depth;
}

void RenderCommand::setQuadData(kmMat4 *transform, V3F_C4B_T2F_Quad quad, GLuint textureID, int shaderID, int blendType)
{
    kmMat4Assign(&_transform, transform);
    _quad = quad;
    _textureID = textureID;
    _shaderID = shaderID;
    _blendType = blendType;
}

NS_CC_END