//
//  StringUtils.cpp
//  Test
//
//  Created by Cocos on 2018/11/2.
//  Copyright © 2018 cocos. All rights reserved.
//

#include "StringUtils.h"

CC_BACKEND_BEGIN

std::string StringUtils::TextureFormat2String(const TextureFormat& textureFormat)
{
    switch (textureFormat) {
        case TextureFormat::R8G8B8A8:
            return "R8G8B8A8";
        case TextureFormat::R8G8B8:
            return "R8G8B8";
        case TextureFormat::A8:
            return "A8";
        default:
            return "";
    }
}

std::string StringUtils::TextureType2String(const TextureType& textureType)
{
    switch (textureType) {
        case TextureType::TEXTURE_2D:
            return "TEXTURE_2D";
        case TextureType::TEXTURE_CUBE:
            return "TEXTURE_CUBE";
        default:
            return "";
    }
}

std::string StringUtils::TextureUsage2String(const TextureUsage& textureUsage)
{
    switch (textureUsage) {
        case TextureUsage::READ:
            return "READ";
        case TextureUsage::WRITE:
            return "WRITE";
        case TextureUsage::RENDER_TARGET:
            return "RENDER_TARGET";
        default:
            return "";
    }
}

std::string StringUtils::SamplerFilterType2String(const SamplerFilter& filterType)
{
    switch (filterType) {
        case SamplerFilter::LINEAR:
            return "LINEAR";
        case SamplerFilter::NEAREST:
            return "NEAREST";
        default:
            return "";
    }
}

std::string StringUtils::SamplerAddressMode2String(const SamplerAddressMode& addressMode)
{
    switch (addressMode) {
        case SamplerAddressMode::REPEAT:
            return "REPEAT";
        case SamplerAddressMode::MIRROR_REPEAT:
            return "MIRROR_REPEAT";
        case SamplerAddressMode::CLAMP_TO_EDGE:
            return "CLAMP_TO_EDGE";
        default:
            return "";
    }
}

std::string StringUtils::SamplerDescriptor2String(const SamplerDescriptor& descriptor)
{
    std::string samplerInfo = descriptor.mipmapEnabled ? "mipmapEnable":"mipmapDisable";
    samplerInfo += SamplerFilterType2String(descriptor.magFilter);
    samplerInfo += SamplerFilterType2String(descriptor.minFilter);
    samplerInfo += SamplerFilterType2String(descriptor.mipmapFilter);
    samplerInfo += SamplerAddressMode2String(descriptor.sAddressMode);
    samplerInfo += SamplerAddressMode2String(descriptor.tAddressMode);
    return samplerInfo;
}

std::string StringUtils::StencilOperation2String(const StencilOperation& operation)
{
    switch (operation) {
        case StencilOperation::KEEP:
            return "KEEP";
        case StencilOperation::ZERO:
            return "ZERO";
        case StencilOperation::REPLACE:
            return "REPLACE";
        case StencilOperation::INVERT:
            return "INVERT";
        case StencilOperation::INCREMENT_WRAP:
            return "INCREMENT_WRAP";
        case StencilOperation::DECREMENT_WRAP:
            return "DECREMENT_WRAP";
        default:
            return "";
    }
}

std::string StringUtils::CompareFunction2String(const CompareFunction& compareFunction)
{
    switch (compareFunction) {
        case CompareFunction::NEVER:
            return "NEVER";
        case CompareFunction::LESS:
            return "LESS";
        case CompareFunction::LESS_EQUAL:
            return "LESS_EQUAL";
        case CompareFunction::GREATER:
            return "GREATER";
        case CompareFunction::GREATER_EQUAL:
            return "GREATER_EQUAL";
        case CompareFunction::EQUAL:
            return "EQUAL";
        case CompareFunction::NOT_EQUAL:
            return "NOT_EQUAL";
        case CompareFunction::ALWAYS:
            return "ALWAYS";
        default:
            return "";
    }
}

std::string StringUtils::ColorWriteMask2String(const ColorWriteMask& colorWriteMask)
{
    switch (colorWriteMask) {
        case ColorWriteMask::NONE:
            return "NONE";
        case ColorWriteMask::RED:
            return "RED";
        case ColorWriteMask::GREEN:
            return "GREEN";
        case ColorWriteMask::BLUE:
            return "BLUE";
        case ColorWriteMask::ALPHA:
            return "ALPHA";
        case ColorWriteMask::ALL:
            return "ALL";
        default:
            return "";
    }
}

std::string StringUtils::BlendOperation2String(const BlendOperation& blendOperation)
{
    switch (blendOperation) {
        case BlendOperation::ADD:
            return "ADD";
        case BlendOperation::SUBTRACT:
            return "SUBTRACT";
        case BlendOperation::RESERVE_SUBTRACT:
            return "RESERVE_SUBTRACT";
        default:
            return "";
    }
}

std::string StringUtils::BlendFactor2String(const BlendFactor& blendFactor)
{
    switch (blendFactor) {
        case BlendFactor::ZERO:
            return "ZERO";
        case BlendFactor::ONE:
            return "ONE";
        case BlendFactor::SRC_COLOR:
            return "SRC_COLOR";
        case BlendFactor::ONE_MINUS_SRC_COLOR:
            return "ONE_MINUS_SRC_COLOR";
        case BlendFactor::SRC_ALPHA:
            return "SRC_ALPHA";
        case BlendFactor::ONE_MINUS_SRC_ALPHA:
            return "ONE_MINUS_SRC_ALPHA";
        case BlendFactor::DST_COLOR:
            return "DST_COLOR";
        case BlendFactor::ONE_MINUS_DST_COLOR:
            return "ONE_MINUS_DST_COLOR";
        case BlendFactor::DST_ALPHA:
            return "DST_ALPHA";
        case BlendFactor::ONE_MINUS_DST_ALPHA:
            return "ONE_MINUS_DST_ALPHA";
        case BlendFactor::SRC_ALPHA_SATURATE:
            return "SRC_ALPHA_SATURATE";
        case BlendFactor::BLEND_CLOLOR:
            return "BLEND_CLOLOR";
        default:
            return "";
    }
}

TextureFormat StringUtils::PixelFormat2TextureFormat(const PixelFormat& pixleFormat)
{
    switch (pixleFormat) {
        case PixelFormat::RGBA8888:
            return TextureFormat::R8G8B8A8;
        case PixelFormat::RGB888:
            return TextureFormat::R8G8B8;
        case PixelFormat::A8:
            return TextureFormat::A8;
        case PixelFormat::RGBA4444:
            return TextureFormat::RGBA4444;
        case PixelFormat::I8:
            return TextureFormat::I8;
        case PixelFormat::AI88:
            return TextureFormat::AI88;
        case PixelFormat::RGB565:
            return TextureFormat::RGB565;
        case PixelFormat::RGB5A1:
            return TextureFormat::RGB5A1;
        case PixelFormat::ETC:
            return TextureFormat::ETC1;
        case PixelFormat::ATC_RGB:
            return TextureFormat::ATC_RGB;
        case PixelFormat::ATC_EXPLICIT_ALPHA:
            return TextureFormat::ATC_EXPLICIT_ALPHA;
        case PixelFormat::ATC_INTERPOLATED_ALPHA:
            return TextureFormat::ATC_INTERPOLATED_ALPHA;
        case PixelFormat::PVRTC2:
            return TextureFormat::PVRTC2;
        case PixelFormat::PVRTC2A:
            return TextureFormat::PVRTC2A;
        case PixelFormat::PVRTC4:
            return TextureFormat::PVRTC4;
        case PixelFormat::PVRTC4A:
            return TextureFormat::PVRTC4A;
        case PixelFormat::S3TC_DXT1:
            return TextureFormat::S3TC_DXT1;
        case PixelFormat::S3TC_DXT3:
            return TextureFormat::S3TC_DXT3;
        case PixelFormat::S3TC_DXT5:
            return TextureFormat::S3TC_DXT5;
        case PixelFormat::MTL_ABGR4:
            return TextureFormat::MTL_ABGR4;
        case PixelFormat::MTL_BGR5A1:
            return TextureFormat::MTL_BGR5A1;
        case PixelFormat::MTL_B5G6R5:
            return TextureFormat::MTL_B5G6R5;
        default:
            return TextureFormat::NONE;
            break;
    }
}

CC_BACKEND_END
