/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2011 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  \file SDL_loadso.h
 *
 *  System dependent library loading routines
 *
 *  Some things to keep in mind:                                        
 *  \li These functions only work on C function names.  Other languages may
 *      have name mangling and intrinsic language support that varies from
 *      compiler to compiler.
 *  \li Make sure you declare your function pointers with the same calling
 *      convention as the actual library function.  Your code will crash
 *      mysteriously if you do not do this.
 *  \li Avoid namespace collisions.  If you load a symbol from the library,
 *      it is not defined whether or not it goes into the global symbol
 *      namespace for the application.  If it does and it conflicts with
 *      symbols in your code or other shared libraries, you will not get
 *      the results you expect. :)
 */

#ifndef _SDL_loadso_h
#define _SDL_loadso_h

#include "SDL_stdinc.h"
#include "SDL_error.h"

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
extern "C" {
/* *INDENT-ON* */
#endif

/**
 *  This function dynamically loads a shared object and returns a pointer
 *  to the object handle (or NULL if there was an error).
 *  The 'sofile' parameter is a system dependent name of the object file.
 */
extern DECLSPEC void *SDLCALL SDL_LoadObject(const char *sofile);

/**
 *  Given an object handle, this function looks up the address of the
 *  named function in the shared object and returns it.  This address
 *  is no longer valid after calling SDL_UnloadObject().
 */
extern DECLSPEC void *SDLCALL SDL_LoadFunction(void *handle,
                                               const char *name);

/**
 *  Unload a shared object from memory.
 */
extern DECLSPEC void SDLCALL SDL_UnloadObject(void *handle);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif
#include "close_code.h"

#endif /* _SDL_loadso_h */

/* vi: set ts=4 sw=4 expandtab: */
