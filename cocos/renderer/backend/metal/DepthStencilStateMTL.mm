/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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
 
#include "DepthStencilStateMTL.h"

CC_BACKEND_BEGIN

namespace
{
    MTLCompareFunction toMTLCompareFunction(CompareFunction compareFunction)
    {
        MTLCompareFunction ret = MTLCompareFunctionNever;
        switch (compareFunction) {
            case CompareFunction::NEVER:
                ret = MTLCompareFunctionNever;
                break;
            case CompareFunction::LESS:
                ret = MTLCompareFunctionLess;
                break;
            case CompareFunction::LESS_EQUAL:
                ret = MTLCompareFunctionLessEqual;
                break;
            case CompareFunction::GREATER:
                ret = MTLCompareFunctionGreater;
                break;
            case CompareFunction::GREATER_EQUAL:
                ret = MTLCompareFunctionGreaterEqual;
                break;
            case CompareFunction::EQUAL:
                ret = MTLCompareFunctionEqual;
                break;
            case CompareFunction::NOT_EQUAL:
                ret = MTLCompareFunctionNotEqual;
                break;
            case CompareFunction::ALWAYS:
                ret = MTLCompareFunctionAlways;
                break;
            default:
                assert(false);
                break;
        }
        return ret;
    }
    
    MTLStencilOperation toMTLStencilOperation(StencilOperation operation)
    {
        MTLStencilOperation ret = MTLStencilOperationKeep;
        switch (operation) {
            case StencilOperation::KEEP:
                ret = MTLStencilOperationKeep;
                break;
            case StencilOperation::ZERO:
                ret = MTLStencilOperationZero;
                break;
            case StencilOperation::REPLACE:
                ret = MTLStencilOperationReplace;
                break;
            case StencilOperation::INVERT:
                ret = MTLStencilOperationInvert;
                break;
            case StencilOperation::INCREMENT_WRAP:
                ret = MTLStencilOperationIncrementWrap;
                break;
            case StencilOperation::DECREMENT_WRAP:
                ret = MTLStencilOperationDecrementWrap;
                break;
            default:
                assert(false);
                break;
        }
        return ret;
    }
    
    void setMTLStencilDescriptor(MTLStencilDescriptor* stencilDescriptor, const StencilDescriptor& descriptor)
    {
        stencilDescriptor.stencilFailureOperation = toMTLStencilOperation(descriptor.stencilFailureOperation);
        stencilDescriptor.depthFailureOperation = toMTLStencilOperation(descriptor.depthFailureOperation);
        stencilDescriptor.depthStencilPassOperation = toMTLStencilOperation(descriptor.depthStencilPassOperation);
        stencilDescriptor.stencilCompareFunction = toMTLCompareFunction(descriptor.stencilCompareFunction);
        stencilDescriptor.readMask = descriptor.readMask;
        stencilDescriptor.writeMask = descriptor.writeMask;
    }
}

DepthStencilStateMTL::DepthStencilStateMTL(id<MTLDevice> mtlDevice, const DepthStencilDescriptor& descriptor)
: DepthStencilState(descriptor)
{
    if (!descriptor.depthTestEnabled && !descriptor.stencilTestEnabled && !descriptor.depthWriteEnabled)
        return;
    
    MTLDepthStencilDescriptor* mtlDescriptor = [[MTLDepthStencilDescriptor alloc] init];

    if (descriptor.depthTestEnabled)
        mtlDescriptor.depthCompareFunction = toMTLCompareFunction(descriptor.depthCompareFunction);
    else
        mtlDescriptor.depthCompareFunction = MTLCompareFunctionAlways;

    mtlDescriptor.depthWriteEnabled = descriptor.depthWriteEnabled;

    if (descriptor.stencilTestEnabled)
    {
        setMTLStencilDescriptor(mtlDescriptor.frontFaceStencil, descriptor.frontFaceStencil);
        setMTLStencilDescriptor(mtlDescriptor.backFaceStencil, descriptor.backFaceStencil);
    }

    _mtlDepthStencilState = [mtlDevice newDepthStencilStateWithDescriptor:mtlDescriptor];
    [mtlDescriptor release];
}

DepthStencilStateMTL::~DepthStencilStateMTL()
{
    [_mtlDepthStencilState release];
}

CC_BACKEND_END
