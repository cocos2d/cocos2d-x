/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.
 
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

#include "CCSpriteV2.h"
#include "renderer/CCTextureCache.h"
#include "base/CCDirector.h"
#include "2d/CCSpriteFrameCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccShaders.h"

namespace creator {
    
class simpleQuadGenerator
{
public:
    std::vector<cocos2d::V3F_C4B_T2F_Quad> _rebuildQuads_base(cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize, const cocos2d::Color4B& colorOpacity, bool isTrimmedContentSize) {
        std::vector<cocos2d::V3F_C4B_T2F_Quad> quads;
        //build vertices
        auto vertices = this->_calculateVertices(spriteFrame, contentSize, isTrimmedContentSize);
        
        //build uvs
        auto uvs = this->_calculateUVs(spriteFrame);
        
        //build quads
        quads.resize(1);
        auto& quad = quads[0];
        
        quad.bl.colors = colorOpacity;
        quad.br.colors = colorOpacity;
        quad.tl.colors = colorOpacity;
        quad.tr.colors = colorOpacity;
        
        quad.bl.vertices = cocos2d::Vec3(vertices[0].x, vertices[0].y, 0);
        quad.br.vertices = cocos2d::Vec3(vertices[1].x, vertices[0].y, 0);
        quad.tl.vertices = cocos2d::Vec3(vertices[0].x, vertices[1].y, 0);
        quad.tr.vertices = cocos2d::Vec3(vertices[1].x, vertices[1].y, 0);
        
        if (!spriteFrame->isRotated()) {
            quad.bl.texCoords = cocos2d::Tex2F(uvs[0].x, uvs[0].y);
            quad.br.texCoords = cocos2d::Tex2F(uvs[1].x, uvs[0].y);
            quad.tl.texCoords = cocos2d::Tex2F(uvs[0].x, uvs[1].y);
            quad.tr.texCoords = cocos2d::Tex2F(uvs[1].x, uvs[1].y);
        } else {
            quad.bl.texCoords = cocos2d::Tex2F(uvs[0].x, uvs[1].y);
            quad.br.texCoords = cocos2d::Tex2F(uvs[0].x, uvs[0].y);
            quad.tl.texCoords = cocos2d::Tex2F(uvs[1].x, uvs[1].y);
            quad.tr.texCoords = cocos2d::Tex2F(uvs[1].x, uvs[0].y);
        }
        
        return quads;
    }
    
    std::vector<cocos2d::Vec2> _calculateVertices(cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize, bool isTrimmedContentSize) {
        float x0, x3;
        float y0, y3;
        if (isTrimmedContentSize) {
            x0 = 0;
            x3 = contentSize.width;
            
            y0 = 0;
            y3 = contentSize.height;
        } else {
            auto originalSize = spriteFrame->getOriginalSize();
            auto rect = spriteFrame->getRect();
            auto offset = spriteFrame->getOffset();
            auto scaleX = contentSize.width / originalSize.width;
            auto scaleY = contentSize.height / originalSize.height;
            auto trimmLeft = offset.x + (originalSize.width - rect.size.width) / 2;
            auto trimmRight = offset.x - (originalSize.width - rect.size.width) / 2;
            auto trimmedBottom = offset.y + (originalSize.height - rect.size.height) / 2;
            auto trimmedTop = offset.y - (originalSize.height - rect.size.height) / 2;
            
            x0 = trimmLeft * scaleX;
            x3 = contentSize.width + trimmRight * scaleX;
            y0 = trimmedBottom * scaleY;
            y3 = contentSize.height + trimmedTop * scaleY;
        }
        
        std::vector<cocos2d::Vec2> vertices(2);
        vertices[0] = cocos2d::Vec2(x0,y0);
        vertices[1] = cocos2d::Vec2(x3,y3);
        
        return vertices;
    };
    
    std::vector<cocos2d::Vec2> _calculateUVs(cocos2d::SpriteFrame* spriteFrame) {
        auto atlasWidth = spriteFrame->getTexture()->getPixelsWide();
        auto atlasHeight = spriteFrame->getTexture()->getPixelsHigh();
        
        auto textureRect = spriteFrame->getRectInPixels();
        
        //uv computation should take spritesheet into account.
        float u0, u3;
        float v0, v3;
        float texStrech = 0;
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        texStrech = 0.5;
#endif
        if (spriteFrame->isRotated()) {
            u0 = (textureRect.origin.x + texStrech) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.height - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.width - texStrech) / atlasHeight;
        }
        else {
            u0 = (textureRect.origin.x + texStrech) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.width - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.height - texStrech) / atlasHeight;
        }
        
        std::vector<cocos2d::Vec2> uvCoordinates(2);
        uvCoordinates[0] = cocos2d::Vec2(u0, v3);
        uvCoordinates[1] = cocos2d::Vec2(u3, v0);
        
        return uvCoordinates;
    }
};

class scale9QuadGenerator
{
public:
    std::vector<cocos2d::V3F_C4B_T2F_Quad> _rebuildQuads_base(cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize, const cocos2d::Color4B& colorOpacity, float insetLeft, float insetRight, float insetTop, float insetBottom) {
        std::vector<cocos2d::V3F_C4B_T2F_Quad> quads(9);
        //build vertices
        auto vertices = this->_calculateVertices(spriteFrame, contentSize, insetLeft, insetRight, insetTop, insetBottom);
        
        //build uvs
        auto uvs = this->_calculateUVs(spriteFrame, insetLeft, insetRight, insetTop, insetBottom);
        
        //build quads
        int quadIndex(0);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                auto& quad = quads[quadIndex++];
                quad.bl.colors = colorOpacity;
                quad.br.colors = colorOpacity;
                quad.tl.colors = colorOpacity;
                quad.tr.colors = colorOpacity;
                
                quad.bl.vertices = cocos2d::Vec3(vertices[i].x, vertices[j].y, 0);
                quad.br.vertices = cocos2d::Vec3(vertices[i + 1].x, vertices[j].y, 0);
                quad.tl.vertices = cocos2d::Vec3(vertices[i].x, vertices[j + 1].y, 0);
                quad.tr.vertices = cocos2d::Vec3(vertices[i + 1].x, vertices[j + 1].y, 0);
                
                if (!spriteFrame->isRotated()) {
                    quad.bl.texCoords = cocos2d::Tex2F(uvs[i].x, uvs[j].y);
                    quad.br.texCoords = cocos2d::Tex2F(uvs[i + 1].x, uvs[j].y);
                    quad.tl.texCoords = cocos2d::Tex2F(uvs[i].x, uvs[j + 1].y);
                    quad.tr.texCoords = cocos2d::Tex2F(uvs[i + 1].x, uvs[j + 1].y);
                } else {
                    quad.bl.texCoords = cocos2d::Tex2F(uvs[j].x, uvs[3 - i].y);
                    quad.br.texCoords = cocos2d::Tex2F(uvs[j].x, uvs[3 - (i + 1)].y);
                    quad.tl.texCoords = cocos2d::Tex2F(uvs[j + 1].x, uvs[3 - i].y);
                    quad.tr.texCoords = cocos2d::Tex2F(uvs[j + 1].x, uvs[3 - (i + 1)].y);
                }
            }
        }
        
        return quads;
    }
    
    std::vector<cocos2d::Vec2>  _calculateVertices(cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize, float insetLeft, float insetRight, float insetTop, float insetBottom) {
        float leftWidth, rightWidth;
        float topHeight, bottomHeight;
        
        auto rect = spriteFrame->getRect();
        leftWidth = insetLeft;
        rightWidth = insetRight;
        
        topHeight = insetTop;
        bottomHeight = insetBottom;
        
        auto preferSize = contentSize;
        auto sizableWidth = preferSize.width - leftWidth - rightWidth;
        auto sizableHeight = preferSize.height - topHeight - bottomHeight;
        auto xScale = preferSize.width / (leftWidth + rightWidth);
        auto yScale = preferSize.height / (topHeight + bottomHeight);
        xScale = xScale > 1 ? 1 : xScale;
        yScale = yScale > 1 ? 1 : yScale;
        sizableWidth = sizableWidth < 0 ? 0 : sizableWidth;
        sizableHeight = sizableHeight < 0 ? 0 : sizableHeight;
        float x0, x1, x2, x3;
        float y0, y1, y2, y3;
        x0 = 0;
        x1 = leftWidth * xScale;
        x2 = x1 + sizableWidth;
        x3 = preferSize.width;
        
        y0 = 0;
        y1 = bottomHeight * yScale;
        y2 = y1 + sizableHeight;
        y3 = preferSize.height;
        
        std::vector<cocos2d::Vec2> vertices(4);
        vertices[0] = cocos2d::Vec2(x0,y0);
        vertices[1] = cocos2d::Vec2(x1,y1);
        vertices[2] = cocos2d::Vec2(x2,y2);
        vertices[3] = cocos2d::Vec2(x3,y3);
        
        return vertices;
    }
    
    std::vector<cocos2d::Vec2> _calculateUVs(cocos2d::SpriteFrame* spriteFrame, float insetLeft, float insetRight, float insetTop, float insetBottom) {
        auto rect = spriteFrame->getRect();
        auto atlasWidth = spriteFrame->getTexture()->getPixelsWide();
        auto atlasHeight = spriteFrame->getTexture()->getPixelsHigh();
        
        //caculate texture coordinate
        float leftWidth, centerWidth, rightWidth;
        float topHeight, centerHeight, bottomHeight;
        leftWidth = insetLeft;
        rightWidth = insetRight;
        centerWidth = rect.size.width - leftWidth - rightWidth;
        
        topHeight = insetTop;
        bottomHeight = insetBottom;
        centerHeight = rect.size.height - topHeight - bottomHeight;
        
        auto textureRect = spriteFrame->getRectInPixels();
        
        //uv computation should take spritesheet into account.
        float u0, u1, u2, u3;
        float v0, v1, v2, v3;
        float texStrech = 0;
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        texStrech = 0.5;
#endif
        
        if (spriteFrame->isRotated()) {
            u0 = (textureRect.origin.x + texStrech) / atlasWidth;
            u1 = (bottomHeight + textureRect.origin.x) / atlasWidth;
            u2 = (bottomHeight + centerHeight + textureRect.origin.x) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.height - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v1 = (leftWidth + textureRect.origin.y) / atlasHeight;
            v2 = (leftWidth + centerWidth + textureRect.origin.y) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.width - texStrech) / atlasHeight;
        }
        else {
            u0 = (textureRect.origin.x + texStrech) / atlasWidth;
            u1 = (leftWidth + textureRect.origin.x) / atlasWidth;
            u2 = (leftWidth + centerWidth + textureRect.origin.x) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.width - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v1 = (topHeight + textureRect.origin.y) / atlasHeight;
            v2 = (topHeight + centerHeight + textureRect.origin.y) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.height - texStrech) / atlasHeight;
        }
        
        std::vector<cocos2d::Vec2> uvCoordinates(4);
        uvCoordinates[0] = cocos2d::Vec2(u0, v3);
        uvCoordinates[1] = cocos2d::Vec2(u1, v2);
        uvCoordinates[2] = cocos2d::Vec2(u2, v1);
        uvCoordinates[3] = cocos2d::Vec2(u3, v0);
        
        return uvCoordinates;
    }
};

class tiledQuadGenerator
{
public:
    std::vector<cocos2d::V3F_C4B_T2F_Quad> _rebuildQuads_base(cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize, const cocos2d::Color4B& colorOpacity) {
        std::vector<cocos2d::V3F_C4B_T2F_Quad> quads;
        
        //build uvs
        auto uvs = this->_calculateUVs(spriteFrame);
        auto u0 = uvs[0].x;
        auto v0 = uvs[0].y;
        auto u1 = uvs[1].x;
        auto v1 = uvs[1].y;
        auto rectWidth = spriteFrame->getRect().size.width;
        auto rectHeight = spriteFrame->getRect().size.height;
        //build quads
        auto hRepeat = contentSize.width / rectWidth;
        auto vRepeat = contentSize.height / rectHeight;
        
        int quadIndex = 0;
        if(ceilf(hRepeat) * ceilf(vRepeat) > (65536 / 4)) {
            CCLOGERROR("too many tiles, only 16384 tiles will be show");
        }
        quads.resize(fminf(ceilf(hRepeat) * ceilf(vRepeat), 65536 / 4));
        for (int hindex = 0; hindex < ceilf(hRepeat); ++hindex) {
            for (int vindex = 0; vindex < ceilf(vRepeat); ++vindex) {
                auto& quad = quads[quadIndex++];
    
                quad.bl.colors = colorOpacity;
                quad.br.colors = colorOpacity;
                quad.tl.colors = colorOpacity;
                quad.tr.colors = colorOpacity;
                
                quad.bl.vertices = cocos2d::Vec3(rectWidth * hindex, rectHeight * vindex, 0);
                quad.br.vertices = cocos2d::Vec3(rectWidth * fminf(hindex + 1, hRepeat), rectHeight * vindex, 0);
                quad.tl.vertices = cocos2d::Vec3(rectWidth * hindex, rectHeight * fminf(vindex + 1, vRepeat), 0);
                quad.tr.vertices = cocos2d::Vec3(rectWidth * fminf(hindex + 1, hRepeat), rectHeight * fminf(vindex + 1, vRepeat), 0);
                
                if (!spriteFrame->isRotated()) {
                    quad.bl.texCoords = cocos2d::Tex2F(u0, v0);
                    quad.br.texCoords = cocos2d::Tex2F(u0 + (u1 - u0) * fminf(1, hRepeat - hindex), v0);
                    quad.tl.texCoords = cocos2d::Tex2F(u0, v0 + (v1 - v0) * fminf(1, vRepeat - vindex));
                    quad.tr.texCoords = cocos2d::Tex2F(u0 + (u1 - u0) * fminf(1, hRepeat - hindex), v0 + (v1 - v0) * fminf(1, vRepeat - vindex));
                } else {
                    quad.bl.texCoords = cocos2d::Tex2F(u0, v1);
                    quad.br.texCoords = cocos2d::Tex2F(u0, v1 + (v0 - v1) * fminf(1, hRepeat - hindex));
                    quad.tl.texCoords = cocos2d::Tex2F(u0 + (u1 - u0) * fminf(1, vRepeat - vindex), v1);
                    quad.tr.texCoords = cocos2d::Tex2F(u0 + (u1 - u0) * fminf(1, vRepeat - vindex), v1 + (v0 - v1) * fminf(1, hRepeat - hindex));
                    
                }
                if(quadIndex >= quads.size()) break;
            }
        }
        return quads;
    }
    
    std::vector<cocos2d::Vec2> _calculateUVs (cocos2d::SpriteFrame* spriteFrame) {
        auto atlasWidth = spriteFrame->getTexture()->getPixelsWide();
        auto atlasHeight = spriteFrame->getTexture()->getPixelsHigh();
        
        auto textureRect = spriteFrame->getRectInPixels();
        
        //uv computation should take spritesheet into account.
        float u0, u3;
        float v0, v3;
        
        float texStrech = 0;
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        texStrech = 0.5;
#endif
        
        if (spriteFrame->isRotated()) {
            u0 = (textureRect.origin.x + texStrech) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.height - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.width - texStrech) / atlasHeight;
        }
        else {
            u0 = (textureRect.origin.x + texStrech)/ atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.width - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.height - texStrech) / atlasHeight;
        }
        
        std::vector<cocos2d::Vec2> uvCoordinates(2);
        uvCoordinates[0] = cocos2d::Vec2(u0, v3);
        uvCoordinates[1] = cocos2d::Vec2(u3, v0);
        
        return uvCoordinates;
    }
};

class fillQuadGeneratorBar
{
public:
    //percentage from 0 to 1;
    std::vector<cocos2d::V3F_C4B_T2F_Quad> _rebuildQuads_base(cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize, const cocos2d::Color4B& colorOpacity, SpriteV2::FillType fillType, float fillStart, float fillRange) {
        float fillEnd;
        //build vertices
        auto vertices = this->_calculateVertices(spriteFrame, contentSize);
        
        //build uvs
        auto uvs = this->_calculateUVs(spriteFrame);
        
        //build quads
        std::vector<cocos2d::V3F_C4B_T2F_Quad> quads(1);
        auto& quad = quads[0];
        
        quad.bl.colors = colorOpacity;
        quad.br.colors = colorOpacity;
        quad.tl.colors = colorOpacity;
        quad.tr.colors = colorOpacity;
        
        quad.bl.vertices.x = quad.tl.vertices.x = vertices[0].x;
        quad.br.vertices.x = quad.tr.vertices.x = vertices[1].x;
        
        quad.bl.vertices.y = quad.br.vertices.y = vertices[0].y;
        quad.tl.vertices.y = quad.tr.vertices.y = vertices[1].y;
        
        cocos2d::Tex2F quadUV[4];
        
        if (!spriteFrame->isRotated()) {
            quadUV[0] = cocos2d::Tex2F(uvs[0].x, uvs[0].y);
            quadUV[1] = cocos2d::Tex2F(uvs[1].x, uvs[0].y);
            quadUV[2] = cocos2d::Tex2F(uvs[0].x, uvs[1].y);
            quadUV[3] = cocos2d::Tex2F(uvs[1].x, uvs[1].y);
        } else {
            quadUV[0] = cocos2d::Tex2F(uvs[0].x, uvs[1].y);
            quadUV[1] = cocos2d::Tex2F(uvs[0].x, uvs[0].y);
            quadUV[2]= cocos2d::Tex2F(uvs[1].x, uvs[1].y);
            quadUV[3]= cocos2d::Tex2F(uvs[1].x, uvs[0].y);
        }
        
        //do clamp
        fillStart = fillStart > 1 ? 1 : fillStart;
        fillStart = fillStart < 0 ? 0 : fillStart;
        
        fillRange = fillRange < 0 ? 0 : fillRange;
        
        fillEnd = fillStart + fillRange;
        
        fillEnd = fillEnd > 1 ? 1 : fillEnd;
        
        float progressStart, progressEnd;
        switch (fillType) {
            case SpriteV2::FillType::HORIZONTAL:
                progressStart = vertices[0].x + (vertices[1].x - vertices[0].x) * fillStart;
                progressEnd = vertices[0].x + (vertices[1].x - vertices[0].x) * fillEnd;
                
                quad.bl.vertices.x = progressStart;
                quad.tl.vertices.x = progressStart;
                
                quad.br.vertices.x = progressEnd;
                quad.tr.vertices.x = progressEnd;
                
                quad.bl.texCoords.u = quadUV[0].u + (quadUV[1].u - quadUV[0].u) * fillStart;
                quad.bl.texCoords.v = quadUV[0].v + (quadUV[1].v - quadUV[0].v) * fillStart;
                
                quad.tl.texCoords.u = quadUV[2].u + (quadUV[3].u - quadUV[2].u) * fillStart;
                quad.tl.texCoords.v = quadUV[2].v + (quadUV[3].v - quadUV[2].v) * fillStart;
                
                quad.br.texCoords.u = quadUV[0].u + (quadUV[1].u - quadUV[0].u) * fillEnd;
                quad.br.texCoords.v = quadUV[0].v + (quadUV[1].v - quadUV[0].v) * fillEnd;
                
                quad.tr.texCoords.u = quadUV[2].u + (quadUV[3].u - quadUV[2].u) * fillEnd;
                quad.tr.texCoords.v = quadUV[2].v + (quadUV[3].v - quadUV[2].v) * fillEnd;
                break;
            case SpriteV2::FillType::VERTICAL:
                progressStart = vertices[0].y + (vertices[1].y - vertices[0].y) * fillStart;
                progressEnd = vertices[0].y + (vertices[1].y - vertices[0].y) * fillEnd;
                
                quad.bl.vertices.y = progressStart;
                quad.br.vertices.y = progressStart;
                
                quad.tl.vertices.y = progressEnd;
                quad.tr.vertices.y = progressEnd;
                
                quad.bl.texCoords.u = quadUV[0].u + (quadUV[2].u - quadUV[0].u) * fillStart;
                quad.bl.texCoords.v = quadUV[0].v + (quadUV[2].v - quadUV[0].v) * fillStart;
                
                quad.br.texCoords.u = quadUV[1].u + (quadUV[3].u - quadUV[1].u) * fillStart;
                quad.br.texCoords.v = quadUV[1].v + (quadUV[3].v - quadUV[1].v) * fillStart;
                
                quad.tl.texCoords.u = quadUV[0].u + (quadUV[2].u - quadUV[0].u) * fillEnd;
                quad.tl.texCoords.v = quadUV[0].v + (quadUV[2].v - quadUV[0].v) * fillEnd;
                
                quad.tr.texCoords.u = quadUV[1].u + (quadUV[3].u - quadUV[1].u) * fillEnd;
                quad.tr.texCoords.v = quadUV[1].v + (quadUV[3].v - quadUV[1].v) * fillEnd;
                break;
            default:
                cocos2d::log("Unrecognized fill type in bar fill");
                break;
        }
        
        return quads;
    }
    
    std::vector<cocos2d::Vec2> _calculateVertices  (cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize) {
        
        float x0,x3;
        float y0,y3;
        x0 = 0;
        x3 = contentSize.width;
        
        y0 = 0;
        y3 = contentSize.height;
        std::vector<cocos2d::Vec2> vertices(2);
        vertices[0] = cocos2d::Vec2(x0,y0);
        vertices[1] = cocos2d::Vec2(x3,y3);
        return vertices;
    }
    
    std::vector<cocos2d::Vec2> _calculateUVs(cocos2d::SpriteFrame* spriteFrame) {
        auto atlasWidth = spriteFrame->getTexture()->getPixelsWide();
        auto atlasHeight = spriteFrame->getTexture()->getPixelsHigh();
        
        auto textureRect = spriteFrame->getRectInPixels();
        
        //uv computation should take spritesheet into account.
        float u0, u3;
        float v0, v3;
        
        float texStrech = 0;
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        texStrech = 0.5;
#endif
        
        if (spriteFrame->isRotated()) {
            u0 = (textureRect.origin.x + texStrech)/ atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.height - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.width - texStrech) / atlasHeight;
        }
        else {
            u0 = (textureRect.origin.x + texStrech) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.width - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.height - texStrech) / atlasHeight;
        }
        std::vector<cocos2d::Vec2> uvs(2);
        uvs[0] = cocos2d::Vec2(u0,v3);
        uvs[1] = cocos2d::Vec2(u3,v0);
        return uvs;
    }
};

class fillQuadGeneratorRadial
{
private:
    cocos2d::Vec2 _vertPos[4];
    cocos2d::Vec2 _vertices[2];
    cocos2d::Vec2 _uvs[2];
    std::vector<cocos2d::Vec2> _intersectPoint_1;
    std::vector<cocos2d::Vec2>  _intersectPoint_2;
public:
    fillQuadGeneratorRadial() {
        _intersectPoint_1.resize(4);
        _intersectPoint_2.resize(4);
        
    }
    
    std::vector<cocos2d::V3F_C4B_T2F_Quad> _rebuildQuads_base(cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize, const cocos2d::Color4B& colorOpacity, const cocos2d::Vec2& fillCenter, float fillStart, float fillRange, cocos2d::V3F_C4B_T2F_Quad& rawQuad) {
        
        //do round fill start [0,1), include 0, exclude 1
        while (fillStart >= 1.0) fillStart -= 1.0;
        while (fillStart < 0.0) fillStart += 1.0;
        
        auto center = cocos2d::Vec2(fillCenter);
        
        center.x *= contentSize.width;
        center.y *= contentSize.height;
        
        fillStart *= M_PI * 2;
        fillRange *= M_PI * 2;
        float fillEnd = fillStart + fillRange;
        
        //build vertices
        this->_calculateVertices(spriteFrame, contentSize);
        //build uvs
        this->_calculateUVs(spriteFrame);
        
        this->_vertPos[0].x = this->_vertPos[3].x = this->_vertices[0].x;
        this->_vertPos[1].x = this->_vertPos[2].x = this->_vertices[1].x;
        this->_vertPos[0].y = this->_vertPos[1].y = this->_vertices[0].y;
        this->_vertPos[2].y = this->_vertPos[3].y = this->_vertices[1].y;
        
        //fallback
        //todo remove it if outside is implemented
        if(center.x > this->_vertices[1].x) {
            center.x = this->_vertices[1].x;
        }
        if(center.x < this->_vertices[0].x) {
            center.x = this->_vertices[0].x;
        }
        if(center.y < this->_vertices[0].y) {
            center.y = this->_vertices[0].y;
        }
        if(center.y > this->_vertices[1].y) {
            center.y = this->_vertices[1].y;
        }
        
        rawQuad.bl.colors = colorOpacity;
        rawQuad.br.colors = colorOpacity;
        rawQuad.tl.colors = colorOpacity;
        rawQuad.tr.colors = colorOpacity;
        
        rawQuad.bl.vertices.x = rawQuad.tl.vertices.x = this->_vertices[0].x;
        rawQuad.br.vertices.x = rawQuad.tr.vertices.x = this->_vertices[1].x;
        
        rawQuad.bl.vertices.y = rawQuad.br.vertices.y = this->_vertices[0].y;
        rawQuad.tl.vertices.y = rawQuad.tr.vertices.y = this->_vertices[1].y;
        
        
        if (!spriteFrame->isRotated()) {
            rawQuad.bl.texCoords.u = rawQuad.tl.texCoords.u = this->_uvs[0].x;
            rawQuad.bl.texCoords.v = rawQuad.br.texCoords.v = this->_uvs[0].y;
            rawQuad.br.texCoords.u = rawQuad.tr.texCoords.u = this->_uvs[1].x;
            rawQuad.tl.texCoords.v = rawQuad.tr.texCoords.v = this->_uvs[1].y;
            
        } else {
            rawQuad.bl.texCoords.u = rawQuad.br.texCoords.u = this->_uvs[0].x;
            rawQuad.tl.texCoords.u = rawQuad.tr.texCoords.u = this->_uvs[1].x;
            rawQuad.br.texCoords.v = rawQuad.tr.texCoords.v = this->_uvs[0].y;
            rawQuad.bl.texCoords.v = rawQuad.tl.texCoords.v = this->_uvs[1].y;
            
        }
        
        int triangles[4][2] = {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}};
        
        if(center.x != this->_vertices[0].x) {
            triangles[0][0] = 3;
            triangles[0][1] = 0;
        }
        if(center.x != this->_vertices[1].x) {
            triangles[2][0] = 1;
            triangles[2][1] = 2;
        }
        if(center.y != this->_vertices[0].y) {
            triangles[1][0] = 0;
            triangles[1][1] = 1;
        }
        if(center.y != this->_vertices[1].y) {
            triangles[3][0] = 2;
            triangles[3][1] = 3;
            
        }
        
        this->_getInsectedPoints(this->_vertices[0].x, this->_vertices[1].x, this->_vertices[0].y, this->_vertices[1].y, center, fillStart, this->_intersectPoint_1);
        this->_getInsectedPoints(this->_vertices[0].x, this->_vertices[1].x, this->_vertices[0].y, this->_vertices[1].y, center, fillStart + fillRange, this->_intersectPoint_2);
        
        std::vector<cocos2d::V3F_C4B_T2F_Quad> quads;
        
        for(int triangleIndex = 0; triangleIndex < 4; ++triangleIndex ) {
            auto& triangle = triangles[triangleIndex];
            if(triangle[0] == -1 || triangle[1] == -1) {
                continue;
            }
            //all in
            if(fillRange >= M_PI * 2) {
                quads.push_back(this->_generateTriangle(rawQuad, center, this->_vertPos[triangle[0]], this->_vertPos[triangle[1]],colorOpacity));
                continue;
            }
            //test against
            auto startAngle = this->_getVertAngle(center,this->_vertPos[triangle[0]]);
            auto endAngle = this->_getVertAngle(center,this->_vertPos[triangle[1]]);
            if(endAngle < startAngle) endAngle += M_PI * 2;
            startAngle -= M_PI * 2;
            endAngle -= M_PI * 2;
            //testing
            for(int testIndex = 0; testIndex < 3; ++testIndex) {
                if(startAngle >= fillEnd) {
                    //all out
                } else if (startAngle >= fillStart) {
                    if(endAngle >= fillEnd) {
                        //startAngle to fillEnd
                        quads.push_back(this->_generateTriangle(rawQuad, center, this->_vertPos[triangle[0]], this->_intersectPoint_2[triangleIndex],colorOpacity));
                    } else {
                        //startAngle to endAngle
                        quads.push_back(this->_generateTriangle(rawQuad, center, this->_vertPos[triangle[0]], this->_vertPos[triangle[1]],colorOpacity));
                    }
                } else {
                    //startAngle < fillStart
                    if(endAngle <= fillStart) {
                        //all out
                    } else if(endAngle <= fillEnd) {
                        //fillStart to endAngle
                        quads.push_back(this->_generateTriangle(rawQuad, center, this->_intersectPoint_1[triangleIndex], this->_vertPos[triangle[1]],colorOpacity));
                    } else {
                        //fillStart to fillEnd
                        quads.push_back(this->_generateTriangle(rawQuad, center, this->_intersectPoint_1[triangleIndex], this->_intersectPoint_2[triangleIndex],colorOpacity));
                    }
                }
                
                //add 2 * PI
                startAngle += M_PI * 2;
                endAngle += M_PI * 2;
            }
            
        }
        
        return quads;
    }
    
    cocos2d::V3F_C4B_T2F_Quad _generateTriangle(const cocos2d::V3F_C4B_T2F_Quad& rawQuad, const cocos2d::Vec2& vert0, const cocos2d::Vec2& vert1, const cocos2d::Vec2& vert2 , const cocos2d::Color4B& colorOpacity) {
        const auto& rawQuad_bl = rawQuad.bl;
        const auto& rawQuad_br = rawQuad.br;
        const auto& rawQuad_tl = rawQuad.tl;
        const auto& rawQuad_tr = rawQuad.tr;
        
        auto v0x = rawQuad_bl.vertices.x;
        auto v0y = rawQuad_bl.vertices.y;
        auto v1x = rawQuad_tr.vertices.x;
        auto v1y = rawQuad_tr.vertices.y;
        float progressX, progressY;
        cocos2d::V3F_C4B_T2F_Quad quad;
        quad.tl.vertices.x  = vert0.x;
        quad.tl.vertices.y  = vert0.y;
        
        quad.bl.vertices.x  = vert1.x;
        quad.bl.vertices.y  = vert1.y;
        
        quad.tr.vertices.x  = vert2.x;
        quad.tr.vertices.y  = vert2.y;
        quad.tl.colors = colorOpacity;
        quad.bl.colors = colorOpacity;
        quad.tr.colors = colorOpacity;
        
        progressX = (vert0.x - v0x) / (v1x - v0x);
        progressY = (vert0.y - v0y) / (v1y - v0y);
        this->_generateUV(progressX, progressY, rawQuad_bl.texCoords,rawQuad_br.texCoords,rawQuad_tr.texCoords,rawQuad_tl.texCoords, quad.tl.texCoords);
        
        progressX = (vert1.x - v0x) / (v1x - v0x);
        progressY = (vert1.y - v0y) / (v1y - v0y);
        this->_generateUV(progressX, progressY, rawQuad_bl.texCoords,rawQuad_br.texCoords,rawQuad_tr.texCoords,rawQuad_tl.texCoords,quad.bl.texCoords);
        
        progressX = (vert2.x - v0x) / (v1x - v0x);
        progressY = (vert2.y - v0y) / (v1y - v0y);
        this->_generateUV(progressX, progressY, rawQuad_bl.texCoords,rawQuad_br.texCoords,rawQuad_tr.texCoords,rawQuad_tl.texCoords,quad.tr.texCoords);
        
        return quad;
    }
    
    bool _isAngleIn (float angle, float start, float rangeAngle) {
        auto pi_2 = M_PI * 2;
        while(angle < start || angle >= start + pi_2) {
            if(angle < start) {
                angle += pi_2;
            }
            if(angle >= start + pi_2) {
                angle -= pi_2;
            }
        }
        
        return angle <= start + rangeAngle;
    }
    
    //[0,PI * 2)
    float _getVertAngle(const cocos2d::Vec2& start, const cocos2d::Vec2& end) {
        float placementX, placementY;
        placementX = end.x - start.x;
        placementY = end.y - start.y;
        
        if(placementX == 0 && placementY == 0) {
            return FLT_MAX;
        } else if(placementX == 0) {
            if(placementY > 0) {
                return M_PI * 0.5;
            } else {
                return M_PI * 1.5;
            }
        } else {
            float angle = atanf(placementY / placementX);
            if(placementX < 0) {
                angle += M_PI;
            }
            
            return angle;
        }
    }
    
    void _getInsectedPoints(float left, float right, float bottom, float top, const cocos2d::Vec2& center, float angle, std::vector<cocos2d::Vec2> &intersectPoints) {
        //left bottom, right, top
        auto sinAngle = sinf(angle);
        auto cosAngle = cosf(angle);
        float tanAngle,cotAngle;
        if(cosf(angle) != 0) {
            tanAngle = sinAngle / cosAngle;
            //calculate right and left
            if((left - center.x) * cosAngle > 0) {
                auto yleft = center.y + tanAngle * (left - center.x);
                intersectPoints[0].x = left;
                intersectPoints[0].y = yleft;
            }
            if((right - center.x) * cosAngle > 0) {
                auto yright = center.y + tanAngle * (right - center.x);
                
                intersectPoints[2].x = right;
                intersectPoints[2].y = yright;
            }
            
        }
        
        if(sinf(angle) != 0) {
            cotAngle = cosAngle / sinAngle;
            //calculate  top and bottom
            if((top - center.y) * sinAngle > 0) {
                auto xtop = center.x  + cotAngle * (top-center.y);
                intersectPoints[3].x = xtop;
                intersectPoints[3].y = top;
            }
            if((bottom - center.y) * sinAngle > 0) {
                auto xbottom = center.x  + cotAngle * (bottom-center.y);
                intersectPoints[1].x = xbottom;
                intersectPoints[1].y = bottom;
            }
            
        }
    }
    
    void _generateUV (float progressX, float progressY, const cocos2d::Tex2F& uvbl, const cocos2d::Tex2F& uvbr, const cocos2d::Tex2F& uvtr, const cocos2d::Tex2F& uvtl, cocos2d::Tex2F& result) {
        auto px1 = uvbl.u + (uvbr.u-uvbl.u) * progressX;
        auto px2 = uvtl.u + (uvtr.u-uvtl.u) * progressX;
        auto py1 = uvbl.v + (uvbr.v-uvbl.v) * progressX;
        auto py2 = uvtl.v + (uvtr.v-uvtl.v) * progressX;
        result.u = px1 + (px2 - px1) * progressY;
        result.v = py1 + (py2 - py1) * progressY;
    }
    
    
    void _calculateVertices(cocos2d::SpriteFrame* spriteFrame, const cocos2d::Size& contentSize) {
        
        float x0,x3;
        float y0,y3;
        x0 = 0;
        x3 = contentSize.width;
        
        y0 = 0;
        y3 = contentSize.height;
        
        this->_vertices[0].x = x0;
        this->_vertices[0].y = y0;
        this->_vertices[1].x = x3;
        this->_vertices[1].y = y3;
    }
    
    void _calculateUVs(cocos2d::SpriteFrame* spriteFrame) {
        auto atlasWidth = spriteFrame->getTexture()->getPixelsWide();
        auto atlasHeight = spriteFrame->getTexture()->getPixelsHigh();
        
        auto textureRect = spriteFrame->getRectInPixels();
        
        //uv computation should take spritesheet into account.
        float u0, u3;
        float v0, v3;
        
        float texStrech = 0;
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        texStrech = 0.5;
#endif
        
        if (spriteFrame->isRotated()) {
            u0 = (textureRect.origin.x + texStrech) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.height - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.width - texStrech) / atlasHeight;
        }
        else {
            u0 = (textureRect.origin.x + texStrech) / atlasWidth;
            u3 = (textureRect.origin.x + textureRect.size.width - texStrech) / atlasWidth;
            
            v0 = (textureRect.origin.y + texStrech) / atlasHeight;
            v3 = (textureRect.origin.y + textureRect.size.height - texStrech) / atlasHeight;
        }
        
        this->_uvs[0].x = u0;
        this->_uvs[0].y = v3;
        this->_uvs[1].x = u3;
        this->_uvs[1].y = v0;
        
    }
};

static std::string distortionProgramKey = "cocos2d_creator_Scale9SpriteV2_distortionProgram";
    
//begin of Scale9 sprite implementation
SpriteV2::SpriteV2() :
_spriteFrame(nullptr),
_insetLeft(0),
_insetRight(0),
_insetTop(0),
_insetBottom(0),
_blendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED),
_renderingType(SpriteV2::RenderingType::SIMPLE),
_brightState(SpriteV2::State::NORMAL),
_quadsDirty(true),
_isTriangle(false),
_isTrimmedContentSize(true),
_fillType(SpriteV2::FillType::HORIZONTAL),
_fillCenter(cocos2d::Vec2::ZERO),
_distortionOffset(cocos2d::Vec2::ZERO),
_distortionTiling(cocos2d::Vec2::ONE),
_fillStart(0),
_fillRange(0),
_needRebuildRenderCommand(true)
{
    this->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    this->setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
}

SpriteV2::~SpriteV2() {
    CC_SAFE_RELEASE(this->_spriteFrame);
}

bool SpriteV2::setTexture(const std::string &textureFile)
{
    auto texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(textureFile);
    return texture && this->setTexture(texture);
}
//
bool SpriteV2::setTexture(cocos2d::Texture2D* texture)
{
    auto spriteFrame = cocos2d::SpriteFrame::createWithTexture(texture, cocos2d::Rect(0,0,texture->getPixelsWide(),texture->getPixelsHigh()));
    return spriteFrame && this->setSpriteFrame(spriteFrame);
}

bool SpriteV2::setSpriteFrame(const std::string& sfName)
{
    auto spriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName);
    return spriteFrame && this->setSpriteFrame(spriteFrame);
}

bool SpriteV2::setSpriteFrame(cocos2d::SpriteFrame* spriteFrame)
{
    if(!spriteFrame) return false;
    CC_SAFE_RELEASE(this->_spriteFrame);
    this->_spriteFrame = spriteFrame;
    CC_SAFE_RETAIN(spriteFrame);
    this->_quadsDirty = true;
    if(this->_contentSize.equals(cocos2d::Size::ZERO))
    {
        this->setContentSize(spriteFrame->getRect().size);
    }
    return true;
}

void SpriteV2::setBlendFunc(const cocos2d::BlendFunc& blendFunc) {
    this->setBlendFunc(blendFunc.src, blendFunc.dst);
}

void SpriteV2::setBlendFunc(GLenum src, GLenum dst) {
    this->_blendFunc.src = src;
    this->_blendFunc.dst = dst;
}

const cocos2d::BlendFunc& SpriteV2::getBlendFunc() const {
    return this->_blendFunc;
}

void SpriteV2::setContentSize(const cocos2d::Size &contentSize) {
    if(contentSize.equals(this->_contentSize)) return;
    Node::setContentSize(contentSize);
    this->_quadsDirty = true;
}

void SpriteV2::enableTrimmedContentSize(bool isTrimmed) {
    if (this->_isTrimmedContentSize != isTrimmed) {
        this->_isTrimmedContentSize = isTrimmed;
        this->_quadsDirty = true;
    }
}

void SpriteV2::setState(State state) {
    this->_brightState = state;
    auto programCache = cocos2d::GLProgramCache::getInstance();
    if(!programCache) return;
    if(SpriteV2::State::DISTORTION == state) {
        cocos2d::GLProgram* distortionProgram(nullptr);
            distortionProgram = programCache->getGLProgram(distortionProgramKey);
            if(!distortionProgram) {
                //TODO: add implementation;
                std::string fShader = "";
                fShader = fShader
                + "varying vec4 v_fragmentColor; \n"
                + "varying vec2 v_texCoord; \n"
                + "uniform vec2 u_offset; \n"
                + "uniform vec2 u_offset_tiling; \n"
                + "const float PI = 3.14159265359;\n"
                + "void main() \n"
                + "{ \n"
                + "float halfPI = 0.5 * PI;\n"
                + "float maxFactor = sin(halfPI);\n"
                + "vec2 uv = v_texCoord;\n"
                + "vec2 xy = 2.0 * uv.xy - 1.0;\n"
                + "float d = length(xy);\n"
                + "if (d < (2.0-maxFactor)) {\n"
                + "d = length(xy * maxFactor);\n"
                + "float z = sqrt(1.0 - d * d);\n"
                + " float r = atan(d, z) / PI;\n"
                + "float phi = atan(xy.y, xy.x);\n"
                + "uv.x = r * cos(phi) + 0.5;\n"
                + "uv.y = r * sin(phi) + 0.5;\n"
                + "} else {\n"
                + "discard;\n"
                + "}\n"
                + "uv = uv * u_offset_tiling + u_offset;\n"
                + "uv = fract(uv); \n"
                + "gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, uv);\n"
                + "}";
                
                distortionProgram = cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert, fShader.c_str());
                
                distortionProgram->link();
                programCache->addGLProgram(distortionProgram, distortionProgramKey);
        }
        
        if(distortionProgram) {
            auto glProgramState = cocos2d::GLProgramState::create(distortionProgram);
            glProgramState->setUniformVec2("u_offset", this->_distortionOffset);
            glProgramState->setUniformVec2("u_offset_tiling", this->_distortionTiling);
            this->setGLProgramState(glProgramState);
        }
    } else {
        auto program = programCache->getGLProgram(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
        this->setGLProgram(program);
    }
    

    
}

void SpriteV2::setRenderingType(RenderingType type) {
    if(this->_renderingType == type) return;
    this->_renderingType = type;
    this->_quadsDirty = true;
}

void SpriteV2::setInsetLeft(float value) {
    this->_insetLeft = value;
    this->_quadsDirty = true;
}

void SpriteV2::setInsetTop(float value) {
    this->_insetTop = value;
    this->_quadsDirty = true;
}

void SpriteV2::setInsetRight(float value) {
    this->_insetRight = value;
    this->_quadsDirty = true;
}

void SpriteV2::setInsetBottom(float value) {
    this->_insetBottom = value;
    this->_quadsDirty = true;
}

void SpriteV2::setFillType(FillType value) {
    if(this->_fillType == value) return;
    this->_fillType = value;
    if(this->_renderingType == RenderingType::FILLED) this->_quadsDirty = true;
}

void SpriteV2::setFillCenter(const cocos2d::Vec2& center) {
    setFillCenter(center.x, center.y);
}

void SpriteV2::setFillCenter(float x, float y) {
    this->_fillCenter.x = x;
    this->_fillCenter.y = y;
    if(this->_renderingType == RenderingType::FILLED && this->_fillType == FillType::RADIAL) this->_quadsDirty = true;
}

void SpriteV2::setFillStart(float value) {
    this->_fillStart = value;
    if(this->_renderingType == RenderingType::FILLED) this->_quadsDirty = true;
}

void SpriteV2::setFillRange(float value) {
    this->_fillRange = value;
    if(this->_renderingType == RenderingType::FILLED) this->_quadsDirty = true;
}

void SpriteV2::_rebuildQuads()
{
    if (this->_quadsDirty == false) return;
    cocos2d::Color4B color(this->getDisplayedColor());
    color.a = this->getDisplayedOpacity();
    this->_isTriangle = false;
    if (this->_renderingType == RenderingType::SIMPLE) {
        this->_quads = simpleQuadGenerator()._rebuildQuads_base(this->_spriteFrame, this->getContentSize(), color, this->_isTrimmedContentSize);
    } else if (this->_renderingType == RenderingType::SLICED) {
        this->_quads = scale9QuadGenerator()._rebuildQuads_base(this->_spriteFrame, this->getContentSize(), color, this->_insetLeft, this->_insetRight, this->_insetTop, this->_insetBottom);
    } else if (this->_renderingType == RenderingType::TILED) {
        this->_quads = tiledQuadGenerator()._rebuildQuads_base(this->_spriteFrame, this->getContentSize(), color);
    } else if (this->_renderingType == RenderingType::FILLED) {
        auto fillstart = this->_fillStart;
        auto fillRange = this->_fillRange;
        if(fillRange < 0) {
            fillstart += fillRange;
            fillRange = -fillRange;
        }
        if(this->_fillType != FillType::RADIAL) {
            fillRange = fillstart + fillRange;
            fillstart = fillstart > 1.0 ? 1.0 : fillstart;
            fillstart = fillstart < 0.0 ? 0.0 : fillstart;
            
            fillRange = fillRange > 1.0 ? 1.0 : fillRange;
            fillRange = fillRange < 0.0 ? 0.0 : fillRange;
            fillRange = fillRange - fillstart;
            this->_quads = fillQuadGeneratorBar()._rebuildQuads_base(this->_spriteFrame, this->getContentSize(), color, this->_fillType, fillstart,fillRange);
        } else {
            this->_isTriangle = true;
            this->_quads = fillQuadGeneratorRadial()._rebuildQuads_base(this->_spriteFrame, this->getContentSize(), color,this->_fillCenter,fillstart,fillRange, this->_rawQuad);
        }
    } else {
        this->_quads.clear();
        cocos2d::log("Can not generate quad");
    }
    this->_quadsDirty = false;
}

void SpriteV2::updateColor() {
    cocos2d::Color4B color(this->getDisplayedColor());
    color.a = this->getDisplayedOpacity();
    for (int index = 0; index < this->_quads.size(); ++index) {
        this->_quads[index].bl.colors = color;
        this->_quads[index].br.colors = color;
        this->_quads[index].tl.colors = color;
        this->_quads[index].tr.colors = color;
    }
    
    this->_needRebuildRenderCommand = true;
}

void SpriteV2::setDistortionOffset(const cocos2d::Vec2& v) {
    this->_distortionOffset = v;
    if(this->_brightState == SpriteV2::State::DISTORTION ) {
        _glProgramState->setUniformVec2("u_offset", v);
    }
}

void SpriteV2::setDistortionTiling(const cocos2d::Vec2& v) {
    this->_distortionTiling = v;
    if(this->_brightState == SpriteV2::State::DISTORTION ) {
        _glProgramState->setUniformVec2("u_offset_tiling", v);
    }
}

void SpriteV2::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
    if (!this->_spriteFrame || !this->_spriteFrame->getTexture()) {
        return;
    }
    
    if(this->_quadsDirty) {
        //rebuild quads
        this->_rebuildQuads();
        this->_needRebuildRenderCommand = true;
    }
    if(this->_needRebuildRenderCommand) {
        //fill triangles
        int vertsStep = this->_isTriangle ? 3 : 4;
        int indicesStep = this->_isTriangle ? 3 : 6;
        this->_verts.resize(_quads.size() * vertsStep);
        this->_indices.resize(_quads.size() * indicesStep);
        unsigned short indices[6];
        for(int index = 0; index < _quads.size(); ++index) {
            memcpy(&this->_verts[vertsStep * index], &this->_quads[index], sizeof(cocos2d::V3F_C4B_T2F) * vertsStep);
            if(this->_isTriangle) {
                indices[0] = indicesStep * index;
                indices[1] = indicesStep * index + 1;
                indices[2] = indicesStep * index + 2;
                
            } else {
                indices[0] = vertsStep * index;
                indices[1] = vertsStep * index + 1;
                indices[2] = vertsStep * index + 2;
                indices[3] = vertsStep * index + 3;
                indices[4] = vertsStep * index + 2;
                indices[5] = vertsStep * index + 1;
                
            }
            
            memcpy(&this->_indices[indicesStep * index], indices, sizeof(unsigned short) * indicesStep);
            
        }
        
        this->_needRebuildRenderCommand = false;
        
    }

	if (!_indices.empty() && !_verts.empty()) {
		cocos2d::TrianglesCommand::Triangles triangles;
		triangles.indices = &this->_indices[0];
		triangles.verts = &this->_verts[0];
		triangles.vertCount = this->_verts.size();
		triangles.indexCount = this->_indices.size();
		auto texture = this->_spriteFrame->getTexture();
		this->_renderCommand.init(_globalZOrder, texture->getName(), _glProgramState, _blendFunc, triangles, transform, 0);
		renderer->addCommand(&this->_renderCommand);
	}

}
    
}
