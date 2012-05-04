/* ========================================================================== */
/*   String table (keeps all strings handled by Killa)                        */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KSTRING_H_
#define KSTRING_H_

#include "kgc.h"
#include "kobject.h"
#include "kstate.h"


#define killa_sizestring(s) (sizeof(union killa_TString)+((s)->len+1)*sizeof(char))

#define killa_sizeudata(u)  (sizeof(union killa_Udata)+(u)->len)

#define killaS_newliteral(L, s) (killaS_newlstr(L, "" s, \
                                    (sizeof(s)/sizeof(char))-1))

#define killaS_fix(s)   killa_l_setbit((s)->tsv.marked, KILLA_FIXEDBIT)


/*
** as all string are internalized, string equality becomes
** pointer equality
*/
#define killa_eqstr(a,b)    ((a) == (b))

KILLAI_FUNC void killaS_resize (killa_State *L, int newsize);
KILLAI_FUNC killa_Udata *killaS_newudata (killa_State *L, size_t s, killa_Table *e);
KILLAI_FUNC killa_TString *killaS_newlstr (killa_State *L, const char *str, size_t l);
KILLAI_FUNC killa_TString *killaS_new (killa_State *L, const char *str);


#endif
