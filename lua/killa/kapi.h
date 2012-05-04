/* ========================================================================== */
/*   Auxiliary functions from Killa API                                       */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KAPI_H_
#define KAPI_H_


#include "klimits.h"
#include "kstate.h"

#define killaA_incr_top(L)   {L->top++; killa_api_check(L, L->top <= L->ci->top, \
				"stack overflow");}

#define killaA_adjustresults(L,nres) \
    { if ((nres) == KILLA_MULTRET && L->ci->top < L->top) L->ci->top = L->top; }

#define killaA_checknelems(L,n)	killa_api_check(L, (n) < (L->top - L->ci->func), \
				  "not enough elements in the stack")


#endif
