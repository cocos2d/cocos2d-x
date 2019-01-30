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
    
    MTLStencilDescriptor* toMTLStencilDescriptor(const StencilDescriptor& descriptor)
    {
        MTLStencilDescriptor* mtlDescriptor = [[MTLStencilDescriptor alloc] init];
        mtlDescriptor.stencilFailureOperation = toMTLStencilOperation(descriptor.stencilFailureOperation);
        mtlDescriptor.depthFailureOperation = toMTLStencilOperation(descriptor.depthFailureOperation);
        mtlDescriptor.depthStencilPassOperation = toMTLStencilOperation(descriptor.depthStencilPassOperation);
        mtlDescriptor.stencilCompareFunction = toMTLCompareFunction(descriptor.stencilCompareFunction);
        mtlDescriptor.readMask = descriptor.readMask;
        mtlDescriptor.writeMask = descriptor.writeMask;
        return mtlDescriptor;
    }
}

DepthStencilStateMTL::DepthStencilStateMTL(id<MTLDevice> mtlDevice, const DepthStencilDescriptor& descriptor)
: DepthStencilState(descriptor)
{
    if (!descriptor.depthTestEnabled && !descriptor.stencilTestEnabled && !descriptor.depthWriteEnabled)
        return;
    
    MTLDepthStencilDescriptor* mtlDescriptor = [[MTLDepthStencilDescriptor alloc] init];
    
    if (descriptor.depthTestEnabled || descriptor.depthWriteEnabled)
    {
        mtlDescriptor.depthWriteEnabled = descriptor.depthWriteEnabled;
        mtlDescriptor.depthCompareFunction = toMTLCompareFunction(descriptor.depthCompareFunction);
    }
    
    MTLStencilDescriptor* frontFaceStencil = nil;
    MTLStencilDescriptor* backFaceStencil = nil;
    if (descriptor.stencilTestEnabled)
    {
        frontFaceStencil = toMTLStencilDescriptor(descriptor.frontFaceStencil);
        backFaceStencil = toMTLStencilDescriptor(descriptor.backFaceStencil);
        
        mtlDescriptor.frontFaceStencil = frontFaceStencil;
        mtlDescriptor.backFaceStencil = backFaceStencil;
    }
    
    _mtlDepthStencilState = [mtlDevice newDepthStencilStateWithDescriptor:mtlDescriptor];
    [frontFaceStencil release];
    [backFaceStencil release];
    [mtlDescriptor release];
}

DepthStencilStateMTL::~DepthStencilStateMTL()
{
    [_mtlDepthStencilState release];
}

CC_BACKEND_END
