//
// Created by NiTe Luo on 10/31/13.
//


#include "RenderCommand.h"

NS_CC_BEGIN

RenderCommand::RenderCommand()
{
    _id = 0;
    _type = UNKNOWN_COMMAND;
}

RenderCommand::~RenderCommand()
{
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