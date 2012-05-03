/* ========================================================================== */
/*   Killa tables (hash)                                                      */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*   Copyright (C) 1994-2012 Lua.org, PUC-Rio.                                */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

/*
** Implementation of tables (aka arrays, objects, or hash tables).
** Tables keep its elements in two parts: an array part and a hash part.
** Non-negative integer keys are all candidates to be kept in the array
** part. The actual size of the array is the largest `n' such that at
** least half the slots between 0 and n are in use.
** Hash uses a mix of chained scatter table with Brent's variation.
** A main invariant of these tables is that, if an element is not
** in its main position (i.e. the `original' position that its hash gives
** to it), then the colliding element is in its own main position.
** Hence even when the load factor reaches 100%, performance remains good.
*/

#include <string.h>

#define KTABLE_C_
#define KILLA_CORE

#include "killa.h"

#include "kdebug.h"
#include "kdo.h"
#include "kgc.h"
#include "kmem.h"
#include "kobject.h"
#include "kstate.h"
#include "kstring.h"
#include "ktable.h"
#include "kvm.h"


/*
** max size of array part is 2^MAXBITS
*/
#if KILLAI_BITSINT >= 32
#define MAXBITS		30
#else
#define MAXBITS		(KILLAI_BITSINT-2)
#endif

#define MAXASIZE	(1 << MAXBITS)


#define hashpow2(t,n)      (killa_gnode(t, killa_lmod((n), killa_sizenode(t))))

#define hashstr(t,str)  hashpow2(t, (str)->tsv.hash)
#define hashboolean(t,p)        hashpow2(t, p)


/*
** for some types, it is better to avoid modulus by power of 2, as
** they tend to have many 2 factors.
*/
#define hashmod(t,n)	(killa_gnode(t, ((n) % ((killa_sizenode(t)-1)|1))))


#define hashpointer(t,p)	hashmod(t, killa_IntPoint(p))


#define dummynode		(&dummynode_)

#define isdummy(n)		((n) == dummynode)

static const killa_Node dummynode_ = {
  {KILLA_NILCONSTANT},  /* value */
  {{KILLA_NILCONSTANT, NULL}}  /* key */
};


/*
** hash for killa_Numbers
*/
static killa_Node *hashnum (const killa_Table *t, killa_Number n) {
  int i;
  killai_hashnum(i, n);
  if (i < 0) {
    if (killa_cast(unsigned int, i) == 0u - i)  /* use unsigned to avoid overflows */
      i = 0;  /* handle INT_MIN */
    i = -i;  /* must be a positive value */
  }
  return hashmod(t, i);
}



/*
** returns the `main' position of an element in a table (that is, the index
** of its hash value)
*/
static killa_Node *mainposition (const killa_Table *t, const killa_TValue *key) {
  switch (killa_ttype(key)) {
    case KILLA_TNUMBER:
      return hashnum(t, killa_nvalue(key));
    case KILLA_TSTRING:
      return hashstr(t, killa_rawtsvalue(key));
    case KILLA_TBOOLEAN:
      return hashboolean(t, killa_bvalue(key));
    case KILLA_TLIGHTUSERDATA:
      return hashpointer(t, killa_pvalue(key));
    case KILLA_TLCF:
      return hashpointer(t, killa_fvalue(key));
    default:
      return hashpointer(t, killa_gcvalue(key));
  }
}


/*
** returns the index for `key' if `key' is an appropriate key to live in
** the array part of the table, -1 otherwise.
*/
static int arrayindex (const killa_TValue *key) {
  if (killa_ttisnumber(key)) {
    killa_Number n = killa_nvalue(key);
    int k;
    killa_number2int(k, n);
    if (killai_numeq(killa_cast_num(k), n))
      return k;
  }
  return -1;  /* `key' did not match some condition */
}


/*
** returns the index of a `key' for table traversals. First goes all
** elements in the array part, then elements in the hash part. The
** beginning of a traversal is signaled by -1.
*/
static int findindex (killa_State *L, killa_Table *t, killa_StkId key) {
  int i;
  if (killa_ttisnil(key)) return -1;  /* first iteration */
  i = arrayindex(key);
  if ((0 < i + 1 - KILLA_BASE) && (i + 1 - KILLA_BASE <= t->sizearray))  /* is `key' inside array part? */
    return i - KILLA_BASE;  /* yes; that's the index (corrected to C) */
  else {
    killa_Node *n = mainposition(t, key);
    for (;;) {  /* check whether `key' is somewhere in the chain */
      /* key may be dead already, but it is ok to use it in `next' */
      if (killaV_rawequalobj(killa_gkey(n), key) ||
            (killa_ttisdeadkey(killa_gkey(n)) && killa_iscollectable(key) &&
             killa_deadvalue(killa_gkey(n)) == killa_gcvalue(key))) {
        i = killa_cast_int(n - killa_gnode(t, 0));  /* key index in hash table */
        /* hash elements are numbered after array ones */
        return i + t->sizearray;
      }
      else n = killa_gnext(n);
      if (n == NULL)
        killaG_runerror(L, "invalid key to " KILLA_QL("next"));  /* key not found */
    }
  }
}


int killaH_next (killa_State *L, killa_Table *t, killa_StkId key) {
  int i = findindex(L, t, key);  /* find original element */
  for (i++; i < t->sizearray; i++) {  /* try first array part */
    if (!killa_ttisnil(&t->array[i])) {  /* a non-nil value? */
      killa_setnvalue(key, killa_cast_num(i + KILLA_BASE));
      killa_setobj2s(L, key+1, &t->array[i]);
      return 1;
    }
  }
  for (i -= t->sizearray; i < killa_sizenode(t); i++) {  /* then hash part */
    if (!killa_ttisnil(killa_gval(killa_gnode(t, i)))) {  /* a non-nil value? */
      killa_setobj2s(L, key, killa_gkey(killa_gnode(t, i)));
      killa_setobj2s(L, key+1, killa_gval(killa_gnode(t, i)));
      return 1;
    }
  }
  return 0;  /* no more elements */
}


/*
** {=============================================================
** Rehash
** ==============================================================
*/


static int computesizes (int nums[], int *narray) {
  int i;
  int twotoi;  /* 2^i */
  int a = 0;  /* number of elements smaller than 2^i */
  int na = 0;  /* number of elements to go to array part */
  int n = 0;  /* optimal size for array part */
  for (i = 0, twotoi = 1; twotoi/2 < *narray; i++, twotoi *= 2) {
    if (nums[i] > 0) {
      a += nums[i];
      if (a > twotoi/2) {  /* more than half elements present? */
        n = twotoi;  /* optimal size (till now) */
        na = a;  /* all elements smaller than n will go to array part */
      }
    }
    if (a == *narray) break;  /* all elements already counted */
  }
  *narray = n;
  killa_assert(*narray/2 <= na && na <= *narray);
  return na;
}


static int countint (const killa_TValue *key, int *nums) {
  int k = arrayindex(key);
  if ((0 < k + 1 - KILLA_BASE) && (k <= MAXASIZE + 1 - KILLA_BASE)) {  /* is `key' an appropriate array index? */
    nums[killaO_ceillog2(k + 1 - KILLA_BASE)]++;  /* count as such */
    return 1;
  }
  else
    return 0;
}


static int numusearray (const killa_Table *t, int *nums) {
  int lg;
  int ttlg;  /* 2^lg */
  int ause = 0;  /* summation of `nums' */
  int i = 1;  /* count to traverse all array keys */
  for (lg=0, ttlg=1; lg<=MAXBITS; lg++, ttlg*=2) {  /* for each slice */
    int lc = 0;  /* counter */
    int lim = ttlg;
    if (lim > t->sizearray) {
      lim = t->sizearray;  /* adjust upper limit */
      if (i > lim)
        break;  /* no more elements to count */
    }
    /* count elements in range (2^(lg-1), 2^lg] */
    for (; i <= lim; i++) {
      if (!killa_ttisnil(&t->array[i-1]))
        lc++;
    }
    nums[lg] += lc;
    ause += lc;
  }
  return ause;
}


static int numusehash (const killa_Table *t, int *nums, int *pnasize) {
  int totaluse = 0;  /* total number of elements */
  int ause = 0;  /* summation of `nums' */
  int i = killa_sizenode(t);
  while (i--) {
    killa_Node *n = &t->node[i];
    if (!killa_ttisnil(killa_gval(n))) {
      ause += countint(killa_gkey(n), nums);
      totaluse++;
    }
  }
  *pnasize += ause;
  return totaluse;
}


static void setarrayvector (killa_State *L, killa_Table *t, int size) {
  int i;
  killaM_reallocvector(L, t->array, t->sizearray, size, killa_TValue);
  for (i=t->sizearray; i<size; i++)
     killa_setnilvalue(&t->array[i]);
  t->sizearray = size;
}


static void setnodevector (killa_State *L, killa_Table *t, int size) {
  int lsize;
  if (size == 0) {  /* no elements to hash part? */
    t->node = killa_cast(killa_Node *, dummynode);  /* use common `dummynode' */
    lsize = 0;
  }
  else {
    int i;
    lsize = killaO_ceillog2(size);
    if (lsize > MAXBITS)
      killaG_runerror(L, "table overflow");
    size = killa_twoto(lsize);
    t->node = killaM_newvector(L, size, killa_Node);
    for (i=0; i<size; i++) {
      killa_Node *n = killa_gnode(t, i);
      killa_gnext(n) = NULL;
      killa_setnilvalue(killa_gkey(n));
      killa_setnilvalue(killa_gval(n));
    }
  }
  t->lsizenode = killa_cast_byte(lsize);
  t->lastfree = killa_gnode(t, size);  /* all positions are free */
}


void killaH_resize (killa_State *L, killa_Table *t, int nasize, int nhsize) {
  int i;
  int oldasize = t->sizearray;
  int oldhsize = t->lsizenode;
  killa_Node *nold = t->node;  /* save old hash ... */
  if (nasize > oldasize)  /* array part must grow? */
    setarrayvector(L, t, nasize);
  /* create new hash part with appropriate size */
  setnodevector(L, t, nhsize);
  if (nasize < oldasize) {  /* array part must shrink? */
    t->sizearray = nasize;
    /* re-insert elements from vanishing slice */
    for (i=nasize; i<oldasize; i++) {
      if (!killa_ttisnil(&t->array[i]))
        killaH_setint(L, t, i + 1, &t->array[i]);
    }
    /* shrink array */
    killaM_reallocvector(L, t->array, oldasize, nasize, killa_TValue);
  }
  /* re-insert elements from hash part */
  for (i = killa_twoto(oldhsize) - 1; i >= 0; i--) {
    killa_Node *old = nold+i;
    if (!killa_ttisnil(killa_gval(old))) {
      /* doesn't need barrier/invalidate cache, as entry was
         already present in the table */
      killa_setobjt2t(L, killaH_set(L, t, killa_gkey(old)), killa_gval(old));
    }
  }
  if (!isdummy(nold))
    killaM_freearray(L, nold, killa_cast(size_t, killa_twoto(oldhsize))); /* free old array */
}


void killaH_resizearray (killa_State *L, killa_Table *t, int nasize) {
  int nsize = isdummy(t->node) ? 0 : killa_sizenode(t);
  killaH_resize(L, t, nasize, nsize);
}


static void rehash (killa_State *L, killa_Table *t, const killa_TValue *ek) {
  int nasize, na;
  int nums[MAXBITS+1];  /* nums[i] = number of keys with 2^(i-1) < k <= 2^i */
  int i;
  int totaluse;
  for (i=0; i<=MAXBITS; i++) nums[i] = 0;  /* reset counts */
  nasize = numusearray(t, nums);  /* count keys in array part */
  totaluse = nasize;  /* all those keys are integer keys */
  totaluse += numusehash(t, nums, &nasize);  /* count keys in hash part */
  /* count extra key */
  nasize += countint(ek, nums);
  totaluse++;
  /* compute new size for array part */
  na = computesizes(nums, &nasize);
  /* resize the table to new computed sizes */
  killaH_resize(L, t, nasize, totaluse - na);
}



/*
** }=============================================================
*/


killa_Table *killaH_new (killa_State *L) {
  killa_Table *t = &killaC_newobj(L, KILLA_TTABLE, sizeof(killa_Table), NULL, 0)->h;
  t->metatable = NULL;
  t->flags = killa_cast_byte(~0);
  t->array = NULL;
  t->sizearray = 0;
  setnodevector(L, t, 0);
  return t;
}


void killaH_free (killa_State *L, killa_Table *t) {
  if (!isdummy(t->node))
    killaM_freearray(L, t->node, killa_cast(size_t, killa_sizenode(t)));
  killaM_freearray(L, t->array, t->sizearray);
  killaM_free(L, t);
}


static killa_Node *getfreepos (killa_Table *t) {
  while (t->lastfree > t->node) {
    t->lastfree--;
    if (killa_ttisnil(killa_gkey(t->lastfree)))
      return t->lastfree;
  }
  return NULL;  /* could not find a free place */
}



/*
** inserts a new key into a hash table; first, check whether key's main
** position is free. If not, check whether colliding node is in its main
** position or not: if it is not, move colliding node to an empty place and
** put new key in its main position; otherwise (colliding node is in its main
** position), new key goes to an empty position.
*/
killa_TValue *killaH_newkey (killa_State *L, killa_Table *t, const killa_TValue *key) {
  killa_Node *mp;
  if (killa_ttisnil(key)) killaG_runerror(L, "table index is nil");
  else if (killa_ttisnumber(key) && killai_numisnan(L, killa_nvalue(key)))
    killaG_runerror(L, "table index is NaN");
  mp = mainposition(t, key);
  if (!killa_ttisnil(killa_gval(mp)) || isdummy(mp)) {  /* main position is taken? */
    killa_Node *othern;
    killa_Node *n = getfreepos(t);  /* get a free place */
    if (n == NULL) {  /* cannot find a free place? */
      rehash(L, t, key);  /* grow table */
      /* whatever called 'newkey' take care of TM cache and GC barrier */
      return killaH_set(L, t, key);  /* insert key into grown table */
    }
    killa_assert(!isdummy(n));
    othern = mainposition(t, killa_gkey(mp));
    if (othern != mp) {  /* is colliding node out of its main position? */
      /* yes; move colliding node into free position */
      while (killa_gnext(othern) != mp) othern = killa_gnext(othern);  /* find previous */
      killa_gnext(othern) = n;  /* redo the chain with `n' in place of `mp' */
      *n = *mp;  /* copy colliding node into free pos. (mp->next also goes) */
      killa_gnext(mp) = NULL;  /* now `mp' is free */
      killa_setnilvalue(killa_gval(mp));
    }
    else {  /* colliding node is in its own main position */
      /* new node will go into free position */
      killa_gnext(n) = killa_gnext(mp);  /* chain new position */
      killa_gnext(mp) = n;
      mp = n;
    }
  }
  killa_setobj2t(L, killa_gkey(mp), key);
  killaC_barrierback(L, killa_obj2gco(t), key);
  killa_assert(killa_ttisnil(killa_gval(mp)));
  return killa_gval(mp);
}


/*
** search function for integers
*/
const killa_TValue *killaH_getint (killa_Table *t, int key) {
  /* (1 <= key && key <= t->sizearray) */
  if (killa_cast(unsigned int, key - KILLA_BASE) < killa_cast(unsigned int, t->sizearray))
    return &t->array[key - KILLA_BASE];
  else {
    killa_Number nk = killa_cast_num(key);
    killa_Node *n = hashnum(t, nk);
    do {  /* check whether `key' is somewhere in the chain */
      if (killa_ttisnumber(killa_gkey(n)) && killai_numeq(killa_nvalue(killa_gkey(n)), nk))
        return killa_gval(n);  /* that's it */
      else n = killa_gnext(n);
    } while (n);
    return killaO_nilobject;
  }
}


/*
** search function for strings
*/
const killa_TValue *killaH_getstr (killa_Table *t, killa_TString *key) {
  killa_Node *n = hashstr(t, key);
  do {  /* check whether `key' is somewhere in the chain */
    if (killa_ttisstring(killa_gkey(n)) && killa_eqstr(killa_rawtsvalue(killa_gkey(n)), key))
      return killa_gval(n);  /* that's it */
    else n = killa_gnext(n);
  } while (n);
  return killaO_nilobject;
}


/*
** main search function
*/
const killa_TValue *killaH_get (killa_Table *t, const killa_TValue *key) {
  switch (killa_ttypenv(key)) {
    case KILLA_TNULL: return killaO_nilobject;
    case KILLA_TSTRING: return killaH_getstr(t, killa_rawtsvalue(key));
    case KILLA_TNUMBER: {
      int k;
      killa_Number n = killa_nvalue(key);
      killa_number2int(k, n);
      if (killai_numeq(killa_cast_num(k), killa_nvalue(key))) /* index is int? */
        return killaH_getint(t, k);  /* use specialized version */
      /* else go through */
    }
    default: {
      killa_Node *n = mainposition(t, key);
      do {  /* check whether `key' is somewhere in the chain */
        if (killaV_rawequalobj(killa_gkey(n), key))
          return killa_gval(n);  /* that's it */
        else n = killa_gnext(n);
      } while (n);
      return killaO_nilobject;
    }
  }
}


/*
** beware: when using this function you probably need to check a GC
** barrier and invalidate the TM cache.
*/
killa_TValue *killaH_set (killa_State *L, killa_Table *t, const killa_TValue *key) {
  const killa_TValue *p = killaH_get(t, key);
  if (p != killaO_nilobject)
    return killa_cast(killa_TValue *, p);
  else return killaH_newkey(L, t, key);
}


void killaH_setint (killa_State *L, killa_Table *t, int key, killa_TValue *value) {
  const killa_TValue *p = killaH_getint(t, key);
  killa_TValue *cell;
  if (p != killaO_nilobject)
    cell = killa_cast(killa_TValue *, p);
  else {
    killa_TValue k;
    killa_setnvalue(&k, killa_cast_num(key));
    cell = killaH_newkey(L, t, &k);
  }
  killa_setobj2t(L, cell, value);
}


static int unbound_search (killa_Table *t, unsigned int j) {
  unsigned int i = j;  /* i is zero or a present index */
  j++;
  /* find `i' and `j' such that i is present and j is not */
  while (!killa_ttisnil(killaH_getint(t, j))) {
    i = j;
    j *= 2;
    if (j > killa_cast(unsigned int, KILLA_MAX_INT)) {  /* overflow? */
      /* table was built with bad purposes: resort to linear search */
      i = 1;
      while (!killa_ttisnil(killaH_getint(t, i))) i++;
      return i - 1;
    }
  }
  /* now do a binary search between them */
  while (j - i > 1) {
    unsigned int m = (i+j)/2;
    if (killa_ttisnil(killaH_getint(t, m))) j = m;
    else i = m;
  }
  return i;
}


/*
** Try to find a boundary in table `t'. A `boundary' is an integer index
** such that t[i] is non-nil and t[i+1] is nil (and 0 if t[1] is nil).
*/
int killaH_getn (killa_Table *t) {
  unsigned int j = t->sizearray;
  if (j > 0 && killa_ttisnil(&t->array[j - 1])) {
    /* there is a boundary in the array part: (binary) search for it */
    unsigned int i = 0;
    while (j - i > 1) {
      unsigned int m = (i+j)/2;
      if (killa_ttisnil(&t->array[m - 1])) j = m;
      else i = m;
    }
    return i;
  }
  /* else must find a boundary in hash part */
  else if (isdummy(t->node))  /* hash part is empty? */
    return j;  /* that is easy... */
  else return unbound_search(t, j);
}



#if defined(KILLA_DEBUG)

killa_Node *killaH_mainposition (const killa_Table *t, const killa_TValue *key) {
  return mainposition(t, key);
}

int killaH_isdummy (killa_Node *n) { return isdummy(n); }

#endif
