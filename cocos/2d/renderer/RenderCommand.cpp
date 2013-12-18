//
// Created by NiTe Luo on 10/31/13.
//


#include "RenderCommand.h"

NS_CC_BEGIN

RenderCommand::RenderCommand()
{
    _id = 0;
    _type = UNKNOWN_COMMAND;
    
    _viewport = 0;
    _depth = CC_RENDERER_DEPTH_HALF;
}

RenderCommand::~RenderCommand()
{
}

void RenderCommand::init(int viewport, float depth)
{
    _viewport = viewport;
    
    //convert depth from float to unsigned int
    //currently we only support 2 digits after decimal point
    _depth = depth * 100 + CC_RENDERER_DEPTH_HALF;
    _depth = MIN(_depth, CC_RENDERER_DEPTH_MAX);
    _depth = MAX(_depth, CC_RENDERER_DEPTH_MIN);
}

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=(int)size-1;i>=0;i--)
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
    printBits(sizeof(_id), &_id);
    printf("\n");
}

NS_CC_END