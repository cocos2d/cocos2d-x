/******************************************************************************
 * Spine Runtimes Software License
 * Version 2
 *
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software, you may not (a) modify, translate, adapt or
 * otherwise create derivative works, improvements of the Software or develop
 * new applications using the Software or (b) remove, delete, alter or obscure
 * any trademarks or any copyright, trademark, patent or other intellectual
 * property or proprietary rights notices on or in the Software, including
 * any copy thereof. Redistributions in binary or source form must include
 * this license and terms. THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

//
//  CCTriangleTextureAtlas.h
//  spine-cocos2d-iphone-ios
//
//  Created by Wojciech Trzasko CodingFingers on 24.02.2014.
//
#ifndef SPINE_CCTRIANGLETEXTUREATLAS_H_
#define SPINE_CCTRIANGLETEXTUREATLAS_H_

#include "CCTextureAtlas.h"

using namespace cocos2d;

typedef struct V3F_C4B_T2F_Triangle
{
	//! Point A
	V3F_C4B_T2F a;
	//! Point B
	V3F_C4B_T2F b;
	//! Point B
	V3F_C4B_T2F c;
} V3F_C4B_T2F_Triangle;

class TriangleTextureAtlas : public Ref
{
public:
    static TriangleTextureAtlas * createWithTexture(Texture2D * texture, ssize_t capacity);
    
public:
    TriangleTextureAtlas();
    virtual ~TriangleTextureAtlas();
    
    bool initWithTexture(Texture2D *texture, ssize_t capacity);
    void updateTrianglesIndices(int * indices, size_t length, size_t offset);
    void updateVertex(V3F_C4B_T2F * vertex, ssize_t atIndex);
    void updateVertices(V3F_C4B_T2F * vertices, ssize_t atIndex, ssize_t length);
    
    void removeAllVertices();
    void removeAllTriangles();
    void removeTrianglesFrom(ssize_t triangleNr);
    
    bool resizeCapacity(ssize_t n);
    
    /**
     * Streaming buffers
     */
    void transferBuffers();

    /**
     * Drawing methods
     */
    void drawTriangles();
    void drawTriangles(ssize_t n);
    void drawTriangles(ssize_t fromIndex, ssize_t triangleNr);

    // get sets
    ssize_t         getCapacity() const;
    ssize_t         getTotalTriangles() const;
    ssize_t         getTotalVertices() const;
    V3F_C4B_T2F     *getVertices();
    ssize_t         getCurrentTriangles() const;
    Texture2D       *getTexture();
    
    void            setCurrentTriangles(ssize_t n);
    
private:
    void            listenBackToForeground(EventCustom* event);

    
    void            setupIndices();
    void            mapBuffers();
    void            setupVBOandVAO();
    void            setupVBO();
    
protected:
    GLushort*           _indices;
    GLuint              _VAOname;
    GLuint              _buffersVBO[2]; //0: vertex  1: indices

    /** quantity of quads that can be stored with the current texture atlas size */
    ssize_t _capacity;
    /** Texture of the texture atlas */
    Texture2D* _texture;

    V3F_C4B_T2F         *_vertices;
    int                 _totalVertices;
    int                 _totalTriangles;
    int                 _currentTriangles;
    bool                _dirtyVertices;
    bool                _dirtyIndices;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _backToForegroundlistener;
#endif
};



#endif
