#ifndef HEADER_CURL_HASH_H
#define HEADER_CURL_HASH_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2007, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#include "curl_setup.h"

#include <stddef.h>

#include "llist.h"

/* Hash function prototype */
typedef size_t (*hash_function) (void* key,
                                 size_t key_length,
                                 size_t slots_num);

/*
   Comparator function prototype. Compares two keys.
*/
typedef size_t (*comp_function) (void* key1,
                                 size_t key1_len,
                                 void*key2,
                                 size_t key2_len);

typedef void (*curl_hash_dtor)(void *);

struct curl_hash {
  struct curl_llist **table;

  /* Hash function to be used for this hash table */
  hash_function hash_func;

  /* Comparator function to compare keys */
  comp_function comp_func;
  curl_hash_dtor   dtor;
  int slots;
  size_t size;
};

struct curl_hash_element {
  void   *ptr;
  char   *key;
  size_t key_len;
};

struct curl_hash_iterator {
  struct curl_hash *hash;
  int slot_index;
  struct curl_llist_element *current_element;
};

int Curl_hash_init(struct curl_hash *h,
                   int slots,
                   hash_function hfunc,
                   comp_function comparator,
                   curl_hash_dtor dtor);

struct curl_hash *Curl_hash_alloc(int slots,
                                  hash_function hfunc,
                                  comp_function comparator,
                                  curl_hash_dtor dtor);

void *Curl_hash_add(struct curl_hash *h, void *key, size_t key_len, void *p);
int Curl_hash_delete(struct curl_hash *h, void *key, size_t key_len);
void *Curl_hash_pick(struct curl_hash *, void * key, size_t key_len);
void Curl_hash_apply(struct curl_hash *h, void *user,
                     void (*cb)(void *user, void *ptr));
int Curl_hash_count(struct curl_hash *h);
void Curl_hash_clean(struct curl_hash *h);
void Curl_hash_clean_with_criterium(struct curl_hash *h, void *user,
                                    int (*comp)(void *, void *));
void Curl_hash_destroy(struct curl_hash *h);

size_t Curl_hash_str(void* key, size_t key_length, size_t slots_num);
size_t Curl_str_key_compare(void*k1, size_t key1_len, void*k2,
                            size_t key2_len);

void Curl_hash_start_iterate(struct curl_hash *hash,
                             struct curl_hash_iterator *iter);
struct curl_hash_element *
Curl_hash_next_element(struct curl_hash_iterator *iter);

void Curl_hash_print(struct curl_hash *h,
                     void (*func)(void *));


#endif /* HEADER_CURL_HASH_H */
