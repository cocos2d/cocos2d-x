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
 
#include "BlendStateMTL.h"

CC_BACKEND_BEGIN


namespace
{
    MTLColorWriteMask toMTLColorWriteMask(ColorWriteMask mask)
    {
        switch (mask) {
            case ColorWriteMask::NONE:
                return MTLColorWriteMaskNone;
            case ColorWriteMask::RED:
                return MTLColorWriteMaskRed;
            case ColorWriteMask::GREEN:
                return MTLColorWriteMaskGreen;
            case ColorWriteMask::BLUE:
                return MTLColorWriteMaskBlue;
            case ColorWriteMask::ALPHA:
                return MTLColorWriteMaskAlpha;
            case ColorWriteMask::ALL:
                return MTLColorWriteMaskAll;
        }
    }
    
    MTLBlendFactor toMTLBlendFactor(BlendFactor factor)
    {
        switch (factor) {
            case BlendFactor::ZERO:
                return MTLBlendFactorZero;
            case BlendFactor::ONE:
                return MTLBlendFactorOne;
            case BlendFactor::SRC_COLOR:
                return MTLBlendFactorSourceColor;
            case BlendFactor::ONE_MINUS_SRC_COLOR:
                return MTLBlendFactorOneMinusSourceColor;
            case BlendFactor::SRC_ALPHA:
                return MTLBlendFactorSourceAlpha;
            case BlendFactor::ONE_MINUS_SRC_ALPHA:
                return MTLBlendFactorOneMinusSourceAlpha;
            case BlendFactor::DST_COLOR:
                return MTLBlendFactorDestinationColor;
            case BlendFactor::ONE_MINUS_DST_COLOR:
                return MTLBlendFactorOneMinusDestinationColor;
            case BlendFactor::DST_ALPHA:
                return MTLBlendFactorDestinationAlpha;
            case BlendFactor::ONE_MINUS_DST_ALPHA:
                return MTLBlendFactorOneMinusDestinationAlpha;
            case BlendFactor::SRC_ALPHA_SATURATE:
                return MTLBlendFactorSourceAlphaSaturated;
            case BlendFactor::BLEND_CLOLOR:
                return MTLBlendFactorBlendColor;
        }
    }
    
    MTLBlendOperation toMTLBlendOperation(BlendOperation operation)
    {
        switch (operation) {
            case BlendOperation::ADD:
                return MTLBlendOperationAdd;
            case BlendOperation::SUBTRACT:
                return MTLBlendOperationSubtract;
            case BlendOperation::RESERVE_SUBTRACT:
                return MTLBlendOperationReverseSubtract;
        }
    }
}

BlendStateMTL::BlendStateMTL(const BlendDescriptor& descriptor)
{
    _blendDescriptorMTL.writeMask = toMTLColorWriteMask(descriptor.writeMask);
    _blendDescriptorMTL.blendEnabled = descriptor.blendEnabled;
    
    _blendDescriptorMTL.rgbBlendOperation = toMTLBlendOperation(descriptor.rgbBlendOperation);
    _blendDescriptorMTL.alphaBlendOperation = toMTLBlendOperation(descriptor.alphaBlendOperation);
    
    _blendDescriptorMTL.sourceRGBBlendFactor = toMTLBlendFactor(descriptor.sourceRGBBlendFactor);
    _blendDescriptorMTL.destinationRGBBlendFactor = toMTLBlendFactor(descriptor.destinationRGBBlendFactor);
    _blendDescriptorMTL.sourceAlphaBlendFactor = toMTLBlendFactor(descriptor.sourceAlphaBlendFactor);
    _blendDescriptorMTL.destinationAlphaBlendFactor = toMTLBlendFactor(descriptor.destinationAlphaBlendFactor);
}

CC_BACKEND_END
