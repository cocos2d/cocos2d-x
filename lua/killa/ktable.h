/* ========================================================================== */
/*   Killa tables (hash)                                                      */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KTABLE_H_
#define KTABLE_H_

#include "kobject.h"


#define killa_gnode(t,i)    (&(t)->node[i])
#define killa_gkey(n)       (&(n)->i_key.tvk)
#define killa_gval(n)       (&(n)->i_val)
#define killa_gnext(n)      ((n)->i_key.nk.next)

#define killa_invalidateTMcache(t)  ((t)->flags = 0)


KILLAI_FUNC const killa_TValue *killaH_getint (killa_Table *t, int key);
KILLAI_FUNC void  killaH_setint (killa_State *L, killa_Table *t, int key, killa_TValue *value);
KILLAI_FUNC const killa_TValue *killaH_getstr (killa_Table *t, killa_TString *key);
KILLAI_FUNC const killa_TValue *killaH_get (killa_Table *t, const killa_TValue *key);
KILLAI_FUNC killa_TValue *killaH_newkey (killa_State *L, killa_Table *t, const killa_TValue *key);
KILLAI_FUNC killa_TValue *killaH_set (killa_State *L, killa_Table *t, const killa_TValue *key);
KILLAI_FUNC killa_Table *killaH_new (killa_State *L);
KILLAI_FUNC void killaH_resize (killa_State *L, killa_Table *t, int nasize, int nhsize);
KILLAI_FUNC void killaH_resizearray (killa_State *L, killa_Table *t, int nasize);
KILLAI_FUNC void killaH_free (killa_State *L, killa_Table *t);
KILLAI_FUNC int  killaH_next (killa_State *L, killa_Table *t, killa_StkId key);
KILLAI_FUNC int  killaH_getn (killa_Table *t);


#if defined(KILLA_DEBUG)
KILLAI_FUNC killa_Node *killaH_mainposition (const killa_Table *t, const killa_TValue *key);
KILLAI_FUNC int killaH_isdummy (killa_Node *n);
#endif


#endif
