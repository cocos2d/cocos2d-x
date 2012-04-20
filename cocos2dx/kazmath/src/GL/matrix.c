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

#include <stdlib.h>
#include <assert.h>

#include "kazmath/GL/matrix.h"
#include "kazmath/GL/mat4stack.h"

km_mat4_stack modelview_matrix_stack;
km_mat4_stack projection_matrix_stack;
km_mat4_stack texture_matrix_stack;

km_mat4_stack* current_stack = NULL;

static unsigned char initialized = 0;

void lazyInitialize()
{

    if (!initialized) {
        kmMat4 identity; //Temporary identity matrix

        //Initialize all 3 stacks
        //modelview_matrix_stack = (km_mat4_stack*) malloc(sizeof(km_mat4_stack));
        km_mat4_stack_initialize(&modelview_matrix_stack);

        //projection_matrix_stack = (km_mat4_stack*) malloc(sizeof(km_mat4_stack));
        km_mat4_stack_initialize(&projection_matrix_stack);

        //texture_matrix_stack = (km_mat4_stack*) malloc(sizeof(km_mat4_stack));
        km_mat4_stack_initialize(&texture_matrix_stack);

        current_stack = &modelview_matrix_stack;
        initialized = 1;

        kmMat4Identity(&identity);

        //Make sure that each stack has the identity matrix
        km_mat4_stack_push(&modelview_matrix_stack, &identity);
        km_mat4_stack_push(&projection_matrix_stack, &identity);
        km_mat4_stack_push(&texture_matrix_stack, &identity);
    }
}

void kmGLMatrixMode(kmGLEnum mode)
{
    lazyInitialize();

    switch(mode)
    {
        case KM_GL_MODELVIEW:
            current_stack = &modelview_matrix_stack;
        break;
        case KM_GL_PROJECTION:
            current_stack = &projection_matrix_stack;
        break;
        case KM_GL_TEXTURE:
            current_stack = &texture_matrix_stack;
        break;
        default:
            assert(0 && "Invalid matrix mode specified"); //TODO: Proper error handling
        break;
    }
}

void kmGLPushMatrix(void)
{
    kmMat4 top;

    lazyInitialize(); //Initialize the stacks if they haven't been already

    //Duplicate the top of the stack (i.e the current matrix)
    kmMat4Assign(&top, current_stack->top);
    km_mat4_stack_push(current_stack, &top);
}

void kmGLPopMatrix(void)
{
    assert(initialized && "Cannot Pop empty matrix stack");
    //No need to lazy initialize, you shouldnt be popping first anyway!
    km_mat4_stack_pop(current_stack, NULL);
}

void kmGLLoadIdentity()
{
    lazyInitialize();

    kmMat4Identity(current_stack->top); //Replace the top matrix with the identity matrix
}

void kmGLFreeAll()
{
    //Clear the matrix stacks
    km_mat4_stack_release(&modelview_matrix_stack);
    km_mat4_stack_release(&projection_matrix_stack);
    km_mat4_stack_release(&texture_matrix_stack);

    //Delete the matrices
    initialized = 0; //Set to uninitialized

    current_stack = NULL; //Set the current stack to point nowhere
}

void kmGLMultMatrix(const kmMat4* pIn)
{
    lazyInitialize();
    kmMat4Multiply(current_stack->top, current_stack->top, pIn);
}

void kmGLLoadMatrix(const kmMat4* pIn)
{
    lazyInitialize();
    kmMat4Assign(current_stack->top, pIn);
}

void kmGLGetMatrix(kmGLEnum mode, kmMat4* pOut)
{
    lazyInitialize();

    switch(mode)
    {
        case KM_GL_MODELVIEW:
            kmMat4Assign(pOut, modelview_matrix_stack.top);
        break;
        case KM_GL_PROJECTION:
            kmMat4Assign(pOut, projection_matrix_stack.top);
        break;
        case KM_GL_TEXTURE:
            kmMat4Assign(pOut, texture_matrix_stack.top);
        break;
        default:
            assert(1 && "Invalid matrix mode specified"); //TODO: Proper error handling
        break;
    }
}

void kmGLTranslatef(float x, float y, float z)
{
    kmMat4 translation;

    //Create a rotation matrix using the axis and the angle
    kmMat4Translation(&translation,x,y,z);

    //Multiply the rotation matrix by the current matrix
    kmMat4Multiply(current_stack->top, current_stack->top, &translation);
}

void kmGLRotatef(float angle, float x, float y, float z)
{
    kmVec3 axis;
    kmMat4 rotation;

    //Create an axis vector
    kmVec3Fill(&axis, x, y, z);

    //Create a rotation matrix using the axis and the angle
    kmMat4RotationAxisAngle(&rotation, &axis, kmDegreesToRadians(angle));

    //Multiply the rotation matrix by the current matrix
    kmMat4Multiply(current_stack->top, current_stack->top, &rotation);
}

void kmGLScalef(float x, float y, float z)
{
    kmMat4 scaling;
    kmMat4Scaling(&scaling, x, y, z);
    kmMat4Multiply(current_stack->top, current_stack->top, &scaling);
}
