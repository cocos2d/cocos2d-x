/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
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

/* Base64 encoding/decoding */

#include "curl_setup.h"

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

#include "urldata.h" /* for the SessionHandle definition */
#include "warnless.h"
#include "curl_base64.h"
#include "curl_memory.h"
#include "non-ascii.h"

/* include memdebug.h last */
#include "memdebug.h"

/* ---- Base64 Encoding/Decoding Table --- */
static const char table64[]=
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static size_t decodeQuantum(unsigned char *dest, const char *src)
{
  size_t padding = 0;
  const char *s, *p;
  unsigned long i, v, x = 0;

  for(i = 0, s = src; i < 4; i++, s++) {
    v = 0;

    if(*s == '=') {
      x = (x << 6);
      padding++;
    }
    else {
      p = table64;

      while(*p && (*p != *s)) {
        v++;
        p++;
      }

      if(*p == *s)
        x = (x << 6) + v;
      else
        return 0;
    }
  }

  if(padding < 1)
    dest[2] = curlx_ultouc(x & 0xFFUL);

  x >>= 8;
  if(padding < 2)
    dest[1] = curlx_ultouc(x & 0xFFUL);

  x >>= 8;
  dest[0] = curlx_ultouc(x & 0xFFUL);

  return 3 - padding;
}

/*
 * Curl_base64_decode()
 *
 * Given a base64 NUL-terminated string at src, decode it and return a
 * pointer in *outptr to a newly allocated memory area holding decoded
 * data. Size of decoded data is returned in variable pointed by outlen.
 *
 * Returns CURLE_OK on success, otherwise specific error code. Function
 * output shall not be considered valid unless CURLE_OK is returned.
 *
 * When decoded data length is 0, returns NULL in *outptr.
 *
 * @unittest: 1302
 */
CURLcode Curl_base64_decode(const char *src,
                            unsigned char **outptr, size_t *outlen)
{
  size_t srclen = 0;
  size_t length = 0;
  size_t padding = 0;
  size_t i;
  size_t result;
  size_t numQuantums;
  size_t rawlen = 0;
  unsigned char *pos;
  unsigned char *newstr;

  *outptr = NULL;
  *outlen = 0;
  srclen = strlen(src);

  /* Check the length of the input string is valid */
  if(!srclen || srclen % 4)
    return CURLE_BAD_CONTENT_ENCODING;

  /* Find the position of any = padding characters */
  while((src[length] != '=') && src[length])
    length++;

  /* A maximum of two = padding characters is allowed */
  if(src[length] == '=') {
    padding++;
    if(src[length + 1] == '=')
      padding++;
  }

  /* Check the = padding characters weren't part way through the input */
  if(length + padding != srclen)
    return CURLE_BAD_CONTENT_ENCODING;

  /* Calculate the number of quantums */
  numQuantums = srclen / 4;

  /* Calculate the size of the decoded string */
  rawlen = (numQuantums * 3) - padding;

  /* Allocate our buffer including room for a zero terminator */
  newstr = malloc(rawlen + 1);
  if(!newstr)
    return CURLE_OUT_OF_MEMORY;

  pos = newstr;

  /* Decode the quantums */
  for(i = 0; i < numQuantums; i++) {
    result = decodeQuantum(pos, src);
    if(!result) {
      Curl_safefree(newstr);

      return CURLE_BAD_CONTENT_ENCODING;
    }

    pos += result;
    src += 4;
  }

  /* Zero terminate */
  *pos = '\0';

  /* Return the decoded data */
  *outptr = newstr;
  *outlen = rawlen;

  return CURLE_OK;
}

/*
 * Curl_base64_encode()
 *
 * Given a pointer to an input buffer and an input size, encode it and
 * return a pointer in *outptr to a newly allocated memory area holding
 * encoded data. Size of encoded data is returned in variable pointed by
 * outlen.
 *
 * Input length of 0 indicates input buffer holds a NUL-terminated string.
 *
 * Returns CURLE_OK on success, otherwise specific error code. Function
 * output shall not be considered valid unless CURLE_OK is returned.
 *
 * When encoded data length is 0, returns NULL in *outptr.
 *
 * @unittest: 1302
 */
CURLcode Curl_base64_encode(struct SessionHandle *data,
                            const char *inputbuff, size_t insize,
                            char **outptr, size_t *outlen)
{
  CURLcode error;
  unsigned char ibuf[3];
  unsigned char obuf[4];
  int i;
  int inputparts;
  char *output;
  char *base64data;
  char *convbuf = NULL;

  const char *indata = inputbuff;

  *outptr = NULL;
  *outlen = 0;

  if(0 == insize)
    insize = strlen(indata);

  base64data = output = malloc(insize*4/3+4);
  if(NULL == output)
    return CURLE_OUT_OF_MEMORY;

  /*
   * The base64 data needs to be created using the network encoding
   * not the host encoding.  And we can't change the actual input
   * so we copy it to a buffer, translate it, and use that instead.
   */
  error = Curl_convert_clone(data, indata, insize, &convbuf);
  if(error) {
    free(output);
    return error;
  }

  if(convbuf)
    indata = (char *)convbuf;

  while(insize > 0) {
    for(i = inputparts = 0; i < 3; i++) {
      if(insize > 0) {
        inputparts++;
        ibuf[i] = (unsigned char) *indata;
        indata++;
        insize--;
      }
      else
        ibuf[i] = 0;
    }

    obuf[0] = (unsigned char)  ((ibuf[0] & 0xFC) >> 2);
    obuf[1] = (unsigned char) (((ibuf[0] & 0x03) << 4) | \
                               ((ibuf[1] & 0xF0) >> 4));
    obuf[2] = (unsigned char) (((ibuf[1] & 0x0F) << 2) | \
                               ((ibuf[2] & 0xC0) >> 6));
    obuf[3] = (unsigned char)   (ibuf[2] & 0x3F);

    switch(inputparts) {
    case 1: /* only one byte read */
      snprintf(output, 5, "%c%c==",
               table64[obuf[0]],
               table64[obuf[1]]);
      break;
    case 2: /* two bytes read */
      snprintf(output, 5, "%c%c%c=",
               table64[obuf[0]],
               table64[obuf[1]],
               table64[obuf[2]]);
      break;
    default:
      snprintf(output, 5, "%c%c%c%c",
               table64[obuf[0]],
               table64[obuf[1]],
               table64[obuf[2]],
               table64[obuf[3]] );
      break;
    }
    output += 4;
  }
  *output = '\0';
  *outptr = base64data; /* return pointer to new data, allocated memory */

  if(convbuf)
    free(convbuf);

  *outlen = strlen(base64data); /* return the length of the new data */

  return CURLE_OK;
}
/* ---- End of Base64 Encoding ---- */
