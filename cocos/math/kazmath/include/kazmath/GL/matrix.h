/*
Copyright (c) 2008, Luke Benstead.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef KM_GL_MATRIX_H_INCLUDED
#define KM_GL_MATRIX_H_INCLUDED

#include "platform/CCPlatformMacros.h"

#define KM_GL_MODELVIEW 0x1700
#define KM_GL_PROJECTION 0x1701
#define KM_GL_TEXTURE 0x1702

typedef unsigned int kmGLEnum;

#include "../mat4.h"
#include "../vec3.h"

#ifdef __cplusplus
extern "C" {
#endif

void CC_DLL kmGLFreeAll(void);
void CC_DLL kmGLPushMatrix(void);
void CC_DLL kmGLPopMatrix(void);
void CC_DLL kmGLMatrixMode(kmGLEnum mode);
void CC_DLL kmGLLoadIdentity(void);
void CC_DLL kmGLLoadMatrix(const kmMat4* pIn);
void CC_DLL kmGLMultMatrix(const kmMat4* pIn);
void CC_DLL kmGLTranslatef(float x, float y, float z);
void CC_DLL kmGLRotatef(float angle, float x, float y, float z);
void CC_DLL kmGLScalef(float x, float y, float z);
void CC_DLL kmGLGetMatrix(kmGLEnum mode, kmMat4* pOut);

#ifdef __cplusplus
}
#endif

#endif // MATRIX_H_INCLUDED
