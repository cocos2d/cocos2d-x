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
 *  \file SDL_blendmode.h
 *  
 *  Header file declaring the SDL_BlendMode enumeration
 */

#ifndef _SDL_blendmode_h
#define _SDL_blendmode_h

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
extern "C" {
/* *INDENT-ON* */
#endif

/**
 *  \brief The blend mode used in SDL_RenderCopy() and drawing operations.
 */
typedef enum
{
    SDL_BLENDMODE_NONE = 0x00000000,     /**< No blending */
    SDL_BLENDMODE_BLEND = 0x00000001,    /**< dst = (src * A) + (dst * (1-A)) */
    SDL_BLENDMODE_ADD = 0x00000002,      /**< dst = (src * A) + dst */
    SDL_BLENDMODE_MOD = 0x00000004       /**< dst = src * dst */
} SDL_BlendMode;

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif
#include "close_code.h"

#endif /* _SDL_video_h */

/* vi: set ts=4 sw=4 expandtab: */
